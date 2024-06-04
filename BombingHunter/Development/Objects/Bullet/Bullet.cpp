#include "Bullet.h"
#include "DxLib.h"


//コンストラクタ
Bullet::Bullet() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Bullet::~Bullet()
{

}

//初期化処理
void Bullet::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Bomb/Bomb.png");


	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("エネミーバレットの画像がありません\n");
	}

	//向きの設定
	radian = -1.6f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.0f, 0.5f);
}

//更新処理
void Bullet::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}
//描画処理
void Bullet::Draw()const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基に弾丸画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bullet::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//direction = 0.0f;
}
//移動処理
void Bullet::Movement()
{
	//画面の端に到達したら、進行方向を反転する
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
		//direction.x *= -1.0f;
	//}

	//if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	//{
		//direction.y *= -1.0f;
	//}


	//現在の位置情報に速さを加算する
	location += direction;
}

//アニメーション制御
void Bullet::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
