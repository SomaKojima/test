#pragma once
#include "../GameObject.h"

class Car : public GameObject
{
public:
	// �R���X�g���N�^
	Car();
	// �f�X�g���N�^
	~Car();

public:
	// �����֐�
	void Instance() override;
};