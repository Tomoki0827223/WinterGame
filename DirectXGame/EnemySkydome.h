#pragma once
#include "Model.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "EnemySkydomeBullet.h"

class EnemySkydome 
{
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos);
	void Update();
	void OnCollision();
	void Draw();

	~EnemySkydome();
	
	void Fire();

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemySkydomeBullet*>& GetBullets() const { return bullets_; }

	// 発射間隔
	static const int kFireInterval = 120;

private:
	
	WorldTransform worldtransfrom_;
	Model* model_ = nullptr;
	
	ViewProjection* vieProjection_ = nullptr;

	Model* modelbullet_ = nullptr;

	// 弾
	std::list<EnemySkydomeBullet*> bullets_;

	// 発射タイマー
	int32_t spawnTimer = 0;

	Player* player_ = nullptr;

	//Phase phase_ = Phase::Approach;

	//Phase Bulletphase_ = Phase::Approach;
};
