/// <summary>
/// Collision.cpp
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "../Object/GameObject.h"
#include "Collision.h"
#include "CollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX::SimpleMath;

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::HitCheck_Sphere_Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::SimpleMath::Vector3* hit_pos)
{
	if (!&sphere || !&sphere2) return false;

	// ���S�Ԃ̋����̕������v�Zf
	DirectX::SimpleMath::Vector3 d = sphere.center - sphere2.center;
	float dist2 = d.Dot(d);

	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
	float radiusSum = sphere.radius + sphere2.radius;
	if (dist2 < radiusSum * radiusSum)
	{
		/*if (hit_pos)
		{
			float l = (sphere.radius + sphere2.radius) - sqrtf(dist2);
			d.Normalize();
			*hit_pos += (d * l);
		}*/
		return true;
	}
	return false;
}

bool Collision::HitCheck_Segment_Plane(const Segment & segment, const Plane & plane, DirectX::SimpleMath::Vector3 * hit_pos)
{
	if (!&segment || !&plane) return false;

	// �����n�_�ƕ��ʂ̋������v�Z
	float length = Plane_Length(plane, segment.pos);
	// �����x�N�g���̒�����2����v�Z
	float vec_length = segment.vec.Dot(segment.vec);
	// ��΂ɓ͂��Ȃ��ꍇ�͏I��
	if (vec_length < (length * length)) return false;
	// �����x�N�g���̐��K������
	float vec_length_nomalize = sqrtf(vec_length);
	// cos�Ƃ���ς𗘗p���ċ��߂�
	Vector3 vec = segment.vec * (1.0f / vec_length_nomalize);
	float cos_theta = vec.Dot(Vector3(-plane.a, -plane.b, -plane.c));
	// ���������ʂɓ͂��������v�Z
	float plane_vec_length = length / cos_theta;
	// �͂��Ă��Ȃ�
	if (plane_vec_length > vec_length) return false;
	// ��_���v�Z
	if (hit_pos)
	{
		*hit_pos = segment.pos + (vec * plane_vec_length);
	}
	return true;
}

bool Collision::HitCheck_Segment_Sphere(const Segment & segment, const Sphere & sphere, DirectX::SimpleMath::Vector3 * hit_pos)
{
	if (!&segment || !&sphere) return false;

	// (2��������) = at^2 + bt + c = 0;
	// 2���������ɂ�����a,b,c���v�Z
	float xa = segment.pos.x - sphere.center.x;
	float ya = segment.pos.y - sphere.center.y;
	float za = segment.pos.z - sphere.center.z;

	// vec = �����̑��x

	// (a) = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	float a = segment.vec.x * segment.vec.x + segment.vec.y * segment.vec.y + segment.vec.z * segment.vec.z;
	// (b) = 2(vec.x * xa + vec.y * ya * vec.z * za);
	float b = 2.0f * (segment.vec.x * xa + segment.vec.y * ya + segment.vec.z * za);
	// (c) = xa^2 + ya^2 + za^2 - radius^2;
	float c = xa * xa + ya * ya + za * za - sphere.radius * sphere.radius;

	// 2���������������Ȃ��Ɣ��f�����Ƃ��͏Փ˂��Ă��Ȃ��Ƃ݂Ȃ�
	float d = b * b - 4.0f * a * c;
	if (d < 0.0f) return false;

	// ���̌���������
	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t)) t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t)) t = t1;

	if (t > 1.0f) return false;

	// ��_���v�Z
	if (hit_pos)
	{
		*hit_pos = segment.pos + (segment.vec * t);
	}
	return true;
}

bool Collision::HitCheck_Segment_Triangle(const Segment & segment, const Triangle & triangle, DirectX::SimpleMath::Vector3 * hit_pos)
{
	if (!&segment || !&triangle) return false;

	// �O�p�`�̕��ʂƃ`�F�b�N
	Vector3 tmp_hit_pos;
	if (!HitCheck_Segment_Plane(segment, triangle.plane, &tmp_hit_pos)) return false;
	if (!Triangle_CheckInner(triangle, tmp_hit_pos))
	{
		// �O��
		return false;
	}
	else
	{
		// ����
		if (hit_pos)
		{
			*hit_pos = tmp_hit_pos;
		}
		return true;
	}
}

bool Collision::Triangle_CheckInner(const Triangle & triangle, DirectX::SimpleMath::Vector3& point)
{
	if (!&triangle) return false;

	Vector3 AB = triangle.pos[1] - triangle.pos[0];
	Vector3 BP = point - triangle.pos[1];

	Vector3 BC = triangle.pos[2] - triangle.pos[1];
	Vector3 CP = point - triangle.pos[2];

	Vector3 CA = triangle.pos[0] - triangle.pos[2];
	Vector3 AP = point - triangle.pos[0];

	Vector3 c1 = AB.Cross(BP);
	Vector3 c2 = BC.Cross(CP);
	Vector3 c3 = CA.Cross(AP);


	//���ςŏ��������t���������ׂ�
	double dot_12 = c1.Dot(c2);
	double dot_13 = c1.Dot(c3);

	if (dot_12 > 0 && dot_13 > 0) {
		//�O�p�`�̓����ɓ_������
		return true;
	}
	return false;
}

