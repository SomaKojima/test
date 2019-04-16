//--------------------------------------------------------------------------------------
// File: DebugPlane.h
//
// �f�o�b�O�{�b�N�X��`�悷��N���X
//
// Date: 2018.9.25
// Author: Soma Kojima
//--------------------------------------------------------------------------------------
#pragma once

class DebugPlane
{
	struct ConstantBuffer
	{
		DirectX::XMMATRIX worldViewProjection;
	};

	// ���S
	DirectX::SimpleMath::Vector3 m_center;

	// ���a
	float m_width;
	float m_height;

	// ��]
	DirectX::SimpleMath::Vector3 m_angle;

	// ���s�ړ��s��
	DirectX::SimpleMath::Matrix m_trans;

	// �X�P�[���s��
	DirectX::SimpleMath::Matrix m_scale;

	// ��]�s��
	DirectX::SimpleMath::Matrix m_rotation;

	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	// ���X�^���C�U�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:
	// �R���X�g���N�^
	DebugPlane(ID3D11Device* device, DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 angle, float width, float height);

	// �f�o�b�O�X�t�B�A�̕`��֐�
	void Draw(ID3D11DeviceContext* context, DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// �f�o�b�O�X�{�b�N�X�̐ݒ�֐�
	void SetCenter(DirectX::SimpleMath::Vector3 center);

	// �f�o�b�O�{�b�N�X�̔��a�̐ݒ�֐�
	void SetWidthHeight(float width, float height);

	// �f�o�b�O�{�b�N�X�̃Z���^�[�̎擾�֐�
	DirectX::SimpleMath::Vector2 GetWidthHeight();

	// ��]�̐ݒ�֐�
	void SetAngle(DirectX::SimpleMath::Vector3 angle);
};