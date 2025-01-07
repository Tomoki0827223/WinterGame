#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Skydome.h"
#include <Model.h>
#include <Sprite.h>

class SelectStage {

public:

	SelectStage();
	~SelectStage();
	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; }

	uint32_t GetStageNumber() const { return StageNumber_; }

	uint32_t StageNumber_ = 0;

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	bool finished_ = false;

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	

};
