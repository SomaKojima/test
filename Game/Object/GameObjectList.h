#pragma once
#include "../Utility/BidirectionalList.h"
#include "GameObject.h"

/// <summary>
/// ゲームオブジェクトのリストクラス
/// </summary>
class GameObjectList : public BidirectionalList<GameObject>::RegisterTo
{
public:
	// コンストラクタ
	GameObjectList();
	// デストラクタ
	~GameObjectList();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
};