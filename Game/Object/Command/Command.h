#pragma once

#include "../GameObject.h"

/// <summary>
/// �R�}���h�N���X
/// </summary>
class Command
{
public:
	// �R���X�g���N�^
	virtual ~Command() {}
	// ���s�֐�
	virtual void Excute(GameObject& obj) = 0;
};