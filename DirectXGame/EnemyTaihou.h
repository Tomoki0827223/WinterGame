// #pragma once
// #include "Model.h"
// #include "Vector3.h"
// #include "ViewProjection.h"
// #include "WorldTransform.h"
//
// class Player;
//
// class EnemyTaihou {
//
// public:
//	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& pos);
//
//	Vector3 GetWorldPosition();
//
//	void Update();
//
//	void OnCollision(const Player* player__);
//
//	void Draw(const ViewProjection& viewProjection);
//
//	~EnemyTaihou();
//
//	bool IsDead() const { return isDead_; }
//
//	const std::list<Player*>& GetBullets() const { return player_; }
//
// private:
//	WorldTransform worldtransfrom_;
//
//	ViewProjection* vieProjection_ = nullptr;
//	Model* model_ = nullptr;
//	// uint32_t textureHandle_ = 0;
//	Vector3 velocity_;
//
//	std::list<Player*> player_;
//
//	// 寿命<frm>
//	static const int32_t kLifeTime = 60 * 3;
//	// デスタイマー
//	int32_t deathTimer_ = kLifeTime;
//	// デスフラグ
//	bool isDead_ = false;
// };
