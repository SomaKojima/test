#include "../../pch.h"
#include "CollisionComponent.h"

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionComponent::Update(float elapsedTime)
{
	isHit = false;
}

/// <summary>
/// 衝突処理
/// </summary>
/// <param name="obj"></param>
/// <param name="data"></param>
void CollisionComponent::OnCollision(GameObject & obj, Collision::CollisionData & data)
{
	// 面と衝突
	if (data.plane) HitBack(data.plane, data.hitPos);
	// 線と衝突
	else if (data.segment) HitBack(data.segment, data.hitPos);
	// 球と衝突
	else if (data.sphere) HitBack(data.sphere, data.hitPos);
	// 三角面（ポリゴン）と衝突
	else if (data.triangle) HitBack(data.triangle, data.hitPos);
	// ポリゴンの集まりと衝突
	else if (data.triangleList.size() > 0);
}