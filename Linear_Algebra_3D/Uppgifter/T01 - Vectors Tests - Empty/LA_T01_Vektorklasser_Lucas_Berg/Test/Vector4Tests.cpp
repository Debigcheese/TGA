#include "stdafx.h"
#include "CppUnitTest.h"
#include <type_traits>
#include "Student Code/Vector4.h"

/// <summary>
/// This is a hack to emulate the TGA vector for the task of convertion
/// It only works because they happen to have the same name
/// </summary>
namespace Tga
{
	template <class T>
	class Vector4
	{
	public:
		T x, y, z, w;

		Vector4() : x(T(0)), y(T(0)), z(T(0)), w(T(0))
		{
		}

		Vector4(const T aX, const T aY, const T aZ, const T aW)
			: x(aX), y(aY), z(aZ), w(aW)
		{
		}

		Vector4(const Vector4&) = default;
		Vector4& operator=(const Vector4&) = default;
	};
}

/// <summary>
/// To make the test-code cleaner we have a shorthand way to refer to the types
/// where the tga-vectors are prefixed Tga.
/// All the shorthands are post-fixed with the dimentionality as a number.
/// Along with the type as a one char shortened version, so for example it identifies:
/// float as 'f', int as 'i' or double as 'd'
/// </summary>
/// 
using Vector4f = CommonUtilities::Vector4<float>;
using Vector4d = CommonUtilities::Vector4<double>;
using Vector4i = CommonUtilities::Vector4<int>;

