/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../SubGame.h"
//#include "BoxCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">半径</param>
CollisionSphere::CollisionSphere(DirectX::SimpleMath::Vector3 center, float radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_sphere.radius = radius;
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Update(float elapsedTime)
{
	CollisionComponent::Update(elapsedTime);
}

void CollisionSphere::LateUpdate(float elapsedTime)
{
	m_sphere.center = Vector3::Transform(m_center, (m_gameObject->GetTransform().WorldMatrix()));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void CollisionSphere::Render()
{
	Matrix world = m_gameObject->GetTransform().WorldMatrix() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().m_game->GetDevice(), m_center, m_radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().m_game;
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void CollisionSphere::Finalize()
{
	m_obj.reset();
}



void CollisionSphere::HitBack(const Collision::Triangle * triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 速度で壁刷りを行う
	 Vector3 w_vec_vel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().LocalVel());
	 m_gameObject->GetTransform().LocalVel(w_vec_vel);
	// 座標の更新
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	pos += Vector3::Transform(w_vec_vel, m_gameObject->GetTransform().WorldDir());
	m_gameObject->GetTransform().LocalPos(pos);

	// 加速度を壁刷りを行った速度にする
	Vector3 w_vec_accel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().LocalAccel());
	m_gameObject->GetTransform().LocalAccel(w_vec_accel);
}


/// <summary>
/// 壁刷りの計算
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3& CollisionSphere::WallCulc(const Collision::Triangle * triangle, Vector3 & hitPos, SimpleMath::Vector3 vel)
{
	// 速度を取得
	Vector3 vec = vel;

	// 面の法線
	Vector3 normal(triangle->plane.a, triangle->plane.b, triangle->plane.c);

	// 法線の向きのベクトルをなくす(プレイヤーの向きに合わせる・ローカル座標にする)
	Quaternion q;
	m_gameObject->GetTransform().WorldDir().Conjugate(q);

	// 壁ずり
	Vector3 normal2 = Vector3::Transform(normal, q);

	float l = vec.Dot(normal2);
	Vector3 w_vec;
	if (l <= 0)
	{
		w_vec = vec - l * normal2;
	}
	else
	{
		w_vec = vec;
	}

	return w_vec;

	// 座標の更新
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	pos += Vector3::Transform(w_vec, m_gameObject->GetTransform().WorldDir());
}

