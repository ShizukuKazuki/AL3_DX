#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;
//コンストラクタ
GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene() {
	delete sprite_;
	delete model_;
}



void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	

	textureHandle_ = TextureManager ::Load("pic.png");

	//生成
	sprite_ = Sprite ::Create(textureHandle_, {100, 50});
	//音声
	soundDataHandle_ = audio_->LoadWave("mokugyo.wav");

	audio_->PlayWave(soundDataHandle_);

	//3D生成
	model_ = Model ::Create();
	//ワールドトンランスフォーム初期化
	ｗorldTransform_.Initialize();
	//ビュープロジェクション初期化
	viewProjection_.Initialize();

	//音声再生
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update()  
{
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}

	value_++;

	std ::string strDebug = std::string("value") +
	std ::to_string(value_);

	debugText_->Print(strDebug, 50, 50, 1.0f);
}

	void GameScene::Draw() {

	XMFLOAT2 position = sprite_->GetPosition();

	position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);
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
	model_->Draw(ｗorldTransform_, viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
    #pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	
	/// </summary>
	sprite_ ->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();
	
#pragma endregion
}
