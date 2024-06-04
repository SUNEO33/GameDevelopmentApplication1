#include "WingEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//�R���X�g���N�^
WingEnemy::WingEnemy() : animation_count(0), flip_flag(FALSE)
{
	anima[0] = NULL;
	anima[1] = NULL;
}

//�f�X�g���N�^
WingEnemy::~WingEnemy()
{

}

//����������
void WingEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	anima[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	anima[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	//�G���[�`�F�b�N
	if (anima[0] == -1 || anima[1] == -1)
	{
		throw("�E�B���O�G�l�~�[�̉摜������܂���\n");
	}


	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = anima[0];
}

//�X�V����
void WingEnemy::Update()
{
	location.x += 1.0f;     //�ʒu���̍X�V

	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}
	//�ړ�����
	//Movement();
	//�A�j���[�V��������
	AnimationControl();
}
//�`�揈��
void WingEnemy::Draw()const
{
	//�E�B���O�G�l�~�[�摜�̕`��
	DrawRotaGraphF(location.x, 390, 0.5, radian, image, TRUE, flip_flag);
	
	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);
	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);

#endif

}

//�I��������
void WingEnemy::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(anima[0]);
	DeleteGraph(anima[1]);
}

//�����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}
//�ړ�����
void WingEnemy::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x += 0.0f;
	}
	//���݂̈ʒu���ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void WingEnemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == anima[0])
		{
			image = anima[1];
		}
		else
		{
			image = anima[0];
		}
	}
}