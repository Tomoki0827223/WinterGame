#define NOMINMAX
#include "Player.h"
#include "Input.h"
#include "MapChipField.h"
#include "MathUtilityForText.h"
#include <AABB.h>
#include <DebugText.h>
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numbers>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	// NULLチェック
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform2_.Initialize();
	worldTransform2_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform3_.Initialize();
	worldTransform3_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform4_.Initialize();
	worldTransform4_.scale_ = {0.5f, 0.5f, 0.5f};

	// 引数の内容をメンバ変数に記録
	model_ = model;
	// textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	soundSE_ = audio_->LoadWave("Audio/ItemGet.wav");
	shotSE_ = audio_->LoadWave("Audio/ShotSE.wav");

	// BulletModelの作成
	bulletmodel_ = Model::CreateFromOBJ("Bullet", true);
}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	MovePlayer();

	worldTransform2_.scale_ = {0.1f, 0.1f, 0.1f};
	worldTransform2_.rotation_.y += 0.1f;
	worldTransform3_.scale_ = {0.1f, 0.1f, 0.1f};
	worldTransform3_.rotation_.y += 0.1f;
	worldTransform4_.scale_ = {0.1f, 0.1f, 0.1f};
	worldTransform4_.rotation_.y += 0.1f;

	// if (itemCount >= 10) {
	worldTransform2_.translation_ = worldTransform_.translation_;
	worldTransform2_.translation_.y += 1;
	worldTransform3_.translation_ = worldTransform_.translation_;
	worldTransform3_.translation_.y += 2;
	worldTransform4_.translation_ = worldTransform_.translation_;
	worldTransform4_.translation_.y += 3;
	//}

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.movement = velocity_;
	collisionMapInfo.landingFlag = false;
	collisionMapInfo.wallContactFlag = false;
	// マップ衝突チェック
	CheckMapCollision(collisionMapInfo);

	JudgmentMove(collisionMapInfo);

	CeilingContact(collisionMapInfo);

	GraundSetting(collisionMapInfo);

	TurnControll();
	// 行列計算
	worldTransform_.UpdateMatrix();

	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_);

	MapChipType mapChipType;

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kGoal) {

		mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		isClear_ = true;
	}
	// ピースのチェック
	if (mapChipType == MapChipType::kATK) {
		itemCountATK += 1;
		mapChipField_->DeleteMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		soundFlag = true; // ピースを取得したときに音を再生するフラグを立てる
	}

	// ピースのチェック
	if (mapChipType == MapChipType::kHPup) {
		itemCount += 1;
		mapChipField_->DeleteMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		soundFlag = true; // ピースを取得したときに音を再生するフラグを立てる
	}

	// ピースのチェック
	if (mapChipType == MapChipType::kWeekPoint) {
		//itemCount += 1;
		mapChipField_->DeleteMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		soundFlag = true; // ピースを取得したときに音を再生するフラグを立てる
	}

	// 音の再生
	if (soundFlag) {
		// 音を再生
		soundSEHanlde_ = audio_->PlayWave(soundSE_, false, 1.0f);

		// 音を再生したらフラグをリセット
		soundFlag = false;
	}

	if (soundFlag == false) {
		audio_->StopWave(soundSE_);
	}

	// Rotate();
	Attack();

	worldTransform2_.UpdateMatrix();
	worldTransform3_.UpdateMatrix();
	worldTransform4_.UpdateMatrix();

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
	if (itemCount >= 10) {
		model_->Draw(worldTransform2_, *viewProjection_);
	}
	if (itemCount >= 20) {
		model_->Draw(worldTransform3_, *viewProjection_);
	}
	if (itemCount >= 30) {
		model_->Draw(worldTransform4_, *viewProjection_);
	}

	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(*viewProjection_);
	}
}

