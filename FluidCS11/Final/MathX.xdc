<?xml version="1.0"?><doc>
<members>
<member name="T:Math.Angle" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\macros.h" line="80">
<summary>
  Provides some functionality for dealing with angles.
</summary>
</member>
<member name="M:_mm_add3_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="28">
<summary>
  Convenience function for adding 3 __m128 types.
</summary>
<param name="a">The first variable to add.</param>
<param name="b">The second variable to add.</param>
<param name="c">The third variable to add.</param>
<returns>The three way add result.</returns>
</member>
<member name="M:_mm_add4_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="41">
<summary>
  Convenience function for adding 4 __m128 types.
</summary>
<param name="a">The first variable to add.</param>
<param name="b">The second variable to add.</param>
<param name="c">The third variable to add.</param>
<param name="d">The fourth variable to add.</param>
<returns>The four way add result.</returns>
</member>
<member name="M:_mm_div_ps_composite(__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,__m128!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="56">
<summary>
  Divides 2 __m128 types and zeroes out indeterminate values caused by divide-by-zero.
</summary>
<remarks>This function is used when masking divide-by-zero.</remarks>
<param name="a">The dividend.</param>
<param name="b">The divisor.</param>
<returns>The quotient.</returns>
</member>
<member name="M:Math.XVector.new(System.UInt32)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="89">
<summary>
  Operator new override for allocation of SSE aligned memory.
</summary>
<param name="Size">The size to allocate.</param>
<returns>A pointer to the allocated memory.</returns>
</member>
<member name="M:Math.XVector.delete(System.Void*)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="99">
<summary>
  Operator delete override for deallocation of SSE aligned memory.
</summary>
<param name="p">The pointer to deallocate.</param>
</member>
<member name="M:Math.XVector.op_Implicit~__m128!System.Runtime.CompilerServices.IsConst" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="108">
<summary>
  Provides a const cast to a __m128.
</summary>
<returns>This vector as a __m128.</returns>
</member>
<member name="M:Math.XVector.GetX" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="117">
<summary>
  Returns the x value of the vector.
</summary>
<returns>The x value of the vector.</returns>
</member>
<member name="M:Math.XVector.GetY" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="128">
<summary>
  Returns the y value of the vector.
</summary>
<returns>The y value of the vector.</returns>
</member>
<member name="M:Math.XVector.GetZ" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="139">
<summary>
  Returns the z value of the vector.
</summary>
<returns>The z value of the vector.</returns>
</member>
<member name="M:Math.XVector.GetW" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="150">
<summary>
  Returns the y value of the vector.
</summary>
<returns>The w value of the vector.</returns>
</member>
<member name="T:Math.XScalar" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="183">
<summary>
  A convenience class for doing scalar operations with the SSE vector classes.
</summary>
</member>
<member name="M:Math.XScalar.#ctor" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="192">
<summary>
  Constructor.
</summary>
</member>
<member name="M:Math.XScalar.#ctor(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="197">
<summary>
  Constructor.
</summary>
<param name="s">A scalar value.</param>
</member>
<member name="M:Math.XScalar.#ctor(__m128)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="206">
<summary>
  Constructor.
</summary>
<param name="x">A broadcasted scalar value.</param>
</member>
<member name="M:Math.XScalar.op_Implicit~System.Single" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="218">
<summary>
  Provides a cast to an f32.
</summary>
<returns>Ths XScalar as an f32.</returns>
</member>
<member name="T:Math.XVector3" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="232">
<summary>
  Provides SSE functionality for a 3D vector.
</summary>
</member>
<member name="M:Math.XVector3.#ctor" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="241">
<summary>
  Constructor.
</summary>
</member>
<member name="M:Math.XVector3.#ctor(System.Single*)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="246">
<summary>
  Constructor.
</summary>
<param name="v">A vector in array form.</param>
</member>
<member name="M:Math.XVector3.#ctor(__m128)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="256">
<summary>
  Constructor.
</summary>
<param name="x">A vector in __m128 form.</param>
</member>
<member name="M:Math.XVector3.#ctor(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="265">
<summary>
  Constructor.
