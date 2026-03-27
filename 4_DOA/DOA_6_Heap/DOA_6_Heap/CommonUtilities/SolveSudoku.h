#pragma once

namespace CommonUtilities
{
	inline bool IsSafe(std::array<int, 81>& aBoard, int index, int aValue)
	{
		int targetRow = index / 9;
		int targetCol = index % 9;

		for (int i = 0; i < 9; i++)
		{
			if (aBoard[targetRow * 9 + i] == aValue)
			{
				return false;
			}
		}

		for (int j = 0; j < 9; j++)
		{
			if (aBoard[j * 9 + targetCol] == aValue)
			{
				return false;
			}
		}

		int boxRow = (targetRow / 3) * 3;
		int boxCol = (targetCol / 3) * 3;
		for (int i = boxRow; i < boxRow + 3; i++)
		{
			for (int j = boxCol; j < boxCol + 3; j++)
			{
				if (aBoard[i * 9 + j] == aValue)
				{
					return false;
				}
			}
		}
		return true;
	}

	inline bool SolveSudoku(std::array<int, 81>& aBoard)
	{
		int index = 0;
		for (int i = 0; i < 81; ++i)
		{
			if (aBoard[i] == 0)
			{
				for (int value = 1; value <= 9; value++)
				{
					if (IsSafe(aBoard, i, value))
					{
						aBoard[i] = value;

						if (SolveSudoku(aBoard))
						{
							return true;
						}

						aBoard[i] = 0;
					}
				}
				return false;
			}
		}
		return true;
	}
}
