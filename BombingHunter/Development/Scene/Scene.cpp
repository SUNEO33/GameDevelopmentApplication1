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

//�R���X�g���N�^
Scene::Scene() : objects()
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�X�R�A
	Score = 0.0f;
	DrawScore = 0;
	B_flg = false;
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
	//�E�B���O�G�l�~�[�𐶐�����
	CreateObject<WingEnemy>(Vector2D(0.0f, 140.0f));
	//�n�[�s�[�𐶐�����
	CreateObject<Harpy>(Vector2D(0.0f, 330.0f));
	//�n�R�e�L�𐶐�����
	CreateObject<Enemy>(Vector2D(40.0f, 400.0f));
	
}

//�X�V����
void Scene::Update()
{


	DrawScore++;
	if (DrawScore > Score) {
		DrawScore = Score;
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//C�L�[����������A�E�B���O�G�l�~�[�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<WingEnemy>(Vector2D(0.0f, 140.0f));
	}

	///Z�L�[����������A�n�R�e�L�𐶐�����
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	CreateObject<Enemy>(Vector2D(40.0f, 400.0f));
	//}

	//X�L�[����������A�n�[�s�[�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_X))
	{
		CreateObject<Harpy>(Vector2D(0.0f, 330.0f));
	}

	//�X�y�[�X�L�[����������A�e�ۂ𐶐�����
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
	//�e�ۂ���ʊO�ɂ�������e�ۂ𐶐�����
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

	//V����������A�e�ۂ𐶐�����
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

	//�G�������ɏ����鏈��
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

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	DrawFormatString(500, 5, GetColor(255, 255, 255), "���_�F%3d", DrawScore);
	//DrawFillBox(150, 100, 150 + DrawScore, 116, GetColor(0, 255, 255));
	//DrawLineBox(150, 100, 450, 116, GetColor(255, 255, 255));
}

//�I��������
void Scene::Finalize()
{


	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}
	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
		
	}
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER