#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 解放処理
	delete modelBlock_;
	for (auto& worldTransformBlockLine : worldTransformBlocks_) {
		for (auto* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
		worldTransformBlockLine.clear();
	}
	worldTransformBlocks_.clear();

	delete modelPeceItem_;
	for (auto& worldTransformPeceItemLine : worldTransformATK_) {
		for (auto* worldTransformPeceItem : worldTransformPeceItemLine) {
			delete worldTransformPeceItem;
		}
		worldTransformPeceItemLine.clear();
	}
	worldTransformATK_.clear();

	delete modelHPItem_;
	for (auto& worldTransformPeceItemHPLine : worldTransformHP_) {
		for (auto* worldTransformPeceHPItem : worldTransformPeceItemHPLine) {
			delete worldTransformPeceHPItem;
		}
		worldTransformPeceItemHPLine.clear();
	}
	worldTransformHP_.clear();

	delete modelweekPoint_;
	for (auto& worldTransformWeekLine : worldTransformWeekPoint_) {
		for (auto* worldTransWeek : worldTransformWeekLine) {
			delete worldTransWeek;
		}
		worldTransformWeekLine.clear();
	}
	worldTransformWeekPoint_.clear();

	delete modelBlock_1;
	for (auto& worldTransformBlockLine_1 : worldTransformBlocks_1) {
		for (auto* worldTransformBlock_1 : worldTransformBlockLine_1) {
			delete worldTransformBlock_1;
		}
		worldTransformBlockLine_1.clear();
	}
	worldTransformBlocks_1.clear();

	delete modelBlock_2;
	for (auto& worldTransformBlockLine_2 : worldTransformBlocks_2) {
		for (auto* worldTransformBlock_2 : worldTransformBlockLine_2) {
			delete worldTransformBlock_2;
		}
		worldTransformBlockLine_2.clear();
	}
	worldTransformBlocks_2.clear();

	delete modelBlock_3;
	for (auto& worldTransformBlockLine_3 : worldTransformBlocks_3) {
		for (auto* worldTransformBlock_3 : worldTransformBlockLine_3) {
			delete worldTransformBlock_3;
		}
		worldTransformBlockLine_3.clear();
	}
	worldTransformBlocks_3.clear();

	delete modelGoal_;
	for (auto& worldTransformGoalBlockLine : worldTransformGoalBlocks_) {
		for (auto* worldTransformGoalBlock : worldTransformGoalBlockLine) {
			delete worldTransformGoalBlock;
		}
		worldTransformGoalBlockLine.clear();
	}
	worldTransformGoalBlocks_.clear();

	delete modelTrap_;
	for (auto& worldTransformTrapLine : worldTransformTraps_) {
		for (auto* worldTransformTrap : worldTransformTrapLine) {
			delete worldTransformTrap;
		}
		worldTransformTrapLine.clear();
	}
	worldTransformTraps_.clear();

	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete mapChipField_;
	delete player_;
	delete modelDeathParticles_;
	delete modelPlayer_;
	delete modelEnemy_;
	delete cameraController_;
	delete playerBullet_;
	delete sprite_;
	delete sprite2_;
	delete esing_;
	delete distance_;

	delete enemy_;
	delete enemySkydome_;
	delete modelEnemySkydome_;
	delete enemySkydome1_;
	delete modelEnemySkydome1_;

	// bullets_ に格納された PlayerBullet インスタンスを解放
	for (PlayerBullet* bullet : Playerbullets_) {
		delete bullet;
	}
	Playerbullets_.clear();
}

