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

	//Load a model onto the Mesh manager
	BOMngr = MyBoundingObjectManager::GetInstance();
	spawner1 = new EnemyManager(vector3(0.0f, 2.0f, -30.0f));
	spawner2 = new EnemyManager(vector3(0.0f, 2.0f, 30.0f));
	spawner3 = new EnemyManager(vector3(-30.0f, 2.0f, 0.0f));
	spawner4 = new EnemyManager(vector3(30.0f, 2.0f, 0.0f));

	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve1");
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve2");
	m_pMeshMngr->LoadModel("FloorCube.obj", "MainCube");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "TopPath");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "BottomPath");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "LeftPath");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "RightPath");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "Tower1");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "Tower2");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "Tower3");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "Tower4");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "TopWall_1");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "TopWall_2");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "BottomWall_1");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "BottomWall_2");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "LeftWall_1");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "LeftWall_2");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "RightWall_1");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "RightWall_2");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "TopPathWall");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "BottomPathWall");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "LeftPathWall");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "RightPathWall");
	m_pMeshMngr->LoadModel("ZippyCube.obj", "Roof");

	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve1");
	std::vector<vector3> cubeVertexList = m_pMeshMngr->GetVertexList("MainCube");

	BOMngr->SetBO(vertexList, "Steve1");
	BOMngr->SetBO(vertexList, "Steve2");
	BOMngr->SetBO(cubeVertexList, "MainCube");
	BOMngr->SetBO(cubeVertexList, "TopPath");
	BOMngr->SetBO(cubeVertexList, "BottomPath");
	BOMngr->SetBO(cubeVertexList, "LeftPath");
	BOMngr->SetBO(cubeVertexList, "RightPath");
	BOMngr->SetBO(cubeVertexList, "Tower1");
	BOMngr->SetBO(cubeVertexList, "Tower2");
	BOMngr->SetBO(cubeVertexList, "Tower3");
	BOMngr->SetBO(cubeVertexList, "Tower4");
	BOMngr->SetBO(cubeVertexList, "TopWall_1");
	BOMngr->SetBO(cubeVertexList, "TopWall_2");
	BOMngr->SetBO(cubeVertexList, "BottomWall_1");
	BOMngr->SetBO(cubeVertexList, "BottomWall_2");
	BOMngr->SetBO(cubeVertexList, "LeftWall_1");
	BOMngr->SetBO(cubeVertexList, "LeftWall_2");
	BOMngr->SetBO(cubeVertexList, "RightWall_1");
	BOMngr->SetBO(cubeVertexList, "RightWall_2");
	BOMngr->SetBO(cubeVertexList, "TopPathWall");
	BOMngr->SetBO(cubeVertexList, "BottomPathWall");
	BOMngr->SetBO(cubeVertexList, "LeftPathWall");
	BOMngr->SetBO(cubeVertexList, "RightPathWall");
	BOMngr->SetBO(cubeVertexList, "Roof");
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
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall), "Steve1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(5.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall), "Steve2");
	//Set up the level
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f)) * glm::scale(vector3(42.0f, 1.0f, 42.0f)), "MainCube");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, -28.0f)) * glm::scale(vector3(14.0f, 1.0f, 14.0f)), "TopPath");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 28.0f)) * glm::scale(vector3(14.0f, 1.0f, 14.0f)), "BottomPath");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-28.0f, 0.0f, 0.0f)) * glm::scale(vector3(14.0f, 1.0f, 14.0f)), "LeftPath");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(28.0f, 0.0f, 0.0f)) * glm::scale(vector3(14.0f, 1.0f, 14.0f)), "RightPath");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-17.5f, 4.0f, -17.5f)) * glm::scale(vector3(7.0f, 7.0f, 7.0f)), "Tower1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-17.5f, 4.0f, 17.5f)) * glm::scale(vector3(7.0f, 7.0f, 7.0f)), "Tower2");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(17.5f, 4.0f, -17.5f)) * glm::scale(vector3(7.0f, 7.0f, 7.0f)), "Tower3");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(17.5f, 4.0f, 17.5f)) * glm::scale(vector3(7.0f, 7.0f, 7.0f)), "Tower4");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-14.0f, 7.5f, -28.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "TopWall_1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(14.0f, 7.5f, -28.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "TopWall_2");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-14.0f, 7.5f, 28.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "BottomWall_1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(14.0f, 7.5f, 28.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "BottomWall_2");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-28.0f, 7.5f, -14.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "LeftWall_1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(28.0f, 7.5f, -14.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "LeftWall_2");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-28.0f, 7.5f, 14.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "RightWall_1");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(28.0f, 7.5f, 14.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "RightWall_2");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 7.5f, -42.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "TopPathWall");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 7.5f, 42.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "BottomPathWall");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-42.0f, 7.5f, 0.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "LeftPathWall");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(42.0f, 7.5f, 0.0f)) * glm::scale(vector3(14.0f, 14.0f, 14.0f)), "RightPathWall");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 15.0f, 0.0f)) * glm::scale(vector3(70.0f, 1.0f, 70.0f)), "Roof");

	//change the model matix of all the bounding objects
	BOMngr->SetModelMatrix("Steve1", m_pMeshMngr->GetModelMatrix("Steve1"));
	BOMngr->SetModelMatrix("Steve2", m_pMeshMngr->GetModelMatrix("Steve2"));
	BOMngr->SetModelMatrix("MainCube", m_pMeshMngr->GetModelMatrix("MainCube"));
	BOMngr->SetModelMatrix("TopPath", m_pMeshMngr->GetModelMatrix("TopPath"));
	BOMngr->SetModelMatrix("BottomPath", m_pMeshMngr->GetModelMatrix("BottomPath"));
	BOMngr->SetModelMatrix("LeftPath", m_pMeshMngr->GetModelMatrix("LeftPath"));
	BOMngr->SetModelMatrix("RightPath", m_pMeshMngr->GetModelMatrix("RightPath"));
	BOMngr->SetModelMatrix("Tower1", m_pMeshMngr->GetModelMatrix("Tower1"));
	BOMngr->SetModelMatrix("Tower2", m_pMeshMngr->GetModelMatrix("Tower2"));
	BOMngr->SetModelMatrix("Tower3", m_pMeshMngr->GetModelMatrix("Tower3"));
	BOMngr->SetModelMatrix("Tower4", m_pMeshMngr->GetModelMatrix("Tower4"));
	BOMngr->SetModelMatrix("TopWall_1", m_pMeshMngr->GetModelMatrix("TopWall_1"));
	BOMngr->SetModelMatrix("TopWall_2", m_pMeshMngr->GetModelMatrix("TopWall_2"));
	BOMngr->SetModelMatrix("BottomWall_1", m_pMeshMngr->GetModelMatrix("BottomWall_1"));
	BOMngr->SetModelMatrix("BottomWall_2", m_pMeshMngr->GetModelMatrix("BottomWall_2"));
	BOMngr->SetModelMatrix("LeftWall_1", m_pMeshMngr->GetModelMatrix("LeftWall_1"));
	BOMngr->SetModelMatrix("LeftWall_2", m_pMeshMngr->GetModelMatrix("LeftWall_2"));
	BOMngr->SetModelMatrix("RightWall_1", m_pMeshMngr->GetModelMatrix("RightWall_1"));
	BOMngr->SetModelMatrix("RightWall_2", m_pMeshMngr->GetModelMatrix("RightWall_2"));
	BOMngr->SetModelMatrix("TopPathWall", m_pMeshMngr->GetModelMatrix("TopPathWall"));
	BOMngr->SetModelMatrix("BottomPathWall", m_pMeshMngr->GetModelMatrix("BottomPathWall"));
	BOMngr->SetModelMatrix("LeftPathWall", m_pMeshMngr->GetModelMatrix("LeftPathWall"));
	BOMngr->SetModelMatrix("RightPathWall", m_pMeshMngr->GetModelMatrix("RightPathWall"));
	BOMngr->SetModelMatrix("Roof", m_pMeshMngr->GetModelMatrix("Roof"));

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve1");
	m_pMeshMngr->AddInstanceToRenderList("Steve2");
	m_pMeshMngr->AddInstanceToRenderList("MainCube");
	m_pMeshMngr->AddInstanceToRenderList("TopPath");
	m_pMeshMngr->AddInstanceToRenderList("BottomPath");
	m_pMeshMngr->AddInstanceToRenderList("LeftPath");
	m_pMeshMngr->AddInstanceToRenderList("RightPath");
	m_pMeshMngr->AddInstanceToRenderList("Tower1");
	m_pMeshMngr->AddInstanceToRenderList("Tower2");
	m_pMeshMngr->AddInstanceToRenderList("Tower3");
	m_pMeshMngr->AddInstanceToRenderList("Tower4");
	m_pMeshMngr->AddInstanceToRenderList("TopWall_1");
	m_pMeshMngr->AddInstanceToRenderList("TopWall_2");
	m_pMeshMngr->AddInstanceToRenderList("BottomWall_1");
	m_pMeshMngr->AddInstanceToRenderList("BottomWall_2");
	m_pMeshMngr->AddInstanceToRenderList("LeftWall_1");
	m_pMeshMngr->AddInstanceToRenderList("LeftWall_2");
	m_pMeshMngr->AddInstanceToRenderList("RightWall_1");
	m_pMeshMngr->AddInstanceToRenderList("RightWall_2");
	m_pMeshMngr->AddInstanceToRenderList("TopPathWall");
	m_pMeshMngr->AddInstanceToRenderList("BottomPathWall");
	m_pMeshMngr->AddInstanceToRenderList("LeftPathWall");
	m_pMeshMngr->AddInstanceToRenderList("RightPathWall");
	m_pMeshMngr->AddInstanceToRenderList("Roof");

	//update enemies
	double fTimeSpan = m_pSystem->LapClock();

	spawner1->Update(fTimeSpan);
	spawner2->Update(fTimeSpan);
	spawner3->Update(fTimeSpan);
	spawner4->Update(fTimeSpan);

	BOMngr->CheckColissions();
	BOMngr->Render();
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

	m_pMeshMngr->ResetRenderList();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}