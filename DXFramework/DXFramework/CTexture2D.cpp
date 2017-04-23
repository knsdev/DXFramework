#include "stdafx.h"
#include "CTexture2D.h"
#include "CMathHelper.h"

CTexture2D::CTexture2D(CGraphics* pGraphics)
	:
	m_pGraphics(pGraphics)
{
}

CTexture2D::~CTexture2D()
{
}

void CTexture2D::Create(UINT width, UINT height, UINT colorRGBA, D3D11_USAGE usage)
{
	HRESULT result = S_OK;

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	UINT colorABGR = CMathHelper::RGBAtoABGR(colorRGBA);

	size_t numTexels = width * height;
	UINT* texels = new UINT[numTexels];
	for (size_t i = 0; i < numTexels; i++)
	{
		texels[i] = colorABGR; // ABGR
	}

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = texels;
	initData.SysMemPitch = width;

	result = m_pGraphics->GetDevice()->CreateTexture2D(&desc, &initData, &m_pTexture);
	if (FAILED(result))
	{
		throw std::exception("CreateTexture2D");
	}

	delete[] texels;

	result = m_pGraphics->GetDevice()->CreateShaderResourceView(m_pTexture, NULL, &m_pShaderResView);
	if (FAILED(result))
	{
		throw std::exception("CreateShaderResourceView");
	}
}

void CTexture2D::Create(const char* pFileName, D3D11_USAGE usage)
{
	HRESULT result = S_OK;

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(pFileName, 0);
	FIBITMAP* pImage = FreeImage_Load(format, pFileName, NULL);
	if (pImage == nullptr)
	{
		throw std::exception("Image not found!");
	}

	UINT bpp = FreeImage_GetBPP(pImage);
	if (bpp != 32)
	{
		FIBITMAP* pNewImage = FreeImage_ConvertTo32Bits(pImage);
		FreeImage_Unload(pImage);
		pImage = pNewImage;
	}

	UINT width = FreeImage_GetWidth(pImage);
	UINT height = FreeImage_GetHeight(pImage);
	UINT pitch = FreeImage_GetPitch(pImage);

	size_t size = height * pitch;
	BYTE* pBits = (BYTE*)malloc(size);
	FreeImage_ConvertToRawBits(pBits, pImage, pitch, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);

	// Convert Texel's Color Format from ARGB to ABGR
	UINT* pTexels = (UINT*)pBits;
	size_t num = size / 4u;
	for (size_t i = 0; i < num; i++)
	{
		UINT ARGB = pTexels[i];
		BYTE A = (ARGB >> 24) & 0xFF;
		BYTE R = (ARGB >> 16) & 0xFF;
		BYTE G = (ARGB >> 8) & 0xFF;
		BYTE B = (ARGB) & 0xFF;
		pTexels[i] = (A << 24) | (B << 16) | (G << 8) | (R);
	}

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = pTexels;
	initData.SysMemPitch = pitch;

	result = m_pGraphics->GetDevice()->CreateTexture2D(&desc, &initData, &m_pTexture);
	if (FAILED(result))
	{
		throw std::exception("CreateTexture2D");
	}

	result = m_pGraphics->GetDevice()->CreateShaderResourceView(m_pTexture, NULL, &m_pShaderResView);
	if (FAILED(result))
	{
		throw std::exception("CreateShaderResourceView");
	}

	free(pBits);
	FreeImage_Unload(pImage);
}

void CTexture2D::Bind(EShaderType shaderType)
{
	ID3D11ShaderResourceView* views[1];
	views[0] = m_pShaderResView;

	switch (shaderType)
	{
	case EShaderType::VertexShader:
		m_pGraphics->GetImmediateContext()->VSSetShaderResources(0, 1, views);
		break;
	case EShaderType::PixelShader:
		m_pGraphics->GetImmediateContext()->PSSetShaderResources(0, 1, views);
		break;
	default:
		break;
	}
}

void CTexture2D::Unbind(EShaderType shaderType)
{
	switch (shaderType)
	{
	case EShaderType::VertexShader:
		m_pGraphics->GetImmediateContext()->VSSetShaderResources(0, 0, NULL);
		break;
	case EShaderType::PixelShader:
		m_pGraphics->GetImmediateContext()->PSSetShaderResources(0, 0, NULL);
		break;
	default:
		break;
	}
}