void GameScene::Initialize(uint32_t StageNumber_) {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 天球を生成
	skydome_ = new Skydome();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 天球を初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	// ブロックの生成
	modelBlock_ = Model::CreateFromOBJ("block", true);
	modelBlock_1 = Model::CreateFromOBJ("block_4", true);
	modelBlock_2 = Model::CreateFromOBJ("block_2", true);
	modelBlock_3 = Model::CreateFromOBJ("block_3", true);

	// ゴールの生成
	modelGoal_ = Model::CreateFromOBJ("goal", true);

	// アイテムかけら
	modelPeceItem_ = Model::CreateFromOBJ("Item", true);

	// アイテムかけら
	modelHPItem_ = Model::CreateFromOBJ("Item2", true);

	// トラップ
	modelTrap_ = Model::CreateFromOBJ("enemy", true);

	// 弱点
	modelweekPoint_ = Model::CreateFromOBJ("weakpoint", true);

	// 空の敵
	modelEnemySkydome_ = Model::CreateFromOBJ("EnemySkydome_", true);

	// 空の敵
	modelEnemySkydome1_ = Model::CreateFromOBJ("EnemySkydome1_", true);

	// 空の敵
	modelEnemySkydome2_ = Model::CreateFromOBJ("EnemySkydome1_", true);

	// 空の敵
	modelEnemySkydome3_ = Model::CreateFromOBJ("EnemySkydome1_", true);

	// 空の敵
	modelEnemySkydome4_ = Model::CreateFromOBJ("EnemySkydome1_", true);

	// 空の敵
	modelEnemySkydome5_ = Model::CreateFromOBJ("EnemySkydome1_", true);

	// マップチップの生成
	mapChipField_ = new MapChipField;

	esing_ = new Esing();
	distance_ = new Distance();

	switch (StageNumber_) {
	
	case 0:
		mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
		
		break;
	}

	// マップチップの初期化
	GenerateBlocks();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(3, 18);

	switch (StageNumber_) {
	case 0:
		playerPosition = mapChipField_->GetMapChipPositionByIndex(12, 12);
		break;
	}

	// 自キャラの生成
	player_ = new Player();
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	// 自キャラの初期化
	player_->Initialize(modelPlayer_, &viewProjection_, playerPosition);
	player_->SetMapChipField(mapChipField_);

	modelEnemy_ = Model::CreateFromOBJ("enemy", true);


	Enemy* enemy = new Enemy();
	// 敵キャラに自キャラのアドレスを渡す
	enemy->SetPlayer(player_);

	enemySkydome_ = new EnemySkydome();
	enemySkydome_->Initialize(modelEnemySkydome_, &viewProjection_, enemySkyPos);
	enemySkydome_->SetPlayer(player_);

	enemySkydome1_ = new EnemySkydome1();
	enemySkydome1_->Initialize(modelEnemySkydome1_, &viewProjection_, enemySkyPos1);
	enemySkydome1_->SetPlayer(player_);

	enemySkydome2_ = new EnemySkydome2();
	enemySkydome2_->Initialize(modelEnemySkydome2_, &viewProjection_, enemySkyPos2);
	enemySkydome2_->SetPlayer(player_);

	enemySkydome3_ = new EnemySkydome3();
	enemySkydome3_->Initialize(modelEnemySkydome3_, &viewProjection_, enemySkyPos3);
	enemySkydome3_->SetPlayer(player_);

	enemySkydome4_ = new EnemySkydome4();
	enemySkydome4_->Initialize(modelEnemySkydome4_, &viewProjection_, enemySkyPos4);
	enemySkydome4_->SetPlayer(player_);

	enemySkydome5_ = new EnemySkydome5();
	enemySkydome5_->Initialize(modelEnemySkydome5_, &viewProjection_, enemySkyPos5);
	enemySkydome5_->SetPlayer(player_);

	// if (StageNumber_ == 0) {
	//	for (int32_t i = 0; i < 3; i++) {
	//		Enemy* newEnemy = new Enemy();
	//		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(23, 18);
	//		newEnemy->Initialize(modelEnemy_, &viewProjection_, enemyPosition,player_);
	//		enemies_.push_back(newEnemy);
	//	}
	// }

	// 仮の生成処理。後で消す。
	deathParticles_ = new DeathParticles;
	modelDeathParticles_ = Model::CreateFromOBJ("deathParticle", true);

	switch (StageNumber_) {
	case 0:
		soundBGM1_ = audio_->LoadWave("Audio/GameBGM.wav");
		break;
	}

	soundSE_ = audio_->LoadWave("Audio/ShotSE.wav");

	cameraController_ = new CameraController();
	cameraController_->Initialize();
	cameraController_->setTarget(player_);
	CameraController::Rect cameraAreaa = {12.0f, 100 - 10.0f, 6.0f, 24.0f};
	cameraController_->SetMovableArea(cameraAreaa);
	cameraController_->Reset();
	textureHandle_ = TextureManager::Load("hpBarBuck.png");
	textureHandle2_ = TextureManager::Load("hpBarFront.png");
	sprite_ = Sprite::Create(textureHandle_, {320, 50});
	sprite2_ = Sprite::Create(textureHandle2_, {320, 50});
}

