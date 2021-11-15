#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "SeqAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Condition.h"

#define ENEMY_ATTACKED_TIME 10.0f
#define ENEMY_ATTACK_TIME 75.0f

class Enemy : public Character {
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	bool IsAttacking() { return m_IsAttacking; }

private:
	bool m_IsDead;
	bool m_IsAttacked;
	bool m_IsAttacking;

	float m_AttackedTime;
	float m_AttackTime;

	int m_damage;

	int m_Xoffset, m_Yoffset; // ��ͬ����ͼ��size��һ�£���Ҫλ��

	Collider* m_Collider; // ��ɫ�ԵĿ�
	SeqAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition; // ����ʱ��λ��

	Condition* m_Condition; // Ѫ����
};

#endif // ENEMY_H