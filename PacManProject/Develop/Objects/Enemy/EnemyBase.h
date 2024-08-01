#pragma once

#include "../GameObject.h"


// エネミー状態
enum eEnemyState
{
	BACKHOME,		//元の場所に戻る
	TERRITORY,      //縄張り
	CHASE,		//追っかけ状態
	DIE,		// 死亡状態
};



class EnemyBase : public GameObject
{
protected:

	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:

	std::vector<int> move_animation;		// 移動のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	bool izike;                             //イジケ状態になったか
	float izike_time;                       //
	bool is_destroy;						// 死んだ状態になったか？
	Vector2D direction;
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	///bool GetPowerUp() const;

	/// <summary>
	/// パワーダウンさせる
	/// </summary>
	///void SetPowerDown();

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	///bool GetDestroy() const;


private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);
};