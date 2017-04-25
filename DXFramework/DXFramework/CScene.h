#pragma once
#include "stdafx.h"
#include "CGameObject.h"
#include "CResourceManager.h"
#include "CGraphics.h"
#include "SRenderCommand.h"
#include "CCamera.h"

namespace dxfw
{
	class CBaseApp;
	class CCamera;

	typedef std::vector<CGameObject>::iterator IterGameObject;

	class CScene
	{
	public:
		CScene(CResourceManager* pResourceManager, CGraphics* pGraphics, const char* pName, CBaseApp* pApp);
		CScene(CResourceManager* pResourceManager, CGraphics* pGraphics, const std::vector<CGameObject>& gameObjects, const char* pName, CBaseApp* pApp);
		~CScene();

		void Init();
		void Start();
		void OnUnload();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();

		CGameObject& CreateGameObject(const char* pName);
		CGameObject& CreateGameObject(const char* pName, std::map<size_t, IComponent*> components);
		void DestroyGameObject(CGameObject& gameObject);
		CGameObject* FindGameObject(const char* pName);

	private:
		void DeleteGameObject(CGameObject& gameObject);

	private:
		CBaseApp* m_pApp;
		CGraphics* m_pGraphics;
		CResourceManager* m_pResourceManager;
		std::vector<CGameObject> m_gameObjects;
		std::string m_name;
	};
}