void Player::Attack() {

	ShotTimer_--;

	//if (input_->TriggerKey(DIK_SPACE)) {
	//	if (ShotTimer_ <= 0 && burstShotCount_ == 0) {
	//		// バースト開始時の準備
	//		ShotTimer_ = 60;                  // 次のバーストまでの待機時間
	//		burstShotCount_ = kMaxBurstShots; // バースト弾数のリセット
	//		burstTimer_ = 0;                  // バーストタイマーのリセット
	//	}
	//}

	//if (burstShotCount_ > 0) {
	//	// バースト発射中
	//	if (burstTimer_ <= 0) {
	//		// 弾を発射
	//		const float kBulletSpeed = 1.0f;
	//		Vector3 localDirection = {0.0f, 0.0f, kBulletSpeed};
	//		Vector3 velocity = TransformNormal(localDirection, worldTransform_.matWorld_);

	//		PlayerBullet* newBullet = new PlayerBullet();
	//		newBullet->Initialize(bulletmodel_, worldTransform_.translation_, velocity);
	//		bullets_.push_back(newBullet);

	//		// サウンド再生
	//		shotHandle_ = audio_->PlayWave(shotSE_, false, 1.0f);

	//		// 次の弾の準備
	//		burstShotCount_--;
	//		burstTimer_ = kBurstInterval; // バースト間隔のリセット
	//	} else {
	//		// バースト間隔タイマーのカウントダウン
	//		burstTimer_--;
	//	}
	//}

	//if (input_->PushKey(DIK_SPACE)) {
	//	
	//	// 弾を発射
	//	const float kBulletSpeed = 1.0f;
	//	Vector3 localDirection = {0.0f, 0.0f, kBulletSpeed};
	//	Vector3 velocity = TransformNormal(localDirection, worldTransform_.matWorld_);

	//	PlayerBullet* newBullet = new PlayerBullet();
	//	newBullet->Initialize(bulletmodel_, worldTransform_.translation_, velocity);
	//	bullets_.push_back(newBullet);

	//	// サウンド再生
	//	shotHandle_ = audio_->PlayWave(shotSE_, false, 1.0f);
	//
	//}


	//// メインループ内の更新処理でのコード
	//if (itemCountATK == 1 && !isItemActive_) {

	//	if (input_->PushKey(DIK_SPACE)) {

	//		// 初期速度の設定
	//		const float kBulletSpeed = 0.3f;

	//		if (ATKFlag_ == true) {

	//			// 横、斜め上、斜め下の方向ベクトルを設定
	//			std::vector<Vector3> directions = {
	//			    {0.0f, 0.0f,  kBulletSpeed}, // 横方向（右）
	//			    {0.0f, 0.5f,  kBulletSpeed}, // 斜め上方向
	//			    {0.0f, -0.5f, kBulletSpeed}  // 斜め下方向
	//			};

	//			// 各方向に弾を発射
	//			for (const Vector3& direction : directions) {
	//				// ワールド座標に速度を変換
	//				Vector3 velocity = TransformNormal(direction, worldTransform_.matWorld_);

	//				// 弾の生成
	//				PlayerBullet* newBullet = new PlayerBullet();
	//				newBullet->Initialize(bulletmodel_, worldTransform_.translation_, velocity);
	//				bullets_.push_back(newBullet);
	//			}
	//		}

	//		ATKTImer_ += 1;

	//		// アイテムを有効化し、タイマーをリセット
	//		isItemActive_ = true;
	//		ATKTImer_ = 0.0f;

	//		itemCountATK = 0; // アイテム使用済み
	//	}
	//}

	// アイテムの効果時間を管理
	if (isItemActive_) {
		const float kItemEffectDuration = 10.0f; // 10秒間の効果時間

		// タイマーを増加
		ATKTImer_ += deltaTime; // deltaTime はフレーム間の経過時間

		// 効果時間が経過した場合
		if (ATKTImer_ >= kItemEffectDuration) {
			isItemActive_ = false; // アイテム効果終了
			ATKTImer_ = 0.0f;      // タイマーをリセット
		}
	}
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列から平行移動成分を取り出す
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

// AABB Player::GetAABB() {
//	Vector3 worldPos = GetWorldPosition();
//
//	AABB aabb;
//	aabb.min = {worldPos.x - radius_, worldPos.y - radius_, worldPos.z - radius_};
//	aabb.max = {worldPos.x + radius_, worldPos.y + radius_, worldPos.z + radius_};
//	return aabb;
//
//	return aabb;
// }

void Player::RemoveBullet(PlayerBullet* bullet) {
	// 弾のリストから該当の弾を削除
	auto it = std::find(bullets_.begin(), bullets_.end(), bullet);
	if (it != bullets_.end()) {
		delete *it;               // 弾を削除
		bullets_.erase(it); // リストから除外
	}
}


void Player::OnCollision(const Enemy* enemy) {
	(void)enemy;
	// ジャンプ開始

	// velocity_ += Vector3(0, kJumpAcceleration / 4.0f, 0);
	isDead_ = true;
}

void Player::OnCollision(const EnemyBoss* enemy) {
	(void)enemy;
	// ジャンプ開始

	// velocity_ += Vector3(0, kJumpAcceleration / 4.0f, 0);
	isDead_ = true;
}

void Player::OnCollision(const Trap* trap) {

	(void)trap;
	// トラップに当たったら死亡フラグを立てる
	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet1* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet2* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet3* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet4* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::OnCollision(const EnemySkydomeBullet5* enemySky) {
	(void)enemySky;

	isDead_ = true;
}

void Player::MovePlayer() {
	// 落下中の死亡チェック
	const float kDeathHeight = 0.0f; // 死亡する高さ

	// 移動入力
	// 接地状態
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_D)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kLimitRunSpeed;
				}
			} else if (Input::GetInstance()->PushKey(DIK_A)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kLimitRunSpeed;
				}
			}
			// 加速/減速
			velocity_.x += acceleration.x;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}
		if (Input::GetInstance()->PushKey(DIK_W)) {
			// ジャンプ初速
			velocity_.y += kJumpAcceleration;
		}
	} else {

		// 落下速度
		velocity_.y += -kGravityAcceleration;

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		// プレイヤーが死亡する高さを下回った場合
		if (worldTransform_.translation_.y < kDeathHeight) {
			// 死亡フラグを立てる
			isDead_ = true;

			// 死亡処理 (例: コンソールに表示)
			std::cout << "Player has fallen and died." << std::endl;

			// リスポーンするなどの処理をここに追加
		}
	}
	if (!onGround_) {
		if (velocity_.x >= 0.1f) {
			velocity_.x = 0.1f;
		}
		if (velocity_.x <= -0.1f) {
			velocity_.x = -0.1f;
		}
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_D)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kLimitRunSpeed;
				}
			} else if (Input::GetInstance()->PushKey(DIK_A)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kLimitRunSpeed;
				}
			}
			// 加速/減速
			velocity_.x += acceleration.x;
			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		}
	}
}

