/// <summary>
/// CollisionSphere.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
//#include "../Component.h"
#include "CollisionComponent.h"
#include "DebugCollision/DebugSphere.h"
#include "Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionSphere : public CollisionComponent
{
public:
	CollisionSphere(DirectX::SimpleMath::Vector3 center, float radius);
	~CollisionSphere();

	// 更新
	void Update(float elapsedTime) override;
	// 遅延更新
	void LateUpdate(float elapsedTime) override;
	// 描画
	void Render() override;
	// 終了
	void Finalize() override;


	void HitBack(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) override;

	// 壁刷りの計算
	DirectX::SimpleMath::Vector3& WallCulc(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos, DirectX::SimpleMath::Vector3 vel);

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }

	const Collision::Sphere* GetSphere() { return &m_sphere; }
	Collision::CollisionType GetShapeType() { return Collision::CollisionType::SPHERE; }

private:
	DirectX::SimpleMath::Vector3 m_center; // 球の中心
	float m_radius;   // 球の半径
	Collision::Sphere m_sphere;

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugSphere> m_obj;
};
