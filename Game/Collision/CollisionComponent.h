/// <summary>
/// CollisionComponent.h
/// 
/// 制作日:2018/10/26
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component/Component.h"
#include "../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent() :isHit(false) {};
	~CollisionComponent() {};

	// 更新
	void Update(float elapsedTime) override;

	// 衝突処理
	void OnCollision(GameObject& obj, Collision::CollisionData& data) override;

	// 壁ずり等の処理
	virtual void HitBack(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Segment* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Sphere* sphere, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Plane* sphere, DirectX::SimpleMath::Vector3& hitPos) {};

	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }

	virtual const Collision::Sphere* GetSphere() { return nullptr; }
	virtual const Collision::Segment* GetSegment() { return nullptr; }
	virtual const Collision::Plane* GetPlane() { return nullptr; }
	virtual const Collision::Triangle* GetTriangle() { return nullptr; }
	virtual const std::list<Collision::Triangle>* GetTriangleList() { return nullptr; }

private:
	bool isHit;
};
