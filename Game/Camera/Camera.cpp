#include "../../pch.h"
#include "Camera.h"
#include "PlayCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target"></param>
Camera::Camera(GameObject* target)
	:
	m_target(target)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	m_target = nullptr;
}

/// <summary>
/// 生成関数
/// </summary>
void Camera::Instance()
{
	// カメラのコンポーネントを作成
	Component* playCamera = new PlayCamera(m_target);
	AddComponent(playCamera);
}
