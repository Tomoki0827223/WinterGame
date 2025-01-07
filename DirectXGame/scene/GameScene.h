#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>

#include "CameraController.h"
#include "DethParticles.h"
#include "Enemy.h"
#include "EnemySkydome.h"
#include "Esing.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include "TextureManager.h"
#include <cassert>

// #include <imgui.h>

#include "Distance.h"
#include "EnemySkydome1.h"
#include "EnemySkydome2.h"
#include "EnemySkydome3.h"
#include "EnemySkydome4.h"
#include "EnemySkydome5.h"

// ゲームのフェーズ（型）
enum class Phase {
	kPlay,  // ゲームプレイ
	kDeath, // デス演出
	        //	kNext,	   // 次のステージ
	kGoal,  // ゲームクリア
};

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t StageNumber_);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ブロック生成
	/// </summary>
	void GenerateBlocks();

	// 全ての当たり判定を行う
	void CheckAllCollisions();

	/// <summary>
	/// フェーズの切り替え
	/// </summary>
	void ChangePhase();

	// デスフラグの getter
	bool IsFinished() const { return finished_; }

	// ゴールフラグの getter
	bool IsGoalFinished() const { return goalFinished_; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// ゲームの現在のフェーズ
	Phase phase_;

	// デバッグカメラ
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	uint32_t soundBGM1_ = 0;
	uint32_t soundBGMHanlde_1 = 0;
	bool isBGMPlaying_ = false;

	uint32_t soundSE_ = 0;
	uint32_t soundSEHanlde_ = 0;

	// uint32_t soundShotSE_1 = 0;
	// uint32_t soundSEShotHanlde_1 = 0;

	// ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	Model* modelBlock_ = nullptr;

	// ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_1;
	Model* modelBlock_1 = nullptr;

	// 透明ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_2;
	Model* modelBlock_2 = nullptr;

	// 透明ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_3;
	Model* modelBlock_3 = nullptr;

	// ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformATK_;
	Model* modelPeceItem_ = nullptr;

	// ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformHP_;
	Model* modelHPItem_ = nullptr;

	// ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformWeekPoint_;
	Model* modelweekPoint_ = nullptr;

	// ゴールブロック
	std::vector<std::vector<WorldTransform*>> worldTransformGoalBlocks_;
	Model* modelGoal_ = nullptr;

	// 罠ブロック
	std::vector<std::vector<WorldTransform*>> worldTransformTraps_;
	Model* modelTrap_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 自キャラ
	Player* player_ = nullptr;
	Model* modelPlayer_ = nullptr;
	std::list<Player*> Player__;

	// パーティクル
	DeathParticles* deathParticles_ = nullptr;
	Model* modelDeathParticles_ = nullptr;

	// 敵キャラ
	Model* modelEnemy_ = nullptr;
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
	std::list<EnemyBullet*> enemyBullets_;

	// 敵キャラ位置
	Vector3 enemySkyPos = {50, 3, 100};
	Vector3 enemySkyPos1 = {60, 3, 100};
	Vector3 enemySkyPos2 = {70, 3, 100};
	Vector3 enemySkyPos3 = {80, 3, 100};
	Vector3 enemySkyPos4 = {90, 3, 100};
	Vector3 enemySkyPos5 = {100, 3, 100};

	std::list<Trap*> Trapps_;
	Distance* distance_ = nullptr;

	EnemySkydome* enemySkydome_ = nullptr;
	Model* modelEnemySkydome_ = nullptr;
	std::list<EnemySkydomeBullet*> enemySkyBullet_;

	EnemySkydome1* enemySkydome1_ = nullptr;
	Model* modelEnemySkydome1_ = nullptr;
	std::list<EnemySkydomeBullet1*> enemySkyListBullet1_;

	EnemySkydome2* enemySkydome2_ = nullptr;
	Model* modelEnemySkydome2_ = nullptr;
	std::list<EnemySkydomeBullet2*> enemySkyListBullet2_;

	EnemySkydome3* enemySkydome3_ = nullptr;
	Model* modelEnemySkydome3_ = nullptr;
	std::list<EnemySkydomeBullet3*> enemySkyListBullet3_;

	EnemySkydome4* enemySkydome4_ = nullptr;
	Model* modelEnemySkydome4_ = nullptr;
	std::list<EnemySkydomeBullet4*> enemySkyListBullet4_;

	EnemySkydome5* enemySkydome5_ = nullptr;
	Model* modelEnemySkydome5_ = nullptr;
	std::list<EnemySkydomeBullet5*> enemySkyListBullet5_;

	std::list<Player*> player__;

	// カメラコントローラ
	CameraController* cameraController_ = nullptr;
	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};

	// 終了フラグ
	bool finished_ = false;

	// ゴール終了フラグ
	bool goalFinished_ = false;

	PlayerBullet* playerBullet_ = nullptr;
	std::list<PlayerBullet*> Playerbullets_;

	uint32_t MapData_ = 0;

	float maxHp = 1000;
	float nowHp = maxHp;
	float width = 640;

	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;

	// 追加　
	bool isInvisible_ = false;
	float invisibleTimmer = 60 * 5;

	Esing* esing_ = nullptr;

	int weakPointHp = 50;
};
