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
	// 状态
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

	Collider* m_Collider; // 角色旁的框
	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition; // 弹回时的位置

	Condition* m_Condition; // 血条等
	// idle, walk, attack, hurt, die
	std::vector<std::string>* m_sprites; // 对应的sprites名
	std::vector<int>* m_spritesLen; // 对应的sprites长度
	std::vector<int>* m_spritesSpeed; // 对应的sprites速度
};

#endif // SPRITEENEMY_H