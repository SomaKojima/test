#pragma once

#include "../Component.h"

/// <summary>
/// 3D���f���`��̃R���|�[�l���g
/// </summary>
class RenderThreeDimention : public Component
{
public:
	// �`�悷����
	enum Type
	{
		Nomal,
		Sky
	};

public:
	// �R���X�g���N�^
	RenderThreeDimention(DirectX::Model* model, Type type);
	// �f�X�g���N�^
	~RenderThreeDimention();

public:
	// �`��
	void Render()override;
	// �I��
	void Finalize()override;
private:
	// �`�悷����
	Type m_type;
	// �`�悷�郂�f��
	DirectX::Model* m_model;
};