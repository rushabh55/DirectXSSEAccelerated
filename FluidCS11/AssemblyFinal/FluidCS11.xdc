<?xml version="1.0"?><doc>
<members>
<member name="T:Math.Angle" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\macros.h" line="80">
<summary>
  Provides some functionality for dealing with angles.
</summary>
</member>
<member name="M:GetY(__m128)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="40">
<summary>
  Returns the y value of the vector.
</summary>
<returns>The y value of the vector.</returns>
</member>
<member name="M:GetZ(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="49">
<summary>
  Returns the z value of the vector.
</summary>
<returns>The z value of the vector.</returns>
</member>
<member name="M:GetW(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="58">
<summary>
  Returns the y value of the vector.
</summary>
<returns>The w value of the vector.</returns>
</member>
<member name="M:_mm_add3_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="74">
<summary>
  Convenience function for adding 3 __m128 types.
</summary>
<param name="a">The first variable to add.</param>
<param name="b">The second variable to add.</param>
<param name="c">The third variable to add.</param>
<returns>The three way add result.</returns>
</member>
<member name="M:_mm_add4_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="87">
<summary>
  Convenience function for adding 4 __m128 types.
</summary>
<param name="a">The first variable to add.</param>
<param name="b">The second variable to add.</param>
<param name="c">The third variable to add.</param>
<param name="d">The fourth variable to add.</param>
<returns>The four way add result.</returns>
</member>
<member name="M:_mm_div_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\new scratch\fluidcs11\constants.h" line="102">
<summary>
  Divides 2 __m128 types and zeroes out indeterminate values caused by divide-by-zero.
</summary>
<remarks>This function is used when masking divide-by-zero.</remarks>
<param name="a">The dividend.</param>
<param name="b">The divisor.</param>
<returns>The quotient.</returns>
</member>
</members>
</doc>