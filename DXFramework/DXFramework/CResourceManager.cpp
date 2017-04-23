#include "stdafx.h"
#include "CResourceManager.h"

CResourceManager::CResourceManager(CGraphics* pGraphics, CSysWindow* pSysWindow)
	:
	m_pGraphics(pGraphics),
	m_pSysWindow(pSysWindow)
{
}

CResourceManager::~CResourceManager()
{
	for (itrModels itr = m_models.begin(); itr != m_models.end(); itr++)
	{
		UnloadModel(itr->second);
	}
	m_models.clear();
	for (itrTextures itr = m_textures.begin(); itr != m_textures.end(); itr++)
	{
		delete itr->second;
	}
	m_textures.clear();
	for (itrShaders itr = m_shaders.begin(); itr != m_shaders.end(); itr++)
	{
		delete itr->second;
	}
	m_shaders.clear();
}

SModel* CResourceManager::LoadModel(const std::string& pFileName)
{
	long fileSize;

	FILE* pFile = fopen(pFileName.c_str(), "rb");
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	BYTE* pBuffer = new BYTE[fileSize];
	fread(pBuffer, fileSize, 1, pFile);
	fclose(pFile);

	char* pCurrent = (char*)pBuffer;
	char* pEnd = (char*)(pBuffer + fileSize - 1);
	SModel model = {};

	// Count number of Positions, UVs, Normals, ...
	while (pCurrent <= pEnd)
	{
		if (pCurrent[0] == 'v')
		{
			if (pCurrent[1] == ' ')
			{
				model.numPositions++;
			}
			else if (pCurrent[1] == 't')
			{
				model.numUVs++;
			}
			else if (pCurrent[1] == 'n')
			{
				model.numNormals++;
			}
		}
		else if (pCurrent[0] == 'f')
		{
			model.numIndices += 3;
		}

		char* pLineEnd = strchr(pCurrent, '\n');
		if (pLineEnd != NULL)
		{
			pCurrent = pLineEnd;
		}
		pCurrent++;
	}

	// Allocate temporary Memory
	SVertexPosition* pPositions = new SVertexPosition[model.numPositions];
	SVertexUV* pUVs = new SVertexUV[model.numUVs];
	SVertexNormal* pNormals = new SVertexNormal[model.numNormals];
	DWORD* pIndicesPos = new DWORD[model.numIndices];
	DWORD* pIndicesUV = new DWORD[model.numIndices];
	DWORD* pIndicesNormal = new DWORD[model.numIndices];

	size_t indexPositions = 0;
	size_t indexUVs = 0;
	size_t indexNormals = 0;

	size_t indexIndicesPos = 0;
	size_t indexIndicesUV = 0;
	size_t indexIndicesNormal = 0;

	// Read Data from Buffer into temporary Memory
	float x, y, z;
	DWORD ip0, ip1, ip2;
	DWORD iuv0, iuv1, iuv2;
	DWORD in0, in1, in2;
	pCurrent = (char*)pBuffer;
	while (pCurrent <= pEnd)
	{
		if (pCurrent[0] == 'v')
		{
			if (pCurrent[1] == ' ')
			{
				// Position
				if (sscanf(pCurrent, "v %f %f %f", &x, &y, &z) == 3)
				{
					pPositions[indexPositions].pos[0] = x;
					pPositions[indexPositions].pos[1] = y;
					pPositions[indexPositions].pos[2] = z;
					indexPositions++;
				}
			}
			else if (pCurrent[1] == 't')
			{
				// UV
				if (sscanf(pCurrent, "vt %f %f", &x, &y) == 2)
				{
					pUVs[indexUVs].uv[0] = x;
					pUVs[indexUVs].uv[1] = 1.0f - y;
					indexUVs++;
				}
			}
			else if (pCurrent[1] == 'n')
			{
				// Normal
				if (sscanf(pCurrent, "vn %f %f %f", &x, &y, &z) == 3)
				{
					pNormals[indexNormals].normal[0] = x;
					pNormals[indexNormals].normal[1] = y;
					pNormals[indexNormals].normal[2] = z;
					indexNormals++;
				}
			}
		}
		else if (pCurrent[0] == 'f')
		{
			// Index
			if (sscanf(pCurrent, "f %u/%u/%u %u/%u/%u %u/%u/%u", &ip0, &iuv0, &in0, &ip1, &iuv1, &in1, &ip2, &iuv2, &in2) == 9)
			{
				pIndicesPos[indexIndicesPos++] = ip0 - 1;
				pIndicesPos[indexIndicesPos++] = ip1 - 1;
				pIndicesPos[indexIndicesPos++] = ip2 - 1;

				pIndicesUV[indexIndicesUV++] = iuv0 - 1;
				pIndicesUV[indexIndicesUV++] = iuv1 - 1;
				pIndicesUV[indexIndicesUV++] = iuv2 - 1;

				pIndicesNormal[indexIndicesNormal++] = in0 - 1;
				pIndicesNormal[indexIndicesNormal++] = in1 - 1;
				pIndicesNormal[indexIndicesNormal++] = in2 - 1;
			}
		}

		char* pLineEnd = strchr(pCurrent, '\n');
		if (pLineEnd != NULL)
		{
			pCurrent = pLineEnd;
		}
		pCurrent++;
	}

	delete[] pBuffer;

	// Determine InputLayoutType
	if (pPositions != nullptr && pUVs != nullptr && pNormals != nullptr)
	{
		model.inputLayoutType = EInputLayoutType::PosUV; // TODO: PosUVNormal
		// Allocate final Model Memory
		model.pVerticesPosUV = new SVertexPosUV[model.numIndices]; // TODO: PosUVNormal
	}
	else if (pPositions != nullptr && pUVs != nullptr)
	{
		model.inputLayoutType = EInputLayoutType::PosUV;
		// Allocate final Model Memory
		model.pVerticesPosUV = new SVertexPosUV[model.numIndices];
	}
	else if (pPositions != nullptr)
	{
		model.inputLayoutType = EInputLayoutType::Pos;
		// Allocate final Model Memory
		model.pVerticesPos = new SVertexPos[model.numIndices];
	}
	else
	{
		throw std::exception("Could not determine InputLayoutType");
	}

	// Allocate final Model Memory
	model.pIndices = new DWORD[model.numIndices];

	switch (model.inputLayoutType)
	{
	case EInputLayoutType::Pos:
		// Copy Data from temporary Memory into final Model Memory
		for (size_t i = 0; i < model.numIndices; i++)
		{
			SVertexPosition pos = pPositions[pIndicesPos[i]];

			model.pVerticesPos[i].pos[0] = pos.pos[0];
			model.pVerticesPos[i].pos[1] = pos.pos[1];
			model.pVerticesPos[i].pos[2] = pos.pos[2];

			model.pIndices[i] = (DWORD)i;
		}
		break;
	case EInputLayoutType::PosUV:
		// Copy Data from temporary Memory into final Model Memory
		for (size_t i = 0; i < model.numIndices; i++)
		{
			SVertexPosition pos = pPositions[pIndicesPos[i]];
			SVertexUV uv = pUVs[pIndicesUV[i]];
			SVertexNormal normal = pNormals[pIndicesNormal[i]];

			model.pVerticesPosUV[i].pos[0] = pos.pos[0];
			model.pVerticesPosUV[i].pos[1] = pos.pos[1];
			model.pVerticesPosUV[i].pos[2] = pos.pos[2];

			model.pVerticesPosUV[i].uv[0] = uv.uv[0];
			model.pVerticesPosUV[i].uv[1] = uv.uv[1];

			model.pIndices[i] = (DWORD)i;
		}
		break;
	case EInputLayoutType::PosUVNormal:
		// Copy Data from temporary Memory into final Model Memory
		// TODO: PosUVNormal
		break;
	default:
		throw std::exception("Unknown InputLayoutType");
		break;
	}

	// Deallocate temporary Memory
	delete[] pPositions;
	delete[] pUVs;
	delete[] pNormals;
	delete[] pIndicesPos;
	delete[] pIndicesUV;
	delete[] pIndicesNormal;

	m_models[pFileName] = model;

	return &(m_models[pFileName]);
}

