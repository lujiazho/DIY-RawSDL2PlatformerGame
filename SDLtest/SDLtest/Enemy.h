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

	int m_Xoffset, m_Yoffset; // 不同动作图像size不一致，需要位移

	Collider* m_Collider; // 角色旁的框
	SeqAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition; // 弹回时的位置

	Condition* m_Condition; // 血条等
};

#endif // ENEMY_H