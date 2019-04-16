#include "../../pch.h"
#include "PlayCamera.h"
#include "Mouse.h"
#include "../Object/GameObject.h"
#include "CameraManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayCamera::PlayCamera(GameObject* player)
	:
	m_target(player)
{
}

void PlayCamera::Initialize()
{
}

void PlayCamera::Update(float elapsedTime)
{
	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 3.0f, -5.0f), m_target->GetTransform().WorldDir());
	Vector3 eyePos = m_target->GetTransform().WorldMatrix().Translation() + eyeVec;

	SetPositionTarget(eyePos, m_target->GetTransform().WorldMatrix().Translation());

	// カメラ管理のビューを更新する
	CameraManager& cameraManager = CameraManager::GetInstace();
	cameraManager.SetView(Matrix::CreateLookAt(GetEyePosition(), GetTargetPosition(), GetUp()));
}

DirectX::SimpleMath::Vector3 PlayCamera::GetUp()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_target->GetTransform().WorldDir());
	return up;
}
