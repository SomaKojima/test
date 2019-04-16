#include "../../pch.h"
#include "CCell.h"
#include "../Object/GameObject.h"
#include "../../Game.h"
#include "Collision.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CLiner8TreeManager::CLiner8TreeManager()
{

}

CLiner8TreeManager::~CLiner8TreeManager()
{
	for (int i = 0; i < m_dwCellNum; i++)
	{
		delete ppCellAry[i];
	}
	delete[] ppCellAry;
}

bool CLiner8TreeManager::Init(unsigned int Level, float left, float top, float right, float bottom, float front, float back)
{
	// 設定最高レベル以上の空間は作れない
	if (Level>CLINER8TREEMANAGER_MAXLEVEL)
		return false;

	// 各レベルでの空間数を算出
	int i;
	m_iPow[0] = 1;
	for (i = 1; i <= CLINER8TREEMANAGER_MAXLEVEL + 1; i++)
	{
		m_iPow[i] = m_iPow[i - 1] * 8;
	}

	// Levelレベル（0基点）の配列作成
	m_dwCellNum = (m_iPow[Level + 1] - 1) / 7;
	ppCellAry = new CCell*[m_dwCellNum];
	ZeroMemory(ppCellAry, sizeof(CCell*) * m_dwCellNum);

	// 有効領域を登録
	m_fLeft = left;
	m_fBottom = bottom;
	m_fBack = back;
	m_fW = right - left;
	m_fH = top - bottom;
	m_fD = front - back;
	m_fUnit_W = m_fW / (1 << Level);
	m_fUnit_H = m_fH / (1 << Level);
	m_fUnit_D = m_fD / (1 << Level);

	m_level = Level;


	// 当たり判定マトリクスの初期化
	InitCollisionMatrix();

	return true;
}


