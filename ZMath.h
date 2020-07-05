#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <random>

// This is a math library for my namespace ZCPP. This math library
// Comes with multiple vector types and matrix classes. 2D vectors,
// 3D vectors, 4D vectors, 3x3 matricies, and 4x4 matricies. Each
// with their own overloaded operators and math functions. This file
// also comes with some basic math functions and tools. Such as: Pi,
// Random (int, float, float), a conversion of Degrees to Radians,
// and Radians to Degrees. Several base functions (that I made), Swap,
// Clamp, Map, Abs, ToString, and several other useful functions.
// I am still working on this file so updates will come, Expect them soon! :D
// -Zyphery

namespace ZCPP
{
	std::random_device device; std::mt19937 rng(device());
	std::uniform_int_distribution<int32_t> rnd(-2147483647, 2147483647);

	// The constant 𝜋
	const float Pi = 3.1415926535897932;
	// The constant e
	const float e = 2.7182818284590452;

	// Converting Degress to Radians
	const float DegtoRad = Pi * 2. / 360.;
	// Converting Radians to Degrees
	const float RadtoDeg = 1. / DegtoRad;

	// Swap two values with eachother
	template <typename Type> void Swap(Type& Val_A, Type& Val_B) { Type temp = Val_A; Val_A = Val_B; Val_B = temp; }

	// Returns bool if Value is a Whole number
	bool IsWhole(float Value) { return ((Value - int(Value)) == 0); }

	// Value to the Nth power
	float Pow(float Value, float Power) { return pow(Value, Power); }
	// Value to the Nth root
	float Root(float Value, float Root) { if (Root == 0) return Value; else return Pow(Value, 1 / Root); }

	// Returns the greatest integer 
	int Floor(float Value) { if (IsWhole(Value)) return Value; int Ivalue = int(Value); if (Value < 0) return int(Value) - 1; else return int(Value); }

	// Returns the Min of the two, doesn't account if they are equal
	template <typename Type> Type Min(Type Val_A, Type Val_B) { if (Val_A < Val_B) return Val_A; else return Val_B; }
	// Returns the Max of the two, doesn't account if they are equal
	template <typename Type> Type Max(Type Val_A, Type Val_B) { if (Val_A > Val_B) return Val_A; else return Val_B; }

	// Returns the absolute Value of Value
	template <typename Type> Type Abs(Type Value) { if (Value < 0) return -Value; else return Value; }
	// Returns the signed Value of Value
	template <typename Type> Type Sign(Type Value) { if (Value < 0) return Value; else return -Value; }

	// Modulator ( Gets the remainder after a "division" )
	float Mod(float Value, float Modulator) { while (Value >= Modulator) { Value -= Modulator; } return Value; }

	// Factorial cannot go higher than 65
	uint64_t Fac(unsigned short int iter) { uint64_t fac = 1; for (int i = 1; i <= iter && i < 66; i++) fac *= i; return fac; }

	// Get percentage of where value is between min and max
	float PercentagefromValue(float min, float max, float value) { return (value - min) / (max - min); }
	// Get value from percentage between min and max
	float PercentagetoValue(float min, float max, float percentage) { return max * percentage + min; }

	// Clamps any type of Value between min and max
	template <typename Type> Type Clamp(Type min, Type max, Type Value) { if (max < min) Swap(min, max); if (Value < min) return min; else if (Value > max) return max; else return Value; }

	// Maps values from in-min and in-max to out-min and out-max
	template <typename Type> Type Map(Type inMin, Type inMax, Type outMin, Type outMax, Type Value) { /*if (inMax < inMin) Swap(inMin, inMax); if (outMax < outMin) Swap(outMin, outMax);*/ return (Type)PercentagetoValue(outMin, outMax, PercentagefromValue(inMin, inMax, Value)); }

	// Converts the Value into a std::string
	template <typename Type> std::string ToString(Type Value) { return std::to_string(Value); }

	// Sorts an array [ Bubble sort ]
	template <typename Type> void Sort(Type* Array, uint32_t size)
	{
		bool Sorted = false;
		while (!Sorted)
		{
			bool Sortmade = false;
			for (int32_t index = 1; index < size; index++)
			{
				if (Array[index - 1] > Array[index])
				{
					Swap(Array[index], Array[index - 1]);
					Sorted = false;
					Sortmade = true;
				}
				else if (!Sortmade)
					Sorted = true;
			}
		}
	}

	// Reverses an array
	template <typename Type> void Reverse(Type* Array, uint32_t size) { for (int32_t index = 0, revindex = size - 1; index < size / 2; index++, revindex--) { Swap(Array[index], Array[revindex]); } }

	/* Int32 Random ( -2147483647, 2147483647 ) */
	// Returns a random number between -2147483647, 2147483647 in int form
	int32_t Random() { return rnd(rng); }
	// Returns a random number between the min and max in int form
	int32_t Random(int32_t min, int32_t max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_int_distribution<int32_t> nrnd(min, max); return nrnd(rng);
	}

