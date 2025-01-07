#include "Enemy.h"
#include "EnemySkydome3.h"
#include "Player.h"

void EnemySkydome3::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos) {
	assert(model);
	model_ = model;
	vieProjection_ = viewProjection;
	modelbullet_ = Model::CreateFromOBJ("EnemySkydomeTama1_", true);
	worldtransfrom_.translation_ = pos;
	worldtransfrom_.Initialize();
}

void EnemySkydome3::Update() {
	Fire();

	// 弾更新
	for (EnemySkydomeBullet3* bullet : bullets3_) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets3_.remove_if([](EnemySkydomeBullet3* bullet) {
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

void EnemySkydome3::OnCollision() {}

void EnemySkydome3::Draw() {
	model_->Draw(worldtransfrom_, *vieProjection_);

	for (EnemySkydomeBullet3* bullet : bullets3_) {
		bullet->Draw(*vieProjection_);
	}
}

EnemySkydome3::~EnemySkydome3() {
	delete modelbullet_;
	for (EnemySkydomeBullet3* bullet : bullets3_) {
		delete bullet;
	}
}

void EnemySkydome3::Fire() {
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
		EnemySkydomeBullet3* newBullet = new EnemySkydomeBullet3();
		newBullet->Initialize(modelbullet_, moveBullet, velocity);

		// 弾を登録する
		bullets3_.push_back(newBullet);

		spawnTimer = kFireInterval;
	}
}

Vector3 EnemySkydome3::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}
