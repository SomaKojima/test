#pragma once
#include"SceneManager.h"

/// <summary>
/// プレイシーン
/// </summary>
class PlayScene : public Scene
{
public:
	// コンストラクタ
	PlayScene();
	// デストラクタ
	~PlayScene();

public:
	// 生成関数
	void Instance() override;
};