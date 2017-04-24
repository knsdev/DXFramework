#pragma once
#include "stdafx.h"
#include "CGameObject.h"

namespace dxfw
{
	class CGameObject;
	class CBaseApp;

	class IComponent
	{
	public:
		IComponent();
		virtual ~IComponent();

		void Init(CGameObject* pGameObject, CBaseApp* pApp);

		template<typename T>
		inline T* GetComponent() { return m_pGameObject->GetComponent<T>(); }

		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void OnDestroy();
		virtual void OnEnable();
		virtual void OnDisable();

		bool IsEnabled() const { return m_enabled; }
		void SetEnabled(bool enabled) { m_enabled = enabled; }

		CBaseApp* GetApp() { return m_pApp; }

	protected:
		CGameObject* m_pGameObject;
		CBaseApp* m_pApp;
		bool m_enabled;
	};
}
