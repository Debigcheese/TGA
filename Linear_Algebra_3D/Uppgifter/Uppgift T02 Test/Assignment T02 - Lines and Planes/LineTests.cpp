#include "stdafx.h"
#include "CppUnitTest.h"
#include "Shared/Utility.h"

#include "Student Code/CommonUtilities/Line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Linef = CommonUtilities::Line<float>;
using Lined = CommonUtilities::Line<double>;
using Vector2f = CommonUtilities::Vector2<float>;
using Vector2d = CommonUtilities::Vector2<double>;

namespace Assignment3LinesAndPlanes
{
	TEST_CLASS(LineTests)
	{
	public:
		TEST_METHOD(L_Inside)
		{
			// Test Inside() of Line<float>
			Linef line1f(Vector2f(-4.5f, -3.0f), Vector2f(0.0f, 6.0f));
			Linef line2f(Vector2f(0.0f, 6.0f), Vector2f(4.5f, -3.0f));
			Linef line3f(Vector2f(4.5f, -3.0f), Vector2f(-4.5f, -3.0f));

			Vector2f point1f(0.0f, 0.0f);
			Assert::IsTrue(line1f.IsInside(point1f),
			               L"Point (0.0f, 0.0f) should be inside of Line<float> intersecting (-4.5f, -3.0f) and (0.0f, 6.0f)");
			Assert::IsTrue(line2f.IsInside(point1f),
			               L"Point (0.0f, 0.0f) should be inside of Line<float> intersecting (0.0f, 6.0f) and (4.5f, -3.0f)");
			Assert::IsTrue(line3f.IsInside(point1f),
			               L"Point (0.0f, 0.0f) should be inside of Line<float> intersecting (4.5f, -3.0f) and (-4.5f, -3.0f)");

			Vector2f point2f(-4.0f, 0.0f);
			Assert::IsFalse(line1f.IsInside(point2f),
			                L"Point (-4.0f, 0.0f) should not be inside of Line<float> intersecting (-4.5f, -3.0f) and (0.0f, 6.0f)");
			Assert::IsTrue(line2f.IsInside(point2f),
			               L"Point (-4.0f, 0.0f) should be inside of Line<float> intersecting (0.0f, 6.0f) and (4.5f, -3.0f)");
			Assert::IsTrue(line3f.IsInside(point2f),
			               L"Point (-4.0f, 0.0f) should be inside of Line<float> intersecting (4.5f, -3.0f) and (-4.5f, -3.0f)");

			Vector2f point3f(4.0f, 0.0f);
			Assert::IsTrue(line1f.IsInside(point3f),
			               L"Point (4.0f, 0.0f) should be inside of Line<float> intersecting (-4.5f, -3.0f) and (0.0f, 6.0f)");
			Assert::IsFalse(line2f.IsInside(point3f),
			                L"Point (4.0f, 0.0f) should not be inside of Line<float> intersecting (0.0f, 6.0f) and (4.5f, -3.0f)");
			Assert::IsTrue(line3f.IsInside(point3f),
			               L"Point (4.0f, 0.0f) should be inside of Line<float> intersecting (4.5f, -3.0f) and (-4.5f, -3.0f)");

			Vector2f point4f(0.0f, -4.0f);
			Assert::IsTrue(line1f.IsInside(point4f),
			               L"Point (0.0f, -4.0f) should be inside of Line<float> intersecting (-4.5f, -3.0f) and (0.0f, 6.0f)");
			Assert::IsTrue(line2f.IsInside(point4f),
			               L"Point (0.0f, -4.0f) should be inside of Line<float> intersecting (0.0f, 6.0f) and (4.5f, -3.0f)");
			Assert::IsFalse(line3f.IsInside(point4f),
			                L"Point (0.0f, -4.0f) should not be inside of Line<float> intersecting (4.5f, -3.0f) and (-4.5f, -3.0f)");

			// Test Inside() of Line<double>
			Lined line1d(Vector2d(-4.5, -3.0), Vector2d(0.0, 6.0));
			Lined line2d(Vector2d(0.0, 6.0), Vector2d(4.5, -3.0));
			Lined line3d(Vector2d(4.5, -3.0), Vector2d(-4.5, -3.0));

			Vector2d point1d(0.0, 0.0);
			Assert::IsTrue(line1d.IsInside(point1d),
			               L"Point (0.0, 0.0) should be inside of Line<double> intersecting (-4.5, -3.0) and (0.0, 6.0)");
			Assert::IsTrue(line2d.IsInside(point1d),
			               L"Point (0.0, 0.0) should be inside of Line<double> intersecting (0.0, 6.0) and (4.5, -3.0)");
			Assert::IsTrue(line3d.IsInside(point1d),
			               L"Point (0.0, 0.0) should be inside of Line<double> intersecting (4.5, -3.0) and (-4.5, -3.0)");

			Vector2d point2d(-4.0, 0.0);
			Assert::IsFalse(line1d.IsInside(point2d),
			                L"Point (-4.0, 0.0) should not be inside of Line<double> intersecting (-4.5, -3.0) and (0.0, 6.0)");
			Assert::IsTrue(line2d.IsInside(point2d),
			               L"Point (-4.0, 0.0) should be inside of Line<double> intersecting (0.0, 6.0) and (4.5, -3.0)");
			Assert::IsTrue(line3d.IsInside(point2d),
			               L"Point (-4.0, 0.0) should be inside of Line<double> intersecting (4.5, -3.0) and (-4.5, -3.0)");

			Vector2d point3d(4.0, 0.0);
			Assert::IsTrue(line1d.IsInside(point3d),
			               L"Point (4.0f, 0.0f) should be inside of Line<double> intersecting (-4.5, -3.0) and (0.0, 6.0)");
			Assert::IsFalse(line2d.IsInside(point3d),
			                L"Point (4.0f, 0.0f) should not be inside of Line<double> intersecting (0.0, 6.0) and (4.5, -3.0)");
			Assert::IsTrue(line3d.IsInside(point3d),
			               L"Point (4.0f, 0.0f) should be inside of Line<double> intersecting (4.5, -3.0) and (-4.5, -3.0)");

			Vector2d point4d(0.0, -4.0);
			Assert::IsTrue(line1d.IsInside(point4d),
			               L"Point (0.0f, -4.0f) should be inside of Line<double> intersecting (-4.5, -3.0) and (0.0f, 6.0)");
			Assert::IsTrue(line2d.IsInside(point4d),
			               L"Point (0.0f, -4.0f) should be inside of Line<double> intersecting (0.0, 6.0) and (4.5, -3.0)");
			Assert::IsFalse(line3d.IsInside(point4d),
			                L"Point (0.0f, -4.0f) should not be inside of Line<double> intersecting (4.5, -3.0) and (-4.5, -3.0)");

			Vector2d pointOnLine1d(-4.5, -3.0);
			Vector2d pointOnLine2d(0.0, 6.0);
			Vector2d pointOnLine3d(4.5, -3.0);
		}

		TEST_METHOD(L_On_Line)
		{
			// Test Inside() of Line<float> with points that are on the lines
			Linef line1f(Vector2f(0.0f, 6.0f), Vector2f(-4.5f, -3.0f));
			Linef line2f(Vector2f(4.5f, -3.0f), Vector2f(0.0f, 6.0f));
			Linef line3f(Vector2f(-4.5f, -3.0f), Vector2f(4.5f, -3.0f));

			Vector2f pointOnLine1f(-4.5f, -3.0f);
			Vector2f pointOnLine2f(0.0f, 6.0f);
			Vector2f pointOnLine3f(4.5f, -3.0f);

			Assert::IsTrue(line1f.IsInside(pointOnLine1f),
			               L"Point (-4.5f, -3.0f) lies on the Line<float> intersecting (0.0f, 6.0f) and (-4.5f, -3.0f) and should be 'inside'.");
			Assert::IsTrue(line1f.IsInside(pointOnLine2f),
			               L"Point (0.0f, 6.0f) lies on the Line<float> intersecting (0.0f, 6.0f) and (-4.5f, -3.0f) and should be 'inside'.");
			Assert::IsFalse(line1f.IsInside(pointOnLine3f),
			                L"Point (4.5f, -3.0f) lies outside of the Line<float> intersecting (0.0f, 6.0f) and (-4.5f, -3.0f) and should not be 'inside'.");

			Assert::IsFalse(line2f.IsInside(pointOnLine1f),
			                L"Point (-4.5f, -3.0f) lies outside of the Line<float> intersecting (4.5f, -3.0f) and (0.0f, 6.0f) and should not be 'inside'.");
			Assert::IsTrue(line2f.IsInside(pointOnLine2f),
			               L"Point (0.0f, 6.0f) lies on the Line<float> intersecting (4.5f, -3.0f) and (0.0f, 6.0f) and should be 'inside'.");
			Assert::IsTrue(line2f.IsInside(pointOnLine3f),
			               L"Point (4.5f, -3.0f) lies on the Line<float> intersecting (4.5f, -3.0f) and (0.0f, 6.0f) and should be 'inside'.");

			Assert::IsTrue(line3f.IsInside(pointOnLine1f),
			               L"Point (-4.5f, -3.0f) lies on the Line<float> intersecting (-4.5f, -3.0f) and (4.5f, -3.0f) and should be 'inside'.");
			Assert::IsFalse(line3f.IsInside(pointOnLine2f),
			                L"Point (0.0f, 6.0f) lies outside of the Line<float> intersecting (-4.5f, -3.0f) and (4.5f, -3.0f) and should not be 'inside'.");
			Assert::IsTrue(line3f.IsInside(pointOnLine3f),
			               L"Point (4.5f, -3.0f) lies on the Line<float> intersecting (-4.5f, -3.0f) and (4.5f, -3.0f) and should be 'inside'.");

			// Test Inside() of Line<double> with points that are on the lines
			Lined line1d(Vector2d(0.0, 6.0), Vector2d(-4.5, -3.0));
			Lined line2d(Vector2d(4.5, -3.0), Vector2d(0.0, 6.0));
			Lined line3d(Vector2d(-4.5, -3.0), Vector2d(4.5, -3.0));

			Vector2d pointOnLine1d(-4.5, -3.0);
			Vector2d pointOnLine2d(0.0, 6.0);
			Vector2d pointOnLine3d(4.5, -3.0);

			Assert::IsTrue(line1d.IsInside(pointOnLine1d),
			               L"Point (-4.5, -3.0) lies on the Line<double> intersecting (0.0, 6.0) and (-4.5, -3.0) and should be 'inside'.");
			Assert::IsTrue(line1d.IsInside(pointOnLine2d),
			               L"Point (0.0, 6.0) lies on the Line<double> intersecting (0.0, 6.0) and (-4.5, -3.0) and should be 'inside'.");
			Assert::IsFalse(line1d.IsInside(pointOnLine3d),
			                L"Point (4.5, -3.0) lies outside of the Line<double> intersecting (0.0, 6.0) and (-4.5, -3.0) and should not be 'inside'.");

			Assert::IsFalse(line2d.IsInside(pointOnLine1d),
			                L"Point (-4.5, -3.0) lies outside of the Line<double> intersecting (4.5, -3.0) and (0.0, 6.0) and should not be 'inside'.");
			Assert::IsTrue(line2d.IsInside(pointOnLine2d),
			               L"Point (0.0, 6.0) lies on the Line<double> intersecting (4.5, -3.0) and (0.0, 6.0) and should be 'inside'.");
			Assert::IsTrue(line2d.IsInside(pointOnLine3d),
			               L"Point (4.5, -3.0) lies on the Line<double> intersecting (4.5, -3.0) and (0.0, 6.0) and should be 'inside'.");

			Assert::IsTrue(line3d.IsInside(pointOnLine1d),
			               L"Point (-4.5, -3.0) lies on the Line<double> intersecting (-4.5, -3.0) and (4.5, -3.0) and should be 'inside'.");
			Assert::IsFalse(line3d.IsInside(pointOnLine2d),
			                L"Point (0.0, 6.0) lies outside of the Line<double> intersecting (-4.5, -3.0) and (4.5, -3.0) and should not be 'inside'.");
			Assert::IsTrue(line3d.IsInside(pointOnLine3d),
			               L"Point (4.5, -3.0) lies on the Line<double> intersecting (-4.5, -3.0) and (4.5, -3.0) and should be 'inside'.");
		}

		TEST_METHOD(L_2_Points)
		{
			// Testing the Line<float> InitWith2Points() function with a bunch of random numbers.
			for (int i = 0; i < 100; ++i)
			{
				float x = TestUtility::GetRandomFloat();
				float y = TestUtility::GetRandomFloat();

				float p0x = TestUtility::GetRandomFloat();
				float p0y = TestUtility::GetRandomFloat();

				float p1x = TestUtility::GetRandomFloat();
				float p1y = TestUtility::GetRandomFloat();

				float directionX = p1x - p0x;
				float directionY = p1y - p0y;

				float normalX = -directionY;
				float normalY = directionX;

				float lineToPointX = x - p0x;
				float lineToPointY = y - p0y;

				float dotLineToPoint = (lineToPointX * normalX) + (lineToPointY * normalY);

				Vector2f point(x, y);
				Vector2f pointOnLine(p0x, p0y);
				Linef lineConstructor(Vector2f(p0x, p0y), Vector2f(p1x, p1y));
				Linef lineInit;
				lineInit.InitWith2Points(Vector2f(p0x, p0y), Vector2f(p1x, p1y));

				// Tolerance is 0.000001f, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001f, lineConstructor.IsInside(point),
				                 L"Inside of Line<float> is not calculated correctly when using the constructor that takes two points.");
				Assert::IsTrue(lineConstructor.IsInside(pointOnLine),
				               L"Point on the Line<float> is not considered 'inside' when using the constructor that takes two points.");

				// Tolerance is 0.000001f, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001f, lineInit.IsInside(point),
				                 L"Inside of Line<float> is not calculated correctly when using the InitWith2Points() function.");
				Assert::IsTrue(lineInit.IsInside(pointOnLine),
				               L"Point on the Line<float> is not considered 'inside' when using the InitWith2Points() function.");
			}

