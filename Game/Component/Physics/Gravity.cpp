#include "../../../pch.h"
#include "Gravity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Gravity::Gravity()
	:
	m_gravity(9.8f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Gravity::~Gravity()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Gravity::Update(float elapsedTime)
{
	float g = m_gravity / (60 * 60);
	// オブジェクトの下方向を計算
	Vector3 down = Vector3::Transform(Vector3::Down ,m_gameObject->GetTransform().LocalDir());
	// 重力加速度を計算
	Vector3 accel = down * g;

	// オブジェクトの加速度に加える
	accel += m_gameObject->GetTransform().LocalAccel();
	m_gameObject->GetTransform().LocalAccel(accel);
}
