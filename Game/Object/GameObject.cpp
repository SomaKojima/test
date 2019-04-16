#include "../../pch.h"
#include "GameObject.h"
#include "../Component/Component.h"
#include "../Collision/CCell.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
GameObject::GameObject() 
	: 
	BidirectionalList<GameObject>(this),
	m_oft(new OBJECT_FOR_TREE(this)),
	m_tag(Tag::Tag_Default)
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// 初期化
/// </summary>
void GameObject::Initialize()
{
	// コンポーネントの初期化
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Initialize();
	}

	// 変形の更新
	m_transform.Update(0);
	// 初期空間登録
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Register(*this, m_transform.CollisionSize());
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::Update(float elapsedTime)
{
	// 変形の更新
	m_transform.Update(elapsedTime);
	// コンポーネントの更新
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Update(elapsedTime);
		(*ite)->LateUpdate(elapsedTime);
	}

	// 初期空間登録
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Register(*this, m_transform.CollisionSize());
}

/// <summary>
/// 描画
/// </summary>
void GameObject::Render()
{
	// コンポーネントの描画
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
}

/// <summary>
/// 終了
/// </summary>
void GameObject::Finalize()
{
	// コンポーネントの終了
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Finalize();
		delete (*ite);
	}
	m_componentList.clear();

	// 当たり判定のリストから離れる
	m_oft->Remove();
	delete m_oft;
}

/// <summary>
/// 衝突
/// </summary>
/// <param name="obj"></param>
/// <param name="data"></param>
void GameObject::OnCollision(GameObject& obj, Collision::CollisionData &data)
{
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->OnCollision(obj, data);
	}
}

/// <summary>
/// コンポーネントをリストに追加する
/// </summary>
/// <param name="component"></param>
void GameObject::AddComponent(Component * component)
{
	component->SetGameObject(this);
	m_componentList.push_back(component);
}
