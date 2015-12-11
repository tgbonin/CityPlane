#include "MyOctant.h"
//  MyOctant
void MyOctant::Init(void)
{

	m_v3Center = vector3(0.0f);
	
	m_fSize = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}
void MyOctant::Swap(MyOctant& other)
{
	std::swap(m_v3Center, other.m_v3Center);

	std::swap(m_fSize, other.m_fSize);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyOctant::Release(void) {/* No pointers allocated yet */ }
//The big 3


MyOctant::MyOctant(void){
	Init();
}

MyOctant::MyOctant(MyOctant const& other)
{
	m_v3Center = other.m_v3Center;
	
	m_fSize = other.m_fSize;

	m_pMeshMngr = other.m_pMeshMngr;
}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };
//Accessors

void MyOctant::DisplayBox(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToQueue(glm::scale(vector3(m_fSize * 2.0f)), a_v3Color, WIRE);
}

void MyOctant::Subdivide(void){
	if (divisionLevel != maxDivisionLevel){
		m_pChild[0] = new MyOctant();
		m_pChild[0]->m_pParent = this;
		m_pChild[0]->m_fSize = m_fSize / 2;
		m_pChild[0]->divisionLevel = divisionLevel + 1;
		m_pChild[0]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[0]->m_v3Center = m_v3Center + vector3(m_fSize / 4, m_fSize / 4, m_fSize / 4);

		m_pChild[1] = new MyOctant();
		m_pChild[1]->m_pParent = this;
		m_pChild[1]->m_fSize = m_fSize / 2;
		m_pChild[1]->divisionLevel = divisionLevel + 1;
		m_pChild[1]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[1]->m_v3Center = m_v3Center + vector3(-m_fSize / 4, m_fSize / 4, m_fSize / 4);

		m_pChild[2] = new MyOctant();
		m_pChild[2]->m_pParent = this;
		m_pChild[2]->m_fSize = m_fSize / 2;
		m_pChild[2]->divisionLevel = divisionLevel + 1;
		m_pChild[2]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[2]->m_v3Center = m_v3Center + vector3(m_fSize / 4, -m_fSize / 4, m_fSize / 4);

		m_pChild[3] = new MyOctant();
		m_pChild[3]->m_pParent = this;
		m_pChild[3]->m_fSize = m_fSize / 2;
		m_pChild[3]->divisionLevel = divisionLevel + 1;
		m_pChild[3]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[3]->m_v3Center = m_v3Center + vector3(m_fSize / 4, m_fSize / 4, -m_fSize / 4);

		m_pChild[4] = new MyOctant();
		m_pChild[4]->m_pParent = this;
		m_pChild[4]->m_fSize = m_fSize / 2;
		m_pChild[4]->divisionLevel = divisionLevel + 1;
		m_pChild[4]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[4]->m_v3Center = m_v3Center + vector3(-m_fSize / 4, -m_fSize / 4, m_fSize / 4);

		m_pChild[5] = new MyOctant();
		m_pChild[5]->m_pParent = this;
		m_pChild[5]->m_fSize = m_fSize / 2;
		m_pChild[5]->divisionLevel = divisionLevel + 1;
		m_pChild[5]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[5]->m_v3Center = m_v3Center + vector3(-m_fSize / 4, m_fSize / 4, -m_fSize / 4);

		m_pChild[6] = new MyOctant();
		m_pChild[6]->m_pParent = this;
		m_pChild[6]->m_fSize = m_fSize / 2;
		m_pChild[6]->divisionLevel = divisionLevel + 1;
		m_pChild[6]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[6]->m_v3Center = m_v3Center + vector3(m_fSize / 4, -m_fSize / 4, -m_fSize / 4);

		m_pChild[7] = new MyOctant();
		m_pChild[7]->m_pParent = this;
		m_pChild[7]->m_fSize = m_fSize / 2;
		m_pChild[7]->divisionLevel = divisionLevel + 1;
		m_pChild[7]->maxDivisionLevel = maxDivisionLevel;
		m_pChild[7]->m_v3Center = m_v3Center + vector3(-m_fSize / 4, -m_fSize / 4, -m_fSize / 4);
	}
}

void MyOctant::checkObjectsWithinBox(void){
	vector3 max = m_v3Center + vector3(m_fSize / 2);
	vector3 min = m_v3Center - vector3(m_fSize / 2);
}