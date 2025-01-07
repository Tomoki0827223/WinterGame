
#pragma once
#include <Model.h>
#include "MathUtilityForText.h"
#include "WorldTransform.h"

class Enemy;

class EnemyBoss;

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Destroy();

	~PlayerBullet();

	Vector3 GetWorldPosition();

	//// AABBを取得する関数
	//AABB GetAABB();

	void OnCollision(const EnemyBoss* enemy);

	void OnCollision(const Enemy* enemy);

	bool IsDead() const { return isDead_; }

private:
	float radius_;
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	Vector3 velocity_;
	bool isActive_ = true;
	bool isDead_ = false;
	static const int32_t kLifeTime = 60;
	int32_t deathTimer_ = kLifeTime;
};