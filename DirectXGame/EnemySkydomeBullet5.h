#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

class EnemySkydomeBullet5 {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	Vector3 GetWorldPosition();

	void Update();

	void OnCollision(const Player* player__);

	void Draw(const ViewProjection& viewProjection);

	~EnemySkydomeBullet5();

	bool IsDead() const { return isDead_; }

	const std::list<Player*>& GetBullets() const { return player_; }

private:
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;
	// uint32_t textureHandle_ = 0;
	Vector3 velocity_;

	std::list<Player*> player_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 3;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};
