#pragma once

#include "RE\ReEngAppClass.h"

class Camera
{
public:
	static Camera* Instance();
	static glm::quat rotationQuat;

	matrix4 GetView(void);
	matrix4 GetProjection(bool bOrthographics);
	

	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);

	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);

	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);

	glm::vec3 position, forward, up, right, target;

private:
	Camera(){};
	Camera(Camera const&){};
	Camera& operator=(Camera const&){};

	static Camera* m_pInstance;
};

