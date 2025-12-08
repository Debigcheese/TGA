#include "stdafx.h"
#include "CppUnitTest.h"
#include "Shared/Utility.h"

#include "Student Code/CommonUtilities/Plane.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Planef = CommonUtilities::Plane<float>;
using Planed = CommonUtilities::Plane<double>;
using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;

namespace Assignment3LinesAndPlanes
{
	TEST_CLASS(PlaneTests)
	{
	public:
		TEST_METHOD(P_IsInside)
		{
			// Testing points with 6 different Plane<float> (normals along x, y and z axes, positive and negative).
			Planef xPlaneF(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Planef xNegPlaneF(Vector3f(-5.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
			Planef yPlaneF(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yNegPlaneF(Vector3f(0.0f, -5.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
			Planef zPlaneF(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef zNegPlaneF(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, -1.0f));

			Vector3f pointF(0.0f, 0.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointF),
			               L"Point (0.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointXF(6.0f, 0.0f, 0.0f);
			Assert::IsFalse(xPlaneF.IsInside(pointXF),
			                L"Point (6.0f, 0.0f, 0.0f) should not be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointXF),
			               L"Point (6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointXF),
			               L"Point (6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointXF),
			               L"Point (6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointXF),
			               L"Point (6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointXF),
			               L"Point (6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointXNegF(-6.0f, 0.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointXNegF),
			               L"Point (-6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsFalse(xNegPlaneF.IsInside(pointXNegF),
			                L"Point (-6.0f, 0.0f, 0.0f) should not be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointXNegF),
			               L"Point (-6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointXNegF),
			               L"Point (-6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointXNegF),
			               L"Point (-6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointXNegF),
			               L"Point (-6.0f, 0.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointYF(0.0f, 6.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 6.0f, 0.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 6.0f, 0.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsFalse(yPlaneF.IsInside(pointYF),
			                L"Point (0.0f, 6.0f, 0.0f) should not be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointYNegF(0.0f, -6.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsFalse(yNegPlaneF.IsInside(pointYNegF),
			                L"Point (0.0f, -6.0f, 0.0f) should not be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointZF(0.0f, 0.0f, 6.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 6.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 6.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 6.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 6.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsFalse(zPlaneF.IsInside(pointZF),
			                L"Point (0.0f, 0.0f, 6.0f) should not be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 6.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			Vector3f pointZNegF(0.0f, 0.0f, -6.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -6.0f) should be inside of Plane<float> with the normal (1.0f, 0.0f, 0.0f) and that contains the point (5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -6.0f) should be inside of Plane<float> with the normal (-1.0f, 0.0f, 0.0f) and that contains the point (-5.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -6.0f) should be inside of Plane<float> with the normal (0.0f, 1.0f, 0.0f) and that contains the point (0.0f, 5.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -6.0f) should be inside of Plane<float> with the normal (0.0f, -1.0f, 0.0f) and that contains the point (0.0f, -5.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -6.0f) should be inside of Plane<float> with the normal (0.0f, 0.0f, 1.0f) and that contains the point (0.0f, 0.0f, 5.0f).");
			Assert::IsFalse(zNegPlaneF.IsInside(pointZNegF),
			                L"Point (0.0f, 0.0f, -6.0f) should not be inside of Plane<float> with the normal (0.0f, 0.0f, -1.0f) and that contains the point (0.0f, 0.0f, -5.0f).");

			// Testing points with 6 different Plane<double> (normals along x, y and z axes, positive and negative).
			Planed xPlaneD(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Planed xNegPlaneD(Vector3d(-5.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
			Planed yPlaneD(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yNegPlaneD(Vector3d(0.0, -5.0, 0.0), Vector3d(0.0, -1.0, 0.0));
			Planed zPlaneD(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0));
			Planed zNegPlaneD(Vector3d(0.0, 0.0, -5.0), Vector3d(0.0, 0.0, -1.0));

			Vector3d pointD(0.0, 0.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointD),
			               L"Point (0.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointXD(6.0, 0.0, 0.0);
			Assert::IsFalse(xPlaneD.IsInside(pointXD),
			                L"Point (6.0, 0.0, 0.0) should not be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointXD),
			               L"Point (6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointXD),
			               L"Point (6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointXD),
			               L"Point (6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointXD),
			               L"Point (6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointXD),
			               L"Point (6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointXNegD(-6.0, 0.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointXNegD),
			               L"Point (-6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsFalse(xNegPlaneD.IsInside(pointXNegD),
			                L"Point (-6.0, 0.0, 0.0) should not be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointXNegD),
			               L"Point (-6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointXNegD),
			               L"Point (-6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointXNegD),
			               L"Point (-6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointXNegD),
			               L"Point (-6.0, 0.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointYD(0.0, 6.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointYD),
			               L"Point (0.0, 6.0, 0.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 6.0, 0.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsFalse(yPlaneD.IsInside(pointYD),
			                L"Point (0.0, 6.0, 0.0) should not be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 6.0, 0.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointYD),
			               L"Point (0.0, 6.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 6.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointYNegD(0.0, -6.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -6.0, 0.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -6.0, 0.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -6.0, 0.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsFalse(yNegPlaneD.IsInside(pointYNegD),
			                L"Point (0.0, -6.0, 0.0) should not be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -6.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -6.0, 0.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointZD(0.0, 0.0, 6.0);
			Assert::IsTrue(xPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 6.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 6.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 6.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 6.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsFalse(zPlaneD.IsInside(pointZD),
			                L"Point (0.0, 0.0, 6.0) should not be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 6.0) should be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");

			Vector3d pointZNegD(0.0, 0.0, -6.0);
			Assert::IsTrue(xPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -6.0) should be inside of Plane<double> with the normal (1.0, 0.0, 0.0) and that contains the point (5.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -6.0) should be inside of Plane<double> with the normal (-1.0, 0.0, 0.0) and that contains the point (-5.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -6.0) should be inside of Plane<double> with the normal (0.0, 1.0, 0.0) and that contains the point (0.0, 5.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -6.0) should be inside of Plane<double> with the normal (0.0, -1.0, 0.0) and that contains the point (0.0, -5.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -6.0) should be inside of Plane<double> with the normal (0.0, 0.0, 1.0) and that contains the point (0.0, 0.0, 5.0).");
			Assert::IsFalse(zNegPlaneD.IsInside(pointZNegD),
			                L"Point (0.0, 0.0, -6.0) should not be inside of Plane<double> with the normal (0.0, 0.0, -1.0) and that contains the point (0.0, 0.0, -5.0).");
		}

		TEST_METHOD(P_On_Plane)
		{
			// Testing points on plane with 6 different Plane<float> (normals along x, y and z axes, positive and negative) in origo.
			Planef xPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Planef xNegPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
			Planef yPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yNegPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
			Planef zPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef zNegPlaneF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f));

			Vector3f pointXF(5.0f, 0.0f, 0.0f);
			Assert::IsFalse(xPlaneF.IsInside(pointXF),
			                L"Point (5.0f, 0.0f, 0.0f) should not be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointXF),
			               L"Point (5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointXF),
			               L"Point (5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointXF),
			               L"Point (5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointXF),
			               L"Point (5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointXF),
			               L"Point (5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			Vector3f pointXNegF(-5.0f, 0.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointXNegF),
			               L"Point (-5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsFalse(xNegPlaneF.IsInside(pointXNegF),
			                L"Point (-5.0f, 0.0f, 0.0f) should not be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointXNegF),
			               L"Point (-5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointXNegF),
			               L"Point (-5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointXNegF),
			               L"Point (-5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointXNegF),
			               L"Point (-5.0f, 0.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			Vector3f pointYF(0.0f, 5.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 5.0f, 0.0f) should be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 5.0f, 0.0f) should be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsFalse(yPlaneF.IsInside(pointYF),
			                L"Point (0.0f, 5.0f, 0.0f) should not be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 5.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 5.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointYF),
			               L"Point (0.0f, 5.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			Vector3f pointYNegF(0.0f, -5.0f, 0.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsFalse(yNegPlaneF.IsInside(pointYNegF),
			                L"Point (0.0f, -6.0f, 0.0f) should not be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointYNegF),
			               L"Point (0.0f, -6.0f, 0.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			Vector3f pointZF(0.0f, 0.0f, 5.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 5.0f) should be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 5.0f) should be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 5.0f) should be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 5.0f) should be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsFalse(zPlaneF.IsInside(pointZF),
			                L"Point (0.0f, 0.0f, 5.0f) should not be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsTrue(zNegPlaneF.IsInside(pointZF),
			               L"Point (0.0f, 0.0f, 5.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			Vector3f pointZNegF(0.0f, 0.0f, -5.0f);
			Assert::IsTrue(xPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -5.0f) should be inside of Plane<float> in origo with the normal (1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(xNegPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -5.0f) should be inside of Plane<float> in origo with the normal (-1.0f, 0.0f, 0.0f).");
			Assert::IsTrue(yPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -5.0f) should be inside of Plane<float> in origo with the normal (0.0f, 1.0f, 0.0f).");
			Assert::IsTrue(yNegPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -5.0f) should be inside of Plane<float> in origo with the normal (0.0f, -1.0f, 0.0f).");
			Assert::IsTrue(zPlaneF.IsInside(pointZNegF),
			               L"Point (0.0f, 0.0f, -5.0f) should be inside of Plane<float> in origo with the normal (0.0f, 0.0f, 1.0f).");
			Assert::IsFalse(zNegPlaneF.IsInside(pointZNegF),
			                L"Point (0.0f, 0.0f, -5.0f) should not be inside of Plane<float> in origo with the normal (0.0f, 0.0f, -1.0f).");

			// Testing points with 6 different Plane<double> (normals along x, y and z axes, positive and negative).
			Planed xPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Planed xNegPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
			Planed yPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yNegPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, -1.0, 0.0));
			Planed zPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0));
			Planed zNegPlaneD(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, -1.0));

			Vector3d pointXD(5.0, 0.0, 0.0);
			Assert::IsFalse(xPlaneD.IsInside(pointXD),
			                L"Point (5.0, 0.0, 0.0) should not be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointXD),
			               L"Point (5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointXD),
			               L"Point (5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointXD),
			               L"Point (5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointXD),
			               L"Point (5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointXD),
			               L"Point (5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");

			Vector3d pointXNegD(-5.0, 0.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointXNegD),
			               L"Point (-5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsFalse(xNegPlaneD.IsInside(pointXNegD),
			                L"Point (-5.0, 0.0, 0.0) should not be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointXNegD),
			               L"Point (-5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointXNegD),
			               L"Point (-5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointXNegD),
			               L"Point (-5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointXNegD),
			               L"Point (-5.0, 0.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");

			Vector3d pointYD(0.0, 5.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointYD),
			               L"Point (0.0, 5.0, 0.0) should be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 5.0, 0.0) should be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsFalse(yPlaneD.IsInside(pointYD),
			                L"Point (0.0, 5.0, 0.0) should not be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointYD),
			               L"Point (0.0, 5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointYD),
			               L"Point (0.0, 5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");

			Vector3d pointYNegD(0.0, -5.0, 0.0);
			Assert::IsTrue(xPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -5.0, 0.0) should be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -5.0, 0.0) should be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsFalse(yNegPlaneD.IsInside(pointYNegD),
			                L"Point (0.0, -5.0, 0.0) should not be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointYNegD),
			               L"Point (0.0, -5.0, 0.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");

			Vector3d pointZD(0.0, 0.0, 5.0);
			Assert::IsTrue(xPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 5.0) should be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 5.0) should be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 5.0) should be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 5.0) should be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsFalse(zPlaneD.IsInside(pointZD),
			                L"Point (0.0, 0.0, 5.0) should not be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsTrue(zNegPlaneD.IsInside(pointZD),
			               L"Point (0.0, 0.0, 5.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");

			Vector3d pointZNegD(0.0, 0.0, -5.0);
			Assert::IsTrue(xPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -5.0) should be inside of Plane<double> in origo with the normal (1.0, 0.0, 0.0).");
			Assert::IsTrue(xNegPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -5.0) should be inside of Plane<double> in origo with the normal (-1.0, 0.0, 0.0).");
			Assert::IsTrue(yPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -5.0) should be inside of Plane<double> in origo with the normal (0.0, 1.0, 0.0).");
			Assert::IsTrue(yNegPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -5.0) should be inside of Plane<double> in origo with the normal (0.0, -1.0, 0.0).");
			Assert::IsTrue(zPlaneD.IsInside(pointZNegD),
			               L"Point (0.0, 0.0, -5.0) should be inside of Plane<double> in origo with the normal (0.0, 0.0, 1.0).");
			Assert::IsFalse(zNegPlaneD.IsInside(pointZNegD),
			                L"Point (0.0, 0.0, -5.0) should not be inside of Plane<double> in origo with the normal (0.0, 0.0, -1.0).");
		}

		TEST_METHOD(P_Point_Normal)
		{
			// Testing the Plane<float> constructor and InitWithPointAndNormal() function with a bunch of random numbers for point and normal.
			for (int i = 0; i < 100; ++i)
			{
				float x = TestUtility::GetRandomFloat();
				float y = TestUtility::GetRandomFloat();
				float z = TestUtility::GetRandomFloat();

				float px = TestUtility::GetRandomFloat();
				float py = TestUtility::GetRandomFloat();
				float pz = TestUtility::GetRandomFloat();

				float nx = TestUtility::GetRandomFloat();
				float ny = TestUtility::GetRandomFloat();
				float nz = TestUtility::GetRandomFloat();


				float planeToLineX = x - px;
				float planeToLineY = y - py;
				float planeToLineZ = z - pz;

				float dotPlaneToLine = (planeToLineX * nx) + (planeToLineY * ny) + (planeToLineZ * nz);

				Vector3f point(x, y, z);
				Vector3f pointOnPlane(px, py, pz);
				Planef planeConstructor(Vector3f(px, py, pz), Vector3f(nx, ny, nz));
				Planef planeInit;
				planeInit.InitWithPointAndNormal(Vector3f(px, py, pz), Vector3f(nx, ny, nz));

				// Tolerance is 0.000001f, which is considered as being 0, that is: the point is in the plane which is "inside".
				Assert::AreEqual(dotPlaneToLine < 0.000001f, planeConstructor.IsInside(point),
				                 L"IsInside of Plane<float> is not calculated correctly when using the constructor that takes a point and a normal.");
				Assert::IsTrue(planeConstructor.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<float> is not considered 'inside' when using the constructor that takes a point and a normal.");

				Assert::AreEqual(dotPlaneToLine < 0.000001f, planeInit.IsInside(point),
				                 L"IsInside of Plane<float> is not calculated correctly when using the InitWithPointAndNormal() function.");
				Assert::IsTrue(planeInit.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<float> is not considered 'inside' when using the InitWithPointAndNormal() function.");
			}

			// Testing the Plane<double> constructor and InitWithPointAndNormal() function with a bunch of random numbers for point and normal.
			for (int i = 0; i < 100; ++i)
			{
				double x = TestUtility::GetRandomDouble();
				double y = TestUtility::GetRandomDouble();
				double z = TestUtility::GetRandomDouble();

				double px = TestUtility::GetRandomDouble();
				double py = TestUtility::GetRandomDouble();
				double pz = TestUtility::GetRandomDouble();

				double nx = TestUtility::GetRandomDouble();
				double ny = TestUtility::GetRandomDouble();
				double nz = TestUtility::GetRandomDouble();


				double planeToLineX = x - px;
				double planeToLineY = y - py;
				double planeToLineZ = z - pz;

				double dotPlaneToLine = (planeToLineX * nx) + (planeToLineY * ny) + (planeToLineZ * nz);

				Vector3d point(x, y, z);
				Vector3d pointOnPlane(px, py, pz);
				Planed plane(Vector3d(px, py, pz), Vector3d(nx, ny, nz));
				Planed planeInit;
				planeInit.InitWithPointAndNormal(Vector3d(px, py, pz), Vector3d(nx, ny, nz));

				// Tolerance is 0.000001, which is considered as being 0, that is: the point is in the plane which is "inside".
				Assert::AreEqual(dotPlaneToLine < 0.000001, plane.IsInside(point),
				                 L"IsInside of Plane<double> is not calculated correctly when using the constructor that takes a point and a normal.");
				Assert::IsTrue(plane.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<double> is not considered 'inside' when using the constructor that takes a point and a normal.");

				Assert::AreEqual(dotPlaneToLine < 0.000001, plane.IsInside(point),
				                 L"IsInside of Plane<double> is not calculated correctly when using the InitWithPointAndNormal() function.");
				Assert::IsTrue(plane.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<double> is not considered 'inside' when using the InitWithPointAndNormal() function.");
			}
		}

		TEST_METHOD(P_3_Points)
		{
			// Testing the Plane<float> constructor and InitWith3Points() function with a bunch of random numbers for point and normal.
			for (int i = 0; i < 100; ++i)
			{
				float x = TestUtility::GetRandomFloat();
				float y = TestUtility::GetRandomFloat();
				float z = TestUtility::GetRandomFloat();

				float p0x = TestUtility::GetRandomFloat();
				float p0y = TestUtility::GetRandomFloat();
				float p0z = TestUtility::GetRandomFloat();

				float p1x = TestUtility::GetRandomFloat();
				float p1y = TestUtility::GetRandomFloat();
				float p1z = TestUtility::GetRandomFloat();

				float p2x = TestUtility::GetRandomFloat();
				float p2y = TestUtility::GetRandomFloat();
				float p2z = TestUtility::GetRandomFloat();

				float vec1X = p1x - p0x;
				float vec1Y = p1y - p0y;
				float vec1Z = p1z - p0z;

				float vec2X = p2x - p0x;
				float vec2Y = p2y - p0y;
				float vec2Z = p2z - p0z;

				float normalX = (vec1Y * vec2Z) - (vec1Z * vec2Y);
				float normalY = (vec1Z * vec2X) - (vec1X * vec2Z);
				float normalZ = (vec1X * vec2Y) - (vec1Y * vec2X);

				float planeToLineX = x - p0x;
				float planeToLineY = y - p0y;
				float planeToLineZ = z - p0z;

				float dotPlaneToLine = (planeToLineX * normalX) + (planeToLineY * normalY) + (planeToLineZ * normalZ);

				Vector3f point(x, y, z);
				Vector3f pointOnPlane(p0x, p0y, p0z);
				Planef planeConstructor(Vector3f(p0x, p0y, p0z), Vector3f(p1x, p1y, p1z), Vector3f(p2x, p2y, p2z));
				Planef planeInit;
				planeInit.InitWith3Points(Vector3f(p0x, p0y, p0z), Vector3f(p1x, p1y, p1z), Vector3f(p2x, p2y, p2z));

				// Tolerance is 0.000001f, which is considered as being 0, that is: the point is in the plane which is "inside".
				Assert::AreEqual(dotPlaneToLine < 0.000001f, planeConstructor.IsInside(point),
				                 L"IsInside of Plane<float> is not calculated correctly when using the constructor that takes a point and a normal.");
				Assert::IsTrue(planeConstructor.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<float> is not considered 'inside' when using the constructor that takes a point and a normal.");

				Assert::AreEqual(dotPlaneToLine < 0.000001f, planeInit.IsInside(point),
				                 L"IsInside of Plane<float> is not calculated correctly when using the InitWithPointAndNormal() function.");
				Assert::IsTrue(planeInit.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<float> is not considered 'inside' when using the InitWithPointAndNormal() function.");
			}

			// Testing the Plane<double> constructor and InitWith3Points() function with a bunch of random numbers for point and normal.
			for (int i = 0; i < 100; ++i)
			{
				double x = TestUtility::GetRandomDouble();
				double y = TestUtility::GetRandomDouble();
				double z = TestUtility::GetRandomDouble();

				double p0x = TestUtility::GetRandomDouble();
				double p0y = TestUtility::GetRandomDouble();
				double p0z = TestUtility::GetRandomDouble();

				double p1x = TestUtility::GetRandomDouble();
				double p1y = TestUtility::GetRandomDouble();
				double p1z = TestUtility::GetRandomDouble();

				double p2x = TestUtility::GetRandomDouble();
				double p2y = TestUtility::GetRandomDouble();
				double p2z = TestUtility::GetRandomDouble();

				double vec1X = p1x - p0x;
				double vec1Y = p1y - p0y;
				double vec1Z = p1z - p0z;

				double vec2X = p2x - p0x;
				double vec2Y = p2y - p0y;
				double vec2Z = p2z - p0z;

				double normalX = (vec1Y * vec2Z) - (vec1Z * vec2Y);
				double normalY = (vec1Z * vec2X) - (vec1X * vec2Z);
				double normalZ = (vec1X * vec2Y) - (vec1Y * vec2X);

				double planeToLineX = x - p0x;
				double planeToLineY = y - p0y;
				double planeToLineZ = z - p0z;

				double dotPlaneToLine = (planeToLineX * normalX) + (planeToLineY * normalY) + (planeToLineZ * normalZ);

				Vector3d point(x, y, z);
				Vector3d pointOnPlane(p0x, p0y, p0z);
				Planed planeConstructor(Vector3d(p0x, p0y, p0z), Vector3d(p1x, p1y, p1z), Vector3d(p2x, p2y, p2z));
				Planed planeInit;
				planeInit.InitWith3Points(Vector3d(p0x, p0y, p0z), Vector3d(p1x, p1y, p1z), Vector3d(p2x, p2y, p2z));

				// Tolerance is 0.000001, which is considered as being 0, that is: the point is in the plane which is "inside".
				Assert::AreEqual(dotPlaneToLine < 0.000001, planeConstructor.IsInside(point),
				                 L"IsInside of Plane<double> is not calculated correctly when using the constructor that takes a point and a normal.");
				Assert::IsTrue(planeConstructor.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<double> is not considered 'inside' when using the constructor that takes a point and a normal.");

				Assert::AreEqual(dotPlaneToLine < 0.000001, planeInit.IsInside(point),
				                 L"IsInside of Plane<double> is not calculated correctly when using the InitWithPointAndNormal() function.");
				Assert::IsTrue(planeInit.IsInside(pointOnPlane),
				               L"Point that lies on the Plane<double> is not considered 'inside' when using the InitWithPointAndNormal() function.");
			}
		}
	};
}
