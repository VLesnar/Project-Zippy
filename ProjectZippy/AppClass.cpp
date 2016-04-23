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
	
	m_pGround = new PrimitiveClass();
	m_pGround->GeneratePlane(10, REWHITE);

	//Load a model onto the Mesh manager
	BOMngr = MyBoundingObjectManager::GetInstance();

	
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve2");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	std::vector<vector3> planeVertexList = { vector3(100.0f, 0.0f, 100.0f), vector3(100.0f, 0.0f, -100.0f), vector3(-100.0f, 0.0f, 100.0f), vector3(-100.0f, 0.0f, -100.0f) };
	
	BOMngr->setBox(vertexList, "Steve1");
	BOMngr->setBox(vertexList, "Steve2");
	BOMngr->setBox(planeVertexList, "ground");

	
	
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the the objects and bounding objects
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, -1.0f, 0.0f)) * ToMatrix4(m_qArcBall), "Steve");

	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(5.0f, 3.0f, 0.0f)) * ToMatrix4(m_qArcBall), "Steve2");

	
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f)) * ToMatrix4(m_qArcBall), "Creeper");
	
	//change the model matix of all the bounding objects
	BOMngr->setModelMatrix("Steve1", m_pMeshMngr->GetModelMatrix("Steve"));
	BOMngr->setModelMatrix("Steve2", m_pMeshMngr->GetModelMatrix("Steve2"));
	BOMngr->setModelMatrix("ground", IDENTITY_M4 * glm::scale(vector3(50.0f, 0.0f, 0.0f)) * glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)));
	
	//Adds all loaded instance to the render list
	
	m_pMeshMngr->AddInstanceToRenderList("Steve");
	m_pMeshMngr->AddInstanceToRenderList("Steve2");
	m_pMeshMngr->AddPlaneToQueue(IDENTITY_M4 * glm::scale(vector3(50.0f)) * glm::rotate(90.0f, vector3(1.0f,0.0f,0.0f)), REWHITE);
	

	BOMngr->checkColissions();
	BOMngr->render();
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

	if (bo_1 != nullptr) {
		delete bo_1;
		bo_1 = nullptr;
	}

	if (bo_2 != nullptr) {
		delete bo_2;
		bo_2 = nullptr;
	}

	if (bo_3 != nullptr) {
		delete bo_3;
		bo_3 = nullptr;
	}

	super::Release(); //release the memory of the inherited fields
}