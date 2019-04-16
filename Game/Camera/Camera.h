#pragma once
#include "../Object/GameObject.h"

class Camera : public GameObject
{
public:
	// �R���X�g���N�^
	Camera(GameObject* target);
	// �f�X�g���N�^
	~Camera();

public:
	// �����֐�
	void Instance() override;

private:
	GameObject* m_target;
};