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

	// ���f���擾
	ModelData& modelData = RoomModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	AddComponent(renderThreeDimention);

	// ���b�V���̓����蔻����쐬
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\room.obj");
	AddComponent(collisionMesh);
}
