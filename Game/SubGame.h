#pragma once

#include "Utility/Singleton.h"

class Game;

class SubGame : public Singleton<SubGame>
{
public:
	//　コンストラクタ
	SubGame();
	~SubGame();
public:
	// 初期化処理
	void Initialize(Game* game);
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Renderer();
	// 終了処理
	void Finalize();

	void SetGame(Game* game) { m_game = game; }
	Game* GetGame() { return m_game; }

private:
	Game* m_game;
};