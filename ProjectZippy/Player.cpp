#include "player.h"
Player* Player::instance = nullptr;

Player::Player()
{

}

Player::~Player()
{

}

void Player::MoveForward()
{
	vector3 move = glm::normalize(vector3(m_pCameraMngr->GetForward().x, 0, m_pCameraMngr->GetForward().z)) * speed;
	m_pCameraMngr->SetPositionTargetAndView(
		m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetForward() + m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetUpward());
}

void Player::MoveBackwards()
{
	vector3 move = glm::normalize(vector3(m_pCameraMngr->GetForward().x, 0, m_pCameraMngr->GetForward().z)) * -speed;
	m_pCameraMngr->SetPositionTargetAndView(
		m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetForward() + m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetUpward());
}

void Player::MoveLeft()
{
	m_pCameraMngr->MoveSideways(speed * 0.75);
}

void Player::MoveRight()
{
	m_pCameraMngr->MoveSideways(speed * 0.75);
}