			// Testing the Line<double> InitWith2Points() function with a bunch of random numbers.
			for (int i = 0; i < 100; ++i)
			{
				double x = TestUtility::GetRandomDouble();
				double y = TestUtility::GetRandomDouble();

				double p0x = TestUtility::GetRandomDouble();
				double p0y = TestUtility::GetRandomDouble();

				double p1x = TestUtility::GetRandomDouble();
				double p1y = TestUtility::GetRandomDouble();

				double directionX = p1x - p0x;
				double directionY = p1y - p0y;
				double lengthInv = 1.0f / sqrt((directionX * directionX) + (directionY * directionY));

				double normalX = -directionY * lengthInv;
				double normalY = directionX * lengthInv;

				double lineToPointX = x - p0x;
				double lineToPointY = y - p0y;

				double dotLineToPoint = (lineToPointX * normalX) + (lineToPointY * normalY);

				Vector2d point(x, y);
				Vector2d pointOnLine(p0x, p0y);
				Lined lineConstructor(Vector2d(p0x, p0y), Vector2d(p1x, p1y));
				Lined lineInit;
				lineInit.InitWith2Points(Vector2d(p0x, p0y), Vector2d(p1x, p1y));

				// Tolerance is 0.000001, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001, lineConstructor.IsInside(point),
				                 L"Inside of Line<double> is not calculated correctly when using the constructor that takes two points.");
				Assert::IsTrue(lineConstructor.IsInside(pointOnLine),
				               L"Point on the Line<double> is not considered 'inside' when using the constructor that takes two points.");

