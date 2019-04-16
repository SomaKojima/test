
#pragma once

#include "CollisionComponent.h"
#include "DebugCollision/DebugMesh.h"
#include "Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionMesh : public CollisionComponent
{
public:
	CollisionMesh(wchar_t* file);
	~CollisionMesh();

	// �X�V
	void Update(float elapsedTime) override;
	// �x���X�V
	void LateUpdate(float elapsedTime) override;
	// �`��
	void Render() override;
	// �I��
	void Finalize() override;

	// �|���S���̏����擾
	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangles; }

	// �`�̏��
	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	// �u.obj�v�̃t�@�C����
	wchar_t* m_file;
	// �|���S���̏��
	std::list<Collision::Triangle> m_triangles;
	// �t�@�C�������������t���O
	bool m_isFile;

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugMesh> m_obj;
};
