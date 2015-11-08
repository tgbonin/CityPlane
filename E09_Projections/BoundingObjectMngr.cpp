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