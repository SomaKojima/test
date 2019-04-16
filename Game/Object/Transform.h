#pragma once

#include <list>

/// <summary>
/// 変形のクラス
/// </summary>
class Transform
{
public:
	// コンストラクタ
	Transform();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);



	// ワールド座標を取得する
	DirectX::SimpleMath::Vector3 LocalPos() { return GetWorldToLocal(m_worldPos, m_parent->WorldPos()); }
	void LocalPos(DirectX::SimpleMath::Vector3& pos) { m_worldPos = SetLocalToWorld(pos); }

	// ワールド座標の向きを取得する
	DirectX::SimpleMath::Quaternion LocalDir();

	// ワールド座標のマトリクスを取得する
	DirectX::SimpleMath::Matrix LocalMatrix();


	// ワールド座標を座標を取得
	DirectX::SimpleMath::Vector3 WorldPos() { return m_worldPos; }
	void WorldPos(DirectX::SimpleMath::Vector3& pos) { 
		UpdateChildPos(m_worldPos - pos);
		m_worldPos = pos; 
	}

	// ワールド速度を取得
	DirectX::SimpleMath::Vector3 WorldVel() { return m_worldVel; }
	void WorldVel(DirectX::SimpleMath::Vector3& vel) { m_worldVel = vel; }

	// ワールド加速度を取得
	DirectX::SimpleMath::Vector3 WorldAccel() { return m_worldAccel; }
	void WorldAccel(DirectX::SimpleMath::Vector3& accel) { m_worldAccel = accel; }

	// ワールド向きを取得
	DirectX::SimpleMath::Quaternion WorldDir() { return m_worldDir; }
	void WorldDir(DirectX::SimpleMath::Quaternion& dir) { 

		m_worldDir = dir; 
	}

	// ワールドマトリクス取得
	DirectX::SimpleMath::Matrix WorldMatrix() { return m_worldMatrix; }
	void WorldMatrix(DirectX::SimpleMath::Matrix& matrix) { m_worldMatrix = matrix; }

	// 大きさを取得
	float CollisionSize() { return m_collisionSize; }
	void CollisionSize(float size) { m_collisionSize = size; }

	/// <summary>
	/// 子供のリストに追加する
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

private:
	// 座標・速度・加速度のローカル座標の取得の計算
	DirectX::SimpleMath::Vector3 GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld);
	// 座標・速度・加速度のローカル座標の設定の計算
	DirectX::SimpleMath::Vector3 SetLocalToWorld(DirectX::SimpleMath::Vector3& local);

	// 子の座標を更新する
	void UpdateChildPos(DirectX::SimpleMath::Vector3& pos);
	// 子の向きを更新する
	void UpdateChildDir(DirectX::SimpleMath::Vector3& dir);
	// 子供のマトリクスを更新する
	void UpdateChildMatrix(float elapsedTime);

private:
	DirectX::SimpleMath::Vector3 m_worldPos;		// 座標

	DirectX::SimpleMath::Vector3 m_worldVel;		// 速度
	DirectX::SimpleMath::Vector3 m_worldAccel;		// 加速度
	DirectX::SimpleMath::Quaternion m_worldDir;		// 向き
	DirectX::SimpleMath::Matrix m_worldMatrix;		// マトリクス
	float m_collisionSize;

private:						
	Transform* m_parent;					// 親の情報
	std::list<Transform*> m_childList;		// 子供のリストの情報
};