#include "../../../pch.h"
#include "ModelData.h"

using namespace DirectX;

ID3D11Device* ModelData::device = nullptr;

/// <summary>
/// ���f���̃R���X�g���N�^
/// </summary>
ModelData::ModelData()
{
	int a = 0;
}

/// <summary>
/// ���f���̃f�X�g���N�^
/// </summary>
ModelData::~ModelData()
{
	m_model.reset();
}


/// <summary>
/// ���f�����Ԃ̃{�f�B���̃R���X�g���N�^
/// </summary>
CarBodyModel::CarBodyModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\car_body.cmo", fx);
}

/// <summary>
/// ���f�����������̃R���X�g���N�^
/// </summary>
RoomModel::RoomModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\room.cmo", fx);
}
