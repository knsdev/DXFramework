#pragma once
#include "stdafx.h"
#include "IComponent.h"

namespace dxfw
{
	class IComponent;
	class CBaseApp;

	typedef std::vector<IComponent*>::iterator IterComponent;

	class CGameObject
	{
	public:
		CGameObject(const char* pName, GUID guid, CBaseApp* pApp);
		CGameObject(const char* pName, std::vector<IComponent*> components, GUID guid, CBaseApp* pApp);
		~CGameObject();

		void Init();
		void Start();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void OnDestroy();

		template<typename T>
		inline T* AddComponent();

		bool RemoveComponent(IComponent* pComponent);

		template<typename T>
		inline T* GetComponent();

		const char* GetName() const { return m_name.c_str(); }
		const GUID GetGUID() const { return m_guid; }
		bool IsAlive() const { return m_alive; }
		bool IsActive() const { return m_active; }

	private:
		CBaseApp* m_pApp;
		std::string m_name;
		std::vector<IComponent*> m_components;
		GUID m_guid;
		bool m_alive;
		bool m_active;
	};

	template<typename T>
	inline T* CGameObject::AddComponent()
	{
		m_components.push_back(new T());

		IComponent* pComponent = m_components.back();
		pComponent->Init(this, m_pApp);
		pComponent->Start();
		return static_cast<T*>(pComponent);
	}

	template<typename T>
	inline T* CGameObject::GetComponent()
	{
		for (IterComponent it = m_components.begin(); it != m_components.end(); it++)
		{
			IComponent* pBase = (*it);
			T* pDerived = dynamic_cast<T*>(pBase);
			if (pDerived != nullptr)
			{
				return pDerived;
			}
		}

		return nullptr;
	}
}
