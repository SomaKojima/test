#pragma once

#include "Command.h"


class InputHandler
{
public:
	// �R���X�g���N�^
	InputHandler();
	// �f�X�g���N�^
	~InputHandler();

public:

	// ���̓n���h�����擾
	std::vector<Command*> GetInputHnadle();

private:
};