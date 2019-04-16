#pragma once
#include "../../Utility/Singleton.h"

class ModelData
{
public:
	static ID3D11Device* device;

public:
	// �R���X�g���N�^
	ModelData();
	// �f�X�g���N�^
	virtual ~ModelData();

public:
	DirectX::Model* GetModel() { return m_model.get(); }
	static void SetDevice(ID3D11Device* _device) { device = _device; }

protected:
	std::unique_ptr<DirectX::Model> m_model;
};

class CarBodyModel : public ModelData, public Singleton<CarBodyModel>
{
public:
	// �R���X�g���N�^
	CarBodyModel();
};

class RoomModel : public ModelData, public Singleton<RoomModel>
{
public:
	// �R���X�g���N�^
	RoomModel();
};

