#pragma once

#include "../GameObject.h"

/// <summary>
/// コマンドクラス
/// </summary>
class Command
{
public:
	// コンストラクタ
	virtual ~Command() {}
	// 実行関数
	virtual void Excute(GameObject& obj) = 0;
};