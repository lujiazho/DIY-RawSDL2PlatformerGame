#include "SpriteEnemy.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"

static Registrar<SpriteEnemy> registrar("ENEMY");

SpriteEnemy::SpriteEnemy(Properties* props) : Character(props) {
	m_IsDead = false;
	m_IsAttacked = false;
	m_IsAttacking = false;

	m_ATTACKED_TIME = props->AttackedTime;
	m_ATTACK_TIME = props->AttackTime;
	m_WALK_FORCE = props->WalkForce;
	m_damage = props->Damage;
	m_sprites = props->Sprites;
	m_spritesLen = props->SpritesLen;
	m_spritesSpeed = props->SpritesSpeed;

	m_Collider = new Collider();
	m_Collider->SetBuffer(-20, 0, 40, -20); // 调整碰撞框

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.5f); // 设置重力

	m_Animation = new SpriteAnimation();

	m_Condition = new Condition(20, 100);
	m_Condition->SetBuffer(0, 0, 0, 0);
}

void SpriteEnemy::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1.0, 1.0, m_Flip);
	m_Collider->Draw();
	m_Condition->Draw();
}

void SpriteEnemy::Update(float dt) {
	m_RigidBody->UnsetForce();
	float player_x = CollisionHandler::GetInstance()->GetPlayerPosition()->X;
	if (!m_IsDead && player_x < m_Transform->X && m_Transform->X - player_x > 20) {
		m_RigidBody->ApplyForceX(BACKWARD * m_WALK_FORCE);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsWalking = true;
		//m_Collider->SetBuffer(-30, -15, 60, 0); // 镜像后有点移位，因此调整下
	}
	if (!m_IsDead && player_x > m_Transform->X && player_x - m_Transform->X > 20) {
		m_RigidBody->ApplyForceX(FORWARD * m_WALK_FORCE);
		m_Flip = SDL_FLIP_NONE;
		m_IsWalking = true;
	}

	// Move on X axis
	m_RigidBody->Update(dt); // 计算加速度、速度、位置
	m_LastSafePosition.X = m_Transform->X; // 记住上一次的位置，碰撞时弹回
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 56, 32);
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	// Move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 56, 32);
	// 血条
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}
	// 被打
	if (CollisionHandler::GetInstance()->CheckCollisionWithPlayer(m_Collider->Get()) && !m_IsAttacked) {
		m_IsAttacked = true;
		m_Condition->ChangeLifePoint(-2);
		if (m_Condition->GetLifePoint() <= 0) {
			//m_Xoffset = -120;
			//m_Yoffset = -5;
			m_IsDead = true;
			m_IsAttacked = false;
			m_IsAttacking = false;
		}
	}

	// Attack
	if (CollisionHandler::GetInstance()->CheckUnderAttackRange(m_Collider->Get()) && !m_IsAttacking && !m_IsAttacked && !m_IsDead) {
		m_IsAttacking = true;
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
		m_AttackTime = m_ATTACK_TIME;
	}

	// Attacked timer
	if (m_IsAttacked && m_AttackedTime > 0) {
		//m_Xoffset = -60;
		//m_Yoffset = -38;
		m_AttackedTime -= dt;
	}
	else {
		m_IsAttacked = false;
		m_AttackedTime = m_ATTACKED_TIME;
	}

	if (player_x > m_Transform->X && !m_IsDead) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		m_Flip = SDL_FLIP_NONE;
	}

	/*m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;*/

	AnimationState();
	m_Animation->Update(dt);
}

void SpriteEnemy::AnimationState() {
	m_Animation->SetProps((*m_sprites)[0], 1, (*m_spritesLen)[0], (*m_spritesSpeed)[0]);

	if (m_IsWalking) {
		m_Animation->SetProps((*m_sprites)[1], 1, (*m_spritesLen)[1], (*m_spritesSpeed)[1]);
	}

	if (m_IsAttacking) {
		m_Animation->SetProps((*m_sprites)[2], 1, (*m_spritesLen)[2], (*m_spritesSpeed)[2]); // 第四个参数减少增加攻速
	}

	if (m_IsAttacked) {
		m_Animation->SetProps((*m_sprites)[3], 1, (*m_spritesLen)[3], (*m_spritesSpeed)[3]);
	}

	if (m_IsDead) {
		m_Animation->SetProps((*m_sprites)[4], 1, (*m_spritesLen)[4], (*m_spritesSpeed)[4]);
	}
}

void SpriteEnemy::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}
