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
	// �Q�[���̐ݒ�
	m_game = game;

	// �����蔻��̋�Ԃ��쐬
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.Init(4, -100.0f, 100.0f, 100.0f, 0.0f, 100.0f, -100.0f);

	// �V�[���Ǘ��̏�����
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Play);
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// ���͂̍X�V
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);

	// �V�[���̍X�V
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Update(elapsedTime);

	// �����蔻��̋�Ԃ��쐬
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	cLiner8TreeManager.HitCheck();
}

void SubGame::Renderer()
{
	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{
	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
