#pragma once
#include "../GameObject.h"

class Room : public GameObject
{
public:
	// コンストラクタ
	Room();
	// デストラクタ
	~Room();

public:
	// 生成関数
	void Instance() override;
};
