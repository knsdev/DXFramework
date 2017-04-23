#pragma once
#include "stdafx.h"
#include "CScene.h"
#include "CResourceManager.h"
#include "CGraphics.h"
class CBaseApp;

typedef std::vector<CScene>::iterator IterScene;

enum class ESceneLoadOption
{
	Single,
	Additive,
};

class CSceneManager
{
public:
	CSceneManager(CResourceManager* pResourceManager, CGraphics* pGraphics, CBaseApp* pApp);
	~CSceneManager();

	// TODO: Load Scene from File (implement function in CResourceManager)
	void LoadScene(const CScene& scene, ESceneLoadOption option);
	void UnloadScene(CScene* pScene);
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render();

	const std::vector<CScene>& GetScenes() { return m_scenes; }
	CScene* GetSceneAt(size_t index) { if (index < m_scenes.size()) { return &m_scenes[index]; } return nullptr; }

private:
	CBaseApp* m_pApp;
	CResourceManager* m_pResourceManager;
	CGraphics* m_pGraphics;
	std::vector<CScene> m_scenes;
};