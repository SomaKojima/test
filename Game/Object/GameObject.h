#pragma once

#include <list>
#include "Transform.h"
#include "../Utility/BidirectionalList.h"
#include "../Data/Data.h"
#include "../Collision/Collision.h"

class Component;
class OBJECT_FOR_TREE;

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃N���X
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// �R���X�g���N�^
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject();

public:
	// �����֐�
	virtual void Instance() = 0;

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
	// �Փˏ���
	void OnCollision(GameObject& obj, Collision::CollisionData &data);

public:
	// �q���̃��X�g�ɒǉ�����
	void AddChild(GameObject* gameObject) { m_transform.AddChild(&gameObject->m_transform); }

	// �R���|�[�l���g�̃N���X�ɒǉ�����
	void AddComponent(Component* component);
	/// <summary>
	/// �R���|�[�l���g���擾����֐�
	/// </summary>
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// �ό`�̎擾
	Transform& GetTransform() { return m_transform; }
	// �����蔻��̃��X�g�Ɏg���v�f���擾����
	OBJECT_FOR_TREE& GetOFT() { return *m_oft; }
	// �^�O�̐ݒ�
	void SetTag(Tag tag) { m_tag = tag; }
	// �^�O�̎擾
	Tag& GetTag() { return m_tag; }

private:
	// �ό`
	Transform m_transform;
	// �R���|�[�l���g�̃��X�g
	std::list<Component*> m_componentList;
	// �����蔻��̃��X�g�Ɏg���v�f
	OBJECT_FOR_TREE* m_oft;
	// �^�O
	Tag m_tag;
};

/// <summary>
/// �R���|�[�l���g�̃��X�g�����̃R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent()
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �����̃|�C���^����R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent(Component * component)
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub == component)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �R���|�[�l���g�̃��X�g���畡���̃R���|�[�l���g�����X�g�Ŏ擾����
/// </summary>
template<class T>
inline std::list<T*> GameObject::GetComponentList()
{
	T* sub = nullptr;
	std::list<T*> list;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			list.push_back(sub);
		}
	}
	return list;
}
