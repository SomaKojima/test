#pragma once

#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Object/GameObject.h"
#include "../Collision/Collision.h"

/// <summary>
/// �R���|�[�l���g�N���X
/// </summary>
class Component
{
protected:
	// �R���X�g���N�^
	Component() : m_gameObject(nullptr){};

public:
	// ���z�f�X�g���N�^
	virtual ~Component() {};

	// ������
	virtual void Initialize() {};
	// �X�V
	virtual void Update(float elapsedTime) {};
	// �x���X�V
	virtual void LateUpdate(float elapsedTime) {}
	// �`��
	virtual void Render() {};
	// �I��
	virtual void Finalize() {};

	// �����蔻��̏���
	virtual void OnCollision(GameObject& obj, Collision::CollisionData& data) {}

	// �I�u�W�F�N�g��ݒ肷��
	void SetGameObject(GameObject* obj) { m_gameObject = obj; }
	// �I�u�W�F�N�g���擾����
	GameObject* GetGameObject(GameObject* obj) { return m_gameObject; }
protected:
	// ���g�̃R���|�[�l���g���A�^�b�`���Ă���I�u�W�F�N�g
	GameObject* m_gameObject;
};