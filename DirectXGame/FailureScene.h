#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Skydome.h"
#include <Model.h>
#include <Sprite.h>
#include "TextureManager.h"
#include <Input.h>
//#include "imgui.h"

#pragma once
class FailureScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	FailureScene();

	/// <summary>
	/// デストクラタ
	/// </summary>
	~FailureScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// デスフラグの getter
	bool IsFinished() const { return finished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 終了フラグ
	bool finished_ = false;

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	Model* modelOver_ = nullptr;
	WorldTransform modelOverForm_;

	Model* modelPushFont_ = nullptr;
	WorldTransform PushFontForm_;
};
