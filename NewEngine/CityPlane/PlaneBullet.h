#include "RE\ReEngAppClass.h"


class PlaneBullet
{
public:
	PlaneBullet();

	void Update(void);

	PlaneBullet(vector3 v3Position, vector3 v3forward);

	PlaneBullet(PlaneBullet const& other);

	PlaneBullet& operator=(PlaneBullet const& other);

	~PlaneBullet();

	vector3 position, forward;

	float distanceTraveled = 0;

	float timeFired = 0;
};

