#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Condition.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

#define RUN_FORCE 5.0f
#define ATTACK_TIME 20.0f
#define ATTACKED_TIME 10.0f

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	bool IsAttacking() { return m_IsAttacking; }
	bool IsDead() { return m_IsDead; }

	void SetAttacked() { m_IsAttacked = true; }
	void SetUnderDmage(int damage) { m_underDamage = damage; }

private:
	void AnimationState();

private:
	// 状态
	bool m_IsRunning;
	bool m_IsJumping;
	bool m_IsFalling;
	bool m_IsGrounded;
	bool m_IsAttacking;
	bool m_IsCrouching;
	bool m_IsAttacked;
	bool m_IsDead;

	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;
	float m_AttackedTime;

	int m_underDamage;

	Collider* m_Collider; // 角色旁的框
	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition; // 弹回时的位置

	Condition* m_Condition; // 血条等
};

#endif // WARRIOR_H