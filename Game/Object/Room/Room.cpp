#include "../../../pch.h"
#include "Room.h"
#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Collision/CollisionMesh.h"

#include"../../Data/Model/ModelData.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Instance()
{

	// モデル取得
	ModelData& modelData = RoomModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	AddComponent(renderThreeDimention);

	// メッシュの当たり判定を作成
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\room.obj");
	AddComponent(collisionMesh);
}
