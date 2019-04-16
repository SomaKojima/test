#pragma once

#include "Command.h"

/// <summary>
/// 加速コマンドのクラス
/// </summary>
class Accel : public Command
{
public:
	// コンストラクタ
	Accel();
	~Accel();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};