#pragma once
#define D_KEYCODE_MAX (256)  //�L�[���͍ő�l

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];      //���݂̓��͒l
	static char old_key[D_KEYCODE_MAX];      //�O��̓��͒l

public:
	static void Update();                    //�X�V����

	static bool GetKey(int key_code);        //���������Ă��邩�H
	static bool GetKeyDown(int key_code);    //�������u�Ԃ��H
	static bool GetKeyUp(int key_code);      //�������u�Ԃ��H

private:
	static bool CheckKeyCodeRange(int key_code);     //�L�[�R�[�h�͈̓`�F�b�N
};

