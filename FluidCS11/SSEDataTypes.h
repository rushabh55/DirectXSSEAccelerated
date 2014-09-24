#pragma once
#include <DXUT.h>
//// Copyright © 2008 Intel Corporation
//// All Rights Reserved
//// 
//// The sample source code contained or described herein and all documents
//// related to the sample source code ("Material") are owned by Intel Corporation
//// or its suppliers or licensors. Title to the Material remains with Intel Corporation
//// or its suppliers and licensors. The Material may contain trade secrets and
//// proprietary and confidential information of Intel Corporation and its suppliers
//// and licensors, and is protected by worldwide copyright and trade secret laws and
//// treaty provisions. The sample source code is provided AS IS, with no warranties
//// of any kind, express or implied. Except as expressly permitted by the Software
//// license, neither Intel Corporation nor its suppliers assumes any responsibility
//// or liability for any errors or inaccuracies that may appear herein.
//
//#include "Macros.h"
//#include <DirectXMath.h>
//
//using namespace DirectX;
//#include <intrin.h>
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//// <summary>
////   Miscellaneous SSE functionality.
//// </summary>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
///// <summary>
/////   Convenience function for adding 3 __m128 types.
///// </summary>
///// <param name="a">The first variable to add.</param>
///// <param name="b">The second variable to add.</param>
///// <param name="c">The third variable to add.</param>
///// <returns>The three way add result.</returns>
//__m128 __forceinline _mm_add3_ps_composite(const __m128& a, const __m128& b, const __m128& c)
//{
//	return _mm_add_ps(_mm_add_ps(a, b), c);
//}
//
//
///// <summary>
/////   Convenience function for adding 4 __m128 types.
///// </summary>
///// <param name="a">The first variable to add.</param>
///// <param name="b">The second variable to add.</param>
///// <param name="c">The third variable to add.</param>
///// <param name="d">The fourth variable to add.</param>
///// <returns>The four way add result.</returns>
//__m128 __forceinline _mm_add4_ps_composite(const __m128& a, const __m128& b,
//	const __m128& c, const __m128& d)
//{
//	return _mm_add_ps(_mm_add_ps(a, b), _mm_add_ps(c, d));
//}
//
//
///// <summary>
/////   Divides 2 __m128 types and zeroes out indeterminate values caused by divide-by-zero.
///// </summary>
///// <remarks>This function is used when masking divide-by-zero.</remarks>
///// <param name="a">The dividend.</param>
///// <param name="b">The divisor.</param>
///// <returns>The quotient.</returns>
//__m128 __forceinline _mm_div_ps_composite(const __m128& a, const __m128& b)
//{
//	__m128 xMask = _mm_cmpneq_ps(b, _mm_setzero_ps());
//	__m128 t = _mm_div_ps(a, b);
//	t = _mm_and_ps(t, xMask);
//	return t;
//}
//
//#ifndef MATH_H_LIB_X
//#define MATH_H_LIB_X
//namespace Math
//{
//	class XVector3;
//	class XVector4;
//	class XQuaternion;
//	class XMatrix4x4;
//	typedef class XVector4 XVector2;
//
//	class XVector
//	{
//		friend class XMatrix4x4;
//
//
//	public:
//
//		XVector(void) {}
//
//		/// <summary>
//		///   Operator new override for allocation of SSE aligned memory.
//		/// </summary>
//		/// <param name="Size">The size to allocate.</param>
//		/// <returns>A pointer to the allocated memory.</returns>
//		void* operator new(size_t Size)
//		{
//			return _aligned_malloc(Size, sizeof(__m128));
//		}
//
//			/// <summary>
//			///   Operator delete override for deallocation of SSE aligned memory.
//			/// </summary>
//			/// <param name="p">The pointer to deallocate.</param>
//			void operator delete(void* p)
//		{
//			_aligned_free(p);
//		}
//
//		/// <summary>
//		///   Provides a const cast to a __m128.
//		/// </summary>
//		/// <returns>This vector as a __m128.</returns>
//		operator const __m128(void) const
//		{
//			return m_Vector;
//		}
//
//		/// <summary>
//		///   Returns the x value of the vector.
//		/// </summary>
//		/// <returns>The x value of the vector.</returns>
//		f32 GetX(void)
//		{
//			f32 x;
//			_mm_store_ss(&x, m_Vector);
//			return x;
//		}
//
//		/// <summary>
//		///   Returns the y value of the vector.
//		/// </summary>
//		/// <returns>The y value of the vector.</returns>
//		f32 GetY(void)
//		{
//			f32 y;
//			_mm_store_ss(&y, _mm_shuffle_ps(m_Vector, m_Vector, 1));
//			return y;
//		}
//
//		/// <summary>
//		///   Returns the z value of the vector.
//		/// </summary>
//		/// <returns>The z value of the vector.</returns>
//		f32 GetZ(void)
//		{
//			f32 z;
//			_mm_store_ss(&z, _mm_movehl_ps(m_Vector, m_Vector));
//			return z;
//		}
//
//		/// <summary>
//		///   Returns the y value of the vector.
//		/// </summary>
//		/// <returns>The w value of the vector.</returns>
//		f32 GetW(void)
//		{
//			f32 w;
//			_mm_store_ss(&w, _mm_shuffle_ps(m_Vector, m_Vector, 3));
//			return w;
//		}
//
//
//	protected:
//
//		static const __m128 sm_kxUnitX;
//		static const __m128 sm_kxUnitY;
//		static const __m128 sm_kxUnitZ;
//		static const __m128 sm_kxUnitW;
//		static const __m128 sm_kxNegateX;
//		static const __m128 sm_kxNegateY;
//		static const __m128 sm_kxNegateZ;
//		static const __m128 sm_kxNegateW;
//		static const __m128 sm_kxNegateXYZ;
//		static const __m128 sm_kxNegateXYZW;
//		static const __m128 sm_kxOne;
//		static const __m128 sm_kxTwo;
//		static const __m128 sm_kxTranslationMask;
//
//		__m128          m_Vector;
//	};
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>
//	///   A convenience class for doing scalar operations with the SSE vector classes.
//	/// </summary>
//	////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class XScalar : public XVector
//	{
//	public:
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		XScalar(void) : XVector() {}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="s">A scalar value.</param>
//		XScalar(f32 s)
//		{
//			m_Vector = _mm_set1_ps(s);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">A broadcasted scalar value.</param>
//		XScalar(__m128 x)
//		{
//			ASSERT((x.m128_f32[0] == x.m128_f32[1]) &&	(x.m128_f32[0] == x.m128_f32[2]) &&	(x.m128_f32[0] == x.m128_f32[3]));
//			m_Vector = x;
//		}
//
//		/// <summary>
//		///   Provides a cast to an f32.
//		/// </summary>
//		/// <returns>Ths XScalar as an f32.</returns>
//		operator f32(void) const
//		{
//			f32 s;
//			_mm_store_ss(&s, m_Vector);
//			return s;
//		}
//	};
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>
//	///   Provides SSE functionality for a 3D vector.
//	/// </summary>
//	////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class XVector3 : public XVector
//	{
//	public:
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		XVector3(void) : XVector() {}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="v">A vector in array form.</param>
//		XVector3(f32* v)
//		{
//			m_Vector = _mm_loadl_pi(m_Vector, reinterpret_cast<__m64*>(v));
//			m_Vector = _mm_movelh_ps(_mm_load_ss(v + 2), m_Vector);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">A vector in __m128 form.</param>
//		XVector3(__m128 x)
//		{
//			m_Vector = x;
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="f">The value to broadcast.</param>
//		XVector3(f32 f)
//		{
//			m_Vector = _mm_and_ps(_mm_set1_ps(f), sm_kxTranslationMask);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">The x value.</param>
//		/// <param name="y">The y value.</param>
//		/// <param name="z">The z value.</param>
//		XVector3(f32 x, f32 y, f32 z);
//
//		/// <summary>
//		///   Functionality for adding two vectors with assignment.
//		/// </summary>
//		/// <param name="a">The vector to add to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator+=(const XVector3& a)
//		{
//			m_Vector = _mm_add_ps(m_Vector, a.m_Vector);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for subtracting two vectors with assignment.
//		/// </summary>
//		/// <param name="a">The vector to subtract from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator-=(const XVector3& a)
//		{
//			m_Vector = _mm_sub_ps(m_Vector, a.m_Vector);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar with assignment.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator*=(const XScalar& s)
//		{
//			m_Vector = _mm_mul_ps(m_Vector, s);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar with assignment.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator*=(f32 s)
//		{
//			m_Vector = _mm_mul_ps(m_Vector, _mm_set1_ps(s));
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar with assignment.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator/=(const XScalar& s){
//			m_Vector = _mm_div_ps_composite(m_Vector, s);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar with assignment.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector3& operator/=(f32 s)
//		{
//			m_Vector = _mm_div_ps_composite(m_Vector, _mm_set1_ps(s));
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for adding two vectors.
//		/// </summary>
//		/// <param name="a">The vector to add to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator+(const XVector3& a) const
//		{
//			return XVector3(_mm_add_ps(m_Vector, a.m_Vector));
//		}
//
//		/// <summary>
//		///   Functionality for subtracting two vectors.
//		/// </summary>
//		/// <param name="a">The vector to subtract from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator-(const XVector3& a) const
//		{
//			return XVector3(_mm_sub_ps(m_Vector, a.m_Vector));
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator*(const XScalar& s) const
//		{
//			return XVector3(_mm_mul_ps(m_Vector, s));
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator*(f32 s) const
//		{
//			return XVector3(_mm_mul_ps(m_Vector, _mm_set1_ps(s)));
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator/(const XScalar& s) const
//		{
//			return XVector3(_mm_div_ps_composite(m_Vector, s));
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector3 operator/(f32 s) const
//		{
//			return XVector3(_mm_div_ps_composite(m_Vector, _mm_set1_ps(s)));
//		}
//
//		/// <summary>
//		///   Functionality for equals.
//		/// </summary>
//		/// <param name="a">The vector to compare to this vector.</param>
//		/// <returns>The result of the comparison.</returns>
//		bool operator==(const XVector3& a) const
//		{
//			return _mm_movemask_ps(_mm_cmpeq_ps(m_Vector, a.m_Vector)) == 7;
//		}
//
//		/// <summary>
//		///   Functionality for not equals.
//		/// </summary>
//		/// <param name="a">The vector to compare to this vector.</param>
//		/// <returns>The result of the comparison.</returns>
//		bool operator!=(const XVector3& a) const
//		{
//			return _mm_movemask_ps(_mm_cmpeq_ps(m_Vector, a.m_Vector)) != 7;
//		}
//
//		/// <summary>
//		///   Returns the dot product of 2 vectors.
//		/// </summary>
//		/// <param name="a">The other vector.</param>
//		/// <returns>The dot product.</returns>
//		XScalar Dot(const XVector3& a) const
//		{
//			__m128 t;
//			__m128 sq = _mm_mul_ps(m_Vector, a.m_Vector);
//			t = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 1, 0, 2)));
//			t = _mm_add_ps(t, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 0, 2, 1)));
//			return XScalar(t);
//		}
//
//		/// <summary>
//		///   Returns the cross product of 2 vectors.
//		/// </summary>
//		/// <param name="a">The other vector.</param>
//		/// <returns>The cross product.</returns>
//		XVector3 Cross(const XVector3& a) const
//		{
//			__m128 x00 = _mm_shuffle_ps(m_Vector, m_Vector, _MM_SHUFFLE(3, 0, 2, 1));
//			__m128 x10 = _mm_shuffle_ps(a.m_Vector, a.m_Vector, _MM_SHUFFLE(3, 1, 0, 2));
//			__m128 x01 = _mm_shuffle_ps(m_Vector, m_Vector, _MM_SHUFFLE(3, 1, 0, 2));
//			__m128 x11 = _mm_shuffle_ps(a.m_Vector, a.m_Vector, _MM_SHUFFLE(3, 0, 2, 1));
//
//			return XVector3(_mm_add_ps(_mm_mul_ps(x00, x10), _mm_mul_ps(x01, x11)));
//		}
//
//		/// <summary>
//		///   Returns the magnitude of the vector.
//		/// </summary>
//		/// <returns>The magnitude of the vector.</returns>
//		XScalar Magnitude(void) const
//		{
//			XScalar s = Dot(*this);
//			return XScalar(_mm_sqrt_ps(s));
//		}
//
//		/// <summary>
//		///   Normalizes this vector.
//		/// </summary>
//		/// <returns>A refrence to this vector.</returns>
//		const XVector3& Normalize(void)
//		{
//			static const __m128 xPtFive = { 0.5f, 0.5f, 0.5f, 0.5f };
//			static const __m128 xThree = { 3.0f, 3.0f, 3.0f, 3.0f };
//
//			XScalar dot = Dot(*this);
//
//			__m128 rsd = _mm_rsqrt_ps(dot);
//
//			rsd = _mm_mul_ps(_mm_mul_ps(xPtFive, rsd),
//				_mm_sub_ps(xThree, _mm_mul_ps(_mm_mul_ps(dot, rsd), rsd)));
//
//			m_Vector = _mm_mul_ps(m_Vector, rsd);
//			return *this;
//		}
//
//
//	public:
//
//		//
//		// Common constants.
//		//
//		static const XVector3 Zero;
//		static const XVector3 One;
//		static const XVector3 UnitX;
//		static const XVector3 UnitY;
//		static const XVector3 UnitZ;
//	};
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>
//	///   Provides SSE functionality of a 3D vector with a modifier.
//	/// </summary>
//	////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class XVector4 : public XVector
//	{
//	public:
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		XVector4(void) {}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="v">A vector in array form.</param>
//		XVector4(f32* v)
//		{
//			m_Vector = _mm_loadu_ps(v);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">A vector in __m128 form.</param>
//		XVector4(__m128 x)
//		{
//			m_Vector = x;
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="f">The value to broadcast.</param>
//		XVector4(f32 f)
//		{
//			m_Vector = _mm_set1_ps(f);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">The x value.</param>
//		/// <param name="y">The y value.</param>
//		/// <param name="z">The z value.</param>
//		/// <param name="w">The w value.</param>
//		XVector4(f32 x, f32 y, f32 z, f32 w);
//
//		/// <summary>
//		///   Functionality for adding two vectors with assignment.
//		/// </summary>
//		/// <param name="a">The vector to add to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator+=(const XVector4& a)
//		{
//			m_Vector = _mm_add_ps(m_Vector, a.m_Vector);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for subtracting two vectors with assignment.
//		/// </summary>
//		/// <param name="a">The vector to subtract from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator-=(const XVector4& a)
//		{
//			m_Vector = _mm_sub_ps(m_Vector, a.m_Vector);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar with assignment.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator*=(const XScalar& s)
//		{
//			m_Vector = _mm_mul_ps(m_Vector, s);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar with assignment.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator*=(f32 s)
//		{
//			m_Vector = _mm_mul_ps(m_Vector, _mm_set1_ps(s));
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar with assignment.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator/=(const XScalar& s)
//		{
//			m_Vector = _mm_div_ps_composite(m_Vector, s);
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar with assignment.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>A reference to this vector.</returns>
//		XVector4& operator/=(f32 s)
//		{
//			m_Vector = _mm_div_ps_composite(m_Vector, _mm_set1_ps(s));
//			return *this;
//		}
//
//		/// <summary>
//		///   Functionality for adding two vectors.
//		/// </summary>
//		/// <param name="a">The vector to add to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator+(const XVector4& a) const
//		{
//			return XVector4(_mm_add_ps(m_Vector, a.m_Vector));
//		}
//
//		/// <summary>
//		///   Functionality for subtracting two vectors.
//		/// </summary>
//		/// <param name="a">The vector to subtract from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator-(const XVector4& a) const
//		{
//			return XVector4(_mm_sub_ps(m_Vector, a.m_Vector));
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator*(const XScalar& s) const
//		{
//			return XVector4(_mm_add_ps(m_Vector, s));
//		}
//
//		/// <summary>
//		///   Functionality for multiplying a vector with a scalar.
//		/// </summary>
//		/// <param name="s">The scalar to multiply to this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator*(f32 s) const
//		{
//			return XVector4(_mm_add_ps(m_Vector, _mm_set1_ps(s)));
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator/(const XScalar& s) const
//		{
//			return XVector4(_mm_div_ps_composite(m_Vector, s));
//		}
//
//		/// <summary>
//		///   Functionality for dividing a vector with a scalar.
//		/// </summary>
//		/// <remarks>Divide by zero needs to be masked.</remarks>
//		/// <param name="s">The scalar to divide from this vector.</param>
//		/// <returns>The new vector created by this operation.</returns>
//		XVector4 operator/(f32 s) const
//		{
//			return XVector4(_mm_div_ps_composite(m_Vector, _mm_set1_ps(s)));
//		}
//
//		/// <summary>
//		///   Functionality for equals.
//		/// </summary>
//		/// <param name="a">The vector to compare to this vector.</param>
//		/// <returns>The result of the comparison.</returns>
//		bool operator==(const XVector4& a) const
//		{
//			return _mm_movemask_ps(_mm_cmpeq_ps(m_Vector, a.m_Vector)) == 0x0F;
//		}
//
//		/// <summary>
//		///   Functionality for not equals.
//		/// </summary>
//		/// <param name="a">The vector to compare to this vector.</param>
//		/// <returns>The result of the comparison.</returns>
//		bool operator!=(const XVector4& a) const
//		{
//			return _mm_movemask_ps(_mm_cmpeq_ps(m_Vector, a.m_Vector)) != 0x0F;
//		}
//
//
//	public:
//
//		//
//		// Common constants.
//		//
//		static const XVector4 Zero;
//		static const XVector4 One;
//	};
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>
//	///   Provides SSE functionality for a quanternion.
//	/// </summary>
//	////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class XQuaternion : public XVector
//	{
//	public:
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		XQuaternion(void) {}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="q">A quaternion in array form.</param>
//		XQuaternion(f32* q)
//		{
//			m_Vector = _mm_loadu_ps(q);
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">A quaternion in __m128 form.</param>
//		XQuaternion(__m128 x)
//		{
//			m_Vector = x;
//		}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="x">The x value.</param>
//		/// <param name="y">The y value.</param>
//		/// <param name="z">The z value.</param>
//		/// <param name="w">The w value.</param>
//		XQuaternion(f32 x, f32 y, f32 z, f32 w);
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="Axis">The normalized vector axis."</param>
//		/// <param name="Angle">The angle of the vector axis."</param>
//		/// <returns>A reference to this quaternion.</returns>
//		XQuaternion(const XVector3& Axis, f32 Angle);
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="Angles">The Euler angles for the quaternion."</param>
//		/// <returns>A reference to this quaternion.</returns>
//
//		XQuaternion(const XMFLOAT3A& Angles);
//
//		/// <summary>
//		///   Functionality for multiplying two quaternions.
//		/// </summary>
//		/// <param name="a">The quaternion to multiply to this quaterion.</param>
//		/// <returns>The new quaternion.</returns>
//		XQuaternion operator*(XQuaternion& a) const;
//
//		/// <summary>
//		///   Functionality for multiplying two quaternions with assignment.
//		/// </summary>
//		/// <param name="a">The quaternion to multiply to this quaterion.</param>
//		/// <returns>A reference to this quaternion.</returns>
//		XQuaternion& operator*=(XQuaternion& a)
//		{
//			*this = *this * a;
//			return *this;
//		}
//
//		/// <summary>
//		///   Calculates the magnitude of this quaternion.
//		/// </summary>
//		/// <returns>The magnitude.</returns>
//		f32 Magnitude(void) const
//		{
//			__m128 t;
//			__m128 sq = _mm_mul_ps(m_Vector, m_Vector);
//			t = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 1, 0, 2)));
//			t = _mm_add_ps(t, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 0, 2, 1)));
//			return XScalar(_mm_sqrt_ps(t));
//		}
//
//		/// <summary>
//		///   Calculates the conjugate or inverse of a quaternion.
//		/// </summary>
//		XQuaternion& Conjugate(void)
//		{
//			m_Vector = _mm_xor_ps(m_Vector, sm_kxNegateXYZ);
//			return *this;
//		}
//
//		/// <summary>
//		///   Calculates the conjugate or inverse of a quaternion.
//		/// </summary>
//		/// <param name="a">The quaternion to set as the inverse of this quaternion.</param>
//		XQuaternion& Conjugate(XQuaternion* a)
//		{
//			*a = (XQuaternion) _mm_xor_ps(m_Vector, sm_kxNegateXYZ);
//			return *a;
//		}
//
//		XVector3 Rotate(const XVector3& a)
//		{
//			//UNREFERENCED_PARAM(a);
//			ASSERTMSG( 0 , "This still needs to be implemented!!!");
//			return XVector3();
//		}
//
//
//	public:
//
//		static const XQuaternion Zero;
//	};
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>
//	///   Row major SSE implementation of a 4x4 matrix.
//	/// </summary>
//	////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class XMatrix4x4
//	{
//	public:
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		XMatrix4x4(void) {}
//
//		/// <summary>
//		///   Constructor.
//		/// </summary>
//		/// <param name="m">A matrix in array form.</param>
//		XMatrix4x4(const f32* m)
//		{
//			m_Matrix[0] = _mm_loadu_ps(m);
//			m_Matrix[1] = _mm_loadu_ps(m + 4);
//			m_Matrix[2] = _mm_loadu_ps(m + 8);
//			m_Matrix[3] = _mm_loadu_ps(m + 12);
//		};
//
//		/// <summary>
//		///   Constructor for a transformation matrix.
//		/// </summary>
//		/// <param name="Translation">The translation for the matrix.</param>
//		/// <param name="Orientation">The orientation for the matrix.</param>
//		XMatrix4x4(const XVector3& Translation, const XQuaternion& Orientation);
//
//		/// <summary>
//		///   Vector matrix multiplication.
//		/// </summary>
//		/// <param name="a">The vector to multiply to this matrix.</param>
//		/// <returns>The new vector.</returns>
//		XVector3 operator*(const XVector3& a) const;
//
//		/// <summary>
//		///   Vector matrix multiplication.
//		/// </summary>
//		/// <param name="a">The vector to multiply to this matrix.</param>
//		/// <returns>The new vector.</returns>
//		XVector4 operator*(const XVector4& a) const;
//
//		/// <summary>
//		///   Functionality for multiplying two matrices.
//		/// </summary>
//		/// <param name="a">The matrix to multiply to this matrix.</param>
//		/// <returns>The new matrix.</returns>
//		XMatrix4x4 operator*(const XMatrix4x4& a) const;
//
//		/// <summary>
//		///   Functionality for multiplying two matrices with assignment.
//		/// </summary>
//		/// <param name="a">The matrix to multiply to this matrix.</param>
//		/// <returns>A reference to this matrix.</returns>
//		const XMatrix4x4& operator*=(const XMatrix4x4& a)
//		{
//			*this = *this * a;
//		}
//
//		/// <summary>
//		///   Gets the translation of this matrix.
//		/// </summary>
//		/// <param name="Translation">A reference to the translation variable to fill in.</param>
//		/// <returns>The reference of the passed in translation.</returns>
//		XVector3& GetTranslation(XVector3& Translation) const
//		{
//			Translation = _mm_and_ps(m_Matrix[3], XVector::sm_kxTranslationMask);
//			return Translation;
//		}
//
//		/// <summary>
//		///   Gets the orientation of this matrix.
//		/// </summary>
//		/// <param name="Orientation">A reference to the orientation variable to fill in.</param>
//		/// <returns>The reference of the passed in orientation.</returns>
//		XQuaternion& GetOrientation(XQuaternion& Orientation) const;
//
//		/// <summary>
//		///   Sets the translation of this matrix.
//		/// </summary>
//		/// <param name="Translation">A reference to the translation to set this matrix to.</param>
//		/// <returns>A reference to this matrix.</returns>
//		XMatrix4x4& SetTranslation(const XVector3& Translation)
//		{
//			ASSERT(((const __m128)Translation).m128_f32[3] == 0.0f);
//			m_Matrix[3] = _mm_or_ps(Translation, sm_kxHighOne);
//			return *this;
//		}
//
//		/// <summary>
//		///   Sets the Orientation of this matrix.
//		/// </summary>
//		/// <param name="Orientation">A reference to the orientation to set this matrix to.</param>
//		/// <returns>A reference to this matrix.</returns>
//		XMatrix4x4& SetOrientation(const XQuaternion& Orientation);
//
//		/// <summary>
//		///   Set the inverse of this matrix.
//		/// </summary>
//		/// <param name="Inverse">The matrix to set as the inverse.</param>
//		/// <returns>A reference to the inverse matrix.</returns>
//		XMatrix4x4& Inverse(XMatrix4x4& Inverse);
//
//
//	public:
//
//		static const XMatrix4x4 Identity;
//
//
//	protected:
//
//		static const __m128 sm_kxHighOne;
//
//		__m128  m_Matrix[4];
//	};
//}
//
//#endif
//namespace Math
//{
//	_MM_ALIGN16 static const u32 kaTranslationMask[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 };
//	_MM_ALIGN16 static const f32 kaIdentityMatrix[16] =
//	{
//		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
//	};
//
//	const __m128 XVector::sm_kxUnitX = { 1.0f, 0.0f, 0.0f, 0.0f };
//	const __m128 XVector::sm_kxUnitY = { 0.0f, 1.0f, 0.0f, 0.0f };
//	const __m128 XVector::sm_kxUnitZ = { 0.0f, 0.0f, 1.0f, 0.0f };
//	const __m128 XVector::sm_kxUnitW = { 0.0f, 0.0f, 0.0f, 1.0f };
//	const __m128 XVector::sm_kxNegateX = { -0.0f, 0.0f, 0.0f, 0.0f };
//	const __m128 XVector::sm_kxNegateY = { 0.0f, -0.0f, 0.0f, 0.0f };
//	const __m128 XVector::sm_kxNegateZ = { 0.0f, 0.0f, -0.0f, 0.0f };
//	const __m128 XVector::sm_kxNegateW = { 0.0f, 0.0f, 0.0f, -0.0f };
//	const __m128 XVector::sm_kxNegateXYZ = { -0.0f, -0.0f, -0.0f, 0.0f };
//	const __m128 XVector::sm_kxNegateXYZW = { -0.0f, -0.0f, -0.0f, -0.0f };
//	const __m128 XVector::sm_kxOne = { 1.0f, 1.0f, 1.0f, 1.0f };
//	const __m128 XVector::sm_kxTwo = { 2.0f, 2.0f, 2.0f, 2.0f };
//	const __m128 XVector::sm_kxTranslationMask = *((const __m128*)kaTranslationMask);
//
//	const XVector3 XVector3::Zero(0.0f);
//	const XVector3 XVector3::One(1.0f);
//	const XVector3 XVector3::UnitX(sm_kxUnitX);
//	const XVector3 XVector3::UnitY(sm_kxUnitY);
//	const XVector3 XVector3::UnitZ(sm_kxUnitZ);
//
//	const XVector4 XVector4::Zero(0.0f, 0.0f, 0.0f, 1.0f);
//	const XVector4 XVector4::One(1.0f);
//
//	const XQuaternion XQuaternion::Zero(0.0f, 0.0f, 0.0f, 1.0f);
//
//	const XMatrix4x4 XMatrix4x4::Identity(kaIdentityMatrix);
//
//	const __m128 XMatrix4x4::sm_kxHighOne = { 0.0f, 0.0f, 0.0f, 1.0f };
//
//
//	XVector3::XVector3(
//		f32 x,
//		f32 y,
//		f32 z
//		)
//	{
//		__m128 xx = _mm_load_ss(&x);
//		__m128 xy = _mm_load_ss(&y);
//		__m128 xz = _mm_load_ss(&z);
//
//		m_Vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), xz);
//	}
//
//
//	XVector4::XVector4(
//		f32 x,
//		f32 y,
//		f32 z,
//		f32 w
//		)
//	{
//		__m128 xx = _mm_load_ss(&x);
//		__m128 xy = _mm_load_ss(&y);
//		__m128 xz = _mm_load_ss(&z);
//		__m128 xw = _mm_load_ss(&w);
//
//		m_Vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
//	}
//
//
//	XQuaternion::XQuaternion(
//		f32 x,
//		f32 y,
//		f32 z,
//		f32 w
//		)
//	{
//		__m128 xx = _mm_load_ss(&x);
//		__m128 xy = _mm_load_ss(&y);
//		__m128 xz = _mm_load_ss(&z);
//		__m128 xw = _mm_load_ss(&w);
//
//		m_Vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
//	}
//
//
//	XQuaternion::XQuaternion(
//		const XVector3& Axis,
//		f32 Angle
//		)
//	{
//		ASSERTMSG(Axis.Magnitude() == 1.0f,
//			"This function requires the vector to be normalized upon entry.");
//		ASSERT(((const __m128)Axis).m128_f32[3] == 0.0f);
//
//		const __m128 xSin = Axis * Angle::Sin(Angle);
//		const __m128 xCos = _mm_set_ss(Angle::Cos(Angle));
//		m_Vector = _mm_or_ps(xSin, xCos);
//	}
//
//
//	XQuaternion::XQuaternion(
//		const XMFLOAT3A& Angles
//		)
//	{
//		//
//		// This function is by no means optimal since it is known that several of the coordinates
//		//  are zero and so can be ignored in the quaternion multiply.
//		//
//		XQuaternion qx(XVector3::UnitX, Angles.x);
//		XQuaternion qy(XVector3::UnitY, Angles.y);
//		XQuaternion qz(XVector3::UnitZ, Angles.z);
//
//		*this = qx * qy;
//		*this *= qz;
//	}
//
//
//	XMatrix4x4::XMatrix4x4(
//		const XVector3& Translation,
//		const XQuaternion& Orientation
//		)
//	{
//		SetTranslation(Translation);
//		SetOrientation(Orientation);
//	}
//
//
//	XQuaternion
//		XQuaternion::operator*(
//		XQuaternion& a
//		) const
//	{
//		__m128 t0 = _mm_mul_ps(_mm_shuffle_ps(m_Vector, m_Vector, _MM_SHUFFLE(3, 3, 3, 3)),
//			a.m_Vector);
//		__m128 t1 = _mm_mul_ps(m_Vector,
//			_mm_shuffle_ps(a.m_Vector, a.m_Vector, _MM_SHUFFLE(0, 3, 3, 3)));
//		__m128 t2 = _mm_mul_ps(_mm_shuffle_ps(m_Vector, m_Vector, _MM_SHUFFLE(1, 0, 2, 1)),
//			_mm_shuffle_ps(a.m_Vector, a.m_Vector, _MM_SHUFFLE(1, 1, 0, 2)));
//		__m128 t3 = _mm_mul_ps(_mm_shuffle_ps(m_Vector, m_Vector, _MM_SHUFFLE(2, 1, 0, 2)),
//			_mm_shuffle_ps(a.m_Vector, a.m_Vector, _MM_SHUFFLE(2, 0, 2, 1)));
//
//		t1 = _mm_xor_ps(t1, sm_kxNegateW);
//		t2 = _mm_xor_ps(t2, sm_kxNegateW);
//
//		return XQuaternion(_mm_add_ps(_mm_add_ps(t0, t1), _mm_sub_ps(t2, t3)));
//	}
//
//
//	XVector3
//		XMatrix4x4::operator*(
//		const XVector3& a
//		) const
//	{
//		const __m128 xVec = a;
//		__m128 xVecRes;
//
//		xVecRes =
//			_mm_add4_ps_composite(
//			_mm_mul_ps(m_Matrix[0], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(0, 0, 0, 0))),
//			_mm_mul_ps(m_Matrix[1], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(1, 1, 1, 1))),
//			_mm_mul_ps(m_Matrix[2], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(2, 2, 2, 2))),
//			m_Matrix[3]
//			);
//
//		return XVector3(_mm_and_ps(xVecRes, XVector::sm_kxTranslationMask));
//	}
//
//
//	XVector4
//		XMatrix4x4::operator*(
//		const XVector4& a
//		) const
//	{
//		const __m128 xVec = a;
//		__m128 xVecRes;
//
//		xVecRes =
//			_mm_add4_ps_composite(
//			_mm_mul_ps(m_Matrix[0], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(0, 0, 0, 0))),
//			_mm_mul_ps(m_Matrix[1], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(1, 1, 1, 1))),
//			_mm_mul_ps(m_Matrix[2], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(2, 2, 2, 2))),
//			_mm_mul_ps(m_Matrix[3], _mm_shuffle_ps(xVec, xVec, _MM_SHUFFLE(3, 3, 3, 3)))
//			);
//
//		return XVector4(xVecRes);
//	}
//
//
//	XMatrix4x4
//		XMatrix4x4::operator*(
//		const XMatrix4x4& a
//		) const
//	{
//		XMatrix4x4 r;
//
//		__m128 t0, t1, t2, t3;
//		__m128 r0, r1, r2, r3;
//		// MSB               LSB
//		t0 = _mm_unpacklo_ps(m_Matrix[0], m_Matrix[1]);       // [ 11 | 01 | 10 | 00 ]
//		t1 = _mm_unpackhi_ps(m_Matrix[0], m_Matrix[1]);       // [ 13 | 03 | 12 | 02 ]
//		t2 = _mm_unpacklo_ps(m_Matrix[2], m_Matrix[3]);       // [ 31 | 21 | 30 | 20 ]
//		t3 = _mm_unpackhi_ps(m_Matrix[2], m_Matrix[3]);       // [ 33 | 23 | 32 | 22 ]
//
//		r0 = _mm_movelh_ps(t0, t2);                               // [ 30 | 20 | 10 | 00 ]
//		r1 = _mm_movehl_ps(t0, t2);                               // [ 31 | 21 | 11 | 01 ]
//		r2 = _mm_movelh_ps(t1, t3);                               // [ 32 | 22 | 12 | 02 ]
//		r3 = _mm_movehl_ps(t1, t3);                               // [ 33 | 23 | 13 | 03 ]
//
//		r.m_Matrix[0] = _mm_add4_ps_composite(_mm_mul_ps(r0, a.m_Matrix[0]),
//			_mm_mul_ps(r1, a.m_Matrix[0]),
//			_mm_mul_ps(r2, a.m_Matrix[0]),
//			_mm_mul_ps(r3, a.m_Matrix[0]));
//
//		r.m_Matrix[1] = _mm_add4_ps_composite(_mm_mul_ps(r0, a.m_Matrix[1]),
//			_mm_mul_ps(r1, a.m_Matrix[1]),
//			_mm_mul_ps(r2, a.m_Matrix[1]),
//			_mm_mul_ps(r3, a.m_Matrix[1]));
//
//		r.m_Matrix[2] = _mm_add4_ps_composite(_mm_mul_ps(r0, a.m_Matrix[2]),
//			_mm_mul_ps(r1, a.m_Matrix[2]),
//			_mm_mul_ps(r2, a.m_Matrix[2]),
//			_mm_mul_ps(r3, a.m_Matrix[2]));
//
//		r.m_Matrix[3] = _mm_add4_ps_composite(_mm_mul_ps(r0, a.m_Matrix[3]),
//			_mm_mul_ps(r1, a.m_Matrix[3]),
//			_mm_mul_ps(r2, a.m_Matrix[3]),
//			_mm_mul_ps(r3, a.m_Matrix[3]));
//
//		return r;
//	}
//
//
//	XQuaternion&
//		XMatrix4x4::GetOrientation(
//		XQuaternion& Orientation
//		) const
//	{
//		_MM_ALIGN16 f32 m[16];
//		_mm_store_ps(m, m_Matrix[0]);
//		_mm_store_ps(m + 4, m_Matrix[1]);
//		_mm_store_ps(m + 8, m_Matrix[2]);
//		_mm_store_ps(m + 12, m_Matrix[3]);
//
//		const f32 T = 1.0f + m[0] + m[5] + m[10];
//
//		if (T > 0.00000001f)
//		{
//			const f32 S = sqrtf(T) * 2.0f;
//			const f32 invS = 1.0f / S;
//
//			Orientation = XQuaternion((m[6] - m[9]) * invS,
//				(m[8] - m[2]) * invS,
//				(m[1] - m[4]) * invS,
//				0.25f * S);
//		}
//		else if (m[0] > m[5] && m[0] > m[10])
//		{
//			const f32 S = sqrtf(1.0f + m[0] - m[5] - m[10]) * 2.0f;
//			const f32 invS = 1.0f / S;
//
//			Orientation = XQuaternion(0.25f * S,
//				(m[1] + m[4]) * invS,
//				(m[8] + m[2]) * invS,
//				(m[6] - m[9]) * invS);
//		}
//		else if (m[5] > m[10])
//		{
//			const f32 S = sqrt(1.0f + m[5] - m[0] - m[10]) * 2.0f;
//			const f32 invS = 1.0f / S;
//
//			Orientation = XQuaternion((m[1] + m[4]) * invS,
//				0.25f * S,
//				(m[6] + m[9]) * invS,
//				(m[8] - m[2]) * invS);
//		}
//		else
//		{
//			const f32 S = sqrt(1.0f + m[10] - m[0] - m[5]) * 2.0f;
//			const f32 invS = 1.0f / S;
//
//			Orientation = XQuaternion((m[8] + m[2]) * invS,
//				(m[6] + m[9]) * invS,
//				0.25f * S,
//				(m[1] - m[4]) * invS);
//		}
//
//		return Orientation;
//	}
//
//
//	XMatrix4x4&
//		XMatrix4x4::SetOrientation(
//		const XQuaternion& Orientation
//		)
//	{
//		__m128 t0, t1;
//
//		//
//		// m[  0 ] = 1.0f - ((yy + zz) * 2.0f);
//		// m[  1 ] =        ((xy - zw) * 2.0f);
//		// m[  2 ] =        ((xz + yw) * 2.0f);
//		//
//		t0 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 0, 0, 1)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 2, 1, 1)));
//		t1 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 1, 2, 2)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 3, 3, 2)));
//		t1 = _mm_xor_ps(t1, XVector::sm_kxNegateY);
//
//		t0 = _mm_mul_ps(_mm_add_ps(t0, t1), XVector::sm_kxTwo);
//		t0 = _mm_add_ps(_mm_xor_ps(t0, XVector::sm_kxNegateX), XVector::sm_kxUnitX);
//
//		m_Matrix[0] = _mm_and_ps(t0, XVector::sm_kxTranslationMask);
//
//		//
//		// m[  4 ] =        ((xy + zw) * 2.0f);
//		// m[  5 ] = 1.0f - ((xx + zz) * 2.0f);
//		// m[  6 ] =        ((yz - xw) * 2.0f);
//		//
//		t0 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 1, 0, 0)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 2, 0, 1)));
//		t1 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 0, 2, 2)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 3, 2, 3)));
//		t1 = _mm_xor_ps(t1, XVector::sm_kxNegateZ);
//
//		t0 = _mm_mul_ps(_mm_add_ps(t0, t1), XVector::sm_kxTwo);
//		t0 = _mm_add_ps(_mm_xor_ps(t0, XVector::sm_kxNegateY), XVector::sm_kxUnitY);
//
//		m_Matrix[1] = _mm_and_ps(t0, XVector::sm_kxTranslationMask);
//
//		//
//		// m[  8 ] =        ((xz - yw) * 2.0f);
//		// m[  9 ] =        ((yz + xw) * 2.0f);
//		// m[ 10 ] = 1.0f - ((xx + yy) * 2.0f);
//		//
//		t0 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 0, 1, 0)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 0, 2, 2)));
//		t1 = _mm_mul_ps(_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 1, 0, 1)),
//			_mm_shuffle_ps(Orientation, Orientation, _MM_SHUFFLE(3, 1, 3, 3)));
//		t1 = _mm_xor_ps(t1, XVector::sm_kxNegateX);
//
//		t0 = _mm_mul_ps(_mm_add_ps(t0, t1), XVector::sm_kxTwo);
//		t0 = _mm_add_ps(_mm_xor_ps(t0, XVector::sm_kxNegateZ), XVector::sm_kxUnitZ);
//
//		m_Matrix[2] = _mm_and_ps(t0, XVector::sm_kxTranslationMask);
//
//		return *this;
//	}
//
//#if 0
//
//	// This code is taken from 
//	// Intel AP-929 Streaming SIMD Extensions - Inverse of 6x6 Matrix
//	// 1999
//
//#pragma warning( push )
//#pragma warning( disable : 4700 )
//	XMatrix4x4&
//		XMatrix4x4::Inverse(Out XMatrix4x4& src)
//	{
//		__m128 minor0, minor1, minor2, minor3;
//		__m128 row0, row1, row2, row3;
//		__m128 det, tmp1;
//
//		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src.m_Matrix)), (__m64*)(src.m_Matrix + 4));
//		row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src.m_Matrix + 8)), (__m64*)(src.m_Matrix + 12));
//		row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
//		row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
//		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src.m_Matrix + 2)), (__m64*)(src.m_Matrix + 6));
//		row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src.m_Matrix + 10)), (__m64*)(src.m_Matrix + 14));
//		row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
//		row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(row2, row3);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		minor0 = _mm_mul_ps(row1, tmp1);
//		minor1 = _mm_mul_ps(row0, tmp1);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
//		minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
//		minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(row1, row2);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
//		minor3 = _mm_mul_ps(row0, tmp1);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
//		minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
//		minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		row2 = _mm_shuffle_ps(row2, row2, 0x4E);
//		minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
//		minor2 = _mm_mul_ps(row0, tmp1);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
//		minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
//		minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(row0, row1);
//
//
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
//		minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
//		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(row0, row3);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
//		minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
//		minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
//		// -----------------------------------------------
//		tmp1 = _mm_mul_ps(row0, row2);
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
//		minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
//		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
//		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
//		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
//		minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
//		// -----------------------------------------------
//		det = _mm_mul_ps(row0, minor0);
//		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
//		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
//		tmp1 = _mm_rcp_ss(det);
//		det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
//		det = _mm_shuffle_ps(det, det, 0x00);
//		minor0 = _mm_mul_ps(det, minor0);
//		_mm_storel_pi((__m64*)(src.m_Matrix), minor0);
//		_mm_storeh_pi((__m64*)(src.m_Matrix + 2), minor0);
//		minor1 = _mm_mul_ps(det, minor1);
//		_mm_storel_pi((__m64*)(src.m_Matrix + 4), minor1);
//		_mm_storeh_pi((__m64*)(src.m_Matrix + 6), minor1);
//		minor2 = _mm_mul_ps(det, minor2);
//		_mm_storel_pi((__m64*)(src.m_Matrix + 8), minor2);
//		_mm_storeh_pi((__m64*)(src.m_Matrix + 10), minor2);
//		minor3 = _mm_mul_ps(det, minor3);
//		_mm_storel_pi((__m64*)(src.m_Matrix + 12), minor3);
//		_mm_storeh_pi((__m64*)(src.m_Matrix + 14), minor3);
//
//		return src;
//	}
//#pragma warning( pop )
//}
//
//#endif
//}