#include "../../pch.h"
#include "CollisionComponent.h"

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionComponent::Update(float elapsedTime)
{
	isHit = false;
}

/// <summary>
/// �Փˏ���
/// </summary>
/// <param name="obj"></param>
/// <param name="data"></param>
void CollisionComponent::OnCollision(GameObject & obj, Collision::CollisionData & data)
{
	// �ʂƏՓ�
	if (data.plane) HitBack(data.plane, data.hitPos);
	// ���ƏՓ�
	else if (data.segment) HitBack(data.segment, data.hitPos);
	// ���ƏՓ�
	else if (data.sphere) HitBack(data.sphere, data.hitPos);
	// �O�p�ʁi�|���S���j�ƏՓ�
	else if (data.triangle) HitBack(data.triangle, data.hitPos);
	// �|���S���̏W�܂�ƏՓ�
	else if (data.triangleList.size() > 0);
}