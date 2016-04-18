#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera
{
	static Camera* instance;
	vector3 pos = vector3(0.0f, 0.0f, 0.0f);
	vector3 forward = vector3(0.0f, 0.0f, 1.0f);
	vector3 up = vector3(0.0f, 1.0f, 0.0f);
public:

	//Constructor
	static Camera* GetInstance()
	{
		if (instance == nullptr)
			instance = new Camera();
		return instance;
	}

	//Destructor
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	//Return the view matrix of the camera
	matrix4 GetView()
	{
		return glm::lookAt(
			pos,
			forward + pos,
			up);
	}

	//Return the projection matrix of the camera
	matrix4 GetProjection()
	{
		return glm::perspective(90.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}

	//Set the position of the camera
	void SetPosition(vector3 v3Position)
	{
		pos = v3Position;
	}

	//Set the target of the camera
	void SetTarget(vector3 v3Target)
	{
		forward = v3Target - pos;
	}

	//Set the up-vector of the camera
	void SetUp(vector3 v3Up)
	{
		up = v3Up;
	}

	//Move the camera forward by an increment
	void MoveForward(float fIncrement)
	{
		vector3 move = glm::normalize(forward) * fIncrement;
		pos += move;
	}

	//Move the camera sideways by an increment
	void MoveSideways(float fIncrement)
	{
		vector3 right = glm::normalize(glm::cross(up, forward)) * fIncrement;
		pos += right;
	}

	//Move the camera vertically by an increment
	void MoveVertical(float fIncrement)
	{
		vector3 move = glm::normalize(up) * fIncrement;
		pos += move;
	}

	//Pitch the gamera up or down
	void ChangePitch(float fIncrement)
	{
		vector3 right = glm::cross(up, forward);
		matrix4 temp = glm::rotate(fIncrement, right);
		TransformByMatrix(temp);
	}

	//Yaw the camera sideways
	void ChangeYaw(float fIncrement)
	{
		matrix4 temp = glm::rotate(fIncrement, up);
		TransformByMatrix(temp);
	}

	//Roll the camera (Aileron, not Barrel)
	void ChangeRoll(float fIncrement)
	{
		matrix4 temp = glm::rotate(fIncrement, forward);
		TransformByMatrix(temp);
	}
private:
	void TransformByMatrix(matrix4 mat)
	{
		forward = vector3(mat * vector4(forward, 1.0f));
		up = vector3(mat * vector4(forward, 1.0f));
	}
	Camera() {};
};
#endif