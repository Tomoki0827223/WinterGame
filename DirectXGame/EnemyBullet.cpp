#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
{
	model_ = model;
	worldtransfrom_.Initialize();
	worldtransfrom_.translation_ = position;
	velocity_ = velocity;
}

void EnemyBullet::Update() 
{
	worldtransfrom_.translation_ += velocity_;

	deathTimer_--;
	if (deathTimer_ < 0) {
		isDead_ = true;
	}
	worldtransfrom_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) 
{ 
	model_->Draw(worldtransfrom_, viewProjection); 
}

EnemyBullet::~EnemyBullet() 
{ 
}
