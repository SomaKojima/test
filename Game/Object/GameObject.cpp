#include "../../pch.h"
#include "GameObject.h"
#include "../Component/Component.h"
#include "../Collision/CCell.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObject::GameObject() 
	: 
	BidirectionalList<GameObject>(this),
	m_oft(new OBJECT_FOR_TREE(this)),
	m_tag(Tag::Tag_Default)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// ������
/// </summary>
void GameObject::Initialize()
{
	// �R���|�[�l���g�̏�����
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Initialize();
	}

	// �ό`�̍X�V
	m_transform.Update(0);
	// ������ԓo�^
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Register(*this, m_transform.CollisionSize());
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::Update(float elapsedTime)
{
	// �ό`�̍X�V
	m_transform.Update(elapsedTime);
	// �R���|�[�l���g�̍X�V
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Update(elapsedTime);
		(*ite)->LateUpdate(elapsedTime);
	}

	// ������ԓo�^
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Register(*this, m_transform.CollisionSize());
}

/// <summary>
/// �`��
/// </summary>
void GameObject::Render()
{
	// �R���|�[�l���g�̕`��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
}

/// <summary>
/// �I��
/// </summary>
void GameObject::Finalize()
{
	// �R���|�[�l���g�̏I��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Finalize();
		delete (*ite);
	}
	m_componentList.clear();

	// �����蔻��̃��X�g���痣���
	m_oft->Remove();
	delete m_oft;
}

/// <summary>
/// �Փ�
/// </summary>
/// <param name="obj"></param>
/// <param name="data"></param>
void GameObject::OnCollision(GameObject& obj, Collision::CollisionData &data)
{
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->OnCollision(obj, data);
	}
}

/// <summary>
/// �R���|�[�l���g�����X�g�ɒǉ�����
/// </summary>
/// <param name="component"></param>
void GameObject::AddComponent(Component * component)
{
	component->SetGameObject(this);
	m_componentList.push_back(component);
}
