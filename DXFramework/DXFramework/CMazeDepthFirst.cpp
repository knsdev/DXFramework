#include "stdafx.h"
#include "CMazeDepthFirst.h"
#include "CMathHelper.h"
#include "Vec2.h"

namespace dxfw
{
	CMazeDepthFirst::CMazeDepthFirst()
	{
		m_pCells = nullptr;
		m_pBoolArray = nullptr;
	}

	CMazeDepthFirst::~CMazeDepthFirst()
	{
		CleanUp();
	}

	void CMazeDepthFirst::Generate(const SMazeParams& params)
	{
		// Reallocate total Data
		CleanUp();
		m_params = params;
		Init();

		assert(m_backTrack.empty());

		m_totalCount = m_params.width * m_params.height;
		m_visitedCount = 0;
		srand(m_params.seed);

		m_pCurrentCell = nullptr;

		// Visit random start Cell
		SMazeCell* pStartCell = GetCell(rand() % m_params.width, rand() % m_params.height);
		VisitCell(pStartCell);

		// While we have not visited every Cell in the Maze ...
		while (m_visitedCount < m_totalCount)
		{
			// Find unvisited Neighbor-Cells and store them in m_unvisitedNeighbors
			FindUnvisitedNeighbors();

			// If we found any unvisited Neighbor-Cell ...
			if (m_unvisitedNeighbors.size() > 0)
			{
				// Pick a random one to be the next Cell
				int randomIndex = rand() % m_unvisitedNeighbors.size();
				SMazeCell* pNextCell = m_unvisitedNeighbors[randomIndex];

				// Store current Cell in Backtrack-Stack and visit the next Cell
				VisitCell(pNextCell);
			}
			// If we have moved to a dead end (no free Neighbor-Cells) ...
			else if (m_backTrack.size() > 0)
			{
				// Move one Cell back
				m_pCurrentCell = m_backTrack.top();
				m_backTrack.pop();
			}
		}

		// Now that we have generated the Maze, we can calculate the bool array representation
		CalcBoolArray();
	}

	void CMazeDepthFirst::ShowDebugMaze(const char* strWall, const char* strField)
	{
		using namespace std;

		for (int y = 0; y < m_params.height * 3; y++)
		{
			for (int x = 0; x < m_params.width * 3; x++)
			{
				cout << (m_pBoolArray[x + m_params.width * 3 * y] ? strWall : strField) << " ";
			}
			cout << endl;
		}
	}

	void CMazeDepthFirst::CalcBoolArray()
	{
		//------------------------------------------------------------------------------------------
		// 1 Cell = 3x3 Grid
		//------------------------------------------------------------------------------------------
		// W t W
		// l c r
		// W b W
		//------------------------------------------------------------------------------------------
		// W = wall, c = center cell, t = top cell, b = bottom cell, l = left cell, r = right cell
		//------------------------------------------------------------------------------------------
		// This is why we need to multiply the size by 3
		int totalWidth = m_params.width * 3;
		int totalHeight = m_params.height * 3;

		// Set all fields to default value (wall) so that the corners are walls
		for (int y = 0; y < totalHeight; y++)
		{
			for (int x = 0; x < totalWidth; x++)
			{
				m_pBoolArray[x + totalWidth * y] = true;
			}
		}

		for (int y = 0; y < m_params.height; y++)
		{
			for (int x = 0; x < m_params.width; x++)
			{
				SMazeCell* pCell = GetCell(x, y);

				//------------------------------------------------------------------------------------------
				// Read Cell Data to set walls (true) or free Cells (false)
				//------------------------------------------------------------------------------------------
				// Center
				int centerX = x * 3 + 1;
				int centerY = y * 3 + 1;
				m_pBoolArray[centerX + totalWidth * centerY] = false;
				// Top
				m_pBoolArray[centerX + totalWidth * (centerY - 1)] = pCell->topWall;
				// Bottom
				m_pBoolArray[centerX + totalWidth * (centerY + 1)] = pCell->bottomWall;
				// Left
				m_pBoolArray[centerX - 1 + totalWidth * centerY] = pCell->leftWall;
				// Right
				m_pBoolArray[centerX + 1 + totalWidth * centerY] = pCell->rightWall;
			}
		}
	}