void GameScene::Update() {

	switch (phase_) {
	case Phase::kPlay:

		// 音声再生（フラグを使用してBGMが再生中でない場合のみ再生）
		if (!isBGMPlaying_) {
			// BGMを再生し、再生中フラグをtrueに設定
			soundBGMHanlde_1 = audio_->PlayWave(soundBGM1_, false, 0.2f);
			isBGMPlaying_ = true;
		} else if (!audio_->IsPlaying(soundBGMHanlde_1)) {
			// BGMが止まったらフラグをリセット
			isBGMPlaying_ = false;
		}

		// ゲームプレイフェーズの処理
		// 天球の更新
		skydome_->Update();

		// 自キャラの更新
		player_->Update();

		enemySkydome_->Update();
		enemySkydome1_->Update();
		enemySkydome2_->Update();
		enemySkydome3_->Update();
		enemySkydome4_->Update();
		enemySkydome5_->Update();

		// 敵キャラの更新
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// デバッグカメラを更新
		debugCamera_->Update();

		enemies_.remove_if([](Enemy* enemy) {
			if (enemy->EnemyIsDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

		if (player_->IsDead()) {
			// 死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;
			// 自キャラの座標を取得
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();

			// パーティクルの初期化
			deathParticles_->Initialize(modelDeathParticles_, &viewProjection_, deathParticlesPosition);
		}

		// プレイヤーがクリアした場合の処理
		if (player_->IsClear()) {
			// フェーズをゴールフェーズに変更
			phase_ = Phase::kGoal;
		}

#ifdef _DEBUG
		// カメラモード切り替え
		if (input_->TriggerKey(DIK_V)) {
			isDebugCameraActive_ = true;
		}
#endif
		if (isDebugCameraActive_) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		} else {
			viewProjection_.matView = cameraController_->GetViewProjection().matView;
			viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			viewProjection_.TransferMatrix();
		}

		// カメラを更新
		cameraController_->Update();

		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				worldTransformBlock->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformPeceItemLine : worldTransformATK_) {
			for (WorldTransform* worldTransformPeceItem : worldTransformPeceItemLine) {
				if (!worldTransformPeceItem)
					continue;
				worldTransformPeceItem->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformHPItemLine : worldTransformHP_) {
			for (WorldTransform* worldTransformHPItem : worldTransformHPItemLine) {
				if (!worldTransformHPItem)
					continue;
				worldTransformHPItem->UpdateMatrix();
			}
		}

		// for (std::vector<WorldTransform*>& worldTransformWeekLine : worldTransformWeekPoint_) {
		//	for (WorldTransform* worldTransWeekPoint : worldTransformWeekLine) {
		//		if (!worldTransWeekPoint)
		//			continue;
		//		worldTransWeekPoint->UpdateMatrix();
		//	}
		// }

		for (std::vector<WorldTransform*>& worldTransformWeekLine : worldTransformWeekPoint_) {
			for (WorldTransform* worldTransWeekPoint : worldTransformWeekLine) {
				if (!worldTransWeekPoint)
					continue;

				Playerbullets_ = player_->GetBullets();

				// 弾との衝突チェック
				for (PlayerBullet* bullet : Playerbullets_) {

					// 弾との当たり判定
					if (worldTransWeekPoint->IsHit(bullet->GetWorldPosition())) {
						// 弾を削除
						player_->RemoveBullet(bullet);
						weakPointHp -= rand() % 3 + 1;

						if (weakPointHp <= 0) {

							weakPointHp = 50;
							// ブロックを削除
							worldTransWeekPoint->translation_ = {0.0f, -100.0f, 0.0f};
							worldTransWeekPoint->UpdateMatrix();
						}
					}
				}
				// 行列の更新
				worldTransWeekPoint->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_1 : worldTransformBlocks_1) {
			for (WorldTransform* worldTransformBlock_1 : worldTransformBlockLine_1) {
				if (!worldTransformBlock_1)
					continue;
				worldTransformBlock_1->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_2 : worldTransformBlocks_2) {
			for (WorldTransform* worldTransformBlock_2 : worldTransformBlockLine_2) {
				if (!worldTransformBlock_2)
					continue;
				worldTransformBlock_2->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_3 : worldTransformBlocks_3) {
			for (WorldTransform* worldTransformBlock_3 : worldTransformBlockLine_3) {
				if (!worldTransformBlock_3)
					continue;
				worldTransformBlock_3->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformGoalBlockLine : worldTransformGoalBlocks_) {
			for (WorldTransform* worldTransformGoalBlock : worldTransformGoalBlockLine) {
				if (!worldTransformGoalBlock)
					continue;
				worldTransformGoalBlock->UpdateMatrix();
			}
		}

		// 罠の落下処理
		for (std::vector<WorldTransform*>& worldTransformTrapLine : worldTransformTraps_) {
			for (WorldTransform* worldTransformTrap : worldTransformTrapLine) {
				if (!worldTransformTrap)
					continue;

				// プレイヤーと罠のY軸の距離を計算
				Vector3 playerPos = player_->GetPlayerPosition(); // プレイヤーの現在位置を取得
				float playerY = playerPos.y;
				float trapY = worldTransformTrap->translation_.y;
				float yDistance = std::abs(playerY - trapY); // Y軸方向の距離計算

				// 発動範囲内かどうか
				const float activationRangeY = 10.0f; // 発動するY軸方向の距離の範囲
				if (yDistance <= activationRangeY) {
					// 罠を発動させる
					MapChipField::IndexSet indexSet;
					MapChipType mapChipType;
					indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformTrap->translation_);
					mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

					if (mapChipType != MapChipType::kBlock1) {
						const float fallSpeed = esing_->easeOutQuint(0.3f);

						// 罠のY座標を減少させる
						worldTransformTrap->translation_.y -= fallSpeed;
					}
				}

				// 行列の更新
				worldTransformTrap->UpdateMatrix();
			}
		}

		// 全ての当たり判定を行う
		CheckAllCollisions();

		break;
	case Phase::kDeath:
		// デス演出フェーズの処理
		// 天球の更新
		skydome_->Update();

		// 敵キャラの更新
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// パーティクルの更新
		deathParticles_->Update();

		// カメラを更新
		cameraController_->Update();

		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				worldTransformBlock->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformPeceItemLine : worldTransformATK_) {
			for (WorldTransform* worldTransformPeceItem : worldTransformPeceItemLine) {
				if (!worldTransformPeceItem)
					continue;
				worldTransformPeceItem->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformHPItemLine : worldTransformHP_) {
			for (WorldTransform* worldTransformHPItem : worldTransformHPItemLine) {
				if (!worldTransformHPItem)
					continue;
				worldTransformHPItem->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformWeekLine : worldTransformWeekPoint_) {
			for (WorldTransform* worldTransWeekPoint : worldTransformWeekLine) {
				if (!worldTransWeekPoint)
					continue;

				Playerbullets_ = player_->GetBullets();

				// 弾との衝突チェック
				for (PlayerBullet* bullet : Playerbullets_) {

					// 弾との当たり判定
					if (worldTransWeekPoint->IsHit(bullet->GetWorldPosition())) {
						// 弾を削除
						player_->RemoveBullet(bullet);

						// ブロックを削除
						worldTransWeekPoint->translation_ = {0.0f, -100.0f, 0.0f};
						worldTransWeekPoint->UpdateMatrix();
					}
				}
				// 行列の更新
				worldTransWeekPoint->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_1 : worldTransformBlocks_1) {
			for (WorldTransform* worldTransformBlock_1 : worldTransformBlockLine_1) {
				if (!worldTransformBlock_1)
					continue;
				worldTransformBlock_1->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_2 : worldTransformBlocks_2) {
			for (WorldTransform* worldTransformBlock_2 : worldTransformBlockLine_2) {
				if (!worldTransformBlock_2)
					continue;
				worldTransformBlock_2->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine_3 : worldTransformBlocks_3) {
			for (WorldTransform* worldTransformBlock_3 : worldTransformBlockLine_3) {
				if (!worldTransformBlock_3)
					continue;
				worldTransformBlock_3->UpdateMatrix();
			}
		}

		for (std::vector<WorldTransform*>& worldTransformGoalBlockLine : worldTransformGoalBlocks_) {
			for (WorldTransform* worldTransformGoalBlock : worldTransformGoalBlockLine) {
				if (!worldTransformGoalBlock)
					continue;
				worldTransformGoalBlock->UpdateMatrix();
			}
		}

		// ゲームシーンの終了条件
		if (deathParticles_ && deathParticles_->IsFinished()) {
			finished_ = true;
		}

		if (soundBGMHanlde_1 != 0) {
			audio_->StopWave(soundBGMHanlde_1);
			isBGMPlaying_ = false; // 再生フラグリセット
		}

		break;
	case Phase::kGoal:
		// 天球の更新
		skydome_->Update();

		// カメラを更新
		cameraController_->Update();

		// ゲームシーンの終了条件
		goalFinished_ = true;

		if (soundBGMHanlde_1 != 0) {
			audio_->StopWave(soundBGMHanlde_1);
			isBGMPlaying_ = false; // 念のため再生フラグをリセット
		}

		break;
	}

	if (player_->itemCount == 1) {

		nowHp += 100.0f;

		player_->itemCount = 0;
	}

	Vector2 size = sprite2_->GetSize();

	size.x = nowHp / maxHp * width;
	size.y = 10.0f;

	sprite2_->SetSize(size);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	switch (phase_) {
	case Phase::kPlay:
		// ゲームプレイフェーズの処理
		// 天球の描画
		skydome_->Draw();

		// 自キャラの描画

		if (invisibleTimmer == 15 * 2 || invisibleTimmer == 15 * 4 || invisibleTimmer == 15 * 6 || invisibleTimmer == 15 * 8 || invisibleTimmer == 15 * 10 || invisibleTimmer == 15 * 12 ||
		    invisibleTimmer == 15 * 14 || invisibleTimmer == 15 * 16 || invisibleTimmer == 15 * 18 || invisibleTimmer == 15 * 20) {
			player_->Draw();
		}

		// 敵キャラの描画
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}

		enemySkydome_->Draw();
		enemySkydome1_->Draw();
		enemySkydome2_->Draw();
		enemySkydome3_->Draw();
		enemySkydome4_->Draw();
		enemySkydome5_->Draw();

		//// 敵キャラの更新
		// for (EnemyBoss* enemyBoss : enemyBoss_) {
		//	enemyBoss->Draw();
		// }

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				modelBlock_->Draw(*worldTransformBlock, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformPeceItemLine : worldTransformATK_) {
			for (WorldTransform* worldTransformPeceItem : worldTransformPeceItemLine) {
				if (!worldTransformPeceItem)
					continue;

				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformPeceItem->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kATK) {

					modelPeceItem_->Draw(*worldTransformPeceItem, viewProjection_);
				}
			}
		}

		for (std::vector<WorldTransform*>& worldTransformHPItemLine : worldTransformHP_) {
			for (WorldTransform* worldTransformHPItem : worldTransformHPItemLine) {
				if (!worldTransformHPItem)
					continue;
				worldTransformHPItem->UpdateMatrix();

				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformHPItem->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kHPup) {
					modelHPItem_->Draw(*worldTransformHPItem, viewProjection_);
				}
			}
		}

		for (std::vector<WorldTransform*>& worldTransformWeekLine : worldTransformWeekPoint_) {
			for (WorldTransform* worldTransWeekPoint : worldTransformWeekLine) {
				if (!worldTransWeekPoint)
					continue;

				modelweekPoint_->Draw(*worldTransWeekPoint, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_1 : worldTransformBlocks_1) {
			for (WorldTransform* worldTransformBlock_1 : worldTransformBlockLine_1) {
				if (!worldTransformBlock_1)
					continue;
				modelBlock_1->Draw(*worldTransformBlock_1, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_2 : worldTransformBlocks_2) {
			for (WorldTransform* worldTransformBlock_2 : worldTransformBlockLine_2) {
				if (!worldTransformBlock_2)
					continue;
				modelBlock_2->Draw(*worldTransformBlock_2, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_3 : worldTransformBlocks_3) {
			for (WorldTransform* worldTransformBlock_3 : worldTransformBlockLine_3) {
				if (!worldTransformBlock_3)
					continue;
				modelBlock_3->Draw(*worldTransformBlock_3, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformTrapLine : worldTransformTraps_) {
			for (WorldTransform* worldTransformTrap : worldTransformTrapLine) {
				if (!worldTransformTrap)
					continue;
				modelTrap_->Draw(*worldTransformTrap, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformGoalBlockLine : worldTransformGoalBlocks_) {
			for (WorldTransform* worldTransformGoalBlock : worldTransformGoalBlockLine) {
				if (!worldTransformGoalBlock)
					continue;
				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformGoalBlock->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kGoal) {

					modelGoal_->Draw(*worldTransformGoalBlock, viewProjection_);

					player_->IsClear();
				}
			}
		}

		break;
	case Phase::kDeath:
		// デス演出フェーズの処理
		// 天球の描画
		skydome_->Draw();

		// 敵キャラの描画
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}

		// パーティクルの描画
		deathParticles_->Draw();

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				modelBlock_->Draw(*worldTransformBlock, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformPeceItemLine : worldTransformATK_) {
			for (WorldTransform* worldTransformPeceItem : worldTransformPeceItemLine) {
				if (!worldTransformPeceItem)
					continue;

				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformPeceItem->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kATK) {

					modelPeceItem_->Draw(*worldTransformPeceItem, viewProjection_);
				}
			}
		}

		for (std::vector<WorldTransform*>& worldTransformHPItemLine : worldTransformHP_) {
			for (WorldTransform* worldTransformHPItem : worldTransformHPItemLine) {
				if (!worldTransformHPItem)
					continue;
				worldTransformHPItem->UpdateMatrix();

				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformHPItem->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kHPup) {
					modelHPItem_->Draw(*worldTransformHPItem, viewProjection_);
				}
			}
		}

		for (std::vector<WorldTransform*>& worldTransformWeekLine : worldTransformWeekPoint_) {
			for (WorldTransform* worldTransWeekPoint : worldTransformWeekLine) {
				if (!worldTransWeekPoint)
					continue;

				modelweekPoint_->Draw(*worldTransWeekPoint, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_1 : worldTransformBlocks_1) {
			for (WorldTransform* worldTransformBlock_1 : worldTransformBlockLine_1) {
				if (!worldTransformBlock_1)
					continue;
				modelBlock_1->Draw(*worldTransformBlock_1, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_2 : worldTransformBlocks_2) {
			for (WorldTransform* worldTransformBlock_2 : worldTransformBlockLine_2) {
				if (!worldTransformBlock_2)
					continue;
				modelBlock_2->Draw(*worldTransformBlock_2, viewProjection_);
			}
		}

		// ブロックの描画
		for (std::vector<WorldTransform*>& worldTransformBlockLine_3 : worldTransformBlocks_3) {
			for (WorldTransform* worldTransformBlock_3 : worldTransformBlockLine_3) {
				if (!worldTransformBlock_3)
					continue;
				modelBlock_3->Draw(*worldTransformBlock_3, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformTrapLine : worldTransformTraps_) {
			for (WorldTransform* worldTransformTrap : worldTransformTrapLine) {
				if (!worldTransformTrap)
					continue;
				modelTrap_->Draw(*worldTransformTrap, viewProjection_);
			}
		}

		for (std::vector<WorldTransform*>& worldTransformGoalBlockLine : worldTransformGoalBlocks_) {
			for (WorldTransform* worldTransformGoalBlock : worldTransformGoalBlockLine) {
				if (!worldTransformGoalBlock)
					continue;
				MapChipField::IndexSet indexSet;
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransformGoalBlock->translation_);

				MapChipType mapChipType;

				mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

				if (mapChipType == MapChipType::kGoal) {

					modelGoal_->Draw(*worldTransformGoalBlock, viewProjection_);

					player_->IsClear();
				}
			}
		}

		break;
	case Phase::kGoal:
		// 天球の描画
		skydome_->Draw();

		// 自キャラの描画
		player_->Draw();

		// 敵キャラの描画
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}

		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();
	sprite2_->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// ブロックの生成
	worldTransformBlocks_1.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_1[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock1) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_1[i][j] = worldTransform;
				worldTransformBlocks_1[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// ブロックの生成
	worldTransformBlocks_2.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_2[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock2) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_2[i][j] = worldTransform;
				worldTransformBlocks_2[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// ブロックの生成
	worldTransformBlocks_3.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_3[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock3) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_3[i][j] = worldTransform;
				worldTransformBlocks_3[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformATK_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformATK_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kATK) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformATK_[i][j] = worldTransform;
				worldTransformATK_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformHP_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformHP_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kHPup) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformHP_[i][j] = worldTransform;
				worldTransformHP_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformWeekPoint_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformWeekPoint_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kWeekPoint) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformWeekPoint_[i][j] = worldTransform;
				worldTransformWeekPoint_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	worldTransformGoalBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformGoalBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kGoal) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformGoalBlocks_[i][j] = worldTransform;
				worldTransformGoalBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	worldTransformTraps_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformTraps_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kTrap) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformTraps_[i][j] = worldTransform;
				worldTransformTraps_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

// 全ての当たり判定を行う
void GameScene::CheckAllCollisions() {
#pragma region 自キャラと敵キャラの当たり判定
	{
		Vector3 posA, posB;

		// 自キャラの座標
		posA = player_->GetWorldPosition();

		// 自キャラと敵キャラの当たり判定
		for (Enemy* enemy : enemies_) {
			// 敵キャラの座標
			posB = enemy->GetWorldPosition();

			Vector3 distance = Subtract(posB, posA);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 1.0f) {
				// 自キャラの衝突時コールバックを呼び出す
				player_->OnCollision(enemy);
				// 敵キャラの衝突時コールバックを呼び出す
				enemy->OnCollision(player_);
			}
		}

		Vector3 posC, posD;

		// 自キャラの弾
		Playerbullets_ = player_->GetBullets();

		for (PlayerBullet* bullet : Playerbullets_) {
			posC = bullet->GetWorldPosition();

			// 敵キャラと弾の当たり判定
			for (Enemy* enemy : enemies_) {
				// 敵キャラの座標
				posD = enemy->GetWorldPosition();

				Vector3 distance = Subtract(posD, posC);

				// 交差判定
				if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 1.0f) {
					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(enemy);
					// 敵キャラの衝突時コールバックを呼び出す
					enemy->OnCollision(bullet);
				}
			}
		}

		Vector3 posG, posH;

		// 自キャラの弾
		enemySkyBullet_ = enemySkydome_->GetBullets();

		for (EnemySkydomeBullet* bullet : enemySkyBullet_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}

		// 自キャラの弾
		enemySkyListBullet1_ = enemySkydome1_->GetBullets();

		for (EnemySkydomeBullet1* bullet : enemySkyListBullet1_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}
		// 自キャラの弾
		enemySkyListBullet2_ = enemySkydome2_->GetBullets();

		for (EnemySkydomeBullet2* bullet : enemySkyListBullet2_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}
		// 自キャラの弾
		enemySkyListBullet3_ = enemySkydome3_->GetBullets();

		for (EnemySkydomeBullet3* bullet : enemySkyListBullet3_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}
		// 自キャラの弾
		enemySkyListBullet4_ = enemySkydome4_->GetBullets();

		for (EnemySkydomeBullet4* bullet : enemySkyListBullet4_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}

				// 自キャラの弾
		enemySkyListBullet5_ = enemySkydome5_->GetBullets();

		for (EnemySkydomeBullet5* bullet : enemySkyListBullet5_) {
			posG = bullet->GetWorldPosition();

			// 敵キャラの座標
			posH = player_->GetWorldPosition();

			Vector3 distance = Subtract(posG, posH);

			// 交差判定
			if ((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z) <= 8.0f) {

				if (isInvisible_ == false) {
					nowHp -= rand() % 11 + 101;
					isInvisible_ = true;
				}
				if (nowHp <= 0) {
					nowHp = 0;
					player_->Dead();

					// 自キャラの弾の衝突時コールバックを呼び出す
					bullet->OnCollision(player_);
					// 敵キャラの衝突時コールバックを呼び出す
					player_->OnCollision(bullet);
				}
			}
			if (isInvisible_ == true) {
				invisibleTimmer--;
			}
			if (invisibleTimmer <= 0) {
				isInvisible_ = false;
				invisibleTimmer = 60 * 5;
			}
		}
	}
}

// フェーズの切り替え
void GameScene::ChangePhase() {
	switch (phase_) {
	case Phase::kPlay:
		// ゲームプレイフェーズの処理
		if (player_->IsDead()) {
			// 死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;
			// 自キャラの座標を取得
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();

			// パーティクルの初期化
			deathParticles_->Initialize(modelDeathParticles_, &viewProjection_, deathParticlesPosition);
		}
		break;
	case Phase::kDeath:
		// デス演出フェーズの処理
		break;
	}
}