#include "Camera.h"

Camera* Camera::m_pInstance = nullptr;
glm::quat Camera::rotationQuat = glm::quat(glm::vec3(0.0f));

Camera* Camera::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Camera;
		rotationQuat = glm::quat(glm::vec3(0.0f));
	}
	return m_pInstance;
}

matrix4 Camera::GetView(void){
	
	glm::mat4 m4View = glm::mat4();
	m4View = glm::lookAt(position, target, up);

	return m4View;
}

matrix4 Camera::GetProjection(bool bOrthographics){
	glm::mat4 m4Projection = glm::mat4();

	if (!bOrthographics)
	{
		m4Projection = glm::perspective(90.0f, 1080.0f / 720.0f, 0.1f, 1000.0f);
	}
	else { m4Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f); }

	return m4Projection;
}

void Camera::SetPosition(vector3 v3Position){
	position = v3Position;
}

void Camera::SetTarget(vector3 v3Target){
	target = v3Target;
}

void Camera::SetUp(vector3 v3Up){
	up = v3Up;
}

void Camera::MoveForward(float fIncrement){
	forward = glm::normalize(target - position);
	target = position + forward;
	position += forward * fIncrement;
}

void Camera::MoveSideways(float fIncrement){
	forward = glm::normalize(position - target);

	position += glm::normalize(glm::cross(forward, up)) * fIncrement;
	target += glm::normalize(glm::cross(forward, up)) * fIncrement;
}

void Camera::MoveVertical(float fIncrement){

	right = glm::normalize(glm::cross(up, forward));
	up = glm::cross(forward, right);

	position += (up * fIncrement);
	target += (up * fIncrement);
}

void Camera::ChangePitch(float fIncrement)
{
	if (fIncrement != 0.0f)
	{
		forward = glm::normalize(target - position);
		right = glm::normalize(glm::cross(up, forward));

		quaternion qPitch = glm::angleAxis(fIncrement, right);
		forward = glm::normalize(qPitch * forward);
		up = glm::normalize(qPitch * up);
		target = position + forward;

		std::cout << "PitchChanged" << std::endl;
	}
	
}

void Camera::ChangeRoll(float fIncrement)
{
	quaternion qRoll = glm::angleAxis(fIncrement, forward);
	up = glm::normalize(qRoll * up);
	right = glm::normalize(glm::cross(up, forward));
	target = position + forward;

	if (fIncrement != 0.0f)
	{
		std::cout << "RollChanged" << std::endl;
	}
}

void Camera::ChangeYaw(float fIncrement)
{
	if (fIncrement != 0.0f)
	{
		quaternion qYaw = glm::angleAxis(fIncrement, up);
		forward = glm::normalize(qYaw * forward);
		right = glm::normalize(qYaw * right);
		target = position + forward;

		std::cout << "YawChanged" << std::endl;
	}
}
