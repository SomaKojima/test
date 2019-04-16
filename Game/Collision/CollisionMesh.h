
#pragma once

#include "CollisionComponent.h"
#include "DebugCollision/DebugMesh.h"
#include "Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionMesh : public CollisionComponent
{
public:
	CollisionMesh(wchar_t* file);
	~CollisionMesh();

	// 更新
	void Update(float elapsedTime) override;
	// 遅延更新
	void LateUpdate(float elapsedTime) override;
	// 描画
	void Render() override;
	// 終了
	void Finalize() override;

	// ポリゴンの情報を取得
	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangles; }

	// 形の情報
	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	// 「.obj」のファイル名
	wchar_t* m_file;
	// ポリゴンの情報
	std::list<Collision::Triangle> m_triangles;
	// ファイルが見つかったフラグ
	bool m_isFile;

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugMesh> m_obj;
};
