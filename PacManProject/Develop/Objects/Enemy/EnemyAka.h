#pragma once
#include "EnemyBase.h"


//// エネミー状態
//enum eEnemyState
//{
//	BACKHOME,		//元の場所に戻る
//	TERRITORY,      //縄張り
//	CHASE,		//追っかけ状態
//	DIE,		// 死亡状態
//};



class EnemyAka : public EnemyBase
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
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	Vector2D direction;

public:
	EnemyAka();
	virtual ~EnemyAka();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

public:
	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	eEnemyState GetEnemyState() const;


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