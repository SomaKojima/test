#pragma once

#include <list>
#include "Transform.h"
#include "../Utility/BidirectionalList.h"
#include "../Data/Data.h"
#include "../Collision/Collision.h"

class Component;
class OBJECT_FOR_TREE;

/// <summary>
/// ゲームオブジェクトのクラス
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// コンストラクタ
	GameObject();
	// デストラクタ
	virtual ~GameObject();

public:
	// 生成関数
	virtual void Instance() = 0;

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
	// 衝突処理
	void OnCollision(GameObject& obj, Collision::CollisionData &data);

public:
	// 子供のリストに追加する
	void AddChild(GameObject* gameObject) { m_transform.AddChild(&gameObject->m_transform); }

	// コンポーネントのクラスに追加する
	void AddComponent(Component* component);
	/// <summary>
	/// コンポーネントを取得する関数
	/// </summary>
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// 変形の取得
	Transform& GetTransform() { return m_transform; }
	// 当たり判定のリストに使う要素を取得する
	OBJECT_FOR_TREE& GetOFT() { return *m_oft; }
	// タグの設定
	void SetTag(Tag tag) { m_tag = tag; }
	// タグの取得
	Tag& GetTag() { return m_tag; }

private:
	// 変形
	Transform m_transform;
	// コンポーネントのリスト
	std::list<Component*> m_componentList;
	// 当たり判定のリストに使う要素
	OBJECT_FOR_TREE* m_oft;
	// タグ
	Tag m_tag;
};

/// <summary>
/// コンポーネントのリストから一つのコンポーネントを取得する
/// </summary>
template<class T>
inline T * GameObject::GetComponent()
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// 引数のポインタからコンポーネントを取得する
/// </summary>
template<class T>
inline T * GameObject::GetComponent(Component * component)
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub == component)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// コンポーネントのリストから複数のコンポーネントをリストで取得する
/// </summary>
template<class T>
inline std::list<T*> GameObject::GetComponentList()
{
	T* sub = nullptr;
	std::list<T*> list;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			list.push_back(sub);
		}
	}
	return list;
}
