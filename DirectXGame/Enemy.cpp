#include "Enemy.h"
#include <cassert>
#include <numbers>

Enemy::~Enemy() {
	delete modelbullet_;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, Player* player) {
	// モデル変数に記録
	model_ = model;
	viewProjection_ = viewProjection;
	player_ = player;

	modelbullet_ = Model::CreateFromOBJ("deathParticle", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;

	// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	// 時間を設定する
	walkTimer_ = 0.0f;
}

void Enemy::Fire() {

	assert(player_);

	spawnTimer--;

	if (spawnTimer < -0.0f) {

		Vector3 moveBullet = worldTransform_.translation_;

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
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(modelbullet_, moveBullet, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);

		spawnTimer = kFireInterval;
	}
}

void Enemy::Update() {

	Fire();

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	//// 回転アニメーション
	//// タイマーを加算
	//walkTimer_ += 1.0f / 60.0f;
	//worldTransform_.rotation_.x = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);

	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Enemy::SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }

void Enemy::Draw() {

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(*viewProjection_);
	}

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	//  ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

// AABB Enemy::GetAABB() {
//	Vector3 worldPos = GetWorldPosition();
//
//	AABB aabb;
//
//	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
//	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
//
//	return aabb;
// }

void Enemy::OnCollision(const Player* player) { (void)player; }

void Enemy::OnCollision(const PlayerBullet* playerBullet) {
	(void)playerBullet;

	EnemyIsDead_ = true;
}