	void CMazeDepthFirst::Init()
	{
		int width = m_params.width;
		int height = m_params.height;

		// Allocate Cell Array for Maze
		m_pCells = new SMazeCell[width * height];

		// Store position in each cell
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				m_pCells[x + width * y].pos = { x, y };
			}
		}

		// Allocate Bool Array as a Maze Representation
		// see CalcBoolArray() for why we multiply by 3 * 3
		int boolArraySize = m_params.width * m_params.height * 3 * 3;
		m_pBoolArray = new bool[boolArraySize];
	}

	void CMazeDepthFirst::CleanUp()
	{
		if (m_pCells != nullptr)
		{
			delete[] m_pCells;
			m_pCells = nullptr;
		}

		if (m_pBoolArray != nullptr)
		{
			delete[] m_pBoolArray;
			m_pBoolArray = nullptr;
		}

		while (m_backTrack.size() > 0)
			m_backTrack.pop();
	}

	SMazeCell* CMazeDepthFirst::GetCell(int x, int y)
	{
		assert(x >= 0 && x < m_params.width);
		assert(y >= 0 && y < m_params.height);

		return &m_pCells[x + m_params.width * y];
	}

	void CMazeDepthFirst::FindUnvisitedNeighbors()
	{
		m_unvisitedNeighbors.clear();

		SPos pos = m_pCurrentCell->pos;

		SMazeCell* pCell = nullptr;

		// Check left cell
		pCell = GetCell(CMathHelper::Clamp<int>(pos.x - 1, 0, m_params.width - 1), CMathHelper::Clamp<int>(pos.y, 0, m_params.height - 1));
		if (!pCell->visited)
		{
			m_unvisitedNeighbors.push_back(pCell);
		}

		// Check right cell
		pCell = GetCell(CMathHelper::Clamp<int>(pos.x + 1, 0, m_params.width - 1), CMathHelper::Clamp<int>(pos.y, 0, m_params.height - 1));
		if (!pCell->visited)
		{
			m_unvisitedNeighbors.push_back(pCell);
		}

		// Check bottom cell
		pCell = GetCell(CMathHelper::Clamp<int>(pos.x, 0, m_params.width - 1), CMathHelper::Clamp<int>(pos.y - 1, 0, m_params.height - 1));
		if (!pCell->visited)
		{
			m_unvisitedNeighbors.push_back(pCell);
		}

		// Check right cell
		pCell = GetCell(CMathHelper::Clamp<int>(pos.x, 0, m_params.width - 1), CMathHelper::Clamp<int>(pos.y + 1, 0, m_params.height - 1));
		if (!pCell->visited)
		{
			m_unvisitedNeighbors.push_back(pCell);
		}
	}

	void CMazeDepthFirst::VisitCell(SMazeCell* pCellToVisit)
	{
		assert(!pCellToVisit->visited);
		assert(pCellToVisit != nullptr);

		// Remove Walls between current and next cell
		if (m_pCurrentCell != nullptr)
		{
			Vec2 vCurrent = Vec2((float)m_pCurrentCell->pos.x, (float)m_pCurrentCell->pos.y);
			Vec2 vNext = Vec2((float)pCellToVisit->pos.x, (float)pCellToVisit->pos.y);
			Vec2 vDelta = vNext - vCurrent;

			if (vDelta.x == -1)
			{
				m_pCurrentCell->leftWall = false;
				pCellToVisit->rightWall = false;
			}
			else if (vDelta.x == 1)
			{
				m_pCurrentCell->rightWall = false;
				pCellToVisit->leftWall = false;
			}
			else if (vDelta.y == -1)
			{
				m_pCurrentCell->topWall = false;
				pCellToVisit->bottomWall = false;
			}
			else if (vDelta.y == 1)
			{
				m_pCurrentCell->bottomWall = false;
				pCellToVisit->topWall = false;
			}
		}

		// Update Cell State and backtrack
		pCellToVisit->visited = true;
		m_backTrack.push(pCellToVisit);
		m_visitedCount++;
		m_pCurrentCell = pCellToVisit;
	}
}
