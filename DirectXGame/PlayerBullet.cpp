#include "PlayerBullet.h"
#include <cassert>
#include <TextureManager.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void PlayerBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection); 
}

void PlayerBullet::Destroy() {
	// バレットを無効化する処理
	isActive_ = false;

	// メモリ解放が必要な場合
	//delete this; // ただし、呼び出し元での管理方法によって注意が必要
}

PlayerBullet::~PlayerBullet() 
{ 
	//delete model_;
}

Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列から平行移動成分を取り出す
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

//AABB PlayerBullet::GetAABB() 
//{
//	Vector3 worldPos = GetWorldPosition();
//
//	AABB aabb;
//	aabb.min = {worldPos.x - radius_, worldPos.y - radius_, worldPos.z - radius_};
//	aabb.max = {worldPos.x + radius_, worldPos.y + radius_, worldPos.z + radius_};
//	return aabb;
//
//	return aabb;
//}

void PlayerBullet::OnCollision(const Enemy* enemy) {
	(void)enemy;

	isDead_ = true;
}

void PlayerBullet::OnCollision(const EnemyBoss* enemy) {
	(void)enemy;
	
	isDead_ = true;
}