#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1

class RigidBody {
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	// Setter for mass, gravity
	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	// Force
	inline void ApplyForce(Vector2D F) { m_Force = F; }
	inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
	inline void UnsetForce() { m_Force = Vector2D(0, 0); }

	// Friction
	inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
	inline void UnsetFriction() { m_Friction = Vector2D(0, 0); }

	// Getters
	inline float GetMass() { return m_Mass; }
	inline Vector2D GetPosition() { return m_Position; }
	inline Vector2D GetVelocity() { return m_Velocity; }
	inline Vector2D GetAcceleration() { return m_Acceleration; }

	// update method
	void Update(float dt) {
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
		m_Velocity = m_Acceleration * dt; // delta time
		m_Position = m_Velocity * dt;
	}

private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Position; // relative movement distance, not actual position
	Vector2D m_Velocity;
	Vector2D m_Acceleration;


};

#endif // RIGIDBODY_H