	/* float Random ( -1, 1 ) */
	// 25 decimal point precision
	// Returns a random number between -1 and 1 in float form
	float Randomf() { std::uniform_real_distribution<float> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in float form
	float Randomf(float min, float max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<float> nrnd(min, max); return nrnd(rng);
	}

	/* float Random ( -1, 1 ) */
	// 50 decimal point precision
	// Returns a random number between -1 and 1 in float form
	float Randomd() { std::uniform_real_distribution<float> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in float form
	float Randomd(float min, float max) {
		if (max < min) std::swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<float> nrnd(min, max); return nrnd(rng);
	}

	// Console Log function:

	void Log(const char* c) { printf("%s\n", c); }
	void Log(std::string s) { printf("%s\n", s.c_str()); }

	void Log(int i) { Log(ToString(i)); }
	void Log(long i) { Log(ToString(i)); }
	void Log(long long i) { Log(ToString(i)); }
	void Log(unsigned i) { Log(ToString(i)); }
	void Log(unsigned long i) { Log(ToString(i)); }
	void Log(unsigned long long i) { Log(ToString(i)); }
	void Log(float i) { Log(ToString(i)); }
	void Log(double i) { Log(ToString(i)); }
	void Log(long double i) { Log(ToString(i)); }

	// Vector classes:

	class Vector2D // Vector2D class ( X, Y )
	{
	public:
		float x, y;

		Vector2D() : x(0), y(0) {}
		Vector2D(float _) : x(_), y(_) {}
		Vector2D(float _x, float _y) : x(_x), y(_y) {}

		void operator = (const Vector2D& vec) { x = vec.x; y = vec.y; }

		static float Length(Vector2D A) { return sqrt(A.x * A.x + A.y * A.y); }
		float Length() { return Length(*this); }
		static float Distance(Vector2D A, Vector2D B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }
		static Vector2D Normalize(Vector2D A) { float L = 1 / Length(A); return Vector2D(A.x * L, A.y * L); }
		void Normalize() { *this = Normalize(*this); }
		static Vector2D Abs(Vector2D A) { return Vector2D(ZCPP::Abs(A.x), ZCPP::Abs(A.y)); }
		void Abs() { *this = Abs(*this); }
		Vector2D UnitVector() { return Normalize(*this); }
		static Vector2D Rotate(Vector2D A, float r) { Vector2D V; V.x = A.x * cos(r) - A.y * sin(r); V.y = sin(r) * A.x + cos(r) * A.y; return V; }
		void Rotate(float r) { *this = Rotate(*this, r); }
		static Vector2D Random() { return Normalize(Vector2D(rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector2D A) { return "<" + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return ToString(*this); }

		// Returns the Max of all the x's, and y's
		static Vector2D Max(Vector2D A, Vector2D B) { return Vector2D(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y)); }
		// Returns the Min of all the x's, and y's
		static Vector2D Min(Vector2D A, Vector2D B) { return Vector2D(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y)); }
	};

	// Vector2D Overloaded Operators

	/* Comparison Operators */

	bool operator == (const Vector2D& A, const Vector2D& B) { return (A.x == B.x && A.y == B.y); }
	bool operator <  (const Vector2D& A, const Vector2D& B) { return (A.x < B.x && A.y < B.y); }
	bool operator >  (const Vector2D& A, const Vector2D& B) { return (A.x > B.x&& A.y > B.y); }
	bool operator <= (const Vector2D& A, const Vector2D& B) { return (A.x <= B.x && A.y <= B.y); }
	bool operator >= (const Vector2D& A, const Vector2D& B) { return (A.x >= B.x && A.y >= B.y); }
	bool operator != (const Vector2D& A, const Vector2D& B) { return (A.x != B.x && A.y != B.y); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Vector2D& A, const float& B) { return (A.x == B && A.y == B); }
	bool operator <  (const Vector2D& A, const float& B) { return (A.x < B && A.y < B); }
	bool operator >  (const Vector2D& A, const float& B) { return (A.x > B&& A.y > B); }
	bool operator <= (const Vector2D& A, const float& B) { return (A.x <= B && A.y <= B); }
	bool operator >= (const Vector2D& A, const float& B) { return (A.x >= B && A.y >= B); }
	bool operator != (const Vector2D& A, const float& B) { return (A.x != B && A.y != B); }

	// Add a Vector2D to a Vector2D
	Vector2D operator + (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x + B.x, A.y + B.y); }

	// Subtract a Vector2D by a Vector2D
	Vector2D operator - (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x - B.x, A.y - B.y); }