DWORD CLiner8TreeManager::BitSeparateFor3D(BYTE n)
{
	DWORD s = n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

DWORD CLiner8TreeManager::Get3DMortonOrder(BYTE x, BYTE y, BYTE z)
{
	return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
}

DWORD CLiner8TreeManager::GetMortonOrderX(float x)
{
	return (DWORD)(x - m_fLeft) / ((int)((m_fLeft + m_fW) - m_fLeft) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetMortonOrderY(float y)
{
	return (DWORD)(y - m_fBottom) / ((int)((m_fBottom + m_fH) - m_fBottom) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetMortonOrderZ(float z)
{
	return (DWORD)(z - m_fBack) / ((int)((m_fBack + m_fD) - m_fBack) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetPosToMortonOrder(DirectX::SimpleMath::Vector3 pos)
{
	DWORD morton = Get3DMortonOrder((BYTE)GetMortonOrderX(pos.x), (BYTE)GetMortonOrderY(pos.y), (BYTE)GetMortonOrderZ(pos.z));
	return morton;
}

DWORD CLiner8TreeManager::Get2PointMortonOrder(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 pos2)
{
	DWORD morton = GetPosToMortonOrder(pos);
	DWORD morton2 = GetPosToMortonOrder(pos2);

	if(morton >= m_dwCellNum ||
		morton2 >= m_dwCellNum)
	{
		return 0;
	}

	DWORD buf = (DWORD)morton ^ (DWORD)morton2;

	for(int i = 0; i <= m_level; i++)
	{
		if (!buf)
		{
			return (morton >> (3 * i)) + ((m_iPow[m_level - (i + 1)] - 1) / 7);
		}
		buf = buf >> 3;
	}

	return 0;
}

bool CLiner8TreeManager::CreateNewCell(DWORD Elem)
{
	// 引数の要素番号
	while (!ppCellAry[Elem])
	{
		// 指定の要素番号に空間を新規作成
		ppCellAry[Elem] = new CCell();

		ppCellAry[Elem];

		// 親空間にジャンプ
		Elem = (Elem - 1) >> 3;
		if (Elem >= m_dwCellNum) break;
	}
	return true;
}

bool CLiner8TreeManager::Register(GameObject& obj, float radius)
{
	if (!&obj)
	{
		return false;
	}
	Vector3 b = Vector3::Transform(Vector3::Zero, obj.GetTransform().WorldMatrix());
	Vector3 c = b;
	b += Vector3(radius, radius * 2, radius);
	c += Vector3(-radius, 0.0f, -radius);
	DWORD elem = Get2PointMortonOrder(b, c);

	obj.GetOFT().Remove();
	if (!ppCellAry[elem])
	{
		CreateNewCell(elem);
	}
	ppCellAry[elem]->Add(&obj.GetOFT());

	return true;
}

bool CLiner8TreeManager::HitCheck()
{
	// ルート空間が無ければ終了
	if (!ppCellAry[0])
	{
		return false;
	}

	int elem = 0;
	// 当たり判定スタックを作成
	vector<BidirectionalList<OBJECT_FOR_TREE>*> cStack;

	// ルート空間の当たり判定
	HitCheckRoom(ppCellAry[elem], elem, cStack);

	return false;
}

void CLiner8TreeManager::HitCheckRoom(CCell* room, int elem, std::vector<BidirectionalList<OBJECT_FOR_TREE>*>& cStack)
{
	if (!room)
	{
		return;
	}

	BidirectionalList<OBJECT_FOR_TREE>* pOFT = room->GetTop();
	BidirectionalList<OBJECT_FOR_TREE>* pNextOFT = nullptr;

	Collision::CollisionData data;
	Collision::CollisionData data2;
	while (pOFT)
	{
		// スタック内のオブジェクトと当たり判定を取る
		for (auto ite = cStack.begin(); ite != cStack.end(); ite++)
		{
			// 当たり判定マトリクスの確認
			if (!GetCollisionMatrix(pOFT->GetObj().GetGameObject().GetTag(), (*ite)->GetObj().GetGameObject().GetTag()))
			{
				continue;
			}
			if (Collision::HitCheck(&pOFT->GetObj().GetGameObject(), &(*ite)->GetObj().GetGameObject(), &data, &data2))
			{
				pOFT->GetObj().GetGameObject().OnCollision((*ite)->GetObj().GetGameObject(), data);
				(*ite)->GetObj().GetGameObject().OnCollision(pOFT->GetObj().GetGameObject(), data2);
			}
		}
		// 同じ空間内のオブジェクトと当たり判定を取る
		pNextOFT = pOFT->GetNext();

		while (pNextOFT)
		{
			// 当たり判定マトリクスの確認
			if (!GetCollisionMatrix(pOFT->GetObj().GetGameObject().GetTag(), pNextOFT->GetObj().GetGameObject().GetTag()))
			{
				pNextOFT = pNextOFT->GetNext();
				continue;
			}
			if (Collision::HitCheck(&pOFT->GetObj().GetGameObject(), &pNextOFT->GetObj().GetGameObject(), &data, &data2))
			{
				pOFT->GetObj().GetGameObject().OnCollision(pNextOFT->GetObj().GetGameObject(), data);
				pNextOFT->GetObj().GetGameObject().OnCollision(pOFT->GetObj().GetGameObject(), data2);
			}
			pNextOFT = pNextOFT->GetNext();
		}
		pOFT = pOFT->GetNext();
	}

	int pushCount = 0;

	pOFT = room->GetTop();
	while (pOFT)
	{
		// スタックに追加
		cStack.push_back(pOFT);

		pushCount++;
		pOFT = pOFT->GetNext();
	}

	// 子空間に移動
	elem = (elem * 8) + 1;

	// 子空間の確認
	for (int i = 0; i < 8; i++)
	{
		if (elem < m_dwCellNum)
		{
			if (ppCellAry[(elem + i)])
			{
				HitCheckRoom(ppCellAry[(elem + i)], (elem + i), cStack);
			}
		}
	}

	// スタックから削除
	for (int i = 0; i < pushCount; i++)
	{
		cStack.pop_back();
	}

	return;
}

void CLiner8TreeManager::InitCollisionMatrix()
{
	m_collisionMatrix.resize(Tag::Tag_Max);
	for (int i = 0; i < Tag::Tag_Max; i++)
	{
		m_collisionMatrix[i].resize(Tag::Tag_Max - i, true);
	}

	SetCollisionMatrix(Tag::Tag_Player1, Tag::Tag_Player1, false);
	SetCollisionMatrix(Tag::Tag_Player2, Tag::Tag_Player2, false);
	SetCollisionMatrix(Tag::Tag_Room, Tag::Tag_Room, false);
}

bool CLiner8TreeManager::GetCollisionMatrix(Tag tag1, Tag tag2)
{
	if ((tag1 == tag2) || (tag1 < tag2))
	{
		return m_collisionMatrix[tag1][Tag::Tag_Max - 1 - tag2];
	}
	else
	{
		return m_collisionMatrix[tag2][Tag::Tag_Max - 1 - tag1];
	}
	return false;
}

void CLiner8TreeManager::SetCollisionMatrix(Tag tag1, Tag tag2, bool flag)
{
	if ((tag1 == tag2) || (tag1 < tag2))
	{
		m_collisionMatrix[tag1][Tag::Tag_Max - 1 - tag2] = flag;
		return;
	}
	else
	{
		m_collisionMatrix[tag2][Tag::Tag_Max - 1 - tag1] = flag;
		return;
	}
	return;
}

