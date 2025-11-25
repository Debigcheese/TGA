#include "stdafx.h"
#include "CppUnitTest.h"

#include "Shared/Utility.hpp"
#include "Student Code/PlaneVolume.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Planef = CommonUtilities::Plane<float>;
using Planed = CommonUtilities::Plane<double>;
using PVf = CommonUtilities::PlaneVolume<float>;
using PVd = CommonUtilities::PlaneVolume<double>;
using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;


namespace Assignment3LinesAndPlanes
{
	TEST_CLASS(PlaneVolumeTests)
	{
	public:

		TEST_METHOD(PV_Constructor)
		{
			// Test the PlaneVolume<float> constructor with passing in one to six planes.
			Planef xPlaneF(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Planef xNegPlaneF(Vector3f(-5.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
			Planef yPlaneF(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yNegPlaneF(Vector3f(0.0f, -5.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
			Planef zPlaneF(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef zNegPlaneF(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, -1.0f));

			Vector3f pointOF(0.0f, 0.0f, 0.0f);
			Vector3f pointXF(6.0f, 0.0f, 0.0f);
			Vector3f pointXNegF(-6.0f, 0.0f, 0.0f);
			Vector3f pointYF(0.0f, 6.0f, 0.0f);
			Vector3f pointYNegF(0.0f, -6.0f, 0.0f);
			Vector3f pointZF(0.0f, 0.0f, 6.0f);
			Vector3f pointZNegF(0.0f, 0.0f, -6.0f);

			PVf planeVolumeXF({ xPlaneF });
			std::wstring pvfDescription(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n");
			Assert::IsTrue(planeVolumeXF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeXF.IsInside(pointXF), (L"Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());



			PVf planeVolumeXNegF({ xNegPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n");
			Assert::IsTrue(planeVolumeXNegF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeXNegF.IsInside(pointXNegF), (L"Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());



			PVf planeVolumeYF({ yPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n");
			Assert::IsTrue(planeVolumeYF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeYF.IsInside(pointYF), (L"Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());



			PVf planeVolumeYNegF({ yNegPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n");
			Assert::IsTrue(planeVolumeYNegF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeYNegF.IsInside(pointYNegF), (L"Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());



			PVf planeVolumeZF({ zPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }\n");
			Assert::IsTrue(planeVolumeZF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeZF.IsInside(pointZF), (L"Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());



			PVf planeVolumeZNegF({ zNegPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"{ (0.0f, 0.0f, -5.0f), (0.0f, 0.0f, -1.0f) }\n");
			Assert::IsTrue(planeVolumeZNegF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeZNegF.IsInside(pointZNegF), (L"Point (0.0f, 0.0f, -6.0f) should not be inside of the " + pvfDescription).c_str());
			


			PVf planeVolume6F({ xPlaneF, xNegPlaneF, yPlaneF, yNegPlaneF, zPlaneF, zNegPlaneF });
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n" \
				"5] { (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }\n" \
				"6] { (0.0f, 0.0f, -5.0f), (0.0f, 0.0f, -1.0f) }");

			Assert::IsTrue(planeVolume6F.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointXF), (L"Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointXNegF), (L"Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointYF), (L"Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointYNegF), (L"Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointZF), (L"Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolume6F.IsInside(pointZNegF), (L"Point (0.0f, 0.0f, -6.0f) should not be inside of the " + pvfDescription).c_str());

			// Test the PlaneVolume<double> constructor with passing in one to six planes.
			Planed xPlaneD(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Planed xNegPlaneD(Vector3d(-5.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
			Planed yPlaneD(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yNegPlaneD(Vector3d(0.0, -5.0, 0.0), Vector3d(0.0, -1.0, 0.0));
			Planed zPlaneD(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0));
			Planed zNegPlaneD(Vector3d(0.0, 0.0, -5.0), Vector3d(0.0, 0.0, -1.0));

			Vector3d pointOD(0.0, 0.0, 0.0);
			Vector3d pointXD(6.0, 0.0, 0.0);
			Vector3d pointXNegD(-6.0, 0.0, 0.0);
			Vector3d pointYD(0.0, 6.0, 0.0);
			Vector3d pointYNegD(0.0, -6.0, 0.0);
			Vector3d pointZD(0.0, 0.0, 6.0);
			Vector3d pointZNegD(0.0, 0.0, -6.0);

			PVd planeVolumeXD({ xPlaneD });
			std::wstring pvdDescription(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n");
			Assert::IsTrue(planeVolumeXD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeXD.IsInside(pointXD), (L"Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolumeXNegD({ xNegPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n");
			Assert::IsTrue(planeVolumeXNegD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeXNegD.IsInside(pointXNegD), (L"Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolumeYD({ yPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n");
			Assert::IsTrue(planeVolumeYD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeYD.IsInside(pointYD), (L"Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolumeYNegD({ yNegPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n");
			Assert::IsTrue(planeVolumeYNegD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeYNegD.IsInside(pointYNegD), (L"Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolumeZD({ zPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }\n");
			Assert::IsTrue(planeVolumeZD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeZD.IsInside(pointZD), (L"Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolumeZNegD({ zNegPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"{ (0.0, 0.0, -5.0), (0.0, 0.0, -1.0) }\n");
			Assert::IsTrue(planeVolumeZNegD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeZNegD.IsInside(pointZNegD), (L"Point (0.0, 0.0, -6.0) should not be inside of the " + pvdDescription).c_str());



			PVd planeVolume6D({ xPlaneD, xNegPlaneD, yPlaneD, yNegPlaneD, zPlaneD, zNegPlaneD });
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n" \
				"5] { (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }\n" \
				"6] { (0.0, 0.0, -5.0), (0.0, 0.0, -1.0) }");

			Assert::IsTrue(planeVolume6D.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointXD), (L"Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointXNegD), (L"Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointYD), (L"Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointYNegD), (L"Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointZD), (L"Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolume6D.IsInside(pointZNegD), (L"Point (0.0, 0.0, -6.0) should not be inside of the " + pvdDescription).c_str());
		}

		TEST_METHOD(PV_IsInside)
		{
			// Test the PlaneVolume<float> IsInside() function.
			Planef xPlaneF(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Planef xNegPlaneF(Vector3f(-5.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
			Planef yPlaneF(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yNegPlaneF(Vector3f(0.0f, -5.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
			Planef zPlaneF(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef zNegPlaneF(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, -1.0f));

			PVf planeVolumeF({ xPlaneF, xNegPlaneF, yPlaneF, yNegPlaneF, zPlaneF, zNegPlaneF });
			std::wstring pvfDescription(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n" \
				"5] { (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }\n" \
				"6] { (0.0f, 0.0f, -5.0f), (0.0f, 0.0f, -1.0f) }");

			Vector3f pointOF(0.0f, 0.0f, 0.0f);
			Vector3f pointXF(6.0f, 0.0f, 0.0f);
			Vector3f pointXNegF(-6.0f, 0.0f, 0.0f);
			Vector3f pointYF(0.0f, 6.0f, 0.0f);
			Vector3f pointYNegF(0.0f, -6.0f, 0.0f);
			Vector3f pointZF(0.0f, 0.0f, 6.0f);
			Vector3f pointZNegF(0.0f, 0.0f, -6.0f);

			Assert::IsTrue(planeVolumeF.IsInside(pointOF), (L"Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYF), (L"Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYNegF), (L"Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointZF), (L"Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointZNegF), (L"Point (0.0f, 0.0f, -6.0f) should not be inside of the " + pvfDescription).c_str());

			// Test the PlaneVolume<double> IsInside() function.
			Planed xPlaneD(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Planed xNegPlaneD(Vector3d(-5.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
			Planed yPlaneD(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yNegPlaneD(Vector3d(0.0, -5.0, 0.0), Vector3d(0.0, -1.0, 0.0));
			Planed zPlaneD(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0));
			Planed zNegPlaneD(Vector3d(0.0, 0.0, -5.0), Vector3d(0.0, 0.0, -1.0));

			PVd planeVolumeD({ xPlaneD, xNegPlaneD, yPlaneD, yNegPlaneD, zPlaneD, zNegPlaneD });
			std::wstring pvdDescription(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n" \
				"5] { (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }\n" \
				"6] { (0.0, 0.0, -5.0), (0.0, 0.0, -1.0) }");

			Vector3d pointOD(0.0, 0.0, 0.0);
			Vector3d pointXD(6.0, 0.0, 0.0);
			Vector3d pointXNegD(-6.0, 0.0, 0.0);
			Vector3d pointYD(0.0, 6.0, 0.0);
			Vector3d pointYNegD(0.0, -6.0, 0.0);
			Vector3d pointZD(0.0, 0.0, 6.0);
			Vector3d pointZNegD(0.0, 0.0, -6.0);

			Assert::IsTrue(planeVolumeD.IsInside(pointOD), (L"Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYD), (L"Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYNegD), (L"Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointZD), (L"Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointZNegD), (L"Point (0.0, 0.0, -6.0) should not be inside of the " + pvdDescription).c_str());
		}

		TEST_METHOD(PV_On_Plane)
		{
			// Test the PlaneVolume<float> IsInside() function with points that are on the different planes.
			Planef xPlaneF(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Planef xNegPlaneF(Vector3f(-5.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
			Planef yPlaneF(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yNegPlaneF(Vector3f(0.0f, -5.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
			Planef zPlaneF(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef zNegPlaneF(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, -1.0f));
			
			PVf planeVolumeF({ xPlaneF, xNegPlaneF, yPlaneF, yNegPlaneF, zPlaneF, zNegPlaneF });
			std::wstring pvfDescription(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n" \
				"5] { (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }\n" \
				"6] { (0.0f, 0.0f, -5.0f), (0.0f, 0.0f, -1.0f) }");

			Vector3f pointXF(5.0f, 0.0f, 0.0f);
			Vector3f pointXNegF(-5.0f, 0.0f, 0.0f);
			Vector3f pointYF(0.0f, 5.0f, 0.0f);
			Vector3f pointYNegF(0.0f, -5.0f, 0.0f);
			Vector3f pointZF(0.0f, 0.0f, 5.0f);
			Vector3f pointZNegF(0.0f, 0.0f, -5.0f);

			Assert::IsTrue(planeVolumeF.IsInside(pointXF), (L"Point (5.0f, 0.0f, 0.0f) on one of the planes should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointXNegF), (L"Point (-5.0f, 0.0f, 0.0f) on one of the planes should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYF), (L"Point (0.0f, 5.0f, 0.0f) on one of the planes should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYNegF), (L"Point (0.0f, -5.0f, 0.0f) on one of the planes should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZF), (L"Point (0.0f, 0.0f, 5.0f) on one of the planes should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"Point (0.0f, 0.0f, -5.0f) on one of the planes should be inside of the " + pvfDescription).c_str());

			// Test the PlaneVolume<double> IsInside() function with points that are on the different planes.
			Planed xPlaneD(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Planed xNegPlaneD(Vector3d(-5.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
			Planed yPlaneD(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yNegPlaneD(Vector3d(0.0, -5.0, 0.0), Vector3d(0.0, -1.0, 0.0));
			Planed zPlaneD(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0));
			Planed zNegPlaneD(Vector3d(0.0, 0.0, -5.0), Vector3d(0.0, 0.0, -1.0));
			
			PVd planeVolumeD({ xPlaneD, xNegPlaneD, yPlaneD, yNegPlaneD, zPlaneD, zNegPlaneD });
			std::wstring pvdDescription(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n" \
				"5] { (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }\n" \
				"6] { (0.0, 0.0, -5.0), (0.0, 0.0, -1.0) }");

			Vector3d pointXD(5.0, 0.0, 0.0);
			Vector3d pointXNegD(-5.0, 0.0, 0.0);
			Vector3d pointYD(0.0, 5.0, 0.0);
			Vector3d pointYNegD(0.0, -5.0, 0.0);
			Vector3d pointZD(0.0, 0.0, 5.0);
			Vector3d pointZNegD(0.0, 0.0, -5.0);

			Assert::IsTrue(planeVolumeD.IsInside(pointXD), (L"Point (5.0, 0.0, 0.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointXNegD), (L"Point (-5.0, 0.0, 0.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYD), (L"Point (0.0, 5.0, 0.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYNegD), (L"Point (0.0, -5.0, 0.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZD), (L"Point (0.0, 0.0, 5.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"Point (0.0, 0.0, -5.0) on one of the planes should be inside of  the " + pvdDescription).c_str());
		}

		TEST_METHOD(PV_AddPlane)
		{
			// Test the PlaneVolume<float> AddPlane() function.
			PVf planeVolumeF({ Planef(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f)) });
			std::wstring pvfDescription(L"PlaneVolume<float> with the following plane (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }");

			Vector3f pointF(0.0f, 0.0f, 0.0f);
			Vector3f pointXF(6.0f, 0.0f, 0.0f);
			Vector3f pointXNegF(-6.0f, 0.0f, 0.0f);
			Vector3f pointYF(0.0f, 6.0f, 0.0f);
			Vector3f pointYNegF(0.0f, -6.0f, 0.0f);
			Vector3f pointZF(0.0f, 0.0f, 6.0f);
			Vector3f pointZNegF(0.0f, 0.0f, -6.0f);

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"1 Plane: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"1 Plane: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointXNegF), (L"1 Plane: Point (-6.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYF), (L"1 Plane: Point (0.0f, 6.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYNegF), (L"1 Plane: Point (0.0f, -6.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZF), (L"1 Plane: Point (0.0f, 0.0f, 6.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"1 Plane: Point (0.0f, 0.0f, -6.0f) should be inside of the " + pvfDescription).c_str());



			planeVolumeF.AddPlane(Planef(Vector3f(-5.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f)));
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }");

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"2 Planes: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"2 Planes: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"2 Planes: Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYF), (L"2 Planes: Point (0.0f, 6.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYNegF), (L"2 Planes: Point (0.0f, -6.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZF), (L"2 Planes: Point (0.0f, 0.0f, 6.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"2 Planes: Point (0.0f, 0.0f, -6.0f) should be inside of the " + pvfDescription).c_str());



			planeVolumeF.AddPlane(Planef(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f)));
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }");

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"3 Planes: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"3 Planes: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"3 Planes: Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYF), (L"3 Planes: Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointYNegF), (L"3 Planes: Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZF), (L"3 Planes: Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"3 Planes: Point (0.0f, 0.0f, -6.0f) should not be inside of the " + pvfDescription).c_str());



			planeVolumeF.AddPlane(Planef(Vector3f(0.0f, -5.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f)));
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }");

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"4 Planes: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"4 Planes: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"4 Planes: Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYF), (L"4 Planes: Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYNegF), (L"4 Planes: Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZF), (L"4 Planes: Point (0.0f, 0.0f, 6.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"4 Planes: Point (0.0f, 0.0f, -6.0f) should be inside of the " + pvfDescription).c_str());



			planeVolumeF.AddPlane(Planef(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f)));
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n" \
				"5] { (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }");

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"5 Planes: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"5 Planes: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"5 Planes: Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYF), (L"5 Planes: Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYNegF), (L"5 Planes: Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointZF), (L"5 Planes: Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsTrue(planeVolumeF.IsInside(pointZNegF), (L"5 Planes: Point (0.0f, 0.0f, -6.0f) should be inside of the " + pvfDescription).c_str());



			planeVolumeF.AddPlane(Planef(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, -1.0f)));
			pvfDescription = std::wstring(L"PlaneVolume<float> with the following planes (point and normal):\n" \
				"1] { (5.0f, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f) }\n" \
				"2] { (-5.0f, 0.0f, 0.0f), (-1.0f, 0.0f, 0.0f) }\n" \
				"3] { (0.0f, 5.0f, 0.0f), (0.0f, 1.0f, 0.0f) }\n" \
				"4] { (0.0f, -5.0f, 0.0f), (0.0f, -1.0f, 0.0f) }\n" \
				"5] { (0.0f, 0.0f, 5.0f), (0.0f, 0.0f, 1.0f) }\n" \
				"6] { (0.0f, 0.0f, -5.0f), (0.0f, 0.0f, -1.0f) }");

			Assert::IsTrue(planeVolumeF.IsInside(pointF), (L"6 Planes: Point (0.0f, 0.0f, 0.0f) should be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXF), (L"6 Planes: Point (6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointXNegF), (L"6 Planes: Point (-6.0f, 0.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYF), (L"6 Planes: Point (0.0f, 6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointYNegF), (L"6 Planes: Point (0.0f, -6.0f, 0.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointZF), (L"6 Planes: Point (0.0f, 0.0f, 6.0f) should not be inside of the " + pvfDescription).c_str());
			Assert::IsFalse(planeVolumeF.IsInside(pointZNegF), (L"6 Planes: Point (0.0f, 0.0f, -6.0f) should not be inside of the " + pvfDescription).c_str());



			// Test the PlaneVolume<double> AddPlane() function.
			PVd planeVolumeD({ Planed(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0)) });
			std::wstring pvdDescription(L"PlaneVolume<double> with the following plane (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }");

			Vector3d pointD(0.0, 0.0, 0.0);
			Vector3d pointXD(6.0, 0.0, 0.0);
			Vector3d pointXNegD(-6.0, 0.0, 0.0);
			Vector3d pointYD(0.0, 6.0, 0.0);
			Vector3d pointYNegD(0.0, -6.0, 0.0);
			Vector3d pointZD(0.0, 0.0, 6.0);
			Vector3d pointZNegD(0.0, 0.0, -6.0);

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"1 Plane: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"1 Plane: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointXNegD), (L"1 Plane: Point (-6.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYD), (L"1 Plane: Point (0.0, 6.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYNegD), (L"1 Plane: Point (0.0, -6.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZD), (L"1 Plane: Point (0.0, 0.0, 6.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"1 Plane: Point (0.0, 0.0, -6.0) should be inside of the " + pvdDescription).c_str());



			planeVolumeD.AddPlane(Planed(Vector3d(-5.0, 0.0, 0.0), Vector3d(-1.0, 0.0, 0.0)));
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }");

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"2 Planes: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"2 Planes: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"2 Planes: Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYD), (L"2 Planes: Point (0.0, 6.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYNegD), (L"2 Planes: Point (0.0, -6.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZD), (L"2 Planes: Point (0.0, 0.0, 6.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"2 Planes: Point (0.0, 0.0, -6.0) should be inside of the " + pvdDescription).c_str());



			planeVolumeD.AddPlane(Planed(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0)));
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }");

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"3 Planes: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"3 Planes: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"3 Planes: Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYD), (L"3 Planes: Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointYNegD), (L"3 Planes: Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZD), (L"3 Planes: Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"3 Planes: Point (0.0, 0.0, -6.0) should not be inside of the " + pvdDescription).c_str());



			planeVolumeD.AddPlane(Planed(Vector3d(0.0, -5.0, 0.0), Vector3d(0.0, -1.0, 0.0)));
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }");

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"4 Planes: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"4 Planes: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"4 Planes: Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYD), (L"4 Planes: Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYNegD), (L"4 Planes: Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZD), (L"4 Planes: Point (0.0, 0.0, 6.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"4 Planes: Point (0.0, 0.0, -6.0) should be inside of the " + pvdDescription).c_str());

			
			planeVolumeD.AddPlane(Planed(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0)));
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n" \
				"5] { (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }");

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"5 Planes: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"5 Planes: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"5 Planes: Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYD), (L"5 Planes: Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYNegD), (L"5 Planes: Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointZD), (L"5 Planes: Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsTrue(planeVolumeD.IsInside(pointZNegD), (L"5 Planes: Point (0.0, 0.0, -6.0) should be inside of the " + pvdDescription).c_str());



			planeVolumeD.AddPlane(Planed(Vector3d(0.0, 0.0, -5.0), Vector3d(0.0, 0.0, -1.0)));
			pvdDescription = std::wstring(L"PlaneVolume<double> with the following planes (point and normal):\n" \
				"1] { (5.0, 0.0, 0.0), (1.0, 0.0, 0.0) }\n" \
				"2] { (-5.0, 0.0, 0.0), (-1.0, 0.0, 0.0) }\n" \
				"3] { (0.0, 5.0, 0.0), (0.0, 1.0, 0.0) }\n" \
				"4] { (0.0, -5.0, 0.0), (0.0, -1.0, 0.0) }\n" \
				"5] { (0.0, 0.0, 5.0), (0.0, 0.0, 1.0) }\n" \
				"6] { (0.0, 0.0, -5.0), (0.0, 0.0, -1.0) }");

			Assert::IsTrue(planeVolumeD.IsInside(pointD), (L"6 Planes: Point (0.0, 0.0, 0.0) should be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXD), (L"6 Planes: Point (6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointXNegD), (L"6 Planes: Point (-6.0, 0.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYD), (L"6 Planes: Point (0.0, 6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointYNegD), (L"6 Planes: Point (0.0, -6.0, 0.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointZD), (L"6 Planes: Point (0.0, 0.0, 6.0) should not be inside of the " + pvdDescription).c_str());
			Assert::IsFalse(planeVolumeD.IsInside(pointZNegD), (L"6 Planes: Point (0.0, 0.0, -6.0) should not be inside of the " + pvdDescription).c_str());
		}
	};
}