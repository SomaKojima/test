#pragma once

#include "../Component.h"

/// <summary>
/// �d�͂̃R���|�[�l���g
/// </summary>
class Gravity : public Component
{
public:
	// �R���X�g���N�^
	Gravity();
	// �f�X�g���N�^
	~Gravity();

public:
	// �X�V����
	void Update(float elapsedTime) override;
private:

	float m_gravity;
};