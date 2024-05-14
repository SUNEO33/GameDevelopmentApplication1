#pragma once
#define D_KEYCODE_MAX (256)  //キー入力最大値

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];      //現在の入力値
	static char old_key[D_KEYCODE_MAX];      //前回の入力値

public:
	static void Update();                    //更新処理

	static bool GetKey(int key_code);        //押し続けているか？
	static bool GetKeyDown(int key_code);    //押した瞬間か？
	static bool GetKeyUp(int key_code);      //離した瞬間か？

private:
	static bool CheckKeyCodeRange(int key_code);     //キーコード範囲チェック
};

