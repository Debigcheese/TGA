#pragma once
#include "Line.h"

namespace CommonUtilities
{
	class LineVolume
	{
	public:
		// Default constructor: empty LineVolume.
		template <typename T>
		LineVolume();
		// Constructor taking a list of Line that makes up the LineVolume.
		template <typename T>
		LineVolume(const std::vector<Line<T>>& aLineList);
		// Add a Line to the LineVolume.
		template <typename T>
		void AddLine(const Line<T>& aLine);
		// Returns whether a point is inside the LineVolume: it is inside when the point is
		// on the line or on the side the normal is pointing away from for all the lines in
		// the LineVolume.
		template <typename T>
		bool IsInside(const Vector2<T>& aPosition) const;

	private:
		template <typename T>
		std::vector<Line<T>>& myLineList;
	};

	template <typename T>
	LineVolume::LineVolume()
	{
	}

	template <typename T>
	LineVolume::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		for (int i = 0; i < aLineList; ++i)
		{
			myLineList<T>
		}
		for (auto& line : aLineList)
		{
		}
	}

	template <typename T>
	LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
	}
}
