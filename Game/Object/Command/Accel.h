#pragma once

#include "Command.h"

/// <summary>
/// �����R�}���h�̃N���X
/// </summary>
class Accel : public Command
{
public:
	// �R���X�g���N�^
	Accel();
	~Accel();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};