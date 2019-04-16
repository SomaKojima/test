#include "../pch.h"
#include "SubGame.h"
#include "../Game.h"

#include "Utility/InputManager.h"
#include "Scene/SceneManager.h"
#include "Collision/CCell.h"

SubGame::SubGame()
	:
	m_game(nullptr)
{
}

SubGame::~SubGame()
{
	m_game = nullptr;
}

void SubGame::Initialize(Game* game)
{
	// ゲームの設定
	m_game = game;

	// 当たり判定の空間を作成
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Init(4, -100.0f, 100.0f, 100.0f, 0.0f, 100.0f, -100.0f);

	// シーン管理の初期化
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Play);
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// 入力の更新
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);

	// シーンの更新
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Update(elapsedTime);

	// 当たり判定の空間を作成
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.HitCheck();
}

void SubGame::Renderer()
{
	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{
	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
