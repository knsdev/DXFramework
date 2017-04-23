#include "stdafx.h"
#include "IComponent.h"

IComponent::IComponent()
	:
	m_enabled(true)
{
}

IComponent::~IComponent()
{
}

void IComponent::Init(CGameObject* pGameObject, CBaseApp* pApp)
{
	m_pGameObject = pGameObject;
	m_pApp = pApp;
}

void IComponent::Start()
{
}

void IComponent::Update(float deltaTime)
{
}

void IComponent::FixedUpdate(float deltaTime)
{
}

void IComponent::OnDestroy()
{
}

void IComponent::OnEnable()
{
}

void IComponent::OnDisable()
{
}
