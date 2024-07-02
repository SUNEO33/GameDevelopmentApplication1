#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//背景画像
int back_img1;
//BGM
int background_sound;
//メイン関数（プログラムはここから始まります。）
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//Windowモードで起動
	ChangeWindowMode(TRUE);

	//ウィンドウサイズ（横：640px, 縦：480px）を設定
	SetGraphMode(640, 480, 32);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1)
	{
		//異常を通知
		return -1;
	}
	//制限時間
	int timediff;
	LONGLONG timelimit = GetNowHiPerformanceCount() + 30000000;
	// BGMの読み込み
	background_sound = LoadSoundMem("Resource/sounds/Evaluation/BGM_arrows.wav");


	//ローカル変数定義
	Scene* scene = new Scene();     //シーン情報
	int result = 0;                 //終了状態情報

	//描画先を裏画面から始めるように指定する
	SetDrawScreen(DX_SCREEN_BACK);


	try
	{

		//BGMの再生
		PlaySoundMem(background_sound, DX_PLAYTYPE_BACK, FALSE);
		//シーンの初期化
		scene->Initialize();

		//メインループ（ウィンドウの異常発生 or ESCキーが押されたら、ループ終了）
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			
			//入力機能の更新
			InputControl::Update();

			//シーンの更新処理
			scene->Update();

			timediff = int(timelimit - GetNowHiPerformanceCount());

			//画面の初期化
			ClearDrawScreen();


			//背景画像
			back_img1 = LoadGraph("Resource/Images/BackGround.png");
			DrawGraph(0, -180, back_img1, TRUE);

			//時間表示
			DrawFormatString(5, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timediff / 60000000, (timediff % 60000000) / 1000000, ((timediff % 60000000) % 1000000) / 100000, (((timediff % 60000000) % 1000000) % 100000) / 10000);

			//制限時間が0になったらゲーム終了させる
			if (timediff < 0) {
				break;

			}
			//シーンの描画処理
			scene->Draw();
			


			//裏画面の内容を表画面に反映する
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//エラー情報をLog.txtに出力する
		OutputDebugString(error_log);
		//異常状態に変更する
		result = -1;
	}

	//シーン情報を削除する
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
	
		
	//DXライブラリの終了時処理
	DxLib_End();

	//終了状態を通知
	return result;
}