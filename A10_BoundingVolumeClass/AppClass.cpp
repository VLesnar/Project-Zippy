#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Veronica Lesnar E12"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void) {
	objManager->GetInstance();
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	//// Steve
	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	objManager->SetBox(vertexList);
	//m_pBounding1 = new MyBoundingObjectClass(vertexList);

	//// Creeper
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	objManager->SetBox(vertexList);
	//m_pBounding2 = new MyBoundingObjectClass(vertexList);
}

void AppClass::Update(void) {
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	objManager->SetModelMatrix(objManager->boundingObjects[0], m_pMeshMngr->GetModelMatrix("Steve"));
	objManager->SetModelMatrix(objManager->boundingObjects[1], m_pMeshMngr->GetModelMatrix("Creeper"));

	objManager->boundingObjects[0]->SetChangingCubeSize();

	if (objManager->boundingObjects[0]->IsColliding(objManager->boundingObjects[1])) {
		m_pMeshMngr->PrintLine("They are colliding! :I", RERED);
		objManager->Render(objManager->boundingObjects[0]);
		objManager->Render(objManager->boundingObjects[1]);
		//m_pMeshMngr->AddCubeToQueue(glm::translate(objManager->boundingObjects[0]->GetGlobalCenter()) * glm::scale(vector3(objManager->boundingObjects[0]->GetChangingSize())), RERED, WIRE);
		//m_pMeshMngr->AddCubeToQueue(objManager->boundingObjects[1]->GetGlobalCenterMatrix()  * glm::scale(vector3(objManager->boundingObjects[1]->GetSize())), RERED, WIRE);
		
	}

	else {
		m_pMeshMngr->PrintLine("They are not colliding! :D", REGREEN);
		objManager->Render(objManager->boundingObjects[0]);
		objManager->Render(objManager->boundingObjects[1]);
		//m_pMeshMngr->AddCubeToQueue(glm::translate(objManager->boundingObjects[0]->GetGlobalCenter()) * glm::scale(vector3(objManager->boundingObjects[0]->GetChangingSize())), REWHITE, WIRE);
		//m_pMeshMngr->AddCubeToQueue(objManager->boundingObjects[1]->GetGlobalCenterMatrix() * glm::scale(vector3(objManager->boundingObjects[1]->GetSize())), REWHITE, WIRE);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->Render(); //renders the render list

	m_pMeshMngr->ResetRenderList();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//if (objManager->boundingObjects[0] != nullptr) {
	//	delete objManager->boundingObjects[0];
	//	objManager->boundingObjects[0] = nullptr;
	//}

	//if (objManager->boundingObjects[1] != nullptr) {
	//	delete objManager->boundingObjects[1];
	//	objManager->boundingObjects[1] = nullptr;
	//}

	if (objManager != nullptr) {
		objManager->ReleaseInstance();
	}

	super::Release(); //release the memory of the inherited fields
}