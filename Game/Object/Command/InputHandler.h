#pragma once

#include "Command.h"


class InputHandler
{
public:
	// コンストラクタ
	InputHandler();
	// デストラクタ
	~InputHandler();

public:

	// 入力ハンドルを取得
	std::vector<Command*> GetInputHnadle();

private:
};