	// Multiply a Vector2D by a Vector2D in the form of Ax * Bx, Ay * By
	Vector2D operator * (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x * B.x, A.y * B.y); }

	// Divide a Vector2D by a Vector2D in the form of Ax / Bx, Ay / By
	Vector2D operator / (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x / B.x, A.y / B.y); }

	// Multiply a Vector2D by a float
	Vector2D operator * (const Vector2D& A, const float& B) { return Vector2D(A.x * B, A.y * B); }
	// Multiply a Vector2D by a float
	Vector2D operator * (const float& A, const Vector2D& B) { return(B * A); }

	// Divide a Vector2D by a float
	Vector2D operator / (const Vector2D& A, const float& B) { return Vector2D(A.x / B, A.y / B); }
	// Divide a Vector2D by a float
	Vector2D operator / (const float& A, const Vector2D& B) { return (B / A); }

	Vector2D& operator += (Vector2D& A, const Vector2D& B) { A = A + B; return A; }
	Vector2D& operator -= (Vector2D& A, const Vector2D& B) { A = A - B; return A; }
	Vector2D& operator *= (Vector2D& A, const Vector2D& B) { A = A * B; return A; }
	Vector2D& operator *= (Vector2D& A, const float& B) { A = A * B; return A; }
	Vector2D& operator /= (Vector2D& A, const Vector2D& B) { A = A / B; return A; }
	Vector2D& operator /= (Vector2D& A, const float& B) { A = A / B; return A; }

	// Normalizes Vector2D A to a unit Vector
	Vector2D operator ~ (Vector2D& A) { return Vector2D::Normalize(A); }

	// Absolute value of Vector2D A
	Vector2D operator ! (Vector2D& A) { A.Abs();  return A; }

	// Vector2D Math functions

	// Dot Product of Vector2D
	float DP2D(Vector2D A, Vector2D B) { Vector2D C = A * B; return C.x + C.y; }
	// Cross Product of Vector2D returning a float
	float CP2D(Vector2D A, Vector2D B) { return (A.x * B.y) - (A.y * B.x); }
	// Cross Product of Vector2D returning a Vector2D
	Vector2D CP2D(Vector2D A) { return Vector2D(A.y, -A.x); }
	// Angle in radians between two Vector2D
	float Angle(Vector2D A, Vector2D B) { if (A < B) Swap(A, B); return 2 * Abs(atan2(B.x - A.x, B.y - A.y)); }



	class Vector3D // Vector3D class ( X, Y, Z )
	{
	public:
		float x, y, z;

		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(float _) : x(_), y(_), z(_) {}
		Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		Vector3D(Vector2D _V, float _z) : x(_V.x), y(_V.y), z(_z) {}

		void operator = (const Vector3D& vec) { x = vec.x; y = vec.y; z = vec.z; }

		/* Casting Vector3D to Vector2D
		x, y, components are saved */
		operator Vector2D() const { return Vector2D(x, y); }

		static const Vector2D Vector2(Vector3D V) { return Vector2D(V.x, V.y); }
		Vector2D Vector2() const { return Vector2(*this); }

		static Vector2D To2D(Vector3D A) { return Vector2D(A.x, A.y); }
		Vector2D To2D() { return To2D(*this); }
		static float Length(Vector3D A) { return sqrt(A.x * A.x + A.y * A.y + A.z * A.z); }
		float Length() { return Length(*this); }
		static float Distance(Vector3D A, Vector3D B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2)); }
		static Vector3D Normalize(Vector3D A) { float L = 1 / Length(A); return Vector3D(A.x * L, A.y * L, A.z * L); }
		void Normalize() { *this = Normalize(*this); }
		Vector3D UnitVector() { return Normalize(*this); }
		static Vector3D Abs(Vector3D A) { return Vector3D(ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z)); }
		void Abs() { *this = Abs(*this); }
		static Vector3D Random() { return Normalize(Vector3D(rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector3D A) { return "<" + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ", " + ZCPP::ToString(A.z) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return ToString(*this); }

		// Returns the Max of all the x's, y's, and z's
		static Vector3D Max(Vector3D A, Vector3D B) { return Vector3D(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y), ZCPP::Max(A.z, B.z)); }
		// Returns the Min of all the x's, y's, and z's
		static Vector3D Min(Vector3D A, Vector3D B) { return Vector3D(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y), ZCPP::Min(A.z, B.z)); }
	};

	// Vector3D Overloaded Operators

	/* Comparison Operators */

	bool operator == (const Vector3D& A, const Vector3D& B) { return (A.x == B.x && A.y == B.y && A.z == B.z); }
	bool operator <  (const Vector3D& A, const Vector3D& B) { return (A.x < B.x && A.y < B.y && A.z < B.z); }
	bool operator >  (const Vector3D& A, const Vector3D& B) { return (A.x > B.x&& A.y > B.y&& A.z > B.z); }
	bool operator <= (const Vector3D& A, const Vector3D& B) { return (A.x <= B.x && A.y <= B.y && A.x <= B.x); }
	bool operator >= (const Vector3D& A, const Vector3D& B) { return (A.x >= B.x && A.y >= B.y && A.x >= B.x); }
	bool operator != (const Vector3D& A, const Vector3D& B) { return (A.x != B.x && A.y != B.y && A.x != B.x); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Vector3D& A, const float& B) { return (A.x == B && A.y == B && A.z == B); }
	bool operator <  (const Vector3D& A, const float& B) { return (A.x < B && A.y < B && A.z < B); }
	bool operator >  (const Vector3D& A, const float& B) { return (A.x > B&& A.y > B&& A.z > B); }
	bool operator <= (const Vector3D& A, const float& B) { return (A.x <= B && A.y <= B && A.x <= B); }
	bool operator >= (const Vector3D& A, const float& B) { return (A.x >= B && A.y >= B && A.x >= B); }
	bool operator != (const Vector3D& A, const float& B) { return (A.x != B && A.y != B && A.x != B); }

	// Add a Vector3D to a Vector3D
	Vector3D operator + (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x + B.x, A.y + B.y, A.z + B.z); }

	// Subtract a Vector3D by a Vector3D
	Vector3D operator - (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x - B.x, A.y - B.y, A.z - B.z); }

	// Multiply a Vector3D by a Vector3D in the form of Ax * Bx, Ay * By, Az * Bz
	Vector3D operator * (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x * B.x, A.y * B.y, A.z * B.z); }

	// Divide a Vector3D by a Vector3D in the form of Ax / Bx, Ay / By, Az / Bz
	Vector3D operator / (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x / B.x, A.y / B.y, A.z / B.z); }

	// Multiply a Vector3D by a float
	Vector3D operator * (const Vector3D& A, const float& B) { return Vector3D(A.x * B, A.y * B, A.z * B); }
	// Multiply a Vector3D by a float
	Vector3D operator * (const float& A, const Vector3D& B) { return(B * A); }

	// Divide a Vector3D by a float
	Vector3D operator / (const Vector3D& A, const float& B) { return Vector3D(A.x / B, A.y / B, A.z / B); }
	// Divide a Vector3D by a float
	Vector3D operator / (const float& A, const Vector3D& B) { return (B / A); }

	Vector3D& operator += (Vector3D& A, const Vector3D& B) { A = A + B; return A; }
	Vector3D& operator -= (Vector3D& A, const Vector3D& B) { A = A - B; return A; }
	Vector3D& operator *= (Vector3D& A, const Vector3D& B) { A = A * B; return A; }
	Vector3D& operator *= (Vector3D& A, const float& B) { A = A * B; return A; }
	Vector3D& operator /= (Vector3D& A, const Vector3D& B) { A = A / B; return A; }
	Vector3D& operator /= (Vector3D& A, const float& B) { A = A / B; return A; }

	// Normalizes Vector3D A to a unit Vector
	Vector3D operator ~ (Vector3D& A) { return Vector3D::Normalize(A); }

	// Absolute value of Vector3D A
	Vector3D operator ! (Vector3D& A) { A.Abs();  return A; }

	// Vector3D Math functions

	// Dot Product of Vector3D
	float DP3D(Vector3D A, Vector3D B) { Vector3D C = A * B; return C.x + C.y + C.z; }
	// Cross Product of Vector3D returning a Vector3D
	Vector3D CP3D(Vector3D A, Vector3D B) { Vector3D C; C.x = A.y * B.z - A.z * B.y; C.y = A.z * B.x - A.x * B.z; C.z = A.x * B.y - A.y * B.x; return C; }



	class Quaternion // Quaternion class ( X, Y, Z, W )
	{
	public:
		float x, y, z, w;

		Quaternion() : x(0), y(0), z(0), w(0) {}
		Quaternion(float _) : x(_), y(_), z(_), w(_) {}
		Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

		Quaternion(Vector2D _V, float _z, float _w) : x(_V.x), y(_V.y), z(_z), w(_w) {}
		Quaternion(Vector3D _V, float _w) : x(_V.x), y(_V.y), z(_V.z), w(_w) {}

		void operator = (const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }

		/* Casting Quaternion to Vector2D
		x, y, components are saved */
		operator Vector2D() const { return Vector2D(x, y); }
		/* Casting Quaternion to Vector3D
		x, y, z, components are saved*/
		operator Vector3D() const { return Vector3D(x, y, z); }

		static const Vector2D Vector2(Quaternion Q) { return Vector2D(Q.x, Q.y); }
		Vector2D Vector2() const { return Vector2(*this); }
		static const Vector3D Vector3(Quaternion Q) { return Vector3D(Q.x, Q.y, Q.z); }
		Vector3D Vector3() const { return Vector3(*this); }

		static Vector2D To2D(Quaternion A) { return Vector2D(A.x, A.y); }
		Vector2D To2D() { return To2D(*this); }
		static Vector3D To3D(Quaternion A) { return Vector3D(A.x, A.y, A.z); }
		Vector3D To3D() { return To3D(*this); }
		static float Length(Quaternion A) { return sqrt(A.x * A.x + A.y * A.y + A.z * A.z + A.w * A.w); }
		float Length() { return Length(*this); }
		static float Distance(Quaternion A, Quaternion B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2) + pow(B.w - A.w, 2)); }
		static Quaternion Normalize(Quaternion A) { float L = 1 / Length(A); return Quaternion(A.x * L, A.y * L, A.z * L, A.w * L); }
		void Normalize() { *this = Normalize(*this); }
		Quaternion UnitQuaternion() { return Normalize(*this); }
		static Quaternion Abs(Quaternion A) { return Quaternion(ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z), ZCPP::Abs(A.w)); }
		void Abs() { *this = Abs(*this); }
		static Quaternion Random() { return Normalize(Quaternion(rnd(rng), rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Quaternion into a std::string
		static std::string ToString(Quaternion A) { return "<" + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ", " + ZCPP::ToString(A.z) + ", " + ZCPP::ToString(A.w) + ">"; }
		// Converts this Quaternion into a std::string
		std::string ToString() { return ToString(*this); }

		// Returns the Max of all the w's, x's, y's, and z's
		static Quaternion Max(Quaternion A, Quaternion B) { return Quaternion(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y), ZCPP::Max(A.z, B.z), ZCPP::Max(A.w, B.w)); }
		// Returns the Min of all the w's, x's, y's, and z's			  																				   
		static Quaternion Min(Quaternion A, Quaternion B) { return Quaternion(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y), ZCPP::Min(A.z, B.z), ZCPP::Min(A.w, B.w)); }
	};

	/* Comparison Operators */
	bool operator == (const Quaternion& A, const Quaternion& B) { return (A.x == B.x && A.y == B.y && A.z == B.z && A.w == B.w); }
	bool operator <  (const Quaternion& A, const Quaternion& B) { return (A.x < B.x && A.y < B.y && A.z < B.z && A.w < B.w); }
	bool operator >  (const Quaternion& A, const Quaternion& B) { return (A.x > B.x&& A.y > B.y&& A.z > B.z&& A.w > B.w); }
	bool operator <= (const Quaternion& A, const Quaternion& B) { return (A.x <= B.x && A.y <= B.y && A.x <= B.x && A.w <= B.w); }
	bool operator >= (const Quaternion& A, const Quaternion& B) { return (A.x >= B.x && A.y >= B.y && A.x >= B.x && A.w >= B.w); }
	bool operator != (const Quaternion& A, const Quaternion& B) { return (A.x != B.x && A.y != B.y && A.x != B.x && A.w != B.w); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Quaternion& A, const float& B) { return (A.x == B && A.y == B && A.z == B && A.w == B); }
	bool operator <  (const Quaternion& A, const float& B) { return (A.x < B && A.y < B && A.z < B && A.w < B); }
	bool operator >  (const Quaternion& A, const float& B) { return (A.x > B&& A.y > B&& A.z > B&& A.w > B); }
	bool operator <= (const Quaternion& A, const float& B) { return (A.x <= B && A.y <= B && A.x <= B && A.w <= B); }
	bool operator >= (const Quaternion& A, const float& B) { return (A.x >= B && A.y >= B && A.x >= B && A.w >= B); }
	bool operator != (const Quaternion& A, const float& B) { return (A.x != B && A.y != B && A.x != B && A.w != B); }

	// Add a Quaternion to a Quaternion
	Quaternion operator + (const Quaternion& A, const Quaternion& B) { return Quaternion(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w); }

	// Subtract a Quaternion from a Quaternion
	Quaternion operator - (const Quaternion& A, const Quaternion& B) { return Quaternion(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w); }

	// Multiply a Quaternion by a Quaternion
	Quaternion operator * (const Quaternion& A, const Quaternion& B) { return Quaternion(A.x * B.x, A.y * B.y, A.z * B.z, A.w * B.w); }

	// Divide a Quaternion by a Quaternion
	Quaternion operator / (const Quaternion& A, const Quaternion& B) { return Quaternion(A.x / B.x, A.y / B.y, A.z / B.z, A.w / B.w); }

	// Multiply a Quaternion by a float (Scalar)
	Quaternion operator * (const Quaternion& A, const float& B) { return Quaternion(A.x * B, A.y * B, A.z * B, A.w * B); }
	// Multiply a Quaternion by a float (Scalar)
	Quaternion operator * (const float& A, const Quaternion& B) { return B * A; }

	// Divide a Quaternion by a float (Scalar)
	Quaternion operator / (const Quaternion& A, const float& B) { return Quaternion(A.x / B, A.y / B, A.z / B, A.w / B); }
	// Divide a Quaternion by a float (Scalar)
	Quaternion operator / (const float& A, const Quaternion& B) { return B / A; }

	Quaternion operator += (Quaternion& A, const Quaternion& B) { A = A + B;  return A; }
	Quaternion operator -= (Quaternion& A, const Quaternion& B) { A = A - B;  return A; }
	Quaternion operator *= (Quaternion& A, const Quaternion& B) { A = A * B; return A; }
	Quaternion operator *= (Quaternion& A, const float& B) { A = A * B; return A; }
	Quaternion operator /= (Quaternion& A, const Quaternion& B) { A = A / B; return A; }
	Quaternion operator /= (Quaternion& A, const float& B) { A = A / B; return A; }

	// Normalizes Quaternion A to a unit Quaternion
	Quaternion operator ~ (const Quaternion& A) { return Quaternion::Normalize(A); }

	// Get the Absolute of a Quaternion
	Quaternion operator ! (const Quaternion& A) { return Quaternion::Abs(A); }

	Vector3D RotateVectorbyQuaternion(Quaternion r, Vector3D v)
	{
		Vector3D p = r * 2;
		float xx = r.x * p.x;
		float yy = r.y * p.y;
		float zz = r.z * p.z;
		float xy = r.x * p.y;
		float xz = r.x * p.z;
		float yz = r.y * p.z;
		float wx = r.w * p.x;
		float wy = r.w * p.y;
		float wz = r.w * p.z;

		Vector3D V;
		V.x = (1 - (yy + zz)) * v.x + (xy - wz) * v.y + (xz + wy) * v.z;
		V.y = (xy + wz) * v.x + (1 - (xx + zz)) * v.y + (yz - wx) * v.z;
		V.z = (xz - wy) * v.x + (yz + wx) * v.y + (1 - (xx + yy)) * v.z;
	}

	Vector3D QuaternionToEuler(Quaternion A)
	{
		Vector3D Euler;
		Euler.x = atan2f(2 * (A.w * A.x + A.y * A.z), 1 - 2 * (A.x * A.x + A.y * A.y));

		float p = 2 * (A.w * A.y - A.z * A.x);
		if (Abs(p) >= 1)
			Euler.y = std::copysign(Pi / 2, p);
		else
			Euler.y = asinf(p);

		Euler.z = atan2f(2 * (A.w * A.z + A.x * A.y), 1 - 2 * (A.y * A.y + A.z * A.z));

		return Euler;
	}

	Quaternion EulerToQuaternion(Vector3D A)
	{
		Quaternion quat;
		float cy = cosf(A.z / 2);
		float sy = sinf(A.z / 2);
		float cp = cosf(A.y / 2);
		float sp = sinf(A.y / 2);
		float cr = cosf(A.x / 2);
		float sr = sinf(A.x / 2);

		quat.w = cr * cp * cy + sr * sp * sy;
		quat.x = sr * cp * cy - cr * sp * sy;
		quat.y = cr * sp * cy + sr * cp * sy;
		quat.z = cr * cp * sy - sr * sp * cy;

		return quat;
	}

	Quaternion Conjugate(Quaternion q)
	{
		return Quaternion(q.To3D() * -1, q.w);
	}

	Quaternion Multiply(Quaternion A, Quaternion B)
	{
		float w = A.w * B.w - A.x * B.x - A.y * B.y - A.z * B.z;
		float x = A.w * B.x + A.x * B.w + A.y * B.z - A.z * B.y;
		float y = A.w * B.y - A.x * B.z + A.y * B.w + A.z * B.x;
		float z = A.w * B.z + A.x * B.y - A.y * B.x + A.z * B.w;

		/*

		ww - xx - yy - zz
		wx + xw + yz - zy
		wy - xz + yw + zx
		wz + xy - yx + zw

		*/

		return Quaternion(x, y, z, w);
	}

	Quaternion RotateVector(Vector3D Vector, Vector3D Axis, float r)
	{
		Quaternion q = Quaternion(Axis.UnitVector() * sinf(r / 2), cosf(r / 2));
		Quaternion VectorP = Multiply(Multiply(q, Quaternion(Vector, 0)), Conjugate(q));

		return VectorP;
	}


	/* Just some personal notes:
	If w == 1, then the vector (x,y,z,1) is a position in space.
	If w == 0, then the vector (x,y,z,0) is a direction.
	*/


	class Matrix3 // Matrix3 Class ( 3 x 3 )
	{
	public:
		float M[3][3] = { 0 };

		void operator = (const Matrix3& m) { for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) this->M[i][j] = m.M[i][j]; }

		static Matrix3 Identity() { Matrix3 M;  M.M[0][0] = 1; M.M[1][1] = 1; M.M[2][2] = 1; return M; }

		static std::string ToString(Matrix3 A) { return "< 0: " + ZCPP::ToString(A.M[0][0]) + ", " + ZCPP::ToString(A.M[0][1]) + ", " + ZCPP::ToString(A.M[0][2]) + " 1: " + ZCPP::ToString(A.M[1][0]) + ", " + ZCPP::ToString(A.M[1][1]) + ", " + ZCPP::ToString(A.M[1][2]) + " 2: " + ZCPP::ToString(A.M[2][0]) + ", " + ZCPP::ToString(A.M[2][1]) + ", " + ZCPP::ToString(A.M[2][2]) + " >"; }
		std::string ToString() { return ToString(*this); }

		// Non-real functions
		// Add two 3x3 Matricies
		static Matrix3 Add(Matrix3 A, Matrix3 B)
		{
			Matrix3 C;
			C.M[0][0] = A.M[0][0] + B.M[0][0]; C.M[0][1] = A.M[0][1] + B.M[0][1]; C.M[0][2] = A.M[0][2] + B.M[0][2];
			C.M[1][0] = A.M[1][0] + B.M[1][0]; C.M[1][1] = A.M[1][1] + B.M[1][1]; C.M[1][2] = A.M[1][2] + B.M[1][2];
			C.M[2][0] = A.M[2][0] + B.M[2][0]; C.M[2][1] = A.M[2][1] + B.M[2][1]; C.M[2][2] = A.M[2][2] + B.M[2][2];
			return C;
		}

		// Subtract two 3x3 Matricies
		static Matrix3 Subtract(Matrix3 A, Matrix3 B)
		{
			Matrix3 C;
			C.M[0][0] = A.M[0][0] - B.M[0][0]; C.M[0][1] = A.M[0][1] - B.M[0][1]; C.M[0][2] = A.M[0][2] - B.M[0][2];
			C.M[1][0] = A.M[1][0] - B.M[1][0]; C.M[1][1] = A.M[1][1] - B.M[1][1]; C.M[1][2] = A.M[1][2] - B.M[1][2];
			C.M[2][0] = A.M[2][0] - B.M[2][0]; C.M[2][1] = A.M[2][1] - B.M[2][1]; C.M[2][2] = A.M[2][2] - B.M[2][2];
			return C;
		}

		// Real functions
		// Multiply two 3x3 Matricies
		static Matrix3 Multiply(Matrix3 A, Matrix3 B)
		{
			Matrix3 C;
			C.M[0][0] = A.M[0][0] * B.M[0][0] + A.M[0][1] * B.M[1][0] + A.M[0][2] * B.M[2][0];
			C.M[0][1] = A.M[0][0] * B.M[0][1] + A.M[0][1] * B.M[1][1] + A.M[0][2] * B.M[2][1];
			C.M[0][2] = A.M[0][0] * B.M[0][2] + A.M[0][1] * B.M[1][2] + A.M[0][2] * B.M[2][2];

			C.M[1][0] = A.M[1][0] * B.M[0][0] + A.M[1][1] * B.M[1][0] + A.M[1][2] * B.M[2][0];
			C.M[1][1] = A.M[1][0] * B.M[0][1] + A.M[1][1] * B.M[1][1] + A.M[1][2] * B.M[2][1];
			C.M[1][2] = A.M[1][0] * B.M[0][2] + A.M[1][1] * B.M[1][2] + A.M[1][2] * B.M[2][2];

			C.M[2][0] = A.M[2][0] * B.M[0][0] + A.M[2][1] * B.M[1][0] + A.M[2][2] * B.M[2][0];
			C.M[2][1] = A.M[2][0] * B.M[0][1] + A.M[2][1] * B.M[1][1] + A.M[2][2] * B.M[2][1];
			C.M[2][2] = A.M[2][0] * B.M[0][2] + A.M[2][1] * B.M[1][2] + A.M[2][2] * B.M[2][2];
			return C;
		}

		// Multiply a Vector3D by a 3x3 Matrix
		static Vector3D Multiply(Matrix3 M, Vector3D V)
		{
			Vector3D NewV;
			NewV.x = V.x * M.M[0][0] + V.y * M.M[0][1] + V.z * M.M[0][2];
			NewV.y = V.x * M.M[1][0] + V.y * M.M[1][1] + V.z * M.M[1][2];
			NewV.z = V.x * M.M[2][0] + V.y * M.M[2][1] + V.z * M.M[2][2];
			return NewV;
		}

		// Multiply a Vector2D by a 3x3 Matrix
		static Vector3D Multiply(Matrix3 M, Vector2D V)
		{
			return Multiply(M, Vector3D(V.x, V.y, 1));
		}

		// Divide two 3x3 Matricies
		static Matrix3 Divide(Matrix3 A, Matrix3 B)
		{
			Matrix3 C;
			C.M[0][0] = A.M[0][0] / B.M[0][0] + A.M[0][1] / B.M[1][0] + A.M[0][2] / B.M[2][0];
			C.M[0][1] = A.M[0][0] / B.M[0][1] + A.M[0][1] / B.M[1][1] + A.M[0][2] / B.M[2][1];
			C.M[0][2] = A.M[0][0] / B.M[0][2] + A.M[0][1] / B.M[1][2] + A.M[0][2] / B.M[2][2];

			C.M[1][0] = A.M[1][0] / B.M[0][0] + A.M[1][1] / B.M[1][0] + A.M[1][2] / B.M[2][0];
			C.M[1][1] = A.M[1][0] / B.M[0][1] + A.M[1][1] / B.M[1][1] + A.M[1][2] / B.M[2][1];
			C.M[1][2] = A.M[1][0] / B.M[0][2] + A.M[1][1] / B.M[1][2] + A.M[1][2] / B.M[2][2];

			C.M[2][0] = A.M[2][0] / B.M[0][0] + A.M[2][1] / B.M[1][0] + A.M[2][2] / B.M[2][0];
			C.M[2][1] = A.M[2][0] / B.M[0][1] + A.M[2][1] / B.M[1][1] + A.M[2][2] / B.M[2][1];
			C.M[2][2] = A.M[2][0] / B.M[0][2] + A.M[2][1] / B.M[1][2] + A.M[2][2] / B.M[2][2];
			return C;
		}

		// Divide a Vector3D by a 3x3 Matrix
		static Vector3D Divide(Matrix3 M, Vector3D V)
		{
			Vector3D NewV;
			NewV.x = M.M[0][0] / V.x + M.M[0][1] / V.y + M.M[0][2] / V.z;
			NewV.y = M.M[1][0] / V.x + M.M[1][1] / V.y + M.M[1][2] / V.z;
			NewV.z = M.M[2][0] / V.x + M.M[2][1] / V.y + M.M[2][2] / V.z;
			return NewV;
		}

		// Divide a Vector2D by a 3x3 Matrix
		static Vector3D Divide(Matrix3 M, Vector2D V) { return Divide(M, Vector3D(V.x, V.y, 1)); }

		// Rotate a Vector2D by r
		static Vector2D Rotate(float r, Vector2D V)
		{
			Matrix3 M = Matrix3::Identity();
			M.M[0][0] = cosf(r);
			M.M[0][1] = -sinf(r);
			M.M[1][0] = sinf(r);
			M.M[1][1] = cosf(r);
			return Multiply(M, V).To2D();
		}
	};

	// Add two 3x3 Matricies
	Matrix3 operator + (const Matrix3& A, const Matrix3& B) { return Matrix3::Add(A, B); }
	// Subtract two 3x3 Matricies
	Matrix3 operator - (const Matrix3& A, const Matrix3& B) { return Matrix3::Subtract(A, B); }

	// Multiply two 3x3 Matricies
	Matrix3 operator * (const Matrix3& A, const Matrix3& B) { return Matrix3::Multiply(A, B); }

	// Multiply a Vector3D by a 3x3 Matrix
	Vector3D operator * (const Matrix3& A, const Vector3D& B) { return Matrix3::Multiply(A, B); }
	Vector3D operator * (const Vector3D& A, const Matrix3& B) { return Matrix3::Multiply(B, A); }

	// Multiply a Vector2D by a 3x3 Matrix
	Vector3D operator * (const Matrix3& A, const Vector2D& B) { return Matrix3::Multiply(A, B); }
	Vector3D operator * (const Vector2D& A, const Matrix3& B) { return Matrix3::Multiply(B, A); }

	// Divide two 3x3 Matricies
	Matrix3 operator / (const Matrix3& A, const Matrix3& B) { return Matrix3::Divide(A, B); }

	// Divide a Vector3D by a 3x3 Matrix
	Vector3D operator / (const Matrix3& A, const Vector3D& B) { return Matrix3::Divide(A, B); }
	Vector3D operator / (const Vector3D& A, const Matrix3 B) { return Matrix3::Divide(B, A); }

	// Divide a Vector2D by a 3x3 Matrix
	Vector3D operator / (const Matrix3& A, const Vector2D& B) { return Matrix3::Divide(A, B); }
	Vector3D operator / (const Vector2D& A, const Matrix3 B) { return Matrix3::Divide(B, A); }

	Matrix3 operator *= (Matrix3& A, const Matrix3& B) { A = A * B; return A; }
	Matrix3 operator /= (Matrix3& A, const Matrix3& B) { A = A / B; return A; }
	Vector3D operator *= (Vector3D& A, const Matrix3& B) { A = A * B; return A; }
	Vector3D operator *= (Vector2D& A, const Matrix3& B) { return Matrix3::Multiply(B, A); }
	Vector3D operator /= (Vector3D& A, const Matrix3& B) { A = A / B; return A; }
	Vector3D operator /= (Vector2D& A, const Matrix3& B) { return Matrix3::Divide(B, A); }



	class Matrix4 // Matrix4 Class ( 4 x 4 )
	{
	public:
		float M[4][4] = { 0 };

		void operator = (const Matrix4& m) { for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) this->M[i][j] = m.M[i][j]; }

		static Matrix4 Identity() { Matrix4 M;  M.M[0][0] = 1; M.M[1][1] = 1; M.M[2][2] = 1; M.M[3][3] = 1; return M; }

		static std::string ToString(Matrix4 A) { return "< 0: " + ZCPP::ToString(A.M[0][0]) + ", " + ZCPP::ToString(A.M[0][1]) + ", " + ZCPP::ToString(A.M[0][2]) + ", " + ZCPP::ToString(A.M[0][3]) + "   1: " + ZCPP::ToString(A.M[1][0]) + ", " + ZCPP::ToString(A.M[1][1]) + ", " + ZCPP::ToString(A.M[1][2]) + ", " + ZCPP::ToString(A.M[1][3]) + "   2: " + ZCPP::ToString(A.M[2][0]) + ", " + ZCPP::ToString(A.M[2][1]) + ", " + ZCPP::ToString(A.M[2][2]) + ", " + ZCPP::ToString(A.M[2][3]) + " 3: " + ZCPP::ToString(A.M[3][0]) + ", " + ZCPP::ToString(A.M[3][1]) + ", " + ZCPP::ToString(A.M[3][2]) + ", " + ZCPP::ToString(A.M[3][3]) + " >"; }
		std::string ToString() { return ToString(*this); }

		// Non-real functions
		// Add two 4x4 Matricies
		static Matrix4 Add(Matrix4 A, Matrix4 B)
		{
			Matrix4 C;
			C.M[0][0] = A.M[0][0] + B.M[0][0]; C.M[0][1] = A.M[0][1] + B.M[0][1]; C.M[0][2] = A.M[0][2] + B.M[0][2]; C.M[0][3] = A.M[0][3] + B.M[0][3];
			C.M[1][0] = A.M[1][0] + B.M[1][0]; C.M[1][1] = A.M[1][1] + B.M[1][1]; C.M[1][2] = A.M[1][2] + B.M[1][2]; C.M[1][3] = A.M[1][3] + B.M[1][3];
			C.M[2][0] = A.M[2][0] + B.M[2][0]; C.M[2][1] = A.M[2][1] + B.M[2][1]; C.M[2][2] = A.M[2][2] + B.M[2][2]; C.M[2][3] = A.M[2][3] + B.M[2][3];
			C.M[3][0] = A.M[3][0] + B.M[3][0]; C.M[3][1] = A.M[3][1] + B.M[3][1]; C.M[3][2] = A.M[3][2] + B.M[3][2]; C.M[3][3] = A.M[3][3] + B.M[3][3];
			return C;
		}

		// Subtract two 4x4 Matricies
		static Matrix4 Subtract(Matrix4 A, Matrix4 B)
		{
			Matrix4 C;
			C.M[0][0] = A.M[0][0] - B.M[0][0]; C.M[0][1] = A.M[0][1] - B.M[0][1]; C.M[0][2] = A.M[0][2] - B.M[0][2]; C.M[0][3] = A.M[0][3] - B.M[0][3];
			C.M[1][0] = A.M[1][0] - B.M[1][0]; C.M[1][1] = A.M[1][1] - B.M[1][1]; C.M[1][2] = A.M[1][2] - B.M[1][2]; C.M[1][3] = A.M[1][3] - B.M[1][3];
			C.M[2][0] = A.M[2][0] - B.M[2][0]; C.M[2][1] = A.M[2][1] - B.M[2][1]; C.M[2][2] = A.M[2][2] - B.M[2][2]; C.M[2][3] = A.M[2][3] - B.M[2][3];
			C.M[3][0] = A.M[3][0] - B.M[3][0]; C.M[3][1] = A.M[3][1] - B.M[3][1]; C.M[3][2] = A.M[3][2] - B.M[3][2]; C.M[3][3] = A.M[3][3] - B.M[3][3];
			return C;
		}

		// Real functions
		// Multiply two 4x4 Matricies
		static Matrix4 Multiply(Matrix4 A, Matrix4 B)
		{
			Matrix4 C;
			C.M[0][0] = A.M[0][0] * B.M[0][0] + A.M[0][1] * B.M[1][0] + A.M[0][2] * B.M[2][0] + A.M[0][3] * B.M[3][0];
			C.M[0][1] = A.M[0][0] * B.M[0][1] + A.M[0][1] * B.M[1][1] + A.M[0][2] * B.M[2][1] + A.M[0][3] * B.M[3][1];
			C.M[0][2] = A.M[0][0] * B.M[0][2] + A.M[0][1] * B.M[1][2] + A.M[0][2] * B.M[2][2] + A.M[0][3] * B.M[3][2];
			C.M[0][3] = A.M[0][0] * B.M[0][3] + A.M[0][1] * B.M[1][3] + A.M[0][2] * B.M[2][3] + A.M[0][3] * B.M[3][3];

			C.M[1][0] = A.M[1][0] * B.M[0][0] + A.M[1][1] * B.M[1][0] + A.M[1][2] * B.M[2][0] + A.M[1][3] * B.M[3][0];
			C.M[1][1] = A.M[1][0] * B.M[0][1] + A.M[1][1] * B.M[1][1] + A.M[1][2] * B.M[2][1] + A.M[1][3] * B.M[3][1];
			C.M[1][2] = A.M[1][0] * B.M[0][2] + A.M[1][1] * B.M[1][2] + A.M[1][2] * B.M[2][2] + A.M[1][3] * B.M[3][2];
			C.M[1][3] = A.M[1][0] * B.M[0][3] + A.M[1][1] * B.M[1][3] + A.M[1][2] * B.M[2][3] + A.M[1][3] * B.M[3][3];

			C.M[2][0] = A.M[2][0] * B.M[0][0] + A.M[2][1] * B.M[1][0] + A.M[2][2] * B.M[2][0] + A.M[2][3] * B.M[3][0];
			C.M[2][1] = A.M[2][0] * B.M[0][1] + A.M[2][1] * B.M[1][1] + A.M[2][2] * B.M[2][1] + A.M[2][3] * B.M[3][1];
			C.M[2][2] = A.M[2][0] * B.M[0][2] + A.M[2][1] * B.M[1][2] + A.M[2][2] * B.M[2][2] + A.M[2][3] * B.M[3][2];
			C.M[2][3] = A.M[2][0] * B.M[0][3] + A.M[2][1] * B.M[1][3] + A.M[2][2] * B.M[2][3] + A.M[2][3] * B.M[3][3];

			C.M[3][0] = A.M[3][0] * B.M[0][0] + A.M[3][1] * B.M[1][0] + A.M[3][2] * B.M[3][0] + A.M[3][3] * B.M[3][0];
			C.M[3][1] = A.M[3][0] * B.M[0][1] + A.M[3][1] * B.M[1][1] + A.M[3][2] * B.M[3][1] + A.M[3][3] * B.M[3][1];
			C.M[3][2] = A.M[3][0] * B.M[0][2] + A.M[3][1] * B.M[1][2] + A.M[3][2] * B.M[3][2] + A.M[3][3] * B.M[3][2];
			C.M[3][3] = A.M[3][0] * B.M[0][3] + A.M[3][1] * B.M[1][3] + A.M[3][2] * B.M[3][3] + A.M[3][3] * B.M[3][3];
			return C;
		}

		// Multiply a Quaternion by a 4x4 Matrix
		static Quaternion Multiply(Matrix4 M, Quaternion V)
		{
			Quaternion NewV;
			NewV.x = V.x * M.M[0][0] + V.y * M.M[0][1] + V.z * M.M[0][2] + V.w * M.M[0][3];
			NewV.y = V.x * M.M[1][0] + V.y * M.M[1][1] + V.z * M.M[1][2] + V.w * M.M[1][3];
			NewV.z = V.x * M.M[2][0] + V.y * M.M[2][1] + V.z * M.M[2][2] + V.w * M.M[2][3];
			NewV.w = V.x * M.M[3][0] + V.y * M.M[3][1] + V.z * M.M[3][2] + V.w * M.M[3][3];
			return NewV;
		}

		// Multiply a Vector3D by a 4x4 Matrix
		static Quaternion Multiply(Matrix4 M, Vector3D V) { return Multiply(M, Quaternion(V.x, V.y, V.z, 1)); }

		// Divide two 4x4 Matricies
		static Matrix4 Divide(Matrix4 A, Matrix4 B)
		{
			Matrix4 C;
			C.M[0][0] = A.M[0][0] / B.M[0][0] + A.M[0][1] / B.M[1][0] + A.M[0][2] / B.M[2][0] + A.M[0][3] / B.M[3][0];
			C.M[0][1] = A.M[0][0] / B.M[0][1] + A.M[0][1] / B.M[1][1] + A.M[0][2] / B.M[2][1] + A.M[0][3] / B.M[3][1];
			C.M[0][2] = A.M[0][0] / B.M[0][2] + A.M[0][1] / B.M[1][2] + A.M[0][2] / B.M[2][2] + A.M[0][3] / B.M[3][2];
			C.M[0][3] = A.M[0][0] / B.M[0][3] + A.M[0][1] / B.M[1][3] + A.M[0][2] / B.M[2][3] + A.M[0][3] / B.M[3][3];

			C.M[1][0] = A.M[1][0] / B.M[0][0] + A.M[1][1] / B.M[1][0] + A.M[1][2] / B.M[2][0] + A.M[1][3] / B.M[3][0];
			C.M[1][1] = A.M[1][0] / B.M[0][1] + A.M[1][1] / B.M[1][1] + A.M[1][2] / B.M[2][1] + A.M[1][3] / B.M[3][1];
			C.M[1][2] = A.M[1][0] / B.M[0][2] + A.M[1][1] / B.M[1][2] + A.M[1][2] / B.M[2][2] + A.M[1][3] / B.M[3][2];
			C.M[1][3] = A.M[1][0] / B.M[0][3] + A.M[1][1] / B.M[1][3] + A.M[1][2] / B.M[2][3] + A.M[1][3] / B.M[3][3];

			C.M[2][0] = A.M[2][0] / B.M[0][0] + A.M[2][1] / B.M[1][0] + A.M[2][2] / B.M[2][0] + A.M[2][3] / B.M[3][0];
			C.M[2][1] = A.M[2][0] / B.M[0][1] + A.M[2][1] / B.M[1][1] + A.M[2][2] / B.M[2][1] + A.M[2][3] / B.M[3][1];
			C.M[2][2] = A.M[2][0] / B.M[0][2] + A.M[2][1] / B.M[1][2] + A.M[2][2] / B.M[2][2] + A.M[2][3] / B.M[3][2];
			C.M[2][3] = A.M[2][0] / B.M[0][3] + A.M[2][1] / B.M[1][3] + A.M[2][2] / B.M[2][3] + A.M[2][3] / B.M[3][3];

			C.M[3][0] = A.M[3][0] / B.M[0][0] + A.M[3][1] / B.M[1][0] + A.M[3][2] / B.M[3][0] + A.M[3][3] / B.M[3][0];
			C.M[3][1] = A.M[3][0] / B.M[0][1] + A.M[3][1] / B.M[1][1] + A.M[3][2] / B.M[3][1] + A.M[3][3] / B.M[3][1];
			C.M[3][2] = A.M[3][0] / B.M[0][2] + A.M[3][1] / B.M[1][2] + A.M[3][2] / B.M[3][2] + A.M[3][3] / B.M[3][2];
			C.M[3][3] = A.M[3][0] / B.M[0][3] + A.M[3][1] / B.M[1][3] + A.M[3][2] / B.M[3][3] + A.M[3][3] / B.M[3][3];
			return C;
		}

		// Divide a Quaternion by a 4x4 Matrix
		static Quaternion Divide(Matrix4 M, Quaternion V)
		{
			Quaternion NewV;
			NewV.x = M.M[0][0] / V.x + M.M[0][1] / V.y + M.M[0][2] / V.z + M.M[0][3] / V.w;
			NewV.y = M.M[1][0] / V.x + M.M[1][1] / V.y + M.M[1][2] / V.z + M.M[1][3] / V.w;
			NewV.z = M.M[2][0] / V.x + M.M[2][1] / V.y + M.M[2][2] / V.z + M.M[2][3] / V.w;
			NewV.w = M.M[3][0] / V.x + M.M[3][1] / V.y + M.M[3][2] / V.z + M.M[3][3] / V.w;
			return NewV;
		}

		// Divide a Vector3D by a 4x4 Matrix
		static Quaternion Divide(Matrix4 M, Vector3D V) { return Divide(M, Quaternion(V.x, V.y, V.z, 1)); }

		// 3D stuff

		static Matrix4 Translate(Vector3D pos)
		{
			Matrix4 m = Matrix4::Identity();
			m.M[0][3] = pos.x;
			m.M[1][3] = pos.y;
			m.M[2][3] = pos.z;
			return m;
		}

		static Matrix4 Scale(Vector3D scl)
		{
			Matrix4 m = Matrix4::Identity();
			m.M[0][0] = scl.x;
			m.M[1][1] = scl.y;
			m.M[2][2] = scl.z;
			return m;
		}

		// Euler rotation
		static Matrix4 Rotate(Vector3D r)
		{
			Matrix4 m = Identity();
			if (r.z != 0)
			{
				Matrix4 zR = Identity();
				zR.M[0][0] = cosf(r.z);
				zR.M[0][1] = sinf(r.z);
				zR.M[1][0] = -sinf(r.z);
				zR.M[1][1] = cosf(r.z);
				m = Multiply(zR, m);
			}

			if (r.x != 0)
			{
				Matrix4 xR = Identity();
				xR.M[1][1] = cosf(r.x);
				xR.M[1][2] = sinf(r.x);
				xR.M[2][1] = -sinf(r.x);
				xR.M[2][2] = cosf(r.x);
				m = Multiply(xR, m);
			}

			if (r.y != 0)
			{
				Matrix4 yR = Identity();
				yR.M[0][0] = cosf(r.y);
				yR.M[0][2] = -sinf(r.y);
				yR.M[2][0] = sinf(r.y);
				yR.M[2][2] = cosf(r.y);
				m = Multiply(yR, m);
			}
			return m;
		}

		static Matrix4 LookAt(Vector3D Right, Vector3D Up, Vector3D Direction, Vector3D Position)
		{
			Matrix4 lM = Identity();
			lM.M[0][0] = Right.x; lM.M[0][1] = Right.y; lM.M[0][2] = Right.z;
			lM.M[1][0] = Up.x; lM.M[1][1] = Up.y; lM.M[1][2] = Up.z;
			lM.M[2][0] = Direction.x; lM.M[2][1] = Direction.y; lM.M[2][2] = Direction.z;
			return Multiply(lM, Translate(Position * -1));
		}

		static Matrix4 Camera_PerspectiveProjection(float Znear, float Zfar, float rFOV, float AP)
		{
			Matrix4 m;
			m.M[0][0] = 1 / (AP * tanf(rFOV / 2));
			m.M[1][1] = -1 / (tanf(rFOV / 2));
			m.M[2][2] = ((Zfar - Znear) / (Zfar - Znear));
			m.M[3][2] = 1;
			m.M[2][3] = ((2 * Zfar * Znear) / (Zfar - Znear));
			return m;
		}

		static Matrix4 Camera_OrthographicProjection(float left, float right, float top, float bottom, float Znear, float Zfar, float AR)
		{
			left *= AR;
			right *= AR;
			Matrix4 m;
			m.M[0][0] = 2 / (right - left);
			m.M[1][1] = -2 / (top - bottom);
			m.M[2][2] = -2 / (Zfar - Znear);
			m.M[0][3] = -((right + left) / (right - left));
			m.M[1][3] = ((top + bottom) / (top - bottom));
			m.M[2][3] = -((Zfar + Znear) / (Zfar - Znear));
			m.M[3][3] = 1;
			return m;
		}

	};

	// Add two 4x4 Matricies
	Matrix4 operator + (const Matrix4& A, const Matrix4& B) { return Matrix4::Add(A, B); }
	// Subtract two 4x4 Matricies
	Matrix4 operator - (const Matrix4& A, const Matrix4& B) { return Matrix4::Subtract(A, B); }

	// Multiply two 4x4 Matricies
	Matrix4 operator * (const Matrix4& A, const Matrix4& B) { return Matrix4::Multiply(A, B); }

	// Multiply a Quaternion by a 4x4 Matrix
	Quaternion operator * (const Matrix4& A, const Quaternion& B) { return Matrix4::Multiply(A, B); }
	Quaternion operator * (const Quaternion& A, const Matrix4& B) { return Matrix4::Multiply(B, A); }

	// Multiply a Vector3D by a 4x4 Matrix
	Quaternion operator * (const Matrix4& A, const Vector3D& B) { return Matrix4::Multiply(A, B); }
	Quaternion operator * (const Vector3D& A, const Matrix4& B) { return Matrix4::Multiply(B, A); }

	// Divide two 4x4 Matricies
	Matrix4 operator / (const Matrix4& A, const Matrix4& B) { return Matrix4::Divide(A, B); }

	// Divide a Quaternion by a 4x4 Matrix
	Quaternion operator / (const Matrix4& A, const Quaternion& B) { return Matrix4::Divide(A, B); }
	Quaternion operator / (const Quaternion& A, const Matrix4 B) { return Matrix4::Divide(B, A); }

	// Divide a Vector3D by a 4x4 Matrix
	Quaternion operator / (const Matrix4& A, const Vector3D& B) { return Matrix4::Divide(A, B); }
	Quaternion operator / (const Vector3D& A, const Matrix4 B) { return Matrix4::Divide(B, A); }

	Matrix4 operator *= (Matrix4& A, const Matrix4& B) { A = A * B; return A; }
	Matrix4 operator /= (Matrix4& A, const Matrix4& B) { A = A / B; return A; }
	Quaternion operator *= (Quaternion& A, const Matrix4& B) { A = A * B; return A; }
	Quaternion operator *= (Vector3D& A, const Matrix4& B) { return Matrix4::Multiply(B, A); }
	Quaternion operator /= (Quaternion& A, const Matrix4& B) { A = A / B; return A; }
	Quaternion operator /= (Vector3D& A, const Matrix4& B) { return Matrix4::Divide(B, A); }
};
