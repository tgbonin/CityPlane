#include "MyBOManager.h"
//  MyBOManager
MyBOManager* MyBOManager::m_pInstance = nullptr;
void MyBOManager::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_nObjectCount = 0;
}
void MyBOManager::Release(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject] != nullptr)
		{
			delete m_lObject[nObject];
			m_lObject[nObject] = nullptr;
		}
		m_llCollidingIndices[nObject].clear();
	}
	m_lObject.clear();
	m_llCollidingIndices.clear();
}
MyBOManager* MyBOManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyBOManager();
	}
	return m_pInstance;
}
void MyBOManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyBOManager::MyBOManager() { Init(); }
MyBOManager::MyBOManager(MyBOManager const& other) { }
MyBOManager& MyBOManager::operator=(MyBOManager const& other) { return *this; }
MyBOManager::~MyBOManager() { Release(); };
//Accessors
MyBOClass* MyBOManager::GetBoundingObject(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	return GetBoundingObject(nIndex);
}
MyBOClass* MyBOManager::GetBoundingObject(uint a_nIndex)
{
	if (a_nIndex < m_nObjectCount)
		return m_lObject[a_nIndex];

	return nullptr;
}
//--- Non Standard Singleton Methods
void MyBOManager::AddObject(String a_sName)
{
	std::vector<vector3> lVertex = m_pMeshMngr->GetVertexList(a_sName);
	AddObject(lVertex, a_sName);
	SetModelMatrix(m_pMeshMngr->GetModelMatrix(a_sName), a_sName);
}
void MyBOManager::AddObject(std::vector<vector3> a_lVertex, String a_sName)
{
	MyBOClass* pObject = new MyBOClass(a_lVertex);
	if (pObject != nullptr)
	{
		m_lObject.push_back(pObject);//Add the Object
		m_mapIndex[a_sName] = m_nObjectCount; //Add entry to the dictionary
	}
	m_nObjectCount = m_lObject.size();
	std::vector<int> lVector;
	m_llCollidingIndices.push_back(lVector);
}
void MyBOManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex)
{
	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
}
void MyBOManager::DisplaySphere(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplaySphere(nIndex, a_v3Color);
}
void MyBOManager::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplaySphere(v3Color);
	}
	else //all objects sent
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplaySphere(v3Color);
		}
	}
}
void MyBOManager::DisplayOriented(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayOriented(nIndex, a_v3Color);
}
void MyBOManager::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayOriented(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplayOriented(v3Color);
		}
	}
}
void MyBOManager::DisplayReAlligned(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayReAlligned(nIndex, a_v3Color);
}
void MyBOManager::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayReAlligned(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplayReAlligned(v3Color);
		}
	}
}
void MyBOManager::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	CheckCollisions();
}
void MyBOManager::CheckCollisions(void)
{
	for (uint nObjectA = 0; nObjectA < m_nObjectCount - 1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < m_nObjectCount; nObjectB++)
		{
			if (m_lObject[nObjectA]->IsColliding(m_lObject[nObjectB]))
			{
				m_llCollidingIndices[nObjectA].push_back(nObjectB);
				m_llCollidingIndices[nObjectB].push_back(nObjectA);
			}
		}
	}
}
std::vector<int> MyBOManager::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}
std::vector<int> MyBOManager::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}
int MyBOManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}

void MyBOManager::CheckCollisionsByList(std::vector<int> a_lIndexList)
{


	for (uint nObjectA = 0; nObjectA < a_lIndexList.size() - 1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < a_lIndexList.size(); nObjectB++)
		{
			if (m_lObject[a_lIndexList[nObjectA]]->IsColliding(m_lObject[a_lIndexList[nObjectB]]))
			{
				m_llCollidingIndices[a_lIndexList[nObjectA]].push_back(a_lIndexList[nObjectA]);
				m_llCollidingIndices[a_lIndexList[nObjectB]].push_back(a_lIndexList[nObjectB]);
			}
		}
	}
}

std::vector<int> MyBOManager::GetObjectsInsideBox(vector3 a_v3BoxPos, float a_fBoxSize)
{
	std::vector<int> indexList;

	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject]->InsideNode(a_v3BoxPos, a_fBoxSize))
		{
			indexList.push_back(nObject);
		}
	}

	return indexList;
}

vector4 MyBOManager::GetSizeAndMid()
{
	vector3 maxSize(0.0f);
	vector3 minSize(0.0f);

	for (int nEntity = 0; nEntity < m_nObjectCount; nEntity++)
	{
		vector3 pos = m_lObject[nEntity]->GetCenterGlobal();
		for (int i = 0; i < 3; i++)
		{
			if (pos[i] > maxSize[i]) maxSize[i] = pos[i];
			if (pos[i] < minSize[i]) minSize[i] = pos[i];
		}
	}

	vector3 mid = maxSize - minSize;
	mid /= 2;

	float size;
	if (glm::distance(maxSize, vector3(0.0f)) > glm::distance(minSize, vector3(0.0f)))
	{
		for (int j = 0; j < 3; j++)
		{
			if (maxSize[j] < 0.0f) maxSize[j] *= -1;
			if (minSize[j] < 0.0f) maxSize[j] *= -1;
		}

		size = maxSize[0];
		if (maxSize[1] > size) size = maxSize[1];
		if (maxSize[2] > size) size = maxSize[2];
		if (minSize[1] > size) size = minSize[1];
		if (minSize[2] > size) size = minSize[2];
		if (minSize[0] > size) size = minSize[0];
	}

	return vector4(mid, size);
}
