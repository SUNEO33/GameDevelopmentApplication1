#include "Fireball.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/Enemy.h"
#include "DxLib.h"


//�R���X�g���N�^
Fireball::Fireball() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Fireball::~Fireball()
{

}

//����������
void Fireball::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/1.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�΋ʂ̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = -1.6f;

	//�傫���̐ݒ�
	box_size = 32.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, -0.5f);
}

//�X�V����
void Fireball::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}
//�`�揈��
void Fireball::Draw()const
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

	//������ɉ΋ʉ摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Fireball::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Fireball::OnHitCollision(GameObject* hit_object)
{
	if (dynamic_cast<Fireball*>(hit_object) != nullptr)   
	{
		BulletSeartch = false;
	}
	else if (dynamic_cast<Enemy*>(hit_object) != nullptr)   
	{
		BulletSeartch = false;
	}
	else
	{
		BulletSeartch = true;
	}
	//�����������̏���
	//direction = 0.0f;
}
//�ړ�����
void Fireball::Movement()
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
void Fireball::AnimationControl()
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
