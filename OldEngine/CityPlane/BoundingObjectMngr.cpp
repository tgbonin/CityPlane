#include "BoundingObjectMngr.h"


BoundingObjectMngr* BoundingObjectMngr::m_pInstance = NULL;


BoundingObjectMngr* BoundingObjectMngr::Instance()
{
	//Normal singleton Shinanigans 
	if (!m_pInstance)
		m_pInstance = new BoundingObjectMngr;

	return m_pInstance;
}

void BoundingObjectMngr::InitMeshManager(MeshManagerSingleton* a_pMeshMngr)
{
	m_pMeshMngr = a_pMeshMngr;
}

void BoundingObjectMngr::SetBOVisibility(std::string a_sObjectName, bool a_bVisibility)
{
	m_mapBoundingObjectMap[a_sObjectName]->SetVisibility(a_bVisibility);
}

void BoundingObjectMngr::SetBOColour(std::string a_sObjectName, vector3 a_v3Colour)
{
	m_mapBoundingObjectMap[a_sObjectName]->SetColour(a_v3Colour);
}

void BoundingObjectMngr::SetBOMatrix(std::string a_sObjectName, matrix4 a_m4ToWorld)
{
	m_mapBoundingObjectMap[a_sObjectName]->SetModelMatrix(a_m4ToWorld);
}

int BoundingObjectMngr::GetNumberBoundingObjects(void)
{
	return m_lBOList.size();
}

void BoundingObjectMngr::AddBoundingObject(std::string a_sObjectName)
{
	//Add a new bounding object the the list using the vertex array from the mesh manager
	m_lBOList.push_back(new BoundingObject(m_pMeshMngr->GetVertices(a_sObjectName)));

	//Add the new object to the map using the name of the object and the last entry in the list
	//which is the new BO
	m_mapBoundingObjectMap.insert(std::make_pair(a_sObjectName, m_lBOList[(m_lBOList.size() - 1)]));
}

void BoundingObjectMngr::RenderBoundingObjects(std::string a_sObjectName)
{
	//Renders all of the bounding objects
	if (a_sObjectName == "ALL")
	{
		for (int i = 0; i < GetNumberBoundingObjects(); i++)
		{
			m_lBOList[i]->DrawBoundingObjects(m_pMeshMngr);
		}
	}
	//Renders a specific bounding object
	else {
		m_mapBoundingObjectMap[a_sObjectName]->DrawBoundingObjects(m_pMeshMngr);
	}
}

void BoundingObjectMngr::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		m_pMeshMngr->AddSphereToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(matrix4(1.0f), m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(vector3(m_lObject[a_nIndex]->GetRadiusG() * 2.0f)),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			m_pMeshMngr->AddSphereToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(matrix4(1.0f), m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(vector3(m_lObject[nObject]->GetRadiusG() * 2.0f)),
				v3Color,
				WIRE);
		}
	}
}
void BoundingObjectMngr::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		m_pMeshMngr->AddCubeToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(matrix4(1.0f), m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(m_lObject[a_nIndex]->GetHalfWidth() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			m_pMeshMngr->AddCubeToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(matrix4(1.0f), m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidth() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}

void BoundingObjectMngr::DisplayReAlligned(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayReAlligned(nIndex, a_v3Color);
}
void BoundingObjectMngr::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}
		m_pMeshMngr->AddCubeToQueue(
			glm::translate(m_lObject[a_nIndex]->GetCenterGlobal()) *
			glm::scale(m_lObject[a_nIndex]->GetHalfWidthG() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			m_pMeshMngr->AddCubeToQueue(
				glm::translate(m_lObject[nObject]->GetCenterGlobal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidthG() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}
void BoundingObjectMngr::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	CheckCollisions();
}

void BoundingObjectMngr::CheckCollisions(void)
{
	int numBOs = GetNumberBoundingObjects();

	//set the colour of all BOs to white (not colliding)
	for (int k = 0; k < numBOs; k++) m_lBOList[k]->SetColour(REWHITE);

	//loop through each BO and check collisions
	for (int i = 0; i < numBOs; i++)
	{
		for (int j = 0; j < numBOs; j++)
		{
			if (i != j)
			{
				if (m_lBOList[i]->IsColliding(m_lBOList[j]))
				{
					//set colour to red (is colliding)
					m_lBOList[i]->SetColour(RERED);
					m_lBOList[j]->SetColour(RERED);
				}
			}
		}
	}
}
std::vector<int> BoundingObjectMngr::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}
std::vector<int> BoundingObjectMngr::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}
int BoundingObjectMngr::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}