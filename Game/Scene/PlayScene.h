#pragma once
#include"SceneManager.h"

/// <summary>
/// �v���C�V�[��
/// </summary>
class PlayScene : public Scene
{
public:
	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	~PlayScene();

public:
	// �����֐�
	void Instance() override;
};