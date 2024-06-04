#include "Bullet.h"
#include "DxLib.h"


//�R���X�g���N�^
Bullet::Bullet() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Bullet::~Bullet()
{

}

//����������
void Bullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Bomb/Bomb.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�G�l�~�[�o���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = -1.6f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 0.5f);
}

//�X�V����
void Bullet::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}
//�`�揈��
void Bullet::Draw()const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������ɒe�ۉ摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bullet::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//direction = 0.0f;
}
//�ړ�����
void Bullet::Movement()
{
	//��ʂ̒[�ɓ��B������A�i�s�����𔽓]����
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
		//direction.x *= -1.0f;
	//}

	//if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	//{
		//direction.y *= -1.0f;
	//}


	//���݂̈ʒu���ɑ��������Z����
	location += direction;
}

//�A�j���[�V��������
void Bullet::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
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
