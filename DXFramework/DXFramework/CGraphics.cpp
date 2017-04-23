#include "stdafx.h"
#include "CGraphics.h"

CGraphics::CGraphics(const SAppConfig& config)
	:
	m_config(config)
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::SetDependencies(CSysWindow* pSysWindow, CResourceManager* pResourceManager)
{
	m_pSysWindow = pSysWindow;
	m_pResourceManager = pResourceManager;
}

void CGraphics::Init()
{
	HRESULT result = S_OK;

	// --------------------------------------------------------------------
	// Create Device, Immediate Context and SwapChain
	// --------------------------------------------------------------------

	const D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	UINT sampleCount = 1;
	UINT sampleQuality = 0;

	DXGI_SWAP_CHAIN_DESC swapDesc = { 0 };
	// Backbuffer Desc
	swapDesc.BufferDesc.Width = m_pSysWindow->GetClientWidth();
	swapDesc.BufferDesc.Height = m_pSysWindow->GetClientHeight();
	swapDesc.BufferDesc.RefreshRate = { 0, 1 };
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	// Sample Desc
	swapDesc.SampleDesc.Count = sampleCount;
	swapDesc.SampleDesc.Quality = sampleQuality;
	// Window dependent
	swapDesc.OutputWindow = m_pSysWindow->GetHandle();
	swapDesc.Windowed = m_pSysWindow->GetMode() == ESysWinMode::Fullscreen ? FALSE : TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	result = D3D11CreateDeviceAndSwapChain(
		NULL, // pAdapter
		D3D_DRIVER_TYPE_HARDWARE, // DriverType
		NULL, // Software
#if _DEBUG
		D3D11_CREATE_DEVICE_DEBUG |
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
#else
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
#endif
		featureLevels,
		sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&swapDesc,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pImmediateContext
	);

	if (FAILED(result))
	{
		throw std::exception("D3D11CreateDeviceAndSwapChain");
	}

	// Get Backbuffer of SwapChain
	CComPtr<ID3D11Texture2D> pBackBuffer;
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(result))
	{
		throw std::exception("m_swapChain->GetBuffer");
	}

	// Create RenderTargetView
	result = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	if (FAILED(result))
	{
		throw std::exception("CreateRenderTargetView");
	}

	// --------------------------------------------------------------------
	// Create DepthStencilBuffer and View
	// --------------------------------------------------------------------

	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};
	depthStencilBufferDesc.Width = m_config.width;
	depthStencilBufferDesc.Height = m_config.height;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.SampleDesc.Count = sampleCount;
	depthStencilBufferDesc.SampleDesc.Quality = sampleQuality;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.MiscFlags = 0;

	result = m_pDevice->CreateTexture2D(&depthStencilBufferDesc, NULL, &m_pDepthStencilBuffer);
	if (FAILED(result))
	{
		throw std::exception("Create DepthStencilBuffer");
	}

	result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView);
	if (FAILED(result))
	{
		throw std::exception("CreateDepthStencilView");
	}

	// --------------------------------------------------------------------
	// Create and Set DepthStencil State
	// --------------------------------------------------------------------

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // TODO: for transparent objs set this to ZERO. separate draw calls.
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilStateDesc.StencilEnable = FALSE;

	result = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, &m_pDepthStencilState);
	if (FAILED(result))
	{
		throw std::exception("CreateDepthStencilState");
	}

	m_pImmediateContext->OMSetDepthStencilState(m_pDepthStencilState, 0);

	// --------------------------------------------------------------------
	// Create and Set Rasterizer State
	// --------------------------------------------------------------------

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
	if (FAILED(result))
	{
		throw std::exception("CreateRasterizerState");
	}

	m_pImmediateContext->RSSetState(m_pRasterizerState);

	// --------------------------------------------------------------------
	// Create and Set ViewPort
	// --------------------------------------------------------------------

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)m_config.width;
	viewport.Height = (float)m_config.height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &viewport);

	// --------------------------------------------------------------------
	// Set Render Target(s)
	// --------------------------------------------------------------------

	ID3D11RenderTargetView* rtvs[1];
	rtvs[0] = m_pRenderTargetView;
	m_pImmediateContext->OMSetRenderTargets(1, rtvs, m_pDepthStencilView);

	// --------------------------------------------------------------------
	// Create and Set Sampler State
	// --------------------------------------------------------------------

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.BorderColor[0] = 1.0f;
	samplerDesc.BorderColor[1] = 1.0f;
	samplerDesc.BorderColor[2] = 1.0f;
	samplerDesc.BorderColor[3] = 1.0f;

	result = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
	if (FAILED(result))
	{
		throw std::exception("CreateSamplerState");
	}

	ID3D11SamplerState* samplers[1];
	samplers[0] = m_pSamplerState;
	m_pImmediateContext->PSSetSamplers(0, 1, samplers);

	LoadResources();
	InitShadersAndBuffers();
}

