#ifndef SPRITEENEMY_H
#define SPRITEENEMY_H

#include "Character.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Condition.h"
#include <vector>
#include <string>

class SpriteEnemy : public Character {
public:
	SpriteEnemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	bool IsAttacking() { return m_IsAttacking; }

	void SetAttackTime(float attacktime) { m_AttackTime = attacktime; }
	void SetAttackedTime(float attackedtime) { m_AttackedTime = attackedtime; }

private:
	void AnimationState();

private:
	// ״̬
	bool m_IsDead;
	bool m_IsWalking;
	bool m_IsAttacked;
	bool m_IsAttacking;

	float m_AttackedTime;
	float m_AttackTime;
	int m_damage;

	float m_ATTACK_TIME;
	float m_ATTACKED_TIME;
	int m_WALK_FORCE;

	Collider* m_Collider; // ��ɫ�ԵĿ�
	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition; // ����ʱ��λ��

	Condition* m_Condition; // Ѫ����
	// idle, walk, attack, hurt, die
	std::vector<std::string>* m_sprites; // ��Ӧ��sprites��
	std::vector<int>* m_spritesLen; // ��Ӧ��sprites����
	std::vector<int>* m_spritesSpeed; // ��Ӧ��sprites�ٶ�
};

#endif // SPRITEENEMY_H