</summary>
<param name="f">The value to broadcast.</param>
</member>
<member name="M:Math.XVector3.#ctor(System.Single,System.Single,System.Single)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="274">
<summary>
  Constructor.
</summary>
<param name="x">The x value.</param>
<param name="y">The y value.</param>
<param name="z">The z value.</param>
</member>
<member name="M:Math.XVector3.op_AdditionAssignment(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="282">
<summary>
  Functionality for adding two vectors with assignment.
</summary>
<param name="a">The vector to add to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_SubtractionAssignment(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="293">
<summary>
  Functionality for subtracting two vectors with assignment.
</summary>
<param name="a">The vector to subtract from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_MultiplicationAssignment(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="304">
<summary>
  Functionality for multiplying a vector with a scalar with assignment.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_MultiplicationAssignment(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="315">
<summary>
  Functionality for multiplying a vector with a scalar with assignment.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_DivisionAssignment(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="326">
<summary>
  Functionality for dividing a vector with a scalar with assignment.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_DivisionAssignment(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="338">
<summary>
  Functionality for dividing a vector with a scalar with assignment.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector3.op_Addition(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="350">
<summary>
  Functionality for adding two vectors.
</summary>
<param name="a">The vector to add to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Subtraction(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="360">
<summary>
  Functionality for subtracting two vectors.
</summary>
<param name="a">The vector to subtract from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Multiply(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="370">
<summary>
  Functionality for multiplying a vector with a scalar.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Multiply(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="380">
<summary>
  Functionality for multiplying a vector with a scalar.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Division(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="390">
<summary>
  Functionality for dividing a vector with a scalar.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Division(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="401">
<summary>
  Functionality for dividing a vector with a scalar.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector3.op_Equality(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="412">
<summary>
  Functionality for equals.
</summary>
<param name="a">The vector to compare to this vector.</param>
<returns>The result of the comparison.</returns>
</member>
<member name="M:Math.XVector3.op_Inequality(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="422">
<summary>
  Functionality for not equals.
</summary>
<param name="a">The vector to compare to this vector.</param>
<returns>The result of the comparison.</returns>
</member>
<member name="M:Math.XVector3.Dot(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="432">
<summary>
  Returns the dot product of 2 vectors.
</summary>
<param name="a">The other vector.</param>
<returns>The dot product.</returns>
</member>
<member name="M:Math.XVector3.Cross(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="446">
<summary>
  Returns the cross product of 2 vectors.
</summary>
<param name="a">The other vector.</param>
<returns>The cross product.</returns>
</member>
<member name="M:Math.XVector3.Magnitude" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="461">
<summary>
  Returns the magnitude of the vector.
</summary>
<returns>The magnitude of the vector.</returns>
</member>
<member name="M:Math.XVector3.Normalize" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="471">
<summary>
  Normalizes this vector.
</summary>
<returns>A refrence to this vector.</returns>
</member>
<member name="T:Math.XVector4" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="506">
<summary>
  Provides SSE functionality of a 3D vector with a modifier.
</summary>
</member>
<member name="M:Math.XVector4.#ctor" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="515">
<summary>
  Constructor.
</summary>
</member>
<member name="M:Math.XVector4.#ctor(System.Single*)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="520">
<summary>
  Constructor.
</summary>
<param name="v">A vector in array form.</param>
</member>
<member name="M:Math.XVector4.#ctor(__m128)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="529">
<summary>
  Constructor.
</summary>
<param name="x">A vector in __m128 form.</param>
</member>
<member name="M:Math.XVector4.#ctor(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="538">
<summary>
  Constructor.
</summary>
<param name="f">The value to broadcast.</param>
</member>
<member name="M:Math.XVector4.#ctor(System.Single,System.Single,System.Single,System.Single)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="547">
<summary>
  Constructor.
</summary>
<param name="x">The x value.</param>
<param name="y">The y value.</param>
<param name="z">The z value.</param>
<param name="w">The w value.</param>
</member>
<member name="M:Math.XVector4.op_AdditionAssignment(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="556">
<summary>
  Functionality for adding two vectors with assignment.
</summary>
<param name="a">The vector to add to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_SubtractionAssignment(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="567">
<summary>
  Functionality for subtracting two vectors with assignment.
</summary>
<param name="a">The vector to subtract from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_MultiplicationAssignment(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="578">
<summary>
  Functionality for multiplying a vector with a scalar with assignment.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_MultiplicationAssignment(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="589">
<summary>
  Functionality for multiplying a vector with a scalar with assignment.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_DivisionAssignment(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="600">
<summary>
  Functionality for dividing a vector with a scalar with assignment.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_DivisionAssignment(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="612">
<summary>
  Functionality for dividing a vector with a scalar with assignment.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>A reference to this vector.</returns>
</member>
<member name="M:Math.XVector4.op_Addition(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="624">
<summary>
  Functionality for adding two vectors.
</summary>
<param name="a">The vector to add to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Subtraction(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="634">
<summary>
  Functionality for subtracting two vectors.
</summary>
<param name="a">The vector to subtract from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Multiply(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="644">
<summary>
  Functionality for multiplying a vector with a scalar.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Multiply(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="654">
<summary>
  Functionality for multiplying a vector with a scalar.
</summary>
<param name="s">The scalar to multiply to this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Division(Math.XScalar!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="664">
<summary>
  Functionality for dividing a vector with a scalar.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Division(System.Single)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="675">
<summary>
  Functionality for dividing a vector with a scalar.
</summary>
<remarks>Divide by zero needs to be masked.</remarks>
<param name="s">The scalar to divide from this vector.</param>
<returns>The new vector created by this operation.</returns>
</member>
<member name="M:Math.XVector4.op_Equality(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="686">
<summary>
  Functionality for equals.
</summary>
<param name="a">The vector to compare to this vector.</param>
<returns>The result of the comparison.</returns>
</member>
<member name="M:Math.XVector4.op_Inequality(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="696">
<summary>
  Functionality for not equals.
</summary>
<param name="a">The vector to compare to this vector.</param>
<returns>The result of the comparison.</returns>
</member>
<member name="T:Math.XQuaternion" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="718">
<summary>
  Provides SSE functionality for a quanternion.
</summary>
</member>
<member name="M:Math.XQuaternion.#ctor" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="727">
<summary>
  Constructor.
</summary>
</member>
<member name="M:Math.XQuaternion.#ctor(System.Single*)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="732">
<summary>
  Constructor.
</summary>
<param name="q">A quaternion in array form.</param>
</member>
<member name="M:Math.XQuaternion.#ctor(__m128)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="741">
<summary>
  Constructor.
</summary>
<param name="x">A quaternion in __m128 form.</param>
</member>
<member name="M:Math.XQuaternion.#ctor(System.Single,System.Single,System.Single,System.Single)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="750">
<summary>
  Constructor.
</summary>
<param name="x">The x value.</param>
<param name="y">The y value.</param>
<param name="z">The z value.</param>
<param name="w">The w value.</param>
</member>
<member name="M:Math.XQuaternion.#ctor(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Single)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="759">
<summary>
  Constructor.
</summary>
<param name="Axis">The normalized vector axis."</param>
<param name="Angle">The angle of the vector axis."</param>
<returns>A reference to this quaternion.</returns>
</member>
<member name="M:Math.XQuaternion.#ctor(Math.XVector3*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="767">
<summary>
  Constructor.
</summary>
<param name="Angles">The Euler angles for the quaternion."</param>
<returns>A reference to this quaternion.</returns>
</member>
<member name="M:Math.XQuaternion.op_Multiply(Math.XQuaternion*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="774">
<summary>
  Functionality for multiplying two quaternions.
</summary>
<param name="a">The quaternion to multiply to this quaterion.</param>
<returns>The new quaternion.</returns>
</member>
<member name="M:Math.XQuaternion.op_MultiplicationAssignment(Math.XQuaternion*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="781">
<summary>
  Functionality for multiplying two quaternions with assignment.
</summary>
<param name="a">The quaternion to multiply to this quaterion.</param>
<returns>A reference to this quaternion.</returns>
</member>
<member name="M:Math.XQuaternion.Magnitude" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="792">
<summary>
  Calculates the magnitude of this quaternion.
</summary>
<returns>The magnitude.</returns>
</member>
<member name="M:Math.XQuaternion.Conjugate" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="805">
<summary>
  Calculates the conjugate or inverse of a quaternion.
</summary>
</member>
<member name="M:Math.XQuaternion.Conjugate(Math.XQuaternion*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="814">
<summary>
  Calculates the conjugate or inverse of a quaternion.
</summary>
<param name="a">The quaternion to set as the inverse of this quaternion.</param>
</member>
<member name="T:Math.XMatrix4x4" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="838">
<summary>
  Row major SSE implementation of a 4x4 matrix.
</summary>
</member>
<member name="M:Math.XMatrix4x4.#ctor" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="847">
<summary>
  Constructor.
</summary>
</member>
<member name="M:Math.XMatrix4x4.#ctor(System.Single!System.Runtime.CompilerServices.IsConst*)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="852">
<summary>
  Constructor.
</summary>
<param name="m">A matrix in array form.</param>
</member>
<member name="M:Math.XMatrix4x4.#ctor(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Math.XQuaternion!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="864">
<summary>
  Constructor for a transformation matrix.
</summary>
<param name="Translation">The translation for the matrix.</param>
<param name="Orientation">The orientation for the matrix.</param>
</member>
<member name="M:Math.XMatrix4x4.op_Multiply(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="871">
<summary>
  Vector matrix multiplication.
</summary>
<param name="a">The vector to multiply to this matrix.</param>
<returns>The new vector.</returns>
</member>
<member name="M:Math.XMatrix4x4.op_Multiply(Math.XVector4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="878">
<summary>
  Vector matrix multiplication.
</summary>
<param name="a">The vector to multiply to this matrix.</param>
<returns>The new vector.</returns>
</member>
<member name="M:Math.XMatrix4x4.op_Multiply(Math.XMatrix4x4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="885">
<summary>
  Functionality for multiplying two matrices.
</summary>
<param name="a">The matrix to multiply to this matrix.</param>
<returns>The new matrix.</returns>
</member>
<member name="M:Math.XMatrix4x4.op_MultiplicationAssignment(Math.XMatrix4x4!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="892">
<summary>
  Functionality for multiplying two matrices with assignment.
</summary>
<param name="a">The matrix to multiply to this matrix.</param>
<returns>A reference to this matrix.</returns>
</member>
<member name="M:Math.XMatrix4x4.GetTranslation(Math.XVector3*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="902">
<summary>
  Gets the translation of this matrix.
</summary>
<param name="Translation">A reference to the translation variable to fill in.</param>
<returns>The reference of the passed in translation.</returns>
</member>
<member name="M:Math.XMatrix4x4.GetOrientation(Math.XQuaternion*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="913">
<summary>
  Gets the orientation of this matrix.
</summary>
<param name="Orientation">A reference to the orientation variable to fill in.</param>
<returns>The reference of the passed in orientation.</returns>
</member>
<member name="M:Math.XMatrix4x4.SetTranslation(Math.XVector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="920">
<summary>
  Sets the translation of this matrix.
</summary>
<param name="Translation">A reference to the translation to set this matrix to.</param>
<returns>A reference to this matrix.</returns>
</member>
<member name="M:Math.XMatrix4x4.SetOrientation(Math.XQuaternion!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="932">
<summary>
  Sets the Orientation of this matrix.
</summary>
<param name="Orientation">A reference to the orientation to set this matrix to.</param>
<returns>A reference to this matrix.</returns>
</member>
<member name="M:Math.XMatrix4x4.Inverse(Math.XMatrix4x4*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\engine class\assignment 1\scratch\dxsse\fluidcs11\mathx.h" line="939">
<summary>
  Set the inverse of this matrix.
</summary>
<param name="Inverse">The matrix to set as the inverse.</param>
<returns>A reference to the inverse matrix.</returns>
</member>
</members>
</doc>