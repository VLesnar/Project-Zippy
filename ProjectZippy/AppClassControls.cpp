#include "AppClass.h"

MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();

void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;

#pragma region ON_KEY_PRESS_RELEASE
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if (state == GameState::play) {

		//shoot
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletTimer > bulletTimerStart + 1) {
			bulletTimerStart = bulletTimer;
			std::cout << "shoot" << std::endl;
			bulletPos = m_pCameraMngr->GetPosition();
			bulletForward = m_pCameraMngr->GetForward();
			Bullet->SetModelMatrix(glm::translate(bulletPos));
		}

		//Move forward
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player->MoveForward(fTimeSpan);
		}

		//Move backwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player->MoveBackwards(fTimeSpan);
		}

		//Move left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->MoveLeft(fTimeSpan);

		//Move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->MoveRight(fTimeSpan);

		//Jump!
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (!spacePressed)
				player->Jump();
			spacePressed = true;
		}
		else {
			spacePressed = false;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			BOMngr->FlipVisibility();

		// Enter pause
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			if (!pPressed)
				state = GameState::pause;
			pPressed = true;
		}

		else {
			pPressed = false;
		}

		// Enter end
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			state = GameState::end;
	}

	if (state == GameState::start) {
		// Enter play
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (!spacePressed)
				state = GameState::play;
			spacePressed = true;
		}
		else {
			spacePressed = false;
		}
	}

	if (state == GameState::pause) {
		// Enter play
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			if (!pPressed)
				state = GameState::play;
			pPressed = true;
		}
		else {
			pPressed = false;
		}

		// Enter end
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			state = GameState::end;
	}

	if (state == GameState::end) {
		// Enter start
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if(!spacePressed)
				state = GameState::start;
			spacePressed = true;
		}
		else {
			spacePressed = false;
		}
	}

#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
	if (bLeft)
	{
		//Turn off the visibility of all BOs for all instances
		m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
		//Get the Position and direction of the click on the screen
		std::pair<vector3, vector3> pair =
			m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		float fDistance = 0;//Stores the distance to the first colliding object
		m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

		//If there is a collision
		if (m_selection.first >= 0)
		{
			//Turn on the BO of the group
			m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

			//Turn of the BO of the instance but not the group
			m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
		}
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}