#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Warrior.h"
#include "Condition.h"
#include "TextureManager.h"

static Registrar<Enemy> registrar("tBettle");

Enemy::Enemy(Properties* props) :Character(props) {
	m_IsDead = false;
	m_IsAttacked = false;
	m_IsAttacking = false;

	m_AttackedTime = ENEMY_ATTACKED_TIME;
	m_AttackTime = ENEMY_ATTACK_TIME;

	m_damage = props->Damage;

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.5f); // 设置重力

	m_Collider = new Collider();
	m_Collider->SetBuffer(-10, 0, 30, 0); // 调整碰撞框

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/animation.aml");
	m_Animation->SetCurrentSeq("tBettle_appear");
	m_Animation->SetRepeat(true);

	m_Condition = new Condition(100, 100);
	m_Condition->SetBuffer(0, 0, 0, 0);
}

void Enemy::Draw() {
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 0.1f, 0.1f, m_Flip); // 把enemy放小
	
	m_Collider->Draw();
	m_Condition->Draw();
}

void Enemy::Update(float dt) {
	// Move on X axis
	m_RigidBody->Update(dt); // 计算加速度、速度、位置
	m_LastSafePosition.X = m_Transform->X; // 记住上一次的位置，碰撞时弹回
	m_Transform->X += m_RigidBody->GetPosition().X;
	//m_Transform->TranslateX(m_RigidBody->GetPosition().X); // 最好不要直接加，而是调用public函数
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	// Move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);
	// 血条
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	// 被打
	if (CollisionHandler::GetInstance()->CheckCollisionWithPlayer(m_Collider->Get()) && !m_IsAttacked) {
		m_IsAttacked = true;
		m_Condition->ChangeLifePoint(-2);
		m_Animation->SetCurrentSeq("tBettle_get_hit");
		if (m_Condition->GetLifePoint() <= 0) {
			//m_Xoffset = -120;
			//m_Yoffset = -5;
			m_IsDead = true;
			m_IsAttacked = false;
			m_IsAttacking = false;
			m_Animation->SetCurrentSeq("tBettle_die");
			m_Animation->SetRepeat(false);
		}
	}

	// Attack
	if (CollisionHandler::GetInstance()->CheckUnderAttackRange(m_Collider->Get()) && !m_IsAttacking && !m_IsAttacked && !m_IsDead) {
		m_IsAttacking = true;
		m_Animation->SetCurrentSeq("tBettle_attack");
		CollisionHandler::GetInstance()->SetPlayerAttacked();
		CollisionHandler::GetInstance()->SetUnderDamage(m_damage);
	}

	// Attack timer
	if (m_IsAttacking && m_AttackTime > 0) {
		//m_Xoffset = -30;
		//m_Yoffset = -5;
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ENEMY_ATTACK_TIME;
	}

	// Attacked timer
	if (m_IsAttacked && m_AttackedTime > 0) {
		//m_Xoffset = -60;
		//m_Yoffset = -38;
		m_AttackedTime -= dt;
	}
	else {
		m_IsAttacked = false;
		m_AttackedTime = ENEMY_ATTACKED_TIME;
	}
	/*SDL_Log("%d %d %d %d", CollisionHandler::GetInstance()->GetPlayerPosition()->X,
		CollisionHandler::GetInstance()->GetPlayerPosition()->Y,
		GetOrigin()->X,
		GetOrigin()->Y);*/
	if (CollisionHandler::GetInstance()->GetPlayerPosition()->X > m_Transform->X && !m_IsDead) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		m_Flip = SDL_FLIP_NONE;
	}

	m_Animation->Update(dt);

	if (m_Animation->IsEnded()) {
		//m_Xoffset = 0;
		//m_Yoffset = 0;
		if (!m_IsDead) {
			m_Animation->SetRepeat(true);
			m_Animation->SetCurrentSeq("tBettle_idle");
		}
		else {
			m_Animation->SetRepeat(false);
			m_Animation->SetCurrentSeq("tBettle_die");
		}
		//SDL_Log("%d %d", m_Xoffset, m_Yoffset);
	}
	//std::cout << (m_Animation->GetCurrentSeq()).TextureIDs[0] << std::endl;
}

void Enemy::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}