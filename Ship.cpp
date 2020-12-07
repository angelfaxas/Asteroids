#include "Ship.hpp"
#include "App.hpp"
#include "Vector2.hpp"

#include <gl\GL.h>

//STL
#include <iostream>
#include <cmath>
#include "GameObject.hpp"
#include "Bullet.hpp"


namespace Engine

{ 
	
	static constexpr float MAX_VELOCITY = 500.0f;
    static constexpr float THRUST = 15.0f;
    static constexpr float DRAG_FORCE = 0.999f;
    static constexpr float ANGLE_OFFSET = 90.0f;
    static constexpr float BULLET_SPEED = 250;
	
	Ship::Ship(App *parent)
		: GameObject(1.0f, 0.0f, 250.0f), m_parent(parent) // TODO: RR: Contemplate using a component based design approach
	{
		std::cout << "Construction of ship\n";
		ChangeShip();
	}

	Ship::Ship(App *parent, float _x, float _y)
		: GameObject(1.0f, 0.0f, 250.0f), m_parent(parent)
	{
		m_position = Math::Vector2(_x, _y);
		std::cout << "Construction of ship\n";
		ChangeShip();
	}

	Ship::~Ship()
	{
		std::cout << "Destruction of ship\n";
	}

	void Ship::MoveUp()
	{
		ApplyImpulse(Math::Vector2(THRUST), m_angle + ANGLE_OFFSET);
	}

	void Ship::RotateLeft(float deltaTime)
	{

		m_angle += m_rotation * deltaTime;
	}

	void Ship::RotateRight(float deltaTime)
	{
		m_angle -= m_rotation * deltaTime;
	}

	void Ship::ApplyDrag(Math::Vector2 force)
	{
		m_velocity.x *= force.x;
		m_velocity.y *= force.y;
	}

	void Ship::Update(float deltaTime)
	{
		//calculate speed
		float speed =
			std::fabs(m_velocity.Length());

		//Cap speed
		if (speed > MAX_VELOCITY)
		{
			m_velocity.x = (m_velocity.x / speed) * MAX_VELOCITY;
			m_velocity.y = (m_velocity.y / speed) * MAX_VELOCITY;
		}

		//Set new state
		m_currentSpeed = speed;
		m_position.x += m_velocity.x * deltaTime;
		m_position.y += m_velocity.y * deltaTime;

		//Applies drag

		ApplyDrag(Math::Vector2(DRAG_FORCE));
		GameObject::Update(m_parent, deltaTime);
	}

	void Ship::ChangeShip()
	{

		m_current_Ship = ++m_current_Ship % 2;

		m_points.clear();

		switch (m_current_Ship)
		{
	case 1:
			/*
			****** Little ship******
								*/

			m_points.push_back(Math::Vector2(0.0, 20.0));
			m_points.push_back(Math::Vector2(12.0, -10.0));
			m_points.push_back(Math::Vector2(6.0, -4.0));
			m_points.push_back(Math::Vector2(-6.0, -4.0));
			m_points.push_back(Math::Vector2(-12.0, -10.0));
			break;
		

		default:
			/* ===========BIG SHIP============*/

	m_points.push_back(Math::Vector2(0.0f, 10.0f));
	m_points.push_back(Math::Vector2(1.6f, 0.52f));
	m_points.push_back(Math::Vector2(2.0f, 10.0f));
	m_points.push_back(Math::Vector2(6.77f, 1.99f));
	m_points.push_back(Math::Vector2(9.86f, -2.5f));
    m_points.push_back(Math::Vector2(23.82f, -15.76f));
    m_points.push_back(Math::Vector2(8.0f, -7.0f));
    m_points.push_back(Math::Vector2(1.22f, -4.79f));
    m_points.push_back(Math::Vector2(9.0f, -10.0f));
    m_points.push_back(Math::Vector2(0.0f, -20.3f));
    m_points.push_back(Math::Vector2(-9.0f, -10.0f));
    m_points.push_back(Math::Vector2(-1.22f, -4.79f));
    m_points.push_back(Math::Vector2(-8.0f, -7.0f));
    m_points.push_back(Math::Vector2(-23.82f, -15.76f));
    m_points.push_back(Math::Vector2(-9.86f, -2.5f));
    m_points.push_back(Math::Vector2(-6.77f, 1.99f));
    m_points.push_back(Math::Vector2(-2.0f, 10.0f));
    m_points.push_back(Math::Vector2(-1.59f, 0.51f));
	break;
		}
	}

	void Ship::Respawn()
	{
		glLoadIdentity();
		m_position.x = 0.0f;
		m_position.y = 0.0f;
		m_velocity.x = 0.0f;
		m_velocity.y = 0.0f;
		m_angle = 0.0f;

		glTranslatef(m_position.x, m_position.y, 0.0);

		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINE_LOOP);
		glEnd();
	}

	Bullet *Ship::Shoot()
	{
		float shootingAngle = m_angle + ANGLE_OFFSET;
		float bulletPx = m_points[0].x * cosf(shootingAngle * (Engine::Math::Vector2::PI / 180));
		float bulletPy = m_points[0].y * sinf(shootingAngle * (Engine::Math::Vector2::PI / 180));

		Bullet *bullet = new Bullet(m_parent);
		bullet->Teleport(m_position.x + bulletPx, m_position.y + bulletPy);
		bullet->ApplyImpulse(Math::Vector2(m_currentSpeed + BULLET_SPEED), shootingAngle);

		return bullet;
	}

} // namespace Engine
