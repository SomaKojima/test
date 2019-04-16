#include "../../pch.h"
#include "Camera.h"
#include "PlayCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target"></param>
Camera::Camera(GameObject* target)
	:
	m_target(target)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	m_target = nullptr;
}

/// <summary>
/// �����֐�
/// </summary>
void Camera::Instance()
{
	// �J�����̃R���|�[�l���g���쐬
	Component* playCamera = new PlayCamera(m_target);
	AddComponent(playCamera);
}