using TgaVectorf = Tga::Vector4<float>;
using TgaVectord = Tga::Vector4<double>;
using TgaVectori = Tga::Vector4<int>;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vectors
{
	TEST_CLASS(Vector4Test)
	{
	public:
		TEST_METHOD(V4_Const)
		{
			// Methods should be callable on const objects (const-correctness)
			const Vector4f v{1.f, 2.f, 3.f, 4.f};
			const Vector4f u{2.f, 0.5f, -1.f, 1.f};

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

			// Type traits sanity
			static_assert(std::is_copy_constructible_v<Vector4f>);
			static_assert(std::is_copy_assignable_v<Vector4f>);
			static_assert(std::is_trivially_destructible_v<Vector4f>);
		}

		TEST_METHOD(V4_Size)
		{
			Assert::AreEqual(sizeof(Vector4f), sizeof(float) * 4u);
			Assert::AreEqual(sizeof(Vector4d), sizeof(double) * 4u);
			Assert::AreEqual(sizeof(Vector4i), sizeof(int) * 4u);
		}

		TEST_METHOD(V4_Default_Constructor)
		{
			Vector4f vf;
			Vector4i vi;
			Assert::AreEqual(0.f, vf.x);
			Assert::AreEqual(0.f, vf.y);
			Assert::AreEqual(0.f, vf.z);
			Assert::AreEqual(0.f, vf.w);

			Assert::AreEqual(0, vi.x);
			Assert::AreEqual(0, vi.y);
			Assert::AreEqual(0, vi.z);
			Assert::AreEqual(0, vi.w);
		}

		TEST_METHOD(V4_Constructor)
		{
			Vector4d v{1.0, 2.5, -3.0, 4.25};
			Assert::AreEqual(1.0, v.x);
			Assert::AreEqual(2.5, v.y);
			Assert::AreEqual(-3.0, v.z);
			Assert::AreEqual(4.25, v.w);
		}

		TEST_METHOD(V4_Copy_Constructor)
		{
			const Vector4f a{3.f, -2.f, 5.f, 1.f};
			Vector4f b{a};
			Assert::AreEqual(a.x, b.x);
			Assert::AreEqual(a.y, b.y);
			Assert::AreEqual(a.z, b.z);
			Assert::AreEqual(a.w, b.w);
		}

		TEST_METHOD(V4_Assignment)
		{
			const Vector4i a{1, 2, 3, 4};
			Vector4i b;
			b = a;
			Assert::AreEqual(1, b.x);
			Assert::AreEqual(2, b.y);
			Assert::AreEqual(3, b.z);
			Assert::AreEqual(4, b.w);
		}

		TEST_METHOD(V4_ToTGAConvertion)
		{
			const Vector4f v{1.f, 2.f, 3.f, 4.f};
			TgaVectorf t = v.ToTga();
			Assert::AreEqual(v.x, t.x);
			Assert::AreEqual(v.y, t.y);
			Assert::AreEqual(v.z, t.z);
			Assert::AreEqual(v.w, t.w);
		}

		TEST_METHOD(V4_ToOtherTypeConvertion)
		{
			const Vector4i vi{1, -2, 3, -4};
			auto vf = vi.ToType<float>();
			Assert::AreEqual(1.f, vf.x);
			Assert::AreEqual(-2.f, vf.y);
			Assert::AreEqual(3.f, vf.z);
			Assert::AreEqual(-4.f, vf.w);

			const Vector4f vfx{1.5f, -2.25f, 3.75f, -4.5f};
			auto vd = vfx.ToType<double>();
			Assert::AreEqual(1.5, vd.x, ourToleranceD);
			Assert::AreEqual(-2.25, vd.y, ourToleranceD);
			Assert::AreEqual(3.75, vd.z, ourToleranceD);
			Assert::AreEqual(-4.5, vd.w, ourToleranceD);
		}

		TEST_METHOD(V4_Negation)
		{
			const Vector4d v{1.0, -2.0, 0.5, -4.0};
			auto n = -v;
			Assert::AreEqual(-1.0, n.x);
			Assert::AreEqual(2.0, n.y);
			Assert::AreEqual(-0.5, n.z);
			Assert::AreEqual(4.0, n.w);
		}

		TEST_METHOD(V4_Addition)
		{
			const Vector4f a{1.f, 2.f, 3.f, 4.f};
			const Vector4f b{-3.f, 5.f, 1.f, -2.f};
			auto c = a + b;
			Assert::AreEqual(-2.f, c.x);
			Assert::AreEqual(7.f, c.y);
			Assert::AreEqual(4.f, c.z);
			Assert::AreEqual(2.f, c.w);
		}

		TEST_METHOD(V4_Subtraction)
		{
			const Vector4i a{5, 7, -2, 10};
			const Vector4i b{3, -1, 4, 6};
			auto c = a - b;
			Assert::AreEqual(2, c.x);
			Assert::AreEqual(8, c.y);
			Assert::AreEqual(-6, c.z);
			Assert::AreEqual(4, c.w);
		}

		TEST_METHOD(V4_Scalar_Multiplication)
		{
			const Vector4f v{1.f, -2.f, 3.f, -4.f};
			auto a = v * 2.f;
			auto b = 2.f * v;
			Assert::AreEqual(2.f, a.x);
			Assert::AreEqual(2.f, b.x);
			Assert::AreEqual(-4.f, a.y);
			Assert::AreEqual(-4.f, b.y);
			Assert::AreEqual(6.f, a.z);
			Assert::AreEqual(6.f, b.z);
			Assert::AreEqual(-8.f, a.w);
			Assert::AreEqual(-8.f, b.w);
		}

		TEST_METHOD(V4_Length)
		{
			const Vector4f v{1.f, 2.f, 2.f, 0.f};
			Assert::AreEqual(3.f, v.Length(), ourToleranceF);
		}

		TEST_METHOD(V4_LengthSqrOptimize)
		{
			const Vector4d v{2.0, -3.0, 4.0, -1.0};

			Assert::AreEqual(30.0, v.LengthSqr(), ourToleranceD);

			Assert::AreEqual(v.Length() * v.Length(), v.LengthSqr(), ourToleranceD);
		}

		TEST_METHOD(V4_Unit_Vector_Length)
		{
			const Vector4f n{0.f, 1.f, 0.f, 0.f};
			Assert::AreEqual(1.f, n.Length(), ourToleranceF);
		}

		TEST_METHOD(V4_Normalise)
		{
			Vector4d v{3.0, 0.0, 4.0, 0.0};
			v.Normalize();
			Assert::AreEqual(0.6, v.x, ourToleranceD);
			Assert::AreEqual(0.0, v.y, ourToleranceD);
			Assert::AreEqual(0.8, v.z, ourToleranceD);
			Assert::AreEqual(0.0, v.w, ourToleranceD);
			Assert::AreEqual(1.0, v.Length(), ourToleranceD);

			const Vector4f u{1.f, 2.f, 2.f, 1.f};
			const float inv = 1.0f / std::sqrt(10.0f);
			auto gn = u.GetNormalized();
			Assert::AreEqual(1.f * inv, gn.x, ourToleranceF);
			Assert::AreEqual(2.f * inv, gn.y, ourToleranceF);
			Assert::AreEqual(2.f * inv, gn.z, ourToleranceF);
			Assert::AreEqual(1.f * inv, gn.w, ourToleranceF);
			Assert::AreEqual(std::sqrt(10.f), u.Length(), ourToleranceF);
		}

		TEST_METHOD(V4_Length_Zero_Vector)
		{
			const Vector4f z{0.f, 0.f, 0.f, 0.f};
			Assert::AreEqual(0.f, z.Length(), ourToleranceF);
			Assert::AreEqual(0.f, z.LengthSqr(), ourToleranceF);
		}

		TEST_METHOD(V4_Normalise_Zero_Vector)
		{
			Vector4d z{0.0, 0.0, 0.0, 0.0};
			z.Normalize();
			Assert::AreEqual(0.0, z.x, ourToleranceD);
			Assert::AreEqual(0.0, z.y, ourToleranceD);
			Assert::AreEqual(0.0, z.z, ourToleranceD);
			Assert::AreEqual(0.0, z.w, ourToleranceD);

			auto gn = Vector4f{0.f, 0.f, 0.f, 0.f}.GetNormalized();
			Assert::AreEqual(0.f, gn.x, ourToleranceF);
			Assert::AreEqual(0.f, gn.y, ourToleranceF);
			Assert::AreEqual(0.f, gn.z, ourToleranceF);
			Assert::AreEqual(0.f, gn.w, ourToleranceF);
		}

		TEST_METHOD(V4_Component_Multiplication)
		{
			const Vector4i a{2, -3, 4, -5};
			const Vector4i b{-1, -2, 3, 2};
			auto c = a * b;
			Assert::AreEqual(-2, c.x);
			Assert::AreEqual(6, c.y);
			Assert::AreEqual(12, c.z);
			Assert::AreEqual(-10, c.w);
		}

		TEST_METHOD(V4_Dot)
		{
			const Vector4f a{1.f, 2.f, 3.f, 4.f};
			const Vector4f b{-2.f, 0.5f, 1.f, 0.f};
			Assert::AreEqual(2.f, a.Dot(b), ourToleranceF);
			Assert::AreEqual(a.LengthSqr(), a.Dot(a), ourToleranceF);
		}

	private:
		static const float ourToleranceF;
		static const double ourToleranceD;
	};

	const float Vector4Test::ourToleranceF = 0.00001f;
	const double Vector4Test::ourToleranceD = 0.00001;
}
