#include "AABB.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "affine.h"

#include "Player.h"

/// <summary>
/// 自キャラ
/// </summary>

class MapChipField;

class PlayerBullet;

class Enemy {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, Player* player);

	~Enemy();

	void Fire();

	void Update();

	void SetPosition(const Vector3& pos);

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	//// AABBを取得
	// AABB GetAABB();

	void OnCollision(const Player* player);

	void OnCollision(const PlayerBullet* playerBullet);

	bool EnemyIsDead() const { return EnemyIsDead_; }

	// const std::list<PlayerBullet*>& GetBullets() const {return bullets_;}

	// 発射間隔
	static const int kFireInterval = 25;

private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// モデルのポインタ
	Model* model_ = nullptr;
	// ビュープロジェクションのポインタ
	ViewProjection* viewProjection_ = nullptr;
	// マップチップフィールドのポインタ
	MapChipField* mapChipField_ = nullptr;

	Model* modelbullet_ = nullptr;
	// 弾
	std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t spawnTimer = 0;

	Player* player_ = nullptr;

	// 歩行の速さ
	static inline const float kWalkSpeed = 0.02f;
	// 速度
	Vector3 velocity_ = {};

	// 最初の角度[度]
	static inline const float kWalkMotionAngleStart = 0.0f;
	// 最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 30.0f;
	// アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 1.0f;
	// 経過時間
	float walkTimer_ = 0.0f;

	static inline const float kWidth = 0.8f;

	static inline const float kHeight = 0.8f;

	bool EnemyIsDead_ = false;

	// std::list<PlayerBullet*> bullets_;
};