void Player::CeilingContact(const CollisionMapInfo& info) {
	// 天井に当たった?
	if (info.hitCeilingFlag) {
		DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0;
	}
}

void Player::CheckMapCollision(CollisionMapInfo& info) {

	CheckMapCollisionUp(info);
	CheckMapCollisionDown(info);
	CheckMapCollisionRight(info);
	CheckMapCollisionLeft(info);
}

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {

	// 上昇あり？
	if (info.movement.y <= 0) {
		return;
	}

	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;

	// 真上の当たり判定を行う
	bool hit = false;

	// 左上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex + 1);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}

	if (mapChipType == MapChipType::kBlock1 && mapChipTypeNext != MapChipType::kBlock1) {
		hit = true;
	}

	if (mapChipType == MapChipType::kBlock3 && mapChipTypeNext != MapChipType::kBlock3) {
		hit = true;
	}

	if (mapChipType == MapChipType::kTrap && mapChipTypeNext != MapChipType::kTrap) {
		hit = true;
	}

	// 右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex + 1);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {

		hit = true;
	}

	if (mapChipType == MapChipType::kBlock1 && mapChipTypeNext != MapChipType::kBlock1) {

		hit = true;
	}

	if (mapChipType == MapChipType::kBlock3 && mapChipTypeNext != MapChipType::kBlock3) {
		hit = true;
	}

	if (mapChipType == MapChipType::kTrap && mapChipTypeNext != MapChipType::kTrap) {
		hit = true;
	}

	// ブロックにヒット
	if (hit) {

		MapChipField::IndexSet indexSetNow;

		// めり込みを排除する方向に移動量を設定する
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, +kHeight / 3.0f, 0));

		if (indexSetNow.yIndex != indexSet.yIndex) {

			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.movement + Vector3(0, +kHeight / 3.0f, 0));

			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.movement.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 3.0f + kBlank));
			info.hitCeilingFlag = true;
		}
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {

	// 下降アリ？
	if (info.movement.y >= 0) {
		return;
	}
	// 移動後４つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Vector3(0, info.movement.y, 0), static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	// 真上の当たり判定を行う
	bool hit = false;

	// 左下点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}

	if (mapChipType == MapChipType::kBlock1 && mapChipTypeNext != MapChipType::kBlock1) {
		hit = true;
	}

	if (mapChipType == MapChipType::kBlock3 && mapChipTypeNext != MapChipType::kBlock3) {
		hit = true;
	}

	if (mapChipType == MapChipType::kTrap && mapChipTypeNext != MapChipType::kTrap) {
		hit = true;
	}

	// 右下点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock1 && mapChipTypeNext != MapChipType::kBlock1) {
		hit = true;
	}

	if (mapChipType == MapChipType::kBlock3 && mapChipTypeNext != MapChipType::kBlock3) {
		hit = true;
	}

	if (mapChipType == MapChipType::kTrap && mapChipTypeNext != MapChipType::kTrap) {
		hit = true;
	}

	// ブロックにヒット？
	if (hit) {
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, -kHeight / 2.0f, 0));
		if (indexSetNow.yIndex != indexSet.yIndex) {
			// めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.movement + Vector3(0, -kHeight / 2.0f, 0));
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.movement.y = std::min(0.0f, (rect.top - worldTransform_.translation_.y) + ((kHeight / 2.0f) + kBlank));
			// 地面に当たったことを記録する
			info.landingFlag = true;
		}
	}
}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Vector3(info.movement.x, 0, 0), static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	bool hit = false;

	// 左下点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock1) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock3) {
		hit = true;
	}
	if (mapChipType == MapChipType::kTrap) {
		hit = true;
	}

	// 左上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock1) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock3) {
		hit = true;
	}
	if (mapChipType == MapChipType::kTrap) {
		hit = true;
	}

	if (hit) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.movement.x = std::max(0.0f, (rect.right - worldTransform_.translation_.x) - (kWidth / 2.0f + kBlank));
	}
}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Vector3(info.movement.x, 0, 0), static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	bool hit = false;

	// 右下点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock1) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock3) {
		hit = true;
	}
	if (mapChipType == MapChipType::kTrap) {
		hit = true;
	}

	// 右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock1) {
		hit = true;
	}
	if (mapChipType == MapChipType::kBlock3) {
		hit = true;
	}
	if (mapChipType == MapChipType::kTrap) {
		hit = true;
	}

	if (hit) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.movement.x = std::min(0.0f, (rect.left - worldTransform_.translation_.x) + (kWidth / 2.0f + kBlank));
	}
}

