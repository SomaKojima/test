#pragma once

#include "../Component.h"

/// <summary>
/// 重力のコンポーネント
/// </summary>
class Gravity : public Component
{
public:
	// コンストラクタ
	Gravity();
	// デストラクタ
	~Gravity();

public:
	// 更新処理
	void Update(float elapsedTime) override;
private:

	float m_gravity;
};