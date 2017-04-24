#pragma once
#include "stdafx.h"

namespace dxfw
{
	struct SPos
	{
		int x;
		int y;
	};

	struct SMazeCell
	{
		bool visited;
		SPos pos;
		bool leftWall;
		bool rightWall;
		bool topWall;
		bool bottomWall;

		SMazeCell()
		{
			visited = false;
			leftWall = true;
			rightWall = true;
			topWall = true;
			bottomWall = true;
		}
	};

	struct SMazeParams
	{
		int width;
		int height;
		unsigned int seed;
	};

	class CMazeDepthFirst
	{
	public:
		CMazeDepthFirst();
		virtual ~CMazeDepthFirst();

		// Generate a new maze. If used another time, it deletes the old maze and creates a new one.
		void Generate(const SMazeParams& params);

		// Logs a string representation of the generated maze to the console
		void ShowDebugMaze(const char* strWall = "o", const char* strField = " ");

		// Get a bool array representation of the generated maze.
		bool* GetBoolArray() { return m_pBoolArray; }

		// Get Maze Parameters
		const SMazeParams& GetParams() { return m_params; }

	private:
		void Init();
		void CleanUp();
		SMazeCell* GetCell(int x, int y);
		void FindUnvisitedNeighbors();
		void VisitCell(SMazeCell* pCell);
		void CalcBoolArray();

	private:
		SMazeParams m_params;
		SMazeCell* m_pCells;

		SMazeCell* m_pCurrentCell;
		int m_visitedCount;
		int m_totalCount;

		std::stack<SMazeCell*> m_backTrack;
		std::vector<SMazeCell*> m_unvisitedNeighbors;

		bool* m_pBoolArray;
	};
}
