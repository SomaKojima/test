#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/GameObject.h"
#include "../Object/Car/Car.h"
#include "../Camera/Camera.h"
#include "../Object/Room/Room.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
}

/// <summary>
/// �����֐�
/// </summary>
void PlayScene::Instance()
{
	// �����̍쐬
	GameObject* room = new Room();
	room->Instance();
	room->GetTransform().CollisionSize(200);
	m_gameObjectList.Add(room);

	// �Ԃ̍쐬
	GameObject* car = new Car();
	car->Instance();
	car->GetTransform().LocalPos(Vector3(0, 2.0f, 0));
	car->GetTransform().CollisionSize(1.5f);
	m_gameObjectList.Add(car);

	// �J�����̍쐬
	GameObject* camera = new Camera(car);
	camera->Instance();
	m_gameObjectList.Add(camera);

}
