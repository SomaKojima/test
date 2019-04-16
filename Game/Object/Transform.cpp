#include "../../pch.h"
#include "Transform.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Transform::Transform()
	:
	m_worldPos(DirectX::SimpleMath::Vector3::Zero),
	m_worldVel(DirectX::SimpleMath::Vector3::Zero),
	m_worldAccel(DirectX::SimpleMath::Vector3::Zero),
	m_worldDir(DirectX::SimpleMath::Quaternion::Identity),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_collisionSize(3),
	m_parent(nullptr)
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Transform::Initialize()
{
	// 初期移動
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	//　座標の更新
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// マトリクスを更新
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);

	// 子供のマトリクスを更新
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// 子供のリストに追加する
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 座標を更新
		Vector3 pos = (*ite)->WorldPos() + m_worldVel;
		(*ite)->WorldPos(pos);
		// マトリクスを更新
		Matrix matrix = Matrix::CreateFromQuaternion((*ite)->WorldDir()) * Matrix::CreateTranslation((*ite)->WorldPos());
		(*ite)->WorldMatrix(matrix);
	}
}

void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 座標を更新
		(*ite)->WorldPos((*ite)->WorldPos() + pos);
		(*ite)->UpdateChildPos(pos);
	}
}

void Transform::UpdateChildDir(DirectX::SimpleMath::Vector3 & dir)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 向きを更新
		Quaternion q = (*ite)->WorldDir() * dir;
		(*ite)->WorldDir(q);
		(*ite)->UpdateChildDir(dir);
	}
}

/// <summary>
/// ローカル座標を取得する
/// </summary>
/// <returns>親を基準にローカル座標を取得する：　親がいない場合はワールド座標を返す</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld)
{
	if (m_parent)
	{
		// 逆回転を取得
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		// 座標を計算
		Vector3 vel = world - parentWorld;
		return Vector3::Transform(vel, inv);
	}
	// 親がいない場合
	return world;
}

/// <summary>
/// ローカル座標を取得する
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::SetLocalToWorld(DirectX::SimpleMath::Vector3 & local)
{
	if (m_parent)return m_parent->WorldVel() + Vector3::Transform(local, LocalDir());
	return Vector3::Transform(local, LocalDir());
}


/// <summary>
/// ローカル座標の向き
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	if (m_parent)
	{
		// 親の逆回転を加える(現在の向き　ー　親の向き)
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		return m_worldDir * inv;
	}
	// 親がいなければ自身の回転を返す
	return m_worldDir;
}

/// <summary>
/// ローカル座標のマトリクス
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Transform::LocalMatrix()
{
	if (m_parent)
	{
		return Matrix::CreateFromQuaternion(LocalDir()) * Matrix::CreateTranslation(LocalPos());
	}
	return m_worldMatrix;
}
