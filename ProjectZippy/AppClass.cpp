#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Project Zippy"); // Window Name

	//Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up

	cam->SetPosition(vector3(0.0f, 0.0f, -4.0f));
	cam->SetTarget(vector3(0.0f, 0.0f, 0.0f));
	cam->SetUp(vector3(0.0f, 1.0f, 0.0f));

	m_pGround = new PrimitiveClass();
	m_pGround->GeneratePlane(5, REWHITE);

	//Load a model onto the Mesh manager
	//m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Stuff
	m_m4Projection = cam->GetProjection();
	m_m4View = cam->GetView();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	//m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	m_pGround->Render(m_m4Projection, m_m4View, IDENTITY_M4);
	
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REBLACK);	
	m_pMeshMngr->Print("FPS: " + std::to_string(nFPS), REBLACK);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the plane
	m_pGround->Render(m_m4Projection, m_m4View, IDENTITY_M4);

	//Render the grid based on the camera's mode:
	/*switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}*/
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (m_pGround != nullptr)
	{
		delete m_pGround;
		m_pGround = nullptr;
	}


	super::Release(); //release the memory of the inherited fields
}