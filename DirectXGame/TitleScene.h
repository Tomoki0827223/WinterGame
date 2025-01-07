#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Audio.h>
#include <Skydome.h>
#include <Sprite.h>
#include <TextureManager.h>



/// <summary>
/// タイトルシーン
/// </summary>
class TitleSence {

public:

	~TitleSence();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return finished_; }

private:
	// 最初の角度[度]
	static inline const float kWalkMotionAngleStart = 5.0f;
	// 最後の角度[度]
	static inline const float kWalkMotionAngleEnd = -5.0f;
	// アニメーションの周期となる時間[秒]
	static inline const float kWalklMotionTime = 1.0f;
	// タイマー
	float Timer_ = 0.0f;

	bool finished_ = false;
	DirectXCommon* dxCommon_ = nullptr;
	WorldTransform titleWorldTransform_;
	WorldTransform titleWorldTransformFont_;
	WorldTransform titleskydome;
	ViewProjection viewProjection_;
	Model* titlemodel_ = nullptr;
	Model* titlemodelFont_ = nullptr;
	Model* TitleSkydome_ = nullptr;
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
