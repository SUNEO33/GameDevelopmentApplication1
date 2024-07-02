#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//�w�i�摜
int back_img1;
//BGM
int background_sound;
//���C���֐��i�v���O�����͂�������n�܂�܂��B�j
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//Window���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�i���F640px, �c�F480px�j��ݒ�
	SetGraphMode(640, 480, 32);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		//�ُ��ʒm
		return -1;
	}
	//��������
	int timediff;
	LONGLONG timelimit = GetNowHiPerformanceCount() + 30000000;
	// BGM�̓ǂݍ���
	background_sound = LoadSoundMem("Resource/sounds/Evaluation/BGM_arrows.wav");


	//���[�J���ϐ���`
	Scene* scene = new Scene();     //�V�[�����
	int result = 0;                 //�I����ԏ��

	//�`���𗠉�ʂ���n�߂�悤�Ɏw�肷��
	SetDrawScreen(DX_SCREEN_BACK);


	try
	{

		//BGM�̍Đ�
		PlaySoundMem(background_sound, DX_PLAYTYPE_BACK, FALSE);
		//�V�[���̏�����
		scene->Initialize();

		//���C�����[�v�i�E�B���h�E�ُ̈픭�� or ESC�L�[�������ꂽ��A���[�v�I���j
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			
			//���͋@�\�̍X�V
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();

			timediff = int(timelimit - GetNowHiPerformanceCount());

			//��ʂ̏�����
			ClearDrawScreen();


			//�w�i�摜
			back_img1 = LoadGraph("Resource/Images/BackGround.png");
			DrawGraph(0, -180, back_img1, TRUE);

			//���ԕ\��
			DrawFormatString(5, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timediff / 60000000, (timediff % 60000000) / 1000000, ((timediff % 60000000) % 1000000) / 100000, (((timediff % 60000000) % 1000000) % 100000) / 10000);

			//�������Ԃ�0�ɂȂ�����Q�[���I��������
			if (timediff < 0) {
				break;

			}
			//�V�[���̕`�揈��
			scene->Draw();
			


			//����ʂ̓��e��\��ʂɔ��f����
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//�G���[����Log.txt�ɏo�͂���
		OutputDebugString(error_log);
		//�ُ��ԂɕύX����
		result = -1;
	}

	//�V�[�������폜����
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
	
		
	//DX���C�u�����̏I��������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}