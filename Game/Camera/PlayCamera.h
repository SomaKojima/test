#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// �v���C�V�[���̃J����
/// </summary>
class PlayCamera : public BaseCamera, public Component
{
private:
	// �ǂ������鑊��
	GameObject* m_target;

public:
	// �R���X�g���N�^
	PlayCamera(GameObject* player);

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;

	// �J�����̏�������擾
	DirectX::SimpleMath::Vector3 GetUp();
};