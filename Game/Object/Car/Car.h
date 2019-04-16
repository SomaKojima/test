#pragma once
#include "../GameObject.h"

class Car : public GameObject
{
public:
	// コンストラクタ
	Car();
	// デストラクタ
	~Car();

public:
	// 生成関数
	void Instance() override;
};