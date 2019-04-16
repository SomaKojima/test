#include "../../pch.h"
#include "GameObjectList.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObjectList::GameObjectList()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObjectList::~GameObjectList()
{
}

/// <summary>
/// ����������
/// </summary>
void GameObjectList::Initialize()
{
	BidirectionalList<GameObject>* obj = m_pTop;
	while (obj)
	{
		obj->GetObj().Initialize();
		obj = obj->GetNext();
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void GameObjectList::Update(float elapsedTime)
{
	BidirectionalList<GameObject>* obj = m_pTop;
	while (obj)
	{
		obj->GetObj().Update(elapsedTime);
		obj = obj->GetNext();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void GameObjectList::Render()
{
	BidirectionalList<GameObject>* obj = m_pTop;
	while (obj)
	{
		obj->GetObj().Render();
		obj = obj->GetNext();
	}
}

/// <summary>
/// �I������
/// </summary>
void GameObjectList::Finalize()
{
	BidirectionalList<GameObject>* obj = m_pTop;
	while (obj)
	{
		obj->GetObj().Finalize();
		obj = obj->GetNext();
	}
}
