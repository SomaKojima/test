#pragma once

#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Object/GameObject.h"
#include "../Collision/Collision.h"

/// <summary>
/// コンポーネントクラス
/// </summary>
class Component
{
protected:
	// コンストラクタ
	Component() : m_gameObject(nullptr){};

public:
	// 仮想デストラクタ
	virtual ~Component() {};

	// 初期化
	virtual void Initialize() {};
	// 更新
	virtual void Update(float elapsedTime) {};
	// 遅延更新
	virtual void LateUpdate(float elapsedTime) {}
	// 描画
	virtual void Render() {};
	// 終了
	virtual void Finalize() {};

	// 当たり判定の処理
	virtual void OnCollision(GameObject& obj, Collision::CollisionData& data) {}

	// オブジェクトを設定する
	void SetGameObject(GameObject* obj) { m_gameObject = obj; }
	// オブジェクトを取得する
	GameObject* GetGameObject(GameObject* obj) { return m_gameObject; }
protected:
	// 自身のコンポーネントをアタッチしているオブジェクト
	GameObject* m_gameObject;
};