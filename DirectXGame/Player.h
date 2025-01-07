#pragma once
#include <AABB.h>
#include <Audio.h>
#include <DebugText.h>
#include <Input.h>
#include <PlayerBullet.h>
#include <WorldTransform.h>
#include <cassert>
#include <iostream>
#include <list>
#include <numbers>
#include "affine.h"
#include "CameraController.h"

class MapChipField;
class Enemy;
class EnemyBoss;
class Trap;
class EnemySkydomeBullet;
class EnemySkydomeBullet1;
class EnemySkydomeBullet2;
class EnemySkydomeBullet3;
class EnemySkydomeBullet4;
class EnemySkydomeBullet5;


class Player {
public:
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};

	// 角
	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数
	};

	// 角
	struct CollisionMapInfo {
		bool hitCeilingFlag = false;
		bool landingFlag = false;
		bool wallContactFlag = false;
		Vector3 movement;
	};

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void UpdateBlockAndTrapPosition(WorldTransform& worldTransform, MapChipField* mapChipField, float fallSpeed);

	// void Rotate();

	void Attack();

	// seteer
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	// getter
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Vector3& GetVelocity() { return velocity_; }

	const Vector3& GetPlayerPosition() const { return worldTransform_.translation_; }

	// 2-10
	//   ワールド座標を取得する関数
	Vector3 GetWorldPosition();
	// AABBを取得する関数
	AABB GetAABB();

	void RemoveBullet(PlayerBullet* bullet);

	// 衝突応答
	void OnCollision(const Enemy* enemy);

	void OnCollision(const EnemyBoss* enemy);

	void OnCollision(const Trap* trap);

	void OnCollision(const EnemySkydomeBullet* enemySky);
	void OnCollision(const EnemySkydomeBullet1* enemySky);
	void OnCollision(const EnemySkydomeBullet2* enemySky);
	void OnCollision(const EnemySkydomeBullet3* enemySky);
	void OnCollision(const EnemySkydomeBullet4* enemySky);
	void OnCollision(const EnemySkydomeBullet5* enemySky);

	void MovePlayer();

	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);

	void JudgmentMove(const CollisionMapInfo& info);

	void CeilingContact(const CollisionMapInfo& info);

	void GraundSetting(const CollisionMapInfo& info);

	void TurnControll();

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	bool Dead();

	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// クリアフラグのgetter
	bool IsClear() const { return isClear_; }

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	int itemCount = 0;
	int itemCountATK = 0;

private:
	Vector3 worldPos_;
	float radius_;

	bool onGround_ = true;
	// bool TamaFlag_ = false;

	bool isDead_ = false;
	bool isClear_ = false;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	/*PlayerBullet* bullet_ = nullptr;*/
	std::list<PlayerBullet*> bullets_;

	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransform2_;
	WorldTransform worldTransform3_;
	WorldTransform worldTransform4_;

	float ShotTimer_ = 60.0f;
	// 三点バースト関連の変数
	int burstShotCount_ = 0;       // 現在のバースト弾数
	int burstTimer_ = 0;           // バースト間隔タイマー
	const int kBurstInterval = 10; // バースト間の時間間隔（フレーム単位）
	const int kMaxBurstShots = 5;  // 1回のバーストで発射する弾数

	// モデル
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	Model* bulletmodel_ = nullptr;
	CameraController* camera_ = nullptr;

	Vector3 velocity_ = {};

	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	float ATKTImer_ = 0.0f;
	bool ATKFlag_ = false;
	bool isItemActive_ = false;
	float deltaTime = 0.0f;

	MapChipField* mapChipField_ = nullptr;

	uint32_t soundSE_ = 0;
	uint32_t soundSEHanlde_ = 0;
	bool soundFlag = false;

	uint32_t shotSE_ = 0;
	uint32_t shotHandle_ = 0;

	// プレイヤーの移動加速度
	static inline const float kAcceleration = 0.1f;
	// プレイヤーが停止する際の減速率
	static inline const float kAttenuation = 0.2f;
	// ジャンプ時の加速度
	static inline const float kJumpAcceleration = 0.6f;
	// 重力による加速度
	static inline const float kGravityAcceleration = 0.04f;
	// 壁に衝突した際の減速率
	static inline const float kAttenuationWall = 0.2f;
	// 着地時の減速率
	static inline const float kAttenuationLanding = 0.7f;
	// 落下速度の制限値
	static inline const float kLimitFallSpeed = 1.0f;
	// 走行速度の制限値
	static inline const float kLimitRunSpeed = 0.5f;
	// ターンするのにかかる時間
	static inline const float kTimeTurn = 0.5f;
	// プレイヤーの幅
	static inline const float kWidth = 0.8f;
	// プレイヤーの高さ
	static inline const float kHeight = 0.8f;
	// 隙間の幅（適切な値に修正する必要あり）
	static inline const float kBlank = 18.0f;
	// 地面を探す際の高さ
	static inline const float kGroundSearchHeight = 0.06f;
};