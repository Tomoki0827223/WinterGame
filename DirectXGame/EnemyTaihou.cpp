// #include "EnemyTaihou.h"
// #include <cassert>
//
// void EnemyTaihou::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos)
//{
//	assert(model);
//	model_ = model;
//	vieProjection_ = viewProjection;
//	modelbullet_ = Model::CreateFromOBJ("EnemySkydomeTama_", true);
//	worldtransfrom_.translation_ = pos;
//	worldtransfrom_.Initialize();
// }
//
// Vector3 EnemyTaihou::GetWorldPosition() {
//	// ワールド座標を入れる変数
//	Vector3 worldPos;
//	// ワールド行列の平行移動成分を取得（ワールド座標）
//	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
//	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
//	worldPos.z = worldtransfrom_.matWorld_.m[3][2];
//
//	return worldPos;
// }
//
// void EnemyTaihou::Update()
//{
//	Fire();
//
//	// 弾更新
//	for (EnemySkydomeBullet* bullet : bullets_) {
//		bullet->Update();
//	}
//
//	// デスフラグの立った弾を削除
//	bullets_.remove_if([](EnemySkydomeBullet* bullet) {
//		if (bullet->IsDead()) {
//			delete bullet;
//			return true;
//		}
//		return false;
//	});
//
//	// キャラクターの移動ベクトル
//	Vector3 move = {0, 0, 0};
//
//	Vector3 accessSpeed = {0.1f, 0.1f, 0.1f};
//
//	Vector3 eliminationSpeed = {0.3f, 0.3f, 0.3f};
//
//	worldtransfrom_.UpdateMatrix();
// }
//
// void EnemyTaihou::OnCollision(const Player* player__)
//{
//
// }
//
// void EnemyTaihou::Draw(const ViewProjection& viewProjection)
//{
//	model_->Draw(worldtransfrom_, *vieProjection_);
//
//	for (EnemySkydomBullet* bullet : bullets_) {
//		bullet->Draw(*vieProjection_);
//	}
// }
//
// EnemyTaihou::~EnemyTaihou()
//{
//
// }
