#include "../../../pch.h"
#include "Gravity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Gravity::Gravity()
	:
	m_gravity(9.8f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Gravity::~Gravity()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Gravity::Update(float elapsedTime)
{
	float g = m_gravity / (60 * 60);
	// �I�u�W�F�N�g�̉��������v�Z
	Vector3 down = Vector3::Transform(Vector3::Down ,m_gameObject->GetTransform().LocalDir());
	// �d�͉����x���v�Z
	Vector3 accel = down * g;

	// �I�u�W�F�N�g�̉����x�ɉ�����
	accel += m_gameObject->GetTransform().LocalAccel();
	m_gameObject->GetTransform().LocalAccel(accel);
}
