#include "Player.h"

Player* Player::m_pInstance = nullptr;
glm::quat Player::rotationQuat = glm::quat(glm::vec3(0.0f));


Player* Player::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Player;
		rotationQuat = glm::quat(glm::vec3(0.0f));	
	}
	return m_pInstance;
}

matrix4 Player::GetView(void){
	
	glm::mat4 m4View = glm::mat4();
	m4View = glm::lookAt((position - ((forward * 10.0f) + (-up * 3.0f))), position, up);

	return m4View;
}

matrix4 Player::GetProjection(bool bOrthographics){
	glm::mat4 m4Projection = glm::mat4();

	if (!bOrthographics)
	{
		m4Projection = glm::perspective(45.0f, 1080.0f / 720.0f, 0.1f, 1000.0f);
	}
	else { m4Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f); }

	return m4Projection;
}

matrix4 Player::GetMatrix(void){
	matrix4 modelMatrix = glm::translate(position);
	modelMatrix *= matrix4(-right.x, -right.y, -right.z, 0, up.x, up.y, up.z, 0, forward.x, forward.y, forward.z, 0, 0, 0, 0, 1);

	return modelMatrix;
}


void Player::SetPosition(vector3 v3Position){
	position = v3Position;
}

void Player::SetTarget(vector3 v3Target){
	target = v3Target;
}

void Player::SetUp(vector3 v3Up){
	up = v3Up;
}

void Player::MoveForward(float fIncrement){
	forward = glm::normalize(target - position);
	target = position + forward;
	position += forward * fIncrement;
}

void Player::MoveSideways(float fIncrement){
	forward = glm::normalize(position - target);

	position += glm::normalize(glm::cross(forward, up)) * fIncrement;
	target += glm::normalize(glm::cross(forward, up)) * fIncrement;
}

void Player::MoveVertical(float fIncrement){

	right = glm::normalize(glm::cross(up, forward));
	up = glm::cross(forward, right);

	position += (up * fIncrement);
	target += (up * fIncrement);
}

void Player::ChangePitch(float fIncrement)
{
	if (fIncrement != 0.0f)
	{
		forward = glm::normalize(target - position);
		right = glm::normalize(glm::cross(up, forward));

		quaternion qPitch = glm::angleAxis(fIncrement, right);
		forward = glm::normalize(qPitch * forward);
		up = glm::normalize(qPitch * up);
		target = position + forward;

		//std::cout << "PitchChanged" << std::endl;
	}
	
}

void Player::ChangeRoll(float fIncrement)
{
	quaternion qRoll = glm::angleAxis(fIncrement, forward);
	up = glm::normalize(qRoll * up);
	right = glm::normalize(glm::cross(up, forward));
	target = position + forward;

	if (fIncrement != 0.0f)
	{
		//std::cout << "RollChanged" << std::endl;
	}
}

void Player::ChangeYaw(float fIncrement)
{
	if (fIncrement != 0.0f)
	{
		quaternion qYaw = glm::angleAxis(fIncrement, up);
		forward = glm::normalize(qYaw * forward);
		right = glm::normalize(qYaw * right);
		target = position + forward;

		//std::cout << "YawChanged" << std::endl;
	}
}


//decrements fuel (used for slowing and boosting)
void Player::useFuel(float fAmount)
{
	fuel -= fAmount;
}

//increments fuel (to be called when not boosing or slowing)
void Player::rechargeFuel(float fAmount)
{
	//do not increment more than maximum
	if (fuel >= 1000){
		return;
	}

	fuel += fAmount;
}

void Player::fireBullet(void){
	PlaneBullet* pb = new PlaneBullet(position + forward*3.0f, forward);
	m_bullets.push_back(pb);
}


void Player::Update(void){
	MoveForward(0.3f);
	for (int i = 0; i < m_bullets.size(); i++)
	{
		PlaneBullet* b = m_bullets[i];
		b->Update();
		if (b->distanceTraveled > 250.0f){
			m_bullets.erase(m_bullets.begin()+i);
		}
	}
}