void Player::GraundSetting(const CollisionMapInfo& info) {
	// 接地状態の切り替え処理
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態の移行
			onGround_ = false;
		} else {
			std::array<Vector3, kNumCorner> positonsNew;

			for (uint32_t i = 0; i < positonsNew.size(); ++i) {
				positonsNew[i] = CornerPosition(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
			}

			MapChipType mapChipType;
			bool hit = false;

			// 左下点の判定
			MapChipField::IndexSet indexSet;
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positonsNew[kLeftBottom] + Vector3(0, 0, 0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}

			// 右下点の判定
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positonsNew[kRightBottom] + Vector3(0, 0, 0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}

			// 落下開始
			if (!hit) {
				// 空中状態に切り替える
				onGround_ = false;
			}
		}
	} else {
		// 着地
		if (info.landingFlag) {
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuationLanding);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 着地状態に切り替える
			onGround_ = true;
		}
	}
}

void Player::JudgmentMove(const CollisionMapInfo& info) {
	// 移動
	worldTransform_.translation_.x += info.movement.x;
	worldTransform_.translation_.y += info.movement.y;
	worldTransform_.translation_.z += info.movement.z;
}

void Player::TurnControll() {
	// 旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;
		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定するa
		worldTransform_.rotation_.y = destinationRotationY;
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0}, // kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0}, // kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0}, // kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0}  // kleftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

bool Player::Dead() {
	isDead_ = true;

	return false;
}