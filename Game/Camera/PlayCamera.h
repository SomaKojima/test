#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// プレイシーンのカメラ
/// </summary>
class PlayCamera : public BaseCamera, public Component
{
private:
	// 追いかける相手
	GameObject* m_target;

public:
	// コンストラクタ
	PlayCamera(GameObject* player);

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapsedTime) override;

	// カメラの上方向を取得
	DirectX::SimpleMath::Vector3 GetUp();
};