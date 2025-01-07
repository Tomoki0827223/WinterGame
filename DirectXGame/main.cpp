#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

#include "ClearScene.h"
#include "FailureScene.h"
#include "SelectStage.h"
#include "Setumei.h"
#include "TitleScene.h"

// #include "SceneTransitionEffect.h"

// シーン（型）
enum class Scene {

	kUnknown = 0,

	kTitleScene,
	kStageTitle,
	kGame,
	ksetumei,
	kFailure,
	kClear,
};

int mapNumber = 0;

// タイトルシーン
TitleSence* titleScene = nullptr;
// ステージセレクト
SelectStage* selectScnce = nullptr;
// ゲームシーン
GameScene* gameScene = nullptr;
// ゲームオーバーシーン
FailureScene* failureScene = nullptr;
// ゲームクリアシーン
ClearScene* clearScene = nullptr;

Setumei* setumei = nullptr;

// SceneTransitionEffect* transitionEffect = nullptr;

// 現在シーン（型）
Scene scene = Scene::kUnknown;

void ChangeScene();
void UpdateScene();
void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"スペースジャンプ");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// 最初のシーン(タイトル)の初期化
	scene = Scene::kTitleScene;
	titleScene = new TitleSence();
	titleScene->Initialize();

	selectScnce = new SelectStage();
	selectScnce->Initialize();

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(0);

	// ゲームオーバーシーンの初期化
	failureScene = new FailureScene();
	failureScene->Initialize();

	// ゲームクリアシーンの初期化
	clearScene = new ClearScene();
	clearScene->Initialize();

	setumei = new Setumei();
	setumei->Initialize();

	// transitionEffect = new SceneTransitionEffect(100);

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		// シーン切り替え
		ChangeScene();
		// 現在シーン更新
		UpdateScene();

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();

		// 現在シーンの描画
		DrawScene();

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete titleScene;
	delete selectScnce;
	delete gameScene;
	delete failureScene;
	delete clearScene;
	delete setumei;

	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene() {
	// 既に初期化されているInputインスタンスを使用
	Input* input_ = Input::GetInstance();

	//// エフェクトが再生中ならシーン切り替えを待機
	// if (transitionEffect->IsPlaying()) {
	//	return;
	// }

	switch (scene) {
	case Scene::kTitleScene:
		if (titleScene->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kStageTitle;
			delete titleScene;
			titleScene = nullptr;

			selectScnce = new SelectStage();
			selectScnce->Initialize();
		}
		break;

	case Scene::kStageTitle:
		if (selectScnce->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			int selectedStage = selectScnce->GetStageNumber();
			delete selectScnce;
			selectScnce = nullptr;

			gameScene = new GameScene();
			gameScene->Initialize(selectedStage); // StageNumber_に基づいてステージを初期化
			scene = Scene::kGame;
		}

		// RETURNキーが押された場合、説明シーンに遷移
		if (input_->TriggerKey(DIK_RETURN)) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::ksetumei;
			delete setumei; // Corrected: Delete previous setumei if exists
			setumei = new Setumei();
			setumei->Initialize();
		}

		break;

	case Scene::kGame:
		if (gameScene->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kFailure;
			delete gameScene;
			gameScene = nullptr;

			failureScene = new FailureScene();
			failureScene->Initialize();
		} else if (gameScene->IsGoalFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kClear;
			delete gameScene;
			gameScene = nullptr;

			clearScene = new ClearScene();
			clearScene->Initialize();
		}

		// Kキーが押された場合、ステージ選択シーンに遷移
		if (input_->TriggerKey(DIK_K)) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kStageTitle;
			delete selectScnce; // Corrected: Delete selectScnce instead of titleScene
			selectScnce = nullptr;

			selectScnce = new SelectStage();
			selectScnce->Initialize();
		}
		break;

	case Scene::ksetumei:
		if (!setumei) {
			setumei = new Setumei();
			setumei->Initialize();
		}
		if (setumei->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kTitleScene;
			delete setumei;
			setumei = nullptr;

			titleScene = new TitleSence();
			titleScene->Initialize();
		}

		// RETURNキーが押された場合、ゲームシーンに戻る
		if (input_->TriggerKey(DIK_RETURN)) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kStageTitle;
			delete setumei;    // Ensure previous setumei is deleted
			setumei = nullptr; // Reset setumei to nullptr to avoid dangling pointer

			selectScnce = new SelectStage();
			selectScnce->Initialize();
		}
		break;

	case Scene::kFailure:
		if (failureScene->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kTitleScene;
			delete failureScene;
			failureScene = nullptr;

			titleScene = new TitleSence();
			titleScene->Initialize();
		}
		break;

	case Scene::kClear:
		if (clearScene->IsFinished()) {
			// エフェクト開始
			// transitionEffect->StartEffect(Vector3(0, 0, 0), 50);
			scene = Scene::kTitleScene;
			delete clearScene;
			clearScene = nullptr;

			titleScene = new TitleSence();
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	// パーティクルエフェクトを更新
	// transitionEffect->Update(1.0f / 60.0f);

	switch (scene) {
	case Scene::kTitleScene:
		titleScene->Update();
		break;
	case Scene::kStageTitle:
		selectScnce->Update();
		break;
	case Scene::ksetumei:
		setumei->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kFailure:
		failureScene->Update();
		break;
	case Scene::kClear:
		clearScene->Update();
		break;
	}
}

void DrawScene() {
	// シーンに応じた描画
	switch (scene) {
	case Scene::kTitleScene:
		titleScene->Draw();
		break;
	case Scene::kStageTitle:
		selectScnce->Draw();
		break;
	case Scene::ksetumei:
		setumei->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kFailure:
		failureScene->Draw();
		break;
	case Scene::kClear:
		clearScene->Draw();
		break;
	}

	// パーティクルエフェクトの描画
	// transitionEffect->Draw();
}
