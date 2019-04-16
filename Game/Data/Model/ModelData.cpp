#include "../../../pch.h"
#include "ModelData.h"

using namespace DirectX;

ID3D11Device* ModelData::device = nullptr;

/// <summary>
/// モデルのコンストラクタ
/// </summary>
ModelData::ModelData()
{
	int a = 0;
}

/// <summary>
/// モデルのデストラクタ
/// </summary>
ModelData::~ModelData()
{
	m_model.reset();
}


/// <summary>
/// モデル＜車のボディ＞のコンストラクタ
/// </summary>
CarBodyModel::CarBodyModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\car_body.cmo", fx);
}

/// <summary>
/// モデル＜部屋＞のコンストラクタ
/// </summary>
RoomModel::RoomModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\room.cmo", fx);
}
