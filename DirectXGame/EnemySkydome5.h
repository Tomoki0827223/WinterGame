#pragma once
#include "EnemyBullet.h"
#include "EnemySkydomeBullet5.h"
#include "Model.h"
#include "Player.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemySkydome5 {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos);
	void Update();
	void OnCollision();
	void Draw();

	~EnemySkydome5();

	void Fire();

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemySkydomeBullet5*>& GetBullets() const { return bullets5_; }

	// 発射間隔
	static const int kFireInterval = 120;

private:
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;

	ViewProjection* vieProjection_ = nullptr;

	Model* modelbullet_ = nullptr;

	// 弾
	std::list<EnemySkydomeBullet5*> bullets5_;

	// 発射タイマー
	int32_t spawnTimer = 0;

	Player* player_ = nullptr;

	// Phase phase_ = Phase::Approach;

	// Phase Bulletphase_ = Phase::Approach;
};
