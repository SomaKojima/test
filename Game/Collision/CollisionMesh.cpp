
#include <fstream>
#include "../../pch.h"
#include "CollisionMesh.h"
#include "../SubGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CollisionMesh::CollisionMesh(wchar_t * file)
	:
	m_file(file),
	m_isFile(false)
{
	// obj形式のファイル読み込み
	std::vector<Vector3> vertexes;
	std::vector<int> indexes;
	std::ifstream ifs(file);
	if (!ifs)
	{
		ifs.close();
		return;
	}
	m_isFile = true;
	std::string str;
	while (getline(ifs, str))
	{
		// 頂点
		if (str[0] == 'v')
		{
			Vector3 val;
			sscanf_s(str.data(), "v  %f %f %f", &val.x, &val.y, &val.z);
			vertexes.push_back(val);
		}
		// インデックス
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する
			if (a != b && a != c && b != c)
			{
				indexes.push_back(a - 1);
				indexes.push_back(c - 1);
				indexes.push_back(b - 1);
			}
		}
	}
	ifs.close();

	for (size_t i = 0; i < indexes.size() / 3; i++)
	{
		Collision::Triangle triangle;
		triangle.Set_Triangle(vertexes[indexes[i * 3 + 2]], vertexes[indexes[i * 3 + 1]], vertexes[indexes[i * 3]]);
		m_triangles.push_back(Collision::Triangle(triangle));
	}
}

CollisionMesh::~CollisionMesh()
{
}

void CollisionMesh::Update(float elapsedTime)
{
	CollisionComponent::Update(elapsedTime);
}

void CollisionMesh::LateUpdate(float elapsedTime)
{
}

void CollisionMesh::Render()
{
	if (m_obj == nullptr && m_isFile)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugMesh>(SubGame::GetInstace().m_game->GetDevice(), m_file);
	}
	else if(m_obj)
	{
		Game* game = SubGame::GetInstace().m_game;
		m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

void CollisionMesh::Finalize()
{
	m_obj.reset();
}
