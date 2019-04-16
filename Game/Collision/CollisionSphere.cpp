/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../SubGame.h"
//#include "BoxCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
CollisionSphere::CollisionSphere(DirectX::SimpleMath::Vector3 center, float radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_sphere.radius = radius;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Update(float elapsedTime)
{
	CollisionComponent::Update(elapsedTime);
}

void CollisionSphere::LateUpdate(float elapsedTime)
{
	m_sphere.center = Vector3::Transform(m_center, (m_gameObject->GetTransform().WorldMatrix()));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void CollisionSphere::Render()
{
	Matrix world = m_gameObject->GetTransform().WorldMatrix() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().m_game->GetDevice(), m_center, m_radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().m_game;
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void CollisionSphere::Finalize()
{
	m_obj.reset();
}



void CollisionSphere::HitBack(const Collision::Triangle * triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// ���x�ŕǍ�����s��
	 Vector3 w_vec_vel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().LocalVel());
	 m_gameObject->GetTransform().LocalVel(w_vec_vel);
	// ���W�̍X�V
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	pos += Vector3::Transform(w_vec_vel, m_gameObject->GetTransform().WorldDir());
	m_gameObject->GetTransform().LocalPos(pos);

	// �����x��Ǎ�����s�������x�ɂ���
	Vector3 w_vec_accel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().LocalAccel());
	m_gameObject->GetTransform().LocalAccel(w_vec_accel);
}


/// <summary>
/// �Ǎ���̌v�Z
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3& CollisionSphere::WallCulc(const Collision::Triangle * triangle, Vector3 & hitPos, SimpleMath::Vector3 vel)
{
	// ���x���擾
	Vector3 vec = vel;

	// �ʂ̖@��
	Vector3 normal(triangle->plane.a, triangle->plane.b, triangle->plane.c);

	// �@���̌����̃x�N�g�����Ȃ���(�v���C���[�̌����ɍ��킹��E���[�J�����W�ɂ���)
	Quaternion q;
	m_gameObject->GetTransform().WorldDir().Conjugate(q);

	// �ǂ���
	Vector3 normal2 = Vector3::Transform(normal, q);

	float l = vec.Dot(normal2);
	Vector3 w_vec;
	if (l <= 0)
	{
		w_vec = vec - l * normal2;
	}
	else
	{
		w_vec = vec;
	}

	return w_vec;

	// ���W�̍X�V
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	pos += Vector3::Transform(w_vec, m_gameObject->GetTransform().WorldDir());
}

