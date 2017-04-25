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

	CGameObject::CGameObject(const char* pName, std::map<size_t, IComponent*> components, GUID guid, CBaseApp* pApp)
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
			if (it->second->IsEnabled())
			{
				it->second->Init(this, m_pApp);
			}
		}
	}

	void CGameObject::Start()
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second->IsEnabled())
			{
				it->second->Start();
			}
		}
	}

	void CGameObject::Update(float deltaTime)
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second->IsEnabled())
			{
				it->second->Update(deltaTime);
			}
		}
	}

	void CGameObject::FixedUpdate(float deltaTime)
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second->IsEnabled())
			{
				it->second->FixedUpdate(deltaTime);
			}
		}
	}

	void CGameObject::OnDestroy()
	{
		m_alive = false;
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			it->second->OnDestroy();
		}
	}
}
