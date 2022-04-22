#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;
//コンストラクタ
GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene() {
	//delete sprite_;
	//delete model_;

	delete spriteBG_; //GB
	delete modelStage_; //ステージ
	delete modelPlayer_; //プレイヤー
}


//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	

	//textureHandle_ = TextureManager ::Load("pic.png");

	//生成
	//sprite_ = Sprite ::Create(textureHandle_, {100, 50});
	//音声
	//soundDataHandle_ = audio_->LoadWave("mokugyo.wav");

	//audio_->PlayWave(soundDataHandle_);

	//3D生成
	//model_ = Model ::Create();
	//ワールドトンランスフォーム初期化
	ｗorldTransform_.Initialize();
	//ビュープロジェクション初期化
	viewProjection_.Initialize();

	//音声再生
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
	// 
	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
	//背景　ステージ
	//BG(2Dスプライト)背景
	textureHandleBG_ = TextureManager ::Load("bg.jpg");
	spriteBG_ = Sprite ::Create(textureHandleBG_, {0,0,});

	//ビュープロジェクションの初期化
	viewProjection_ .Initialize();
	//ステージ表示(拡大　移動)
	viewProjection_.eye = {0, 1, -6};
	viewProjection_.target = {0, 1, 0};
	viewProjection_.Initialize();

	modelStage_ = Model ::Create();
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	worldTransformStage_.Initialize();

	//ステージ
	textureHandleStage_ = TextureManager ::Load("stage.jpg");
	modelStage_ = Model ::Create();
	worldTransformStage_.Initialize();
	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

	//プレイヤー
	textureHandlePlayer_ = TextureManager ::Load("player.png");
	modelPlayer_ = Model ::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
}
//更新
void GameScene::Update()  
{
	/*if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}*/

	value_++;

	/*std ::string strDebug = std::string("value") +
	std ::to_string(value_);*/
	//debugText_->Print(strDebug, 50, 50, 1.0f);


	PlayerUpdate(); //プレイヤー更新
}
//表示
	void GameScene::Draw() {


	//XMFLOAT2 position = sprite_->GetPosition();

	/*position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);*/
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	//背景
	spriteBG_->Draw();

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	//ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(ｗorldTransform_, viewProjection_, textureHandle_);
	//プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
    #pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	
	/// </summary>
	//sprite_ ->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();
	
#pragma endregion
    }

	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
	//プレイヤーの更新
    void GameScene::PlayerUpdate()
	{
		//移動
		//右移動
	    if (input_->PushKey(DIK_RIGHT))
		{
		    worldTransformPlayer_.translation_.x += 0.1f;	    
		}

		//左移動
	    if (input_->PushKey(DIK_LEFT))
		{
		    worldTransformPlayer_.translation_.x -= 0.1f;	
		}

		//行列更新
	    worldTransformPlayer_.UpdateMatrix();

	}

