#include "EnemySkydomeBullet.h"
#include <cassert>

void EnemySkydomeBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
{
	assert(model);
	model_ = model;
	worldtransfrom_.translation_ = position;
	worldtransfrom_.Initialize();
	velocity_ = velocity;
}

Vector3 EnemySkydomeBullet::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void EnemySkydomeBullet::Update() 
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldtransfrom_.translation_.x += velocity_.x;
	worldtransfrom_.translation_.y += velocity_.y;
	worldtransfrom_.translation_.z += velocity_.z;

	worldtransfrom_.UpdateMatrix();
}

void EnemySkydomeBullet::OnCollision(const Player* player__) 
{ 
	(void)player__;

	isDead_ = true;
}

void EnemySkydomeBullet::Draw(const ViewProjection& viewProjection) 
{
	// モデルの描画
	model_->Draw(worldtransfrom_, viewProjection);
}

EnemySkydomeBullet::~EnemySkydomeBullet() { model_ = nullptr; }