				// Tolerance is 0.000001, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001, lineInit.IsInside(point),
				                 L"Inside of Line<double> is not calculated correctly when using the InitWith2Points() function.");
				Assert::IsTrue(lineInit.IsInside(pointOnLine),
				               L"Point on the Line<double> is not considered 'inside' when using the InitWith2Points() function.");
			}
		}

		TEST_METHOD(L_Init_With_Point_And_Direction)
		{
			// Testing the Line<float> InitWithPointAndDirection() function with a bunch of random numbers.
			for (int i = 0; i < 100; ++i)
			{
				float x = TestUtility::GetRandomFloat();
				float y = TestUtility::GetRandomFloat();

				float p0x = TestUtility::GetRandomFloat();
				float p0y = TestUtility::GetRandomFloat();

				float p1x = TestUtility::GetRandomFloat();
				float p1y = TestUtility::GetRandomFloat();

				float directionX = p1x - p0x;
				float directionY = p1y - p0y;

				float normalX = -directionY;
				float normalY = directionX;

				float lineToPointX = x - p0x;
				float lineToPointY = y - p0y;

				float dotLineToPoint = (lineToPointX * normalX) + (lineToPointY * normalY);

				Vector2f point(x, y);
				Vector2f pointOnLine(p0x, p0y);
				Linef line;
				line.InitWithPointAndDirection(Vector2f(p0x, p0y), Vector2f(directionX, directionY));

				// Tolerance is 0.000001f, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001f, line.IsInside(point),
				                 L"Inside of Line<float> is not calculated correctly.");
				Assert::IsTrue(line.IsInside(pointOnLine), L"Point on the Line<float> is not considered 'inside'.");
			}

			// Testing the Line<double> InitWithPointAndDirection() function with a bunch of random numbers.
			for (int i = 0; i < 100; ++i)
			{
				double x = TestUtility::GetRandomDouble();
				double y = TestUtility::GetRandomDouble();

				double p0x = TestUtility::GetRandomDouble();
				double p0y = TestUtility::GetRandomDouble();

				double p1x = TestUtility::GetRandomDouble();
				double p1y = TestUtility::GetRandomDouble();

				double directionX = p1x - p0x;
				double directionY = p1y - p0y;
				double lengthInv = 1.0f / sqrt((directionX * directionX) + (directionY * directionY));

				double normalX = -directionY * lengthInv;
				double normalY = directionX * lengthInv;

				double lineToPointX = x - p0x;
				double lineToPointY = y - p0y;

				double dotLineToPoint = (lineToPointX * normalX) + (lineToPointY * normalY);

				Vector2d point(x, y);
				Vector2d pointOnLine(p0x, p0y);
				Lined line;
				line.InitWithPointAndDirection(Vector2d(p0x, p0y), Vector2d(directionX, directionY));

				// Tolerance is 0.000001, which is considered as being 0, that is: the point is on the line which is "inside".
				Assert::AreEqual(dotLineToPoint < 0.000001, line.IsInside(point),
				                 L"Inside of Line<double> is not calculated correctly.");
				Assert::IsTrue(line.IsInside(pointOnLine), L"Point on the Line<double> is not considered 'inside'.");
			}
		}
	};
}
