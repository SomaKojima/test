#include "../../pch.h"
#include "GameObjectList.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameObjectList::GameObjectList()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameObjectList::~GameObjectList()
{
}

/// <summary>
/// 初期化処理
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
/// 更新処理
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
/// 描画処理
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
/// 終了処理
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
