#pragma once
#include "EnemyBullet.h"
#include "EnemySkydomeBullet1.h"
#include "Model.h"
#include "Player.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemySkydome1 {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos);
	void Update();
	void OnCollision();
	void Draw();

	~EnemySkydome1();

	void Fire();

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemySkydomeBullet1*>& GetBullets() const { return bullets1_; }

	// 発射間隔
	static const int kFireInterval = 120;

private:
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;

	ViewProjection* vieProjection_ = nullptr;

	Model* modelbullet_ = nullptr;

	// 弾
	std::list<EnemySkydomeBullet1*> bullets1_;

	// 発射タイマー
	int32_t spawnTimer = 0;

	Player* player_ = nullptr;

	// Phase phase_ = Phase::Approach;

	// Phase Bulletphase_ = Phase::Approach;
};
