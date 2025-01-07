#include "Enemy.h"
#include "EnemySkydome2.h"
#include "Player.h"

void EnemySkydome2::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos) {
	assert(model);
	model_ = model;
	vieProjection_ = viewProjection;
	modelbullet_ = Model::CreateFromOBJ("EnemySkydomeTama1_", true);
	worldtransfrom_.translation_ = pos;
	worldtransfrom_.Initialize();
}

void EnemySkydome2::Update() {
	Fire();

	// 弾更新
	for (EnemySkydomeBullet2* bullet : bullets2_) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets2_.remove_if([](EnemySkydomeBullet2* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	Vector3 accessSpeed = {0.1f, 0.1f, 0.1f};

	Vector3 eliminationSpeed = {0.3f, 0.3f, 0.3f};

	worldtransfrom_.UpdateMatrix();
}

void EnemySkydome2::OnCollision() {}

void EnemySkydome2::Draw() {
	model_->Draw(worldtransfrom_, *vieProjection_);

	for (EnemySkydomeBullet2* bullet : bullets2_) {
		bullet->Draw(*vieProjection_);
	}
}

EnemySkydome2::~EnemySkydome2() {
	delete modelbullet_;
	for (EnemySkydomeBullet2* bullet : bullets2_) {
		delete bullet;
	}
}

void EnemySkydome2::Fire() {
	assert(player_);

	spawnTimer--;

	if (spawnTimer < -0.0f) {

		Vector3 moveBullet = worldtransfrom_.translation_;

		// 弾の速度
		const float kBulletSpeed = -3.0f;

		Vector3 velocity(0, 0, 0);

		Vector3 playerWorldtransform = player_->GetWorldPosition();
		Vector3 enemyWorldtransform = GetWorldPosition();
		Vector3 homingBullet = enemyWorldtransform - playerWorldtransform;
		homingBullet = Normalize(homingBullet);
		velocity.x += kBulletSpeed * homingBullet.x;
		velocity.y += kBulletSpeed * homingBullet.y;
		velocity.z += kBulletSpeed * homingBullet.z;

		// 弾を生成し、初期化
		EnemySkydomeBullet2* newBullet = new EnemySkydomeBullet2();
		newBullet->Initialize(modelbullet_, moveBullet, velocity);

		// 弾を登録する
		bullets2_.push_back(newBullet);

		spawnTimer = kFireInterval;
	}
}

Vector3 EnemySkydome2::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}
