#include "stdafx.h"
#include "CppUnitTest.h"

#include "Shared/Utility.hpp"
#include "Student Code/LineVolume.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Linef = CommonUtilities::Line<float>;
using Lined = CommonUtilities::Line<double>;
using LVf = CommonUtilities::LineVolume<float>;
using LVd = CommonUtilities::LineVolume<double>;
using Vector2f = CommonUtilities::Vector2<float>;
using Vector2d = CommonUtilities::Vector2<double>;

namespace Assignment3LinesAndPlanes
{
	TEST_CLASS(LineVolumeTests)
	{
	public:

		TEST_METHOD(LV_Constructor)
		{
			// Test the LineVolume<float> constructor with passing in one to four lines.
			Linef line1F(Vector2f(-4.5f, -3.0f), Vector2f(0.0f, 6.0f));
			Linef line2F(Vector2f(0.0f, 6.0f), Vector2f(4.5f, -3.0f));
			Linef line3F(Vector2f(4.5f, -3.0f), Vector2f(-4.5f, -3.0f));
			Linef line1NegF(Vector2f(0.0f, 6.0f), Vector2f(-4.5f, -3.0f));

			Vector2f pointF(0.0f, 0.0f);
			
			LVf lineVolume1F({ line1F });
			Assert::IsTrue(lineVolume1F.IsInside(pointF), L"Point (0.0f, 0.0f) should be inside of the LineVolume<float> with one line going through points (-4.5f, -3.0f) and (0.0f, 6.0f).");
			
			LVf lineVolume2F({ line2F });
			Assert::IsTrue(lineVolume2F.IsInside(pointF), L"Point (0.0f, 0.0f) should be inside of the LineVolume<float> with one line going through points (0.0f, 6.0f) and (4.5f, -3.0f).");

			LVf lineVolume3F({ line3F });
			Assert::IsTrue(lineVolume3F.IsInside(pointF), L"Point (0.0f, 0.0f) should be inside of the LineVolume<float> with one line going through points (4.5f, -3.0f) and (-4.5f, -3.0f).");
			
			LVf lineVolume1NegF({ line1NegF });
			Assert::IsFalse(lineVolume1NegF.IsInside(pointF), L"Point (0.0f, 0.0f) should not be inside of the LineVolume<float> with one line going through points (0.0f, 6.0f) and (-4.5f, -3.0f).");

			LVf lineVolume3LinesF({ line1F, line2F, line3F });
			Assert::IsTrue(lineVolume3LinesF.IsInside(pointF), L"Point (0.0f, 0.0f) should be inside of the LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }\n" \
				"3] { (4.5f, -3.0f), (-4.5f, -3.0f) }");

			LVf lineVolume4LinesF({ line1F, line2F, line3F, line1NegF });
			Assert::IsFalse(lineVolume4LinesF.IsInside(pointF), L"Point (0.0f, 0.0f) should not be inside of the LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }\n" \
				"3] { (4.5f, -3.0f), (-4.5f, -3.0f) }\n" \
				"4] { (0.0f, 6.0f), (-4.5f, -3.0f) }");

			// Test the LineVolume<double> constructor with passing in one to four lines.
			Lined line1D(Vector2d(-4.5, -3.0), Vector2d(0.0, 6.0));
			Lined line2D(Vector2d(0.0, 6.0), Vector2d(4.5, -3.0));
			Lined line3D(Vector2d(4.5, -3.0), Vector2d(-4.5, -3.0));
			Lined line1NegD(Vector2d(0.0, 6.0), Vector2d(-4.5, -3.0));

			Vector2d pointD(0.0, 0.0);

			LVd lineVolume1D({ line1D });
			Assert::IsTrue(lineVolume1D.IsInside(pointD), L"Point (0.0, 0.0) should be inside of the LineVolume<double> with one line going through points (-4.5, -3.0) and (0.0, 6.0).");

			LVd lineVolume2D({ line2D });
			Assert::IsTrue(lineVolume2D.IsInside(pointD), L"Point (0.0, 0.0) should be inside of the LineVolume<double> with one line going through points (0.0, 6.0) and (4.5, -3.0).");

			LVd lineVolume3D({ line3D });
			Assert::IsTrue(lineVolume3D.IsInside(pointD), L"Point (0.0, 0.0) should be inside of the LineVolume<double> with one line going through points (4.5, -3.0) and (-4.5, -3.0).");

			LVd lineVolume1NegD({ line1NegD });
			Assert::IsFalse(lineVolume1NegD.IsInside(pointD), L"Point (0.0, 0.0) should not be inside of the LineVolume<double> with one line going through points (0.0, 6.0) and (-4.5, -3.0).");

			LVd lineVolume3LinesD({ line1D, line2D, line3D });
			Assert::IsTrue(lineVolume3LinesD.IsInside(pointD), L"Point (0.0, 0.0) should be inside of the LineVolume<double> with the following lines:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }\n" \
				"2] { (0.0, 6.0), (4.5, -3.0) }\n" \
				"3] { (4.5, -3.0), (-4.5, -3.0) }");

			LVd lineVolume4LinesD({ line1D, line2D, line3D, line1NegD });
			Assert::IsFalse(lineVolume4LinesD.IsInside(pointD), L"Point (0.0, 0.0) should not be inside of the LineVolume<double> with the following lines:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }\n" \
				"2] { (0.0, 6.0), (4.5, -3.0) }\n" \
				"3] { (4.5, -3.0), (-4.5, -3.0) }\n" \
				"4] { (0.0, 6.0), (-4.5, -3.0) }");
		}

		TEST_METHOD(LV_IsInside)
		{
			// Test the LineVolume<float> IsInside() function.
			LVf lineVolumeF({ Linef(Vector2f(-4.5f, -3.0f), Vector2f(0.0f, 6.0f))
							, Linef(Vector2f(0.0f, 6.0f), Vector2f(4.5f, -3.0f))
							, Linef(Vector2f(4.5f, -3.0f), Vector2f(-4.5f, -3.0f)) });
			std::wstring lvfDescription(L"LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }\n" \
				"3] { (4.5f, -3.0f), (-4.5f, -3.0f) }");

			Vector2f pointF(0.0f, 0.0f);
			Vector2f point1F(-4.0f, 0.0f);
			Vector2f point2F(4.0f, 0.0f);
			Vector2f point3F(0.0f, -4.0f);

			Assert::IsTrue(lineVolumeF.IsInside(pointF), (L"Point (0.0f, 0.0f) should be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(point1F), (L"Point (-4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(point2F), (L"Point (4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(point3F), (L"Point (0.0f, -4.0f) should not be inside of the " + lvfDescription).c_str());

			// Test the LineVolume<double> IsInside() function.
			LVd lineVolumeD({ Lined(Vector2d(-4.5f, -3.0f), Vector2d(0.0f, 6.0f))
							, Lined(Vector2d(0.0f, 6.0f), Vector2d(4.5f, -3.0f))
							, Lined(Vector2d(4.5f, -3.0f), Vector2d(-4.5f, -3.0f)) });
			std::wstring lvdDescription(L"LineVolume<double> with the following lines:\n" \
				"{ (-4.5, -3.0), (0.0, 6.0) }\n" \
				"{ (0.0, 6.0), (4.5, -3.0) }\n" \
				"{ (4.5, -3.0), (-4.5, -3.0) }");

			Vector2d pointD(0.0, 0.0);
			Vector2d point1D(-4.0, 0.0);
			Vector2d point2D(4.0, 0.0);
			Vector2d point3D(0.0, -4.0);

			Assert::IsTrue(lineVolumeD.IsInside(pointD), (L"Point (0.0, 0.0) should be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(point1D), (L"Point (-4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(point2D), (L"Point (4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(point3D), (L"Point (0.0, -4.0) should not be inside of the " + lvdDescription).c_str());
		}

		TEST_METHOD(LV_On_Line)
		{
			// Test the LineVolume<float> IsInside() function with points that are on the different lines.
			LVf lineVolumeF({ Linef(Vector2f(-4.5f, -3.0f), Vector2f(0.0f, 6.0f))
							, Linef(Vector2f(0.0f, 6.0f), Vector2f(4.5f, -3.0f))
							, Linef(Vector2f(4.5f, -3.0f), Vector2f(-4.5f, -3.0f)) });
			std::wstring lvfDescription(L"LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }\n" \
				"3] { (4.5f, -3.0f), (-4.5f, -3.0f) }");

			Vector2f pointF(0.0f, 0.0f);
			Vector2f point1F(0.0f, 6.0f);
			Vector2f point2F(4.5f, -3.0f);
			Vector2f point3F(-4.5f, -3.0f);

			Assert::IsTrue(lineVolumeF.IsInside(pointF), (L"Point (0.0f, 0.0f) on one of the lines should be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(point1F), (L"Point (0.0f, 6.0f) on one of the lines should be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(point2F), (L"Point (4.5f, -3.0f) on one of the lines should be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(point3F), (L"Point (-4.5, -3.0f) on one of the lines should be inside of the " + lvfDescription).c_str());

			// Test the LineVolume<double> IsInside() function with points that are on the different lines.
			LVd lineVolumeD({ Lined(Vector2d(-4.5, -3.0), Vector2d(0.0, 6.0))
							, Lined(Vector2d(0.0, 6.0), Vector2d(4.5, -3.0))
							, Lined(Vector2d(4.5, -3.0), Vector2d(-4.5, -3.0)) });
			std::wstring lvdDescription(L"LineVolume<double> with the following line:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }\n" \
				"2] { (0.0, 6.0), (4.5, -3.0) }\n" \
				"3] { (4.5, -3.0), (-4.5, -3.0) }");

			Vector2d pointD(0.0, 0.0);
			Vector2d point1D(0.0, 6.0);
			Vector2d point2D(4.5, -3.0);
			Vector2d point3D(-4.5, -3.0);

			Assert::IsTrue(lineVolumeD.IsInside(pointD), (L"Point (0.0, 0.0) on one of the lines should be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(point1D), (L"Point (0.0, 6.0) on one of the lines should be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(point2D), (L"Point (4.5, -3.0) on one of the lines should be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(point3D), (L"Point (-4.5, -3.0) on one of the lines should be inside of the " + lvdDescription).c_str());
		}

		TEST_METHOD(LV_AddLine)
		{
			// Test the LineVolume<float> AddLine() function.
			LVf lineVolumeF({ Linef(Vector2f(-4.5f, -3.0f), Vector2f(0.0f, 6.0f)) });
			std::wstring lvfDescription(L"LineVolume<float> with the following line:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }");

			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(0.0f, 0.0f)), (L"1 Line: Point (0.0f, 0.0f) should be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(-4.0f, 0.0f)), (L"1 Line: Point (-4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(4.0f, 0.0f)), (L"1 Line: Point (4.0f, 0.0f) should be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(0.0f, -4.0f)), (L"1 Line: Point (0.0f, -4.0f) should be inside of the " + lvfDescription).c_str());



			lineVolumeF.AddLine(Linef(Vector2f(0.0f, 6.0f), Vector2f(4.5f, -3.0f)));
			lvfDescription = std::wstring(L"LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }");

			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(0.0f, 0.0f)), (L"2 Lines: Point (0.0f, 0.0f) should be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(-4.0f, 0.0f)), (L"2 Lines: Point (-4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(4.0f, 0.0f)), (L"2 Lines: Point (4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(0.0f, -4.0f)), (L"2 Lines: Point (0.0f, -4.0f) should be inside of the " + lvfDescription).c_str());



			lineVolumeF.AddLine(Linef(Vector2f(4.5f, -3.0f), Vector2f(-4.5f, -3.0f)));
			lvfDescription = std::wstring(L"LineVolume<float> with the following lines:\n" \
				"1] { (-4.5f, -3.0f), (0.0f, 6.0f) }\n" \
				"2] { (0.0f, 6.0f), (4.5f, -3.0f) }\n" \
				"3] { (4.5f, -3.0f), (-4.5f, -3.0f) }");

			Assert::IsTrue(lineVolumeF.IsInside(Vector2f(0.0f, 0.0f)), (L"3 Lines: Point (0.0f, 0.0f) should be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(-4.0f, 0.0f)), (L"3 Lines: Point (-4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(4.0f, 0.0f)), (L"3 Lines: Point (4.0f, 0.0f) should not be inside of the " + lvfDescription).c_str());
			Assert::IsFalse(lineVolumeF.IsInside(Vector2f(0.0f, -4.0f)), (L"3 Lines: Point (0.0f, -4.0f) should be inside of the " + lvfDescription).c_str());



			// Test the LineVolume<double> AddLine() function.
			LVd lineVolumeD({ Lined(Vector2d(-4.5, -3.0), Vector2d(0.0, 6.0)) });
			std::wstring lvdDescription(L"LineVolume<double> with the following line:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }");

			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(0.0, 0.0)), (L"1 Line: Point (0.0, 0.0) should be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(-4.0, 0.0)), (L"1 Line: Point (-4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(4.0, 0.0)), (L"1 Line: Point (4.0, 0.0) should be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(0.0, -4.0)), (L"1 Line: Point (0.0, -4.0) should be inside of the " + lvdDescription).c_str());



			lineVolumeD.AddLine(Lined(Vector2d(0.0, 6.0), Vector2d(4.5, -3.0)));
			lvdDescription = std::wstring(L"LineVolume<double> with the following line:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }\n" \
				"2] { (0.0, 6.0), (4.5, -3.0) }");

			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(0.0, 0.0)), (L"2 Lines: Point (0.0, 0.0) should be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(-4.0, 0.0)), (L"2 Lines: Point (-4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(4.0, 0.0)), (L"2 Lines: Point (4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(0.0, -4.0)), (L"2 Lines: Point (0.0, -4.0) should be inside of the " + lvdDescription).c_str());



			lineVolumeD.AddLine(Lined(Vector2d(4.5, -3.0), Vector2d(-4.5, -3.0)));
			lvdDescription = std::wstring(L"LineVolume<double> with the following line:\n" \
				"1] { (-4.5, -3.0), (0.0, 6.0) }\n" \
				"2] { (0.0, 6.0), (4.5, -3.0) }\n" \
				"3] { (4.5, -3.0), (-4.5, -3.0) }");

			Assert::IsTrue(lineVolumeD.IsInside(Vector2d(0.0, 0.0)), (L"3 Lines: Point (0.0, 0.0) should be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(-4.0, 0.0)), (L"3 Lines: Point (-4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(4.0, 0.0)), (L"3 Lines: Point (4.0, 0.0) should not be inside of the " + lvdDescription).c_str());
			Assert::IsFalse(lineVolumeD.IsInside(Vector2d(0.0, -4.0)), (L"3 Lines: Point (0.0, -4.0) should be inside of the " + lvdDescription).c_str());
		}
	};
}