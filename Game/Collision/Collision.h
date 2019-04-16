/// <summary>
/// Collision.h
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
//#include "../Component/Collision/CollisionComponent.h"

/// <summary>
/// �O���錾
/// </summary>
class GameObject;
class CollisionComponent;
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collision
{
	/// <summary>
	/// �`��̒�`
	/// </summary>
public:
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	// ���S���W
		float radius;	// ���a
	};
	struct Segment
	{
		DirectX::SimpleMath::Vector3 pos;		// �n�_
		DirectX::SimpleMath::Vector3 vec;		// �x�N�g��
	};
	struct Plane
	{
		void Set_Plane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
		{
			// �@���𐳋K�����Ă���
			normal.Normalize();
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		void Set_Plane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// �@�������߂�
			DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
			DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

			DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);
			Set_Plane(normal, pos1);
		}
		void Set_Plane(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point)
		{
			DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, dir);

			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		float a, b, c, d;		// ABC�@���@�@��
	};
	struct Triangle
	{
		void Set_Triangle(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 3�_�𗘗p�������ʂ����߂�
			plane.Set_Plane(pos1, pos2, pos3);
			startPos[0] = pos1;
			startPos[1] = pos2;
			startPos[2] = pos3;
			for (int i = 0; i < 3; i++)
			{
				pos[i] = startPos[i];
			}
		}
		void Set_Triangle(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Quaternion dir)
		{
			pos[0] = DirectX::SimpleMath::Vector3::Transform(startPos[0], world);
			pos[1] = DirectX::SimpleMath::Vector3::Transform(startPos[1], world);
			pos[2] = DirectX::SimpleMath::Vector3::Transform(startPos[2], world);

			plane.Set_Plane(dir, pos[0]);
		}
		DirectX::SimpleMath::Vector3 pos[3];
		DirectX::SimpleMath::Vector3 startPos[3];
		Plane plane;
	};

	/// <summary>
	/// �f�[�^�̒�`
	/// </summary>
public:

	enum CollisionType
	{
		NONE = 0,
		SPHERE = 1 << 1,
		SEGMENT = 1 << 2,
		PLANE = 1 << 3,
		TRIANGLE = 1 << 4,

		COLLISION_MAX
	};

	class CollisionData
	{
	public:
		DirectX::SimpleMath::Vector3 hitPos;
		const Sphere* sphere;
		const Segment* segment;
		const Plane* plane;
		const Triangle* triangle;
		std::list<const Triangle*> triangleList;

		CollisionData() :sphere(nullptr), segment(nullptr), plane(nullptr), triangle(nullptr) {}
	};
public:
	/// <summary>
	/// �����蔻��̎��̌�
	/// </summary>
	template<class T, class T2>
	static bool HitCheck(const T& shape, const T2& shape2, DirectX::SimpleMath::Vector3* hit_pos = nullptr) 
	{ 
		return false; 
	}

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	static bool HitCheck_Sphere_Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::SimpleMath::Vector3* hit_pos = nullptr);

	template<>
	static bool HitCheck<Sphere, Sphere>(const Sphere& sphere, const Sphere& sphere2, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Sphere_Sphere(sphere, sphere2, hit_pos);
	}

	/// <summary>
	/// �����ƕ��ʂ̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Plane(const Segment& segment, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);

	template<>
	static bool HitCheck<Segment, Plane>(const Segment& segment, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Plane(segment, plane, hit_pos);
	}
	template<>
	static bool HitCheck<Plane, Segment>(const Plane& plane, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Plane(segment, plane, hit_pos);
	}

	/// <summary>
	/// �����Ƌ��̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Sphere(const Segment& segment, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	template<>
	static bool HitCheck<Segment, Sphere>(const Segment& segment, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Sphere(segment, sphere, hit_pos);
	}
	template<>
	static bool HitCheck<Sphere, Segment>(const Sphere& sphere, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Sphere(segment, sphere, hit_pos);
	}

	/// <summary>
	/// �����ƎO�p�`�̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Triangle(const Segment& segment, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	template<>
	static bool HitCheck<Segment, Triangle>(const Segment& segment, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Triangle(segment, triangle, hit_pos);
	}
	template<>
	static bool HitCheck<Triangle, Segment>(const Triangle& triangle, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Segment_Triangle(segment, triangle, hit_pos);
	}

	// �O�p�`�̔C�ӂ̓_���O�p�`���ɑ��݂��邩�ǂ���
	static bool Triangle_CheckInner(const Triangle& triangle, DirectX::SimpleMath::Vector3& point);

	// ���ƕ��ʂ̓����蔻��
	static bool HitCheck_Sphere_Plane(const Sphere& sphere, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	template<>
	static bool HitCheck<Sphere, Plane>(const Sphere& sphere, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Sphere_Plane(sphere, plane, hit_pos);
	}
	template<>
	static bool HitCheck<Plane, Sphere>(const Plane& plane, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Sphere_Plane(sphere, plane, hit_pos);
	}

	// ���ƎO�p�`�̏Փ˔���
	static bool HitCheck_Sphere_Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	template<>
	static bool HitCheck<Sphere, Triangle>(const Sphere& sphere, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Sphere_Triangle(sphere, triangle, hit_pos);
	}
	template<>
	static bool HitCheck<Triangle, Sphere>(const Triangle& triangle, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos)
	{
		return HitCheck_Sphere_Triangle(sphere, triangle, hit_pos);
	}

	/// <summary>
	/// ���ʂ̕�����
	/// </summary>
	/// <param name="plane">����</param>
	/// <param name="p">�_</param>
	/// <returns>���ʂƓ_�̋���</returns>
	static float Plane_Length(const Plane& plane, const DirectX::SimpleMath::Vector3& p)
	{
		float l;
		l = plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d;
		return l;
	}

public:
	Collision();
	~Collision();
	
private:
	static bool CheckOne(CollisionComponent* collision, CollisionComponent* collision2, CollisionData* data, CollisionData* data2);
	template<class T>
	static bool CheckTwo(const T* shape, CollisionComponent* collision, CollisionData* data);

public:
	static bool HitCheck(GameObject* entity, GameObject* entity2, CollisionData* data, CollisionData* data2);
};


/// <summary>
/// �����蔻��̌`�𔻒f���ē����蔻����s���֐�
/// </summary>
/// <param name="shape">�����蔻��̌`�P</param>
/// <param name="collision2">�����蔻��̌`�Q</param>
/// <param name="data">�����蔻��̌`�Q���P�̃I�u�W�F�N�g�ɓn���p�̃o�b�t�@</param>
/// <returns>�����蔻��</returns>
template<class T>
inline bool Collision::CheckTwo(const T * shape, CollisionComponent * collision, CollisionData* data)
{
	const Sphere* sphere = collision->GetSphere();
	const Plane* plane = collision->GetPlane();
	const Triangle* triangle = collision->GetTriangle();
	const list<Triangle>* triangleList = collision->GetTriangleList();

	if (data)
	{
		data->sphere = sphere;
		data->plane = plane;
		data->triangle = triangle;
	}

	if (sphere) return HitCheck(*sphere, *shape, &data->hitPos);
	if (plane)return HitCheck(*plane, *shape, &data->hitPos);
	if (triangle)return HitCheck(*triangle, *shape, &data->hitPos);

	if (triangleList)
	{
		bool flag = false;
		for (auto ite = triangleList->begin(); ite != triangleList->end(); ite++)
		{
			triangle = &(*ite);
			if (HitCheck(*triangle, *shape, &data->hitPos))
			{
				if (data) data->triangle = &(*ite);
				return true;
			}
		}
	}
	return false;
}
