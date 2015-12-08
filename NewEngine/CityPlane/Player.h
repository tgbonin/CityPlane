#pragma once

#include "RE\ReEngAppClass.h"
#include "PlaneBullet.h"

class Player
{
public:
	static Player* Instance();
	static glm::quat rotationQuat;
	float fuel;
	float timeLastFired = 0.0f;
	float currentTime = 0.0f;

	std::vector <PlaneBullet*> m_bullets;

	matrix4 GetView(void);
	matrix4 GetProjection(bool bOrthographics);
	matrix4 GetMatrix(void);
	
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);

	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);

	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);

	void useFuel(float fAmount);
	void rechargeFuel(float fAmount);

	void fireBullet(void);

	void Update(void);

	glm::vec3 position, forward, up, right, target;

private:
	Player(){};
	Player(Player const&){};
	Player& operator=(Player const&){};

	static Player* m_pInstance;
};

