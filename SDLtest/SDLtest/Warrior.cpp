#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"

static Registrar<Warrior> registrar("PLAYER");

Warrior::Warrior(Properties* props): Character(props) {
	//// the smaller, the faster;
	//// because this means how much milisecond represents a single state 
	//// from a series of states of a character
	//m_AnimSpeed = 80;
	m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsCrouching = false;
	m_IsAttacked = false;
	m_IsDead = false;

	m_Flip = SDL_FLIP_NONE;
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;
	m_AttackedTime = ATTACKED_TIME;

	m_Collider = new Collider();
	m_Collider->SetBuffer(-25, -15, 60, 0); // 调整碰撞框

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f); // 设置重力

	m_Animation = new SpriteAnimation();
	m_Animation->SetProps(m_TextureID, 1, 6, 80);

	m_Condition = new Condition(200, 100);
	m_Condition->SetBuffer(0, 0, 0, 0);
}

void Warrior::Draw() {
	//TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1.0, 1.0, m_Flip);

	/// <summary>
	/// 画角色旁边的框
	/// </summary>
	m_Collider->Draw();

	m_Condition->Draw();
}

void Warrior::Update(float dt) {
	
	//m_Animation->SetProps("player", 1, 6, 100);
	m_IsRunning = false;
	m_IsCrouching = false;
	m_Flip = SDL_FLIP_NONE;
	m_Collider->SetBuffer(-25, -15, 60, 0);
	m_RigidBody->UnsetForce();

	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
		m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
		m_Collider->SetBuffer(-30, -15, 60, 0); // 镜像后有点移位，因此调整下
	}
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking) {
		m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}

	if (Input::GetInstance()->GetAxisKey(VERTICAL) == DOWNWARD) {
		m_RigidBody->UnsetForce();
		m_IsCrouching = true;
	}

	// Attack
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && !m_IsDead) {
		m_RigidBody->UnsetForce();
		m_IsAttacking = true;
	}

	// Jump 按W跳
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce); // 加力，还没计算加速度
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce); // 长按跳得更高
	}
	else {
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	// Fall
	if (m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded) {
		m_IsFalling = true;
	}
	else {
		m_IsFalling = false;
	}

	// Attack timer
	if (m_IsAttacking && m_AttackTime > 0) {
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}

	if (m_IsAttacked && m_AttackedTime == ATTACKED_TIME) {
		m_Condition->ChangeLifePoint(-m_underDamage);
		if (m_Condition->GetLifePoint() <= 0) {
			m_IsRunning = false;
			m_IsJumping = false;
			m_IsFalling = false;
			m_IsGrounded = true;
			m_IsAttacking = false;
			m_IsCrouching = false;
			m_IsAttacked = false;
			m_IsDead = true;
		}
	}

	// Attacked timer
	if (m_IsAttacked && m_AttackedTime > 0) {
		m_AttackedTime -= dt;
	}
	else {
		m_IsAttacked = false;
		m_AttackedTime = ATTACKED_TIME;
	}
	//SDL_Log("%d", m_IsAttacked);

	// Move on X axis
	m_RigidBody->Update(dt); // 计算加速度、速度、位置
	m_LastSafePosition.X = m_Transform->X; // 记住上一次的位置，碰撞时弹回
	m_Transform->X += m_RigidBody->GetPosition().X;
	//m_Transform->TranslateX(m_RigidBody->GetPosition().X); // 最好不要直接加，而是调用public函数
	m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 44);
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w * 15, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	// Move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 44);
	m_Condition->Set(m_Transform->X, m_Transform->Y - int(m_Collider->Get().h * 0.2), m_Collider->Get().w * 15, int(m_Collider->Get().h * 0.1));

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}

	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();
	m_Animation->Update(dt);
}

void Warrior::AnimationState() {
	m_Animation->SetProps("player", 1, 6, 100);

	if (m_IsRunning) {
		m_Animation->SetProps("player_run", 1, 8, 50);
	}

	if (m_IsCrouching) {
		m_Animation->SetProps("player_crouch", 1, 4, 200);
	}

	if (m_IsJumping) {
		m_Animation->SetProps("player_jump", 1, 3, 200);
	}

	if (m_IsFalling) {
		m_Animation->SetProps("player_fall", 1, 3, 200);
	}

	if (m_IsAttacking) {
		m_Animation->SetProps("player_attack", 1, 12, 50); // 第四个参数减少增加攻速
	}

	if (m_IsAttacked) {
		m_Animation->SetProps("player_hurt", 1, 4, 200);
	}

	if (m_IsDead) {
		m_Animation->SetProps("player_die", 1, 11, 100);
	}
}

void Warrior::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}
