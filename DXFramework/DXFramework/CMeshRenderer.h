#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "SModel.h"
#include "EShaderType.h"

namespace dxfw
{
	class CMeshRenderer : public IComponent
	{
	public:
		CMeshRenderer();
		virtual ~CMeshRenderer();

		void SetModelFileName(const char* pModelFileName) { m_modelFileName = pModelFileName; }
		std::string& GetModelFileName() { return m_modelFileName; }

		void SetTextureFileName(const char* pTextureFileName) { m_textureFileName = pTextureFileName; }
		std::string& GetTextureFileName() { return m_textureFileName; }

		void SetShaderFileName(EShaderType shaderType, const char* pShaderFileName) { m_shaderFileNames[shaderType] = pShaderFileName; }
		std::string& GetShaderFileName(EShaderType shaderType) { return m_shaderFileNames[shaderType]; }

	private:
		std::string m_modelFileName;
		std::string m_textureFileName;
		std::unordered_map<EShaderType, std::string> m_shaderFileNames;
	};
}
