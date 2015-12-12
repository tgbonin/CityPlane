#include "MyOctant.h"
uint MyOctant::m_nMaxSubLevel = 3;
//  MyOctant
void MyOctant::Init(void)
{
	m_nLevel = 0;
	m_nChildren = 0;
	m_v3Center = vector3(0.0f);
	
	m_fSize = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();

	MyOctant* m_pParent = nullptr;
	
	for (uint nChild = 0; nChild < 8; nChild++)
	{
		m_pChild[nChild] = nullptr;
	}
}
void MyOctant::Swap(MyOctant& other)
{
	std::swap(m_nLevel, other.m_nLevel);
	std::swap(m_nChildren, other.m_nChildren);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_fSize, other.m_fSize);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyOctant::Release(void)
{
	if (m_nLevel == 0)
		KillBranch();

	/* No pointers allocated yet */
}
//The big 3
MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;
}
MyOctant::MyOctant(MyOctant const& other)
{
	m_nLevel = other.m_nLevel;
	m_v3Center = other.m_v3Center;
	m_fSize = other.m_fSize;
	m_nChildren = other.m_nChildren;
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
float MyOctant::GetSize(void) { return m_fSize; }
//--- Non Standard Singleton Methods
void MyOctant::Display()
{
	vector3 color = REYELLOW;

	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		m_pChild[nChild]->Display();
	}

	if ((m_nChildren == 0 && m_vecContainedObjects.size() > 3) || m_nLevel == 3) color = RERED;
	
	m_pMeshMngr->AddCubeToQueue( glm::translate(m_v3Center) * glm::scale(vector3(m_fSize * 2.0f)), color, WIRE);
}

void MyOctant::Subdivide(void)
{
	//if (m_nLevel >= m_nMaxSubLevel)
	//	return;

	m_vecContainedObjects = m_pBOMngr->GetObjectsInsideBox(m_v3Center, m_fSize);

	if (m_vecContainedObjects.size() > 3 && m_nLevel < 3)
	{
		m_nChildren = 8;

		uint nIndex = 0;
		float fNewSize = m_fSize / 2.0f;

		vector3 vCenter = m_v3Center + vector3(fNewSize, fNewSize, fNewSize);
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(-fNewSize, fNewSize, fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(-fNewSize, -fNewSize, fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(fNewSize, -fNewSize, fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(fNewSize, fNewSize, -fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(-fNewSize, fNewSize, -fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(-fNewSize, -fNewSize, -fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();

		vCenter = m_v3Center + vector3(fNewSize, -fNewSize, -fNewSize);
		nIndex++;
		m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
		m_pChild[nIndex]->Subdivide();
	}
}

MyOctant * MyOctant::GetChild(uint nIndex)
{
	if(nIndex >= 8)
		return nullptr;

	return m_pChild[nIndex];
}

void MyOctant::KillBranch(void)
{
	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		m_pChild[nChild]->KillBranch();
	}
	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		if (m_pChild[nChild] != nullptr)
		{
			delete m_pChild[nChild];
			m_pChild[nChild] = nullptr;
		}
	}
}

void MyOctant::OcTreeCollisions()
{
	if (m_nChildren != 0)
	{
		for (uint nChild = 0; nChild < m_nChildren; nChild++)
		{
			m_pChild[nChild]->OcTreeCollisions();
		}
	}
	else
	{
		if (m_vecContainedObjects.size() > 0) m_pBOMngr->CheckCollisionsByList(m_vecContainedObjects);
	}
}