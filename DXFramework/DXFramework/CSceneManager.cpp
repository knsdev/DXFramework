#include "stdafx.h"
#include "CSceneManager.h"

namespace dxfw
{
	CSceneManager::CSceneManager(CResourceManager* pResourceManager, CGraphics* pGraphics, CBaseApp* pApp)
		:
		m_pResourceManager(pResourceManager),
		m_pGraphics(pGraphics),
		m_pApp(pApp)
	{
	}

	CSceneManager::~CSceneManager()
	{
	}

	void CSceneManager::LoadScene(const CScene& scene, ESceneLoadOption option)
	{
		switch (option)
		{
		case ESceneLoadOption::Single:
		{
			// Unload all scenes
			IterScene it = m_scenes.begin();
			while (m_scenes.size() > 0)
			{
				UnloadScene(&(*it));
			}
			break;
		}
		case ESceneLoadOption::Additive:
			// do nothing because we just add a new scene
			break;
		default:
			break;
		}

		m_scenes.push_back(scene);
		CScene& newScene = m_scenes.back();
		newScene.Init();
		newScene.Start();
	}

	void CSceneManager::UnloadScene(CScene* pScene)
	{
		IterScene it = std::find_if(m_scenes.begin(), m_scenes.end(), [pScene](const CScene& current)
		{
			return (pScene == &current);
		});

		it->OnUnload();

		if (it != m_scenes.end())
		{
			CScene& s = m_scenes.back();
			std::swap(*it, s);
			m_scenes.pop_back();
		}
	}

	void CSceneManager::Update(float deltaTime)
	{
		for (IterScene it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			it->Update(deltaTime);
		}
	}

	void CSceneManager::FixedUpdate(float deltaTime)
	{
		for (IterScene it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			it->FixedUpdate(deltaTime);
		}
	}

	void CSceneManager::Render()
	{
		for (IterScene it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			it->Render();
		}
	}
}
