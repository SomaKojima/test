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
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
}

/// <summary>
/// 生成関数
/// </summary>
void PlayScene::Instance()
{
	// 部屋の作成
	GameObject* room = new Room();
	room->Instance();
	room->GetTransform().CollisionSize(200);
	m_gameObjectList.Add(room);

	// 車の作成
	GameObject* car = new Car();
	car->Instance();
	car->GetTransform().LocalPos(Vector3(0, 2.0f, 0));
	car->GetTransform().CollisionSize(1.5f);
	m_gameObjectList.Add(car);

	// カメラの作成
	GameObject* camera = new Camera(car);
	camera->Instance();
	m_gameObjectList.Add(camera);

}
