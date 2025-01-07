//#pragma once
//
//#include "Model.h"
//#include "ObjectColor.h"
//#include "Vector3.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include <vector>
//
//class ParticleSystem {
//public:
//	// コンストラクタとデストラクタ
//	ParticleSystem();
//	~ParticleSystem();
//
//	// 初期化
//	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
//
//	// 更新処理
//	void Update();
//
//	// 描画処理
//	void Draw();
//
//	// 終了判定
//	bool IsFinished() const { return isFinished_; }
//
//private:
//	struct Particle {
//		WorldTransform worldTransform; // 個々のパーティクルのワールド変換
//		Vector3 velocity;              // 移動速度
//		float lifeTime;                // 現在の寿命
//		float maxLifeTime;             // 最大寿命
//	};
//
//	Model* model_ = nullptr;                   // パーティクルのモデル
//	ViewProjection* viewProjection_ = nullptr; // ビュープロジェクション
//
//	std::vector<Particle> particles_; // パーティクルのリスト
//	ObjectColor objectColor_;         // 色情報
//	Vector4 color_;                   // カラー
//
//	bool isFinished_ = false;                  // 完了フラグ
//	float counter_ = 0.0f;                     // 時間カウンタ
//	const float kDuration = 1.0f;              // パーティクルの寿命
//	const float kSpeed = 0.1f;                 // 初速
//	const float kAngleUint = 3.141592f / 4.0f; // 分割角
//};
