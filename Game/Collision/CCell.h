#pragma once

#include <vector>
#include "../Utility/BidirectionalList.h"
#include "../Utility/Singleton.h"
#include "../Data/Data.h"

class CCell;
class GameObject;

class OBJECT_FOR_TREE : public BidirectionalList<OBJECT_FOR_TREE>
{
public:
	OBJECT_FOR_TREE(GameObject* pObject):BidirectionalList<OBJECT_FOR_TREE>(this), m_gameObject(pObject) {}
	~OBJECT_FOR_TREE() { m_gameObject = nullptr; }

	GameObject& GetGameObject() { return *m_gameObject; }
private:
	GameObject* m_gameObject;
};

class CCell : public BidirectionalList<OBJECT_FOR_TREE>::RegisterTo
{
public:
	CCell() {};
	~CCell() {};
};

class CLiner8TreeManager : public Singleton<CLiner8TreeManager>
{
public:
	static const int CLINER8TREEMANAGER_MAXLEVEL = 4;

public:
	CLiner8TreeManager();
	~CLiner8TreeManager();

	bool Init(unsigned int Level, float left, float top, float right, float bottom, float front, float back);

	DWORD BitSeparateFor3D(BYTE n);
	DWORD Get3DMortonOrder(BYTE x, BYTE y, BYTE z);
	DWORD GetMortonOrderX(float x);
	DWORD GetMortonOrderY(float y);
	DWORD GetMortonOrderZ(float z);
	DWORD GetPosToMortonOrder(DirectX::SimpleMath::Vector3 pos);
	DWORD Get2PointMortonOrder(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 pos2);

	bool CreateNewCell(DWORD Elem);
	bool Register(GameObject& obj, float radius);
	bool HitCheck();
	void  HitCheckRoom(CCell* room, int elem, std::vector<BidirectionalList<OBJECT_FOR_TREE>*>& cStack);

	CCell** GetCCell() { return ppCellAry; }


	void InitCollisionMatrix();
	bool GetCollisionMatrix(Tag tag1, Tag tag2);
	void SetCollisionMatrix(Tag tag1, Tag tag2, bool flag);
private:
	float m_fLeft;
	float m_fBottom;
	float m_fBack;
	float m_fW;
	float m_fH;
	float m_fD;
	float m_fUnit_W;
	float m_fUnit_H;
	float m_fUnit_D;
	int m_level;
	int m_iPow[CLINER8TREEMANAGER_MAXLEVEL];
	int m_dwCellNum;

	CCell** ppCellAry;

	std::vector<std::vector<bool>> m_collisionMatrix;

	//bool m_collisionMatrix[Tag::Max][Tag::Max];
};