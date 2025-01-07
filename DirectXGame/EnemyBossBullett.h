#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"

class Player;

class EnemyBossBullett {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void OnCollision(const Player* player);

	void Draw(const ViewProjection& viewProjection);

	~EnemyBossBullett();

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition();

private:
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;
	Vector3 velocity_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 3;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};
