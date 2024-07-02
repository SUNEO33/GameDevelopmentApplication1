#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/WingEnemy/WingEnemy.h"
#include "../Objects/Bullet/Bullet.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Fireball/Fireball.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects()
{

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//スコア
	Score = 0.0f;
	DrawScore = 0;
	B_flg = false;
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
	//ウィングエネミーを生成する
	CreateObject<WingEnemy>(Vector2D(0.0f, 140.0f));
	//ハーピーを生成する
	CreateObject<Harpy>(Vector2D(0.0f, 330.0f));
	//ハコテキを生成する
	CreateObject<Enemy>(Vector2D(40.0f, 400.0f));
	
}

//更新処理
void Scene::Update()
{


	DrawScore++;
	if (DrawScore > Score) {
		DrawScore = Score;
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Cキーを押したら、ウィングエネミーを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<WingEnemy>(Vector2D(0.0f, 140.0f));
	}

	///Zキーを押したら、ハコテキを生成する
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	CreateObject<Enemy>(Vector2D(40.0f, 400.0f));
	//}

	//Xキーを押したら、ハーピーを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_X))
	{
		CreateObject<Harpy>(Vector2D(0.0f, 330.0f));
	}

	//スペースキーを押したら、弾丸を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE)) 
	{
		if (B_flg == false) {
			for (int i = 0; i < objects.size(); i++)
			{
				if (!(dynamic_cast<Player*>(objects[i]) == nullptr))
				{
					CreateObject<Bullet>(objects[i]->GetLocation());
					B_flg = true;
				}
			}
		}
		
	}
	Vector2D location;
	//弾丸が画面外にいったら弾丸を生成する
	for (int i = 0; i < objects.size(); i++)
	{
		if (!(dynamic_cast<Bullet*>(objects[i]) == nullptr))
		{
			location=objects[i]->GetLocation();
			if (location.y >= 480) {
				this->objects.erase(objects.begin() + i);
				B_flg = false;
			}
			
		}
	}

	//Vを押したら、弾丸を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_V)) 
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (!(dynamic_cast<Enemy*>(objects[i]) == nullptr))
			{
				CreateObject<Fireball>(objects[i]->GetLocation());
			}
		}
	}

	//敵が完璧に消える処理
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->DeleteObject() == true)
		{
			this->objects.erase(objects.begin() + i);
			Score += 0.5f;
			CreateObject<Enemy>(Vector2D(0.0f, 200.0f));
			B_flg = false;
			CreateObject<Harpy>(Vector2D(0.0f, 330.0f));
			CreateObject<WingEnemy>(Vector2D(0.0f, 140.0f));
		}
	}
	
}

//描画処理
void Scene::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	DrawFormatString(500, 5, GetColor(255, 255, 255), "得点：%3d", DrawScore);
	//DrawFillBox(150, 100, 150 + DrawScore, 116, GetColor(0, 255, 255));
	//DrawLineBox(150, 100, 450, 116, GetColor(255, 255, 255));
}

//終了時処理
void Scene::Finalize()
{


	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}
	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定をとる）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
		
	}
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER