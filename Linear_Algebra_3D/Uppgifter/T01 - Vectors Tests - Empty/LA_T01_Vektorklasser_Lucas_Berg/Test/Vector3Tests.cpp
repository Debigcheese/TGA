#include "stdafx.h"
#include "CppUnitTest.h"
#include <type_traits>
#include <cmath>

#include "Student Code/Vector3.h"

// Dummy TGA Vector3 for ToTga() tests
namespace Tga
{
	template <class T>
	class Vector3
	{
	public:
		T x, y, z;

		Vector3() : x(T(0)), y(T(0)), z(T(0))
		{
		}

		Vector3(const T aX, const T aY, const T aZ) : x(aX), y(aY), z(aZ)
		{
		}

		Vector3(const Vector3&) = default;
		Vector3& operator=(const Vector3&) = default;
	};
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;
using Vector3i = CommonUtilities::Vector3<int>;

using TgaVector3f = Tga::Vector3<float>;
using TgaVector3d = Tga::Vector3<double>;
using TgaVector3i = Tga::Vector3<int>;

namespace Vectors
{
	TEST_CLASS(Vector3Test)
	{
	public:
		TEST_METHOD(V3_Const)
		{
			const Vector3f v{1.f, 2.f, 3.f};
			const Vector3f u{-2.f, 0.5f, 1.f};

			auto len = v.Length();
			auto lensq = v.LengthSqr();
			auto dot = v.Dot(u);
			auto nrm = v.GetNormalized();
			auto tga = v.ToTga();
			auto castd = v.ToType<double>();
			(void)len;
			(void)lensq;
			(void)dot;
			(void)nrm;
			(void)tga;
			(void)castd;

			static_assert(std::is_copy_constructible_v<Vector3f>);
			static_assert(std::is_copy_assignable_v<Vector3f>);
			static_assert(std::is_trivially_destructible_v<Vector3f>);
		}

		TEST_METHOD(V3_Size)
		{
			Assert::AreEqual<size_t>(sizeof(Vector3f), sizeof(float) * size_t(3));
			Assert::AreEqual<size_t>(sizeof(Vector3d), sizeof(double) * size_t(3));
			Assert::AreEqual<size_t>(sizeof(Vector3i), sizeof(int) * size_t(3));
		}

		TEST_METHOD(V3_Default_Constructor)
		{
			Vector3f vf;
			Vector3i vi;
			Assert::AreEqual(0.f, vf.x);
			Assert::AreEqual(0.f, vf.y);
			Assert::AreEqual(0.f, vf.z);
			Assert::AreEqual(0, vi.x);
			Assert::AreEqual(0, vi.y);
			Assert::AreEqual(0, vi.z);
		}

		TEST_METHOD(V3_Constructor)
		{
			Vector3d v{1.0, -2.5, 3.25};
			Assert::AreEqual(1.0, v.x);
			Assert::AreEqual(-2.5, v.y);
			Assert::AreEqual(3.25, v.z);
		}

		TEST_METHOD(V3_Copy_Constructor)
		{
			const Vector3f a{3.f, -2.f, 5.f};
			Vector3f b{a};
			Assert::AreEqual(a.x, b.x);
			Assert::AreEqual(a.y, b.y);
			Assert::AreEqual(a.z, b.z);
		}

		TEST_METHOD(V3_Assignment)
		{
			const Vector3i a{1, 2, 3};
			Vector3i b;
			b = a;
			Assert::AreEqual(1, b.x);
			Assert::AreEqual(2, b.y);
			Assert::AreEqual(3, b.z);
		}

		TEST_METHOD(V3_ToTGAConvertion)
		{
			const Vector3f v{1.f, 2.f, 3.f};
			TgaVector3f t = v.ToTga();
			Assert::AreEqual(v.x, t.x);
			Assert::AreEqual(v.y, t.y);
			Assert::AreEqual(v.z, t.z);
		}

		TEST_METHOD(V3_ToOtherTypeConvertion)
		{
			const Vector3i vi{1, -2, 3};
			auto vf = vi.ToType<float>();
			Assert::AreEqual(1.f, vf.x);
			Assert::AreEqual(-2.f, vf.y);
			Assert::AreEqual(3.f, vf.z);

			const Vector3f vfx{1.5f, -2.25f, 3.75f};
			auto vd = vfx.ToType<double>();
			Assert::AreEqual(1.5, vd.x, ourToleranceD);
			Assert::AreEqual(-2.25, vd.y, ourToleranceD);
			Assert::AreEqual(3.75, vd.z, ourToleranceD);
		}

		TEST_METHOD(V3_Negation)
		{
			const Vector3d v{1.0, -2.0, 0.5};
			auto n = -v;
			Assert::AreEqual(-1.0, n.x);
			Assert::AreEqual(2.0, n.y);
			Assert::AreEqual(-0.5, n.z);
		}

		TEST_METHOD(V3_Addition)
		{
			const Vector3f a{1.f, 2.f, 3.f};
			const Vector3f b{-3.f, 5.f, 1.f};
			auto c = a + b;
			Assert::AreEqual(-2.f, c.x);
			Assert::AreEqual(7.f, c.y);
			Assert::AreEqual(4.f, c.z);
		}

		TEST_METHOD(V3_Subtraction)
		{
			const Vector3i a{5, 7, -2};
			const Vector3i b{3, -1, 4};
			auto c = a - b;
			Assert::AreEqual(2, c.x);
			Assert::AreEqual(8, c.y);
			Assert::AreEqual(-6, c.z);
		}

		TEST_METHOD(V3_Scalar_Multiplication)
		{
			const Vector3f v{1.f, -2.f, 3.f};
			auto a = v * 2.f;
			auto b = 2.f * v;
			Assert::AreEqual(2.f, a.x);
			Assert::AreEqual(2.f, b.x);
			Assert::AreEqual(-4.f, a.y);
			Assert::AreEqual(-4.f, b.y);
			Assert::AreEqual(6.f, a.z);
			Assert::AreEqual(6.f, b.z);
		}

		TEST_METHOD(V3_Length)
		{
			const Vector3f v{1.f, 2.f, 2.f}; // len = 3
			Assert::AreEqual(3.f, v.Length(), ourToleranceF);
		}

		TEST_METHOD(V3_LengthSqrOptimize)
		{
			const Vector3d v{2.0, -3.0, 4.0}; // len^2 = 4 + 9 + 16 = 29
			Assert::AreEqual(29.0, v.LengthSqr(), ourToleranceD);
			Assert::AreEqual(v.Length() * v.Length(), v.LengthSqr(), ourToleranceD);
		}

		TEST_METHOD(V3_Unit_Vector_Length)
		{
			const Vector3f n{0.f, 1.f, 0.f};
			Assert::AreEqual(1.f, n.Length(), ourToleranceF);
		}

		TEST_METHOD(V3_Normalise)
		{
			Vector3d v{3.0, 0.0, 4.0};
			v.Normalize();
			Assert::AreEqual(0.6, v.x, ourToleranceD);
			Assert::AreEqual(0.0, v.y, ourToleranceD);
			Assert::AreEqual(0.8, v.z, ourToleranceD);
			Assert::AreEqual(1.0, v.Length(), ourToleranceD);

			const Vector3f u{1.f, 2.f, 2.f}; // len = 3
			auto gn = u.GetNormalized();
			Assert::AreEqual(1.f / 3.f, gn.x, ourToleranceF);
			Assert::AreEqual(2.f / 3.f, gn.y, ourToleranceF);
			Assert::AreEqual(2.f / 3.f, gn.z, ourToleranceF);
			Assert::AreEqual(3.f, u.Length(), ourToleranceF); // original unchanged
		}

		TEST_METHOD(V3_Length_Zero_Vector)
		{
			const Vector3f z{0.f, 0.f, 0.f};
			Assert::AreEqual(0.f, z.Length(), ourToleranceF);
			Assert::AreEqual(0.f, z.LengthSqr(), ourToleranceF);
		}

		TEST_METHOD(V3_Normalise_Zero_Vector)
		{
			Vector3d z{0.0, 0.0, 0.0};
			z.Normalize(); // stay zero, no NaN
			Assert::AreEqual(0.0, z.x, ourToleranceD);
			Assert::AreEqual(0.0, z.y, ourToleranceD);
			Assert::AreEqual(0.0, z.z, ourToleranceD);

			auto gn = Vector3f{0.f, 0.f, 0.f}.GetNormalized();
			Assert::AreEqual(0.f, gn.x, ourToleranceF);
			Assert::AreEqual(0.f, gn.y, ourToleranceF);
			Assert::AreEqual(0.f, gn.z, ourToleranceF);
		}

		TEST_METHOD(V3_Component_Multiplication)
		{
			const Vector3i a{2, -3, 4};
			const Vector3i b{-1, -2, 3};
			auto c = a * b; // component-wise
			Assert::AreEqual(-2, c.x);
			Assert::AreEqual(6, c.y);
			Assert::AreEqual(12, c.z);
		}

		TEST_METHOD(V3_Dot)
		{
			const Vector3f a{1.f, 2.f, 3.f};
			const Vector3f b{-2.f, 0.5f, 1.f}; // dot = -2 + 1 + 3 = 2
			Assert::AreEqual(2.f, a.Dot(b), ourToleranceF);
			Assert::AreEqual(a.LengthSqr(), a.Dot(a), ourToleranceF);
		}

		TEST_METHOD(V3_Cross)
		{
			// Basic right-hand rule
			const Vector3f ex{1.f, 0.f, 0.f};
			const Vector3f ey{0.f, 1.f, 0.f};
			const Vector3f ez{0.f, 0.f, 1.f};

			auto ez_from_cross = ex.Cross(ey);
			Assert::AreEqual(ez.x, ez_from_cross.x, ourToleranceF);
			Assert::AreEqual(ez.y, ez_from_cross.y, ourToleranceF);
			Assert::AreEqual(ez.z, ez_from_cross.z, ourToleranceF);

			// Anti-commutativity: a x b = -(b x a)
			auto a = Vector3f{2.f, -1.f, 3.f};
			auto b = Vector3f{-4.f, 5.f, 1.f};
			auto axb = a.Cross(b);
			auto bxa = b.Cross(a);
			Assert::AreEqual(-bxa.x, axb.x, ourToleranceF);
			Assert::AreEqual(-bxa.y, axb.y, ourToleranceF);
			Assert::AreEqual(-bxa.z, axb.z, ourToleranceF);

			// Orthogonality: (a x b) · a == 0 and (a x b) · b == 0
			Assert::AreEqual(0.f, axb.Dot(a), ourToleranceF);
			Assert::AreEqual(0.f, axb.Dot(b), ourToleranceF);

			// Self cross is zero
			auto zero = a.Cross(a);
			Assert::AreEqual(0.f, zero.x, ourToleranceF);
			Assert::AreEqual(0.f, zero.y, ourToleranceF);
			Assert::AreEqual(0.f, zero.z, ourToleranceF);

			// Integer case sanity
			const Vector3i ai{1, 2, 3};
			const Vector3i bi{4, 5, 6};
			auto ci = ai.Cross(bi); // ( -3, 6, -3 )
			Assert::AreEqual(-3, ci.x);
			Assert::AreEqual(6, ci.y);
			Assert::AreEqual(-3, ci.z);
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector3Test::ourToleranceF = 0.00001f;
	const double Vector3Test::ourToleranceD = 0.00001;
} // namespace Vectors
