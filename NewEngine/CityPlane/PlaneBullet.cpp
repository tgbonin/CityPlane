#include "PlaneBullet.h"


PlaneBullet::PlaneBullet()
{
	distanceTraveled = 0;
}

PlaneBullet::PlaneBullet(vector3 v3Position, vector3 v3forward){
	distanceTraveled = 0;
	position = v3Position;
	forward = v3forward;
}

PlaneBullet::PlaneBullet(PlaneBullet const& other){

}

void PlaneBullet::Update(void){
	position += forward * 1.0f;
	distanceTraveled += 1.0f;
}

PlaneBullet::~PlaneBullet()
{
}
