/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09 (Last Modified on: 15/11)
----------------------------------------------*/
/*----------------------------------------------
Programmers: Alexander Bronner, Joseph Horsmann,
Veronica Lesnar, and Steven Siewert
Date: 2016/04
Application: Project Zippy
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "EnemyManager.h"
#include "MyBoundingObjectManager.h"
#include "EnvironmentManager.h"
#include "Player.h"
#include "MyOctant.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	double fTimeSpan = 0;
	float bulletTimer = 0.0f;
	float bulletTimerStart = 0.0f;
	GameObject* Bullet = nullptr;
	vector3 bulletPos = vector3(0.0f);
	vector3 bulletForward = vector3(0.0f);
	MyBoundingObjectManager* BOMngr = MyBoundingObjectManager::GetInstance();
	EnvironmentManager* GOMngr = EnvironmentManager::GetInstance();
	Player* player = nullptr;
	MyOctant* mainOctant = nullptr;

	int updateRelianceDelay = 120;	//Number of frames before app uses system FPS for dt instead of LapClock
	int updateRelianceCounter = 0;	//Counter for those frames

	bool bKeyO = false;
	bool bVisibleO = false;

	enum class GameState
	{
		start,
		play,
		pause,
		end
	};

	GameState state;
	bool pPressed = false;
	bool spacePressed = false;

	EnemyManager* spawner1 = nullptr;
	EnemyManager* spawner2 = nullptr;
	EnemyManager* spawner3 = nullptr;
	EnemyManager* spawner4 = nullptr;
public:
	typedef ReEngAppClass super;

	/*
	USAGE: Constructor
	ARGUMENTS: 
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: std::string a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(std::string a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;
};
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__APPLICATION_H_
