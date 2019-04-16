#include "../../pch.h"
#include "Transform.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Transform::Transform()
	:
	m_worldPos(DirectX::SimpleMath::Vector3::Zero),
	m_worldVel(DirectX::SimpleMath::Vector3::Zero),
	m_worldAccel(DirectX::SimpleMath::Vector3::Zero),
	m_worldDir(DirectX::SimpleMath::Quaternion::Identity),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_collisionSize(3),
	m_parent(nullptr)
{
}

/// <summary>
/// ����������
/// </summary>
void Transform::Initialize()
{
	// �����ړ�
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	//�@���W�̍X�V
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// �}�g���N�X���X�V
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);

	// �q���̃}�g���N�X���X�V
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// �q���̃��X�g�ɒǉ�����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// ���W���X�V
		Vector3 pos = (*ite)->WorldPos() + m_worldVel;
		(*ite)->WorldPos(pos);
		// �}�g���N�X���X�V
		Matrix matrix = Matrix::CreateFromQuaternion((*ite)->WorldDir()) * Matrix::CreateTranslation((*ite)->WorldPos());
		(*ite)->WorldMatrix(matrix);
	}
}

void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// ���W���X�V
		(*ite)->WorldPos((*ite)->WorldPos() + pos);
		(*ite)->UpdateChildPos(pos);
	}
}

void Transform::UpdateChildDir(DirectX::SimpleMath::Vector3 & dir)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// �������X�V
		Quaternion q = (*ite)->WorldDir() * dir;
		(*ite)->WorldDir(q);
		(*ite)->UpdateChildDir(dir);
	}
}

/// <summary>
/// ���[�J�����W���擾����
/// </summary>
/// <returns>�e����Ƀ��[�J�����W���擾����F�@�e�����Ȃ��ꍇ�̓��[���h���W��Ԃ�</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld)
{
	if (m_parent)
	{
		// �t��]���擾
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		// ���W���v�Z
		Vector3 vel = world - parentWorld;
		return Vector3::Transform(vel, inv);
	}
	// �e�����Ȃ��ꍇ
	return world;
}

/// <summary>
/// ���[�J�����W���擾����
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::SetLocalToWorld(DirectX::SimpleMath::Vector3 & local)
{
	if (m_parent)return m_parent->WorldVel() + Vector3::Transform(local, LocalDir());
	return Vector3::Transform(local, LocalDir());
}


/// <summary>
/// ���[�J�����W�̌���
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	if (m_parent)
	{
		// �e�̋t��]��������(���݂̌����@�[�@�e�̌���)
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		return m_worldDir * inv;
	}
	// �e�����Ȃ���Ύ��g�̉�]��Ԃ�
	return m_worldDir;
}

/// <summary>
/// ���[�J�����W�̃}�g���N�X
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Transform::LocalMatrix()
{
	if (m_parent)
	{
		return Matrix::CreateFromQuaternion(LocalDir()) * Matrix::CreateTranslation(LocalPos());
	}
	return m_worldMatrix;
}
