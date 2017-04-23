#pragma once
#include "stdafx.h"
#include "EInputLayoutType.h"
#include "SVertex.h"

struct SVertexPosition
{
	float pos[3];
};

struct SVertexUV
{
	float uv[2];
};

struct SVertexNormal
{
	float normal[3];
};

struct SModel
{
	EInputLayoutType inputLayoutType;

	DWORD numPositions;
	DWORD numUVs;
	DWORD numNormals;
	DWORD numIndices;

	SVertexPos* pVerticesPos;
	SVertexPosUV* pVerticesPosUV;
	SVertexPosUVNormal* pVerticesPosUVNormal;
	DWORD* pIndices;
};