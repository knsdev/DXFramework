#include "stdafx.h"
#include "CGameObject.h"
#include "CTransform.h"

namespace dxfw
{
	CGameObject::CGameObject(const char* pName, GUID guid, CBaseApp* pApp)
		:
		m_name(pName),
		m_guid(guid),
		m_pApp(pApp),
		m_alive(true),
		m_active(true)
	{
	}

	CGameObject::CGameObject(const char* pName, std::vector<IComponent*> components, GUID guid, CBaseApp* pApp)
		:
		m_name(pName),
		m_components(components),
		m_guid(guid),
		m_pApp(pApp),
		m_alive(true),
		m_active(true)
	{
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Init()
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if ((*it)->IsEnabled())
			{
				(*it)->Init(this, m_pApp);
			}
		}
	}

	void CGameObject::Start()
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if ((*it)->IsEnabled())
			{
				(*it)->Start();
			}
		}
	}

	void CGameObject::Update(float deltaTime)
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if ((*it)->IsEnabled())
			{
				(*it)->Update(deltaTime);
			}
		}
	}

	void CGameObject::FixedUpdate(float deltaTime)
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if ((*it)->IsEnabled())
			{
				(*it)->FixedUpdate(deltaTime);
			}
		}
	}

	void CGameObject::OnDestroy()
	{
		m_alive = false;
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			(*it)->OnDestroy();
		}
	}

	bool CGameObject::RemoveComponent(IComponent* pComponent)
	{
		IterComponent it = std::find(m_components.begin(), m_components.end(), pComponent);
		if (it != m_components.end())
		{
			std::swap(*it, m_components.back());
			m_components.pop_back();
			delete pComponent;
			return true;
		}
		return false;
	}
}