void CResourceManager::UnloadModel(SModel& model)
{
	delete[] model.pVerticesPos;
	delete[] model.pVerticesPosUV;
	delete[] model.pVerticesPosUVNormal;
	delete[] model.pIndices;
}

SModel* CResourceManager::GetModel(const std::string& pFileName)
{
	itrModels itr = m_models.find(pFileName);
	if (itr != m_models.end())
	{
		return &itr->second;
	}
	return nullptr;
}

CTexture2D* CResourceManager::LoadTexture(const std::string& pFileName)
{
	CTexture2D* pTexture = new CTexture2D(m_pGraphics);
	pTexture->Create(pFileName.c_str(), D3D11_USAGE_DEFAULT);
	m_textures[pFileName] = pTexture;
	return pTexture;
}

CTexture2D* CResourceManager::GetTexture(const std::string& pFileName)
{
	itrTextures itr = m_textures.find(pFileName);
	if (itr != m_textures.end())
	{
		return itr->second;
	}
	return nullptr;
}

CShader* CResourceManager::LoadShader(EShaderType shaderType, const std::string& pFileName, const std::string& entryPoint)
{
	std::wstring wstr = std::wstring(pFileName.begin(), pFileName.end());

	CShader* pShader = new CShader(wstr.c_str(), entryPoint.c_str(), shaderType, m_pGraphics, m_pSysWindow);
	pShader->Compile();
	m_shaders[pFileName] = pShader;
	return pShader;
}

CShader* CResourceManager::GetShader(EShaderType shaderType, const std::string& pFileName)
{
	itrShaders itr = m_shaders.find(pFileName);
	if (itr != m_shaders.end())
	{
		return itr->second;
	}
	return nullptr;
}
