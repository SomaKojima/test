#pragma once
#include "../GameObject.h"

class Room : public GameObject
{
public:
	// �R���X�g���N�^
	Room();
	// �f�X�g���N�^
	~Room();

public:
	// �����֐�
	void Instance() override;
};