bool Collision::HitCheck_Sphere_Plane(const Sphere & sphere, const Plane & plane, DirectX::SimpleMath::Vector3* hit_pos)
{
	if (!&sphere || !&plane) return false;

	float length = Plane_Length(plane, sphere.center);
	if (length > sphere.radius) return false;
	
	// ��_���v�Z
	if (hit_pos)
	{
		length = sphere.radius - length;
		*hit_pos = Vector3(plane.a, plane.b, plane.c) * length;
	}
	return true;
}

bool Collision::HitCheck_Sphere_Triangle(const Sphere & sphere, const Triangle & triangle, DirectX::SimpleMath::Vector3 * hit_pos)
{
  	if (!&sphere || !&triangle) return false;

	if (!HitCheck_Sphere_Plane(sphere, triangle.plane, hit_pos)) return false;

	// �O�p�`�̕ӂ̓����蔻��
	Vector3 vec;
	vec = triangle.pos[1] - triangle.pos[0];
	Segment segment = Segment{Vector3(triangle.pos[0]), Vector3(vec)};
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos))
	{
		return true;
	}

	vec = triangle.pos[2] - triangle.pos[1];
	segment = Segment{ Vector3(triangle.pos[1]), Vector3(vec) };
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos))
	{
		return true;
	}

	vec = triangle.pos[0] - triangle.pos[2];
	segment = Segment{ Vector3(triangle.pos[2]), Vector3(vec) };
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos))
	{
		return true;
	}

	// �����O�p�`�̒����ɂ߂荞�ނ��ǂ���
	vec = Vector3(-triangle.plane.a * sphere.radius, -triangle.plane.b * sphere.radius, -triangle.plane.c * sphere.radius);
	segment = Segment{ Vector3(sphere.center), Vector3(vec) };
	if (HitCheck_Segment_Triangle(segment, triangle, hit_pos))
	{
		return true;
	}

	return false;
}

/// <summary>
/// �����蔻��̌`�𔻒f���ē����蔻����s���֐�
/// </summary>
/// <param name="collision">�����蔻��̌`�P</param>
/// <param name="collision2">�����蔻��̌`�Q</param>
/// <param name="data">�����蔻��̌`�Q���P�̃I�u�W�F�N�g�ɓn���p�̃o�b�t�@</param>
/// <param name="data2">�����蔻��̌`�P���Q�̃I�u�W�F�N�g�ɓn���p�̃o�b�t�@</param>
/// <returns>�����蔻��</returns>
bool Collision::CheckOne(CollisionComponent* collision, CollisionComponent* collision2, CollisionData* data, CollisionData* data2)
{
	const Sphere* sphere = collision->GetSphere();
	const Plane* plane = collision->GetPlane();
	const Triangle* triangle = collision->GetTriangle();
	const list<Triangle>* triangleList = collision->GetTriangleList();

	if (data2)
	{
		data2->sphere = sphere;
		data2->plane = plane;
		data2->triangle = triangle;
	}

	if (sphere)		return CheckTwo(sphere, collision2, data);
	if (plane)		return CheckTwo(plane, collision2, data);
	if (triangle)	return CheckTwo(triangle, collision2, data);

	if (triangleList)
	{
		bool flag = false;
		for (auto ite = triangleList->begin(); ite != triangleList->end(); ite++)
		{
			if (CheckTwo(&(*ite), collision2, data))
			{
				if (data2) data2->triangleList.push_back(&(*ite));
				flag = true;
			}
		}
		return flag;
	}

	return false;
}

/// <summary>
/// �����蔻������߂�
/// </summary>
/// <param name="entity">����</param>
/// <param name="repulsionVel">�������x</param>
/// <returns>�����蔻��</returns>
bool Collision::HitCheck(GameObject * entity, GameObject* entity2, CollisionData *data, CollisionData* data2)
{
	if(!entity || !entity2)
	{
		return false;
	}

	list<CollisionComponent*> collisionList1 = entity->GetComponentList<CollisionComponent>();
	list<CollisionComponent*> collisionList2 = entity2->GetComponentList<CollisionComponent>();

	for (auto ite = collisionList1.begin(); ite != collisionList1.end(); ite++)
	{
		for (auto ite2 = collisionList2.begin(); ite2 != collisionList2.end(); ite2++)
		{
			// ��
			if (CheckOne((*ite), (*ite2), data, data2))
			{
				// ��������
				(*ite)->SetHit(true);
				(*ite2)->SetHit(true);

				// ���������ꏊ�̃f�[�^�����L
				data2->hitPos = data->hitPos;
				return true;
			}
		}
	}
	return false;
}
