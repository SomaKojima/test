/// <summary>
/// CollisionSphere.h
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
//#include "../Component.h"
#include "CollisionComponent.h"
#include "DebugCollision/DebugSphere.h"
#include "Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionSphere : public CollisionComponent
{
public:
	CollisionSphere(DirectX::SimpleMath::Vector3 center, float radius);
	~CollisionSphere();

	// �X�V
	void Update(float elapsedTime) override;
	// �x���X�V
	void LateUpdate(float elapsedTime) override;
	// �`��
	void Render() override;
	// �I��
	void Finalize() override;


	void HitBack(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) override;

	// �Ǎ���̌v�Z
	DirectX::SimpleMath::Vector3& WallCulc(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos, DirectX::SimpleMath::Vector3 vel);

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }

	const Collision::Sphere* GetSphere() { return &m_sphere; }
	Collision::CollisionType GetShapeType() { return Collision::CollisionType::SPHERE; }

private:
	DirectX::SimpleMath::Vector3 m_center; // ���̒��S
	float m_radius;   // ���̔��a
	Collision::Sphere m_sphere;

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugSphere> m_obj;
};