void CGraphics::BeginDraw()
{
	// Clear BackBuffer
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Process RenderCommands
	for (auto itr = m_renderCommands.begin(); itr != m_renderCommands.end(); itr++)
	{
		const SRenderCommand& command = (*itr);

		if (command.pVertexShader != nullptr && command.pPixelShader != nullptr)
		{
			CShader* pVertexShader = command.pVertexShader;
			CShader* pPixelShader = command.pPixelShader;

			pVertexShader->Bind();
			pPixelShader->Bind();

			if (command.pModel != nullptr)
			{
				CInputLayout* pInputLayout = command.pVertexShader->GetInputLayout();
				// If InputLayout has not been created yet or InputLayoutType changed ...
				if (pInputLayout == nullptr || command.pModel->inputLayoutType != pVertexShader->GetInputLayout()->GetType())
				{
					// Create new InputLayout for this Shader
					pInputLayout = pVertexShader->CreateInputLayout(command.pModel->inputLayoutType, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				}
				pInputLayout->Bind();

				UINT vertexBufferSize = m_pVertexBuffer->GetSize();
				UINT modelSize = command.pModel->numIndices * sizeof(SVertexPosUV);

				// If VertexBuffer is too small for this Model ...
				if (vertexBufferSize < modelSize)
				{
					// Recreate VertexBuffer
					m_pVertexBuffer->Destroy();
					m_pVertexBuffer->Create(command.pModel->pVerticesPosUV, command.pModel->numIndices, sizeof(SVertexPosUV), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);

					// Recreate IndexBuffer
					m_pIndexBuffer->Destroy();
					m_pIndexBuffer->Create(command.pModel->pIndices, command.pModel->numIndices, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
				}
				else
				{
					m_pVertexBuffer->Update(command.pModel->pVerticesPosUV, command.pModel->numIndices, sizeof(SVertexPosUV));
					m_pIndexBuffer->Update(command.pModel->pIndices, command.pModel->numIndices);
				}
				m_pVertexBuffer->Bind();
				m_pIndexBuffer->Bind();
			}

			if (command.pTexture != nullptr)
			{
				command.pTexture->Bind(EShaderType::PixelShader);
			}

			UpdateVSConstantBuffer(DirectX::XMLoadFloat4x4(&command.worldMatrix));

			if (command.pModel != nullptr && command.pTexture != nullptr)
			{
				m_pImmediateContext->DrawIndexed(command.pModel->numIndices, 0, 0);
			}
		}
	}

	m_renderCommands.clear();
}

void CGraphics::EndDraw()
{
	if (m_config.vsync)
	{
		m_pSwapChain->Present(1, NULL);
	}
	else
	{
		m_pSwapChain->Present(0, NULL);
	}
}

void CGraphics::AddRenderCommand(const SRenderCommand& command)
{
	m_renderCommands.push_back(command);
}

void CGraphics::LoadResources()
{
	m_pResourceManager->LoadModel("res/model_cube.obj");
	m_pResourceManager->LoadModel("res/model_golem.obj");

	m_pResourceManager->LoadTexture("res/tex_cube_diffuse.tga");
	m_pResourceManager->LoadTexture("res/tex_golem_diffuse.png");
	m_pResourceManager->LoadTexture("res/tex_golem_normal.png");
	m_pResourceManager->LoadTexture("res/tex_brick_lumpy_basecolor.png");
	m_pResourceManager->LoadTexture("res/tex_metal_overlaping_plates_bolted_basecolor.png");
}

void CGraphics::InitShadersAndBuffers()
{
	CShader* pVertexShader = m_pResourceManager->LoadShader(EShaderType::VertexShader, "shader/basic_vs.fx", "VS_MAIN");
	CShader* pPixelShader = m_pResourceManager->LoadShader(EShaderType::PixelShader, "shader/basic_ps.fx", "PS_MAIN");

	m_pVertexBuffer = std::make_unique<CVertexBuffer>(this, m_pSysWindow);
	m_pIndexBuffer = std::make_unique<CIndexBuffer>(this, m_pSysWindow);

	m_pVSConstantBuffer = std::make_unique<CConstantBuffer>(EConstantBufferShaderType::VertexShader, D3D11_USAGE_DEFAULT, this, m_pSysWindow);
	SVSConstantBufferData cBufferData = {};
	m_pVSConstantBuffer->Create(&cBufferData, sizeof(SVSConstantBufferData));
	m_pVSConstantBuffer->Bind();
}

void CGraphics::UpdateVSConstantBuffer(const DirectX::XMMATRIX& objWorldMatrix)
{
	SVSConstantBufferData cBufferData;
	cBufferData.world = DirectX::XMMatrixTranspose(objWorldMatrix);
	cBufferData.view = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_viewMatrix));
	cBufferData.projection = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_projectionMatrix));

	m_pVSConstantBuffer->Update(&cBufferData, sizeof(SVSConstantBufferData));
}



