#pragma once
#include "../Object/GameObject.h"

class Camera : public GameObject
{
public:
	// コンストラクタ
	Camera(GameObject* target);
	// デストラクタ
	~Camera();

public:
	// 生成関数
	void Instance() override;

private:
	GameObject* m_target;
};