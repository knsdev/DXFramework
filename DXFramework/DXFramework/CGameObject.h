#pragma once
#include "stdafx.h"
#include "IComponent.h"

namespace dxfw
{
	class IComponent;
	class CBaseApp;

	typedef std::map<size_t, IComponent*>::iterator IterComponent;

	class CGameObject
	{
	public:
		CGameObject(const char* pName, GUID guid, CBaseApp* pApp);
		CGameObject(const char* pName, std::map<size_t, IComponent*> components, GUID guid, CBaseApp* pApp);
		~CGameObject();

		void Init();
		void Start();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void OnDestroy();

		template<typename T>
		T* AddComponent();

		template<typename T>
		bool RemoveComponent();

		template<typename T>
		T* GetComponent();

		const char* GetName() const { return m_name.c_str(); }
		const GUID GetGUID() const { return m_guid; }
		bool IsAlive() const { return m_alive; }
		bool IsActive() const { return m_active; }

	private:
		CBaseApp* m_pApp;
		std::string m_name;
		std::map<size_t, IComponent*> m_components; // key = hash of typeid, value = pointer
		GUID m_guid;
		bool m_alive;
		bool m_active;
	};

	template<typename T>
	T* CGameObject::AddComponent()
	{
		T* pComponent = GetComponent<T>();

		// If we already added a component of this type ...
		if (pComponent != nullptr)
		{
			// Do not allow to add a second one
			return pComponent;
		}

		size_t key = typeid(T).hash_code();
		pComponent = new T();
		m_components[key] = pComponent;

		pComponent->Init(this, m_pApp);
		pComponent->Start();
		return static_cast<T*>(pComponent);
	}

	template<typename T>
	bool CGameObject::RemoveComponent()
	{
		size_t key = typeid(T).hash_code();
		auto it = m_components.find(key);

		if (it != m_components.end())
		{
			delete it->second;
			m_components.erase(it);

			return true;
		}

		return false;
	}

	template<typename T>
	T* CGameObject::GetComponent()
	{
		size_t key = typeid(T).hash_code();
		auto it = m_components.find(key);

		if (it != m_components.end())
		{
			return static_cast<T*>(it->second);
		}

		return nullptr;
	}

}
