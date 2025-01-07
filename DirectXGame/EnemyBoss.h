#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "affine.h"

class Player;
class EnemyBossBullett;

class EnemyBoss {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos);
	void Update();
	void OnCollision();
	void Draw();
	~EnemyBoss();
	void Fire();

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemyBossBullett*>& GetBullets() const { return bullets_; }

	// 発射間隔
	static const int kFireInterval = 1280;

private:
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	Model* modelbullet_ = nullptr;

	// 弾
	std::list<EnemyBossBullett*> bullets_;

	// 発射タイマー
	int32_t spawnTimer = 0;

	Player* player_ = nullptr;

	//Phase phase_ = Phase::Approach;

	//Phase Bulletphase_ = Phase::Approach;
};
