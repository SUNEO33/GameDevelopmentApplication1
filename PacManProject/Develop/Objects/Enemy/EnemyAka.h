#pragma once
#include "EnemyBase.h"


//// �G�l�~�[���
//enum eEnemyState
//{
//	BACKHOME,		//���̏ꏊ�ɖ߂�
//	TERRITORY,      //�꒣��
//	CHASE,		//�ǂ��������
//	DIE,		// ���S���
//};



class EnemyAka : public EnemyBase
{
protected:

	// �i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:

	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	Vector2D velocity;						// �ړ���
	eEnemyState enemy_state;				// �v���C���[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
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
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	eEnemyState GetEnemyState() const;


private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);
};