#include "Player.h"

void Player::MoveForward(double dt)
{
	vector3 move = glm::normalize(vector3(m_pCameraMngr->GetForward().x, 0, m_pCameraMngr->GetForward().z)) * speed * static_cast<float>(dt);
	m_pCameraMngr->SetPositionTargetAndView(
		m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetForward() + m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetUpward());

	transform = glm::translate(m_pCameraMngr->GetPosition());
	EstablishModelMatrix();
}

void Player::MoveBackwards(double dt)
{
	vector3 move = glm::normalize(vector3(m_pCameraMngr->GetForward().x, 0, m_pCameraMngr->GetForward().z)) * -speed * static_cast<float>(dt);
	m_pCameraMngr->SetPositionTargetAndView(
		m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetForward() + m_pCameraMngr->GetPosition() + move,
		m_pCameraMngr->GetUpward());

	transform = glm::translate(m_pCameraMngr->GetPosition());
	EstablishModelMatrix();
}

void Player::MoveLeft(double dt)
{
	m_pCameraMngr->MoveSideways(speed * -0.75 * static_cast<float>(dt));
	
	transform = glm::translate(m_pCameraMngr->GetPosition());
	EstablishModelMatrix();
}

void Player::MoveRight(double dt)
{
	m_pCameraMngr->MoveSideways(speed * 0.75 * static_cast<float>(dt));
	
	transform = glm::translate(m_pCameraMngr->GetPosition());
	EstablishModelMatrix();
}

void Player::Translate(vector3 dir)
{
	m_pCameraMngr->SetPositionTargetAndView(
		m_pCameraMngr->GetPosition() + dir,
		m_pCameraMngr->GetForward() + m_pCameraMngr->GetPosition() + dir,
		m_pCameraMngr->GetUpward());

	transform = glm::translate(m_pCameraMngr->GetPosition());
	EstablishModelMatrix();
}