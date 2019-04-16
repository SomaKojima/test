#pragma once
#include "../Utility/BidirectionalList.h"
#include "GameObject.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃��X�g�N���X
/// </summary>
class GameObjectList : public BidirectionalList<GameObject>::RegisterTo
{
public:
	// �R���X�g���N�^
	GameObjectList();
	// �f�X�g���N�^
	~GameObjectList();

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
};