#include "../../pch.h"
#include "CameraManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
CameraManager::CameraManager()
	:
	m_view(Matrix::Identity)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CameraManager::~CameraManager()
{
}
