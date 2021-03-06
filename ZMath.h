#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <sstream>

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
	std::uniform_int_distribution<int32_t> rnd(-2147483648, 2147483647);

	// The constant 𝜋
	const double Pi = 3.1415926535897932;
	// The constant e
	const double e = 2.7182818284590452;
	// The constant ϕ
	const double phi = 1.618033988749895;
	// The constant c (speed of light in a vacuum)
	const double c = 299792458;

	// Converting Degress to Radians
	const float DegtoRad = Pi * 2.0f / 360.0f;
	float DtoR(float Deg) { return Deg * DegtoRad; }
	// Converting Radians to Degrees
	const float RadtoDeg = 1.0f / DegtoRad;
	float RtoD(float Rad) { return Rad * RadtoDeg; }

	// Swap two values with eachother
	template <typename Type> void Swap(Type& Val_A, Type& Val_B) { Type temp = Val_A; Val_A = Val_B; Val_B = temp; }

	// Clamps any type of Value between min and max
	template <typename Type> Type Clamp(Type min, Type max, Type Value) { if (max < min) Swap(min, max); if (Value < min) return min; else if (Value > max) return max; else return Value; }

	// Returns the Min of the two, doesn't account if they are equal
	template <typename Type> Type Min(Type Val_A, Type Val_B) { if (Val_A < Val_B) return Val_A; return Val_B; }
	// Returns the Max of the two, doesn't account if they are equal
	template <typename Type> Type Max(Type Val_A, Type Val_B) { if (Val_A > Val_B) return Val_A; return Val_B; }

	// Returns the absolute Value of Value
	template <typename Type> Type Abs(Type Value) { if (Value < 0) return -Value; return Value; }
	// Returns -1 if Value is negative and 1 otherwise
	template <typename Type> int Sign(Type Value) { if (Value < 0) return -1; return 1; }

	// Copies the sign value of Sign and applies it to Value
	template <typename Type> void CopySign(Type& Value, Type Sign) { bool Negative = Sign < 0; if (Value < 0 == Negative) return; Value = -Value; }

	// returns float between -1 & 1
	float GetDecimal(float Value) { return Value - int(Value); }
	// returns double between -1 & 1
	double GetDecimal(double Value) { return Value - int(Value); }

	/* Int32 Random ( -2147483648, 2147483647 ) */
	// Returns a random number between -2147483648, 2147483647 in int form
	int32_t Random() { return rnd(rng); }
	// Returns a random number between the min and max in int form
	int32_t Random(int32_t min, int32_t max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_int_distribution<int32_t> nrnd(min, max); return nrnd(rng);
	}

	/* float Random ( -1, 1 ) */
	// Returns a random number between -1 and 1 in float form
	float Randomf() { std::uniform_real_distribution<float> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in float form
	float Randomf(float min, float max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<float> nrnd(min, max); return nrnd(rng);
	}

	/* double Random ( -1, 1 ) */
	// Returns a random number between -1 and 1 in double form
	double Randomd() { std::uniform_real_distribution<double> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in double form
	double Randomd(double min, double max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<double> nrnd(min, max); return nrnd(rng);
	}

	/* long double Random ( -1, 1 ) */
	// Returns a random number between -1 and 1 in long double form
	long double Randomhl() { std::uniform_real_distribution<double> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in long double form
	long double Randomhl(long double min, long double max) {
		if (max < min) Swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<long double> nrnd(min, max); return nrnd(rng);
	}

	// Returns bool if Value is a Whole number
	bool IsWhole(float Value) { return !GetDecimal(Value); }

	// Value to the Nth power
	float Pow(float Value, float Power) { return pow(Value, Power); }
	// Value to the Nth root
	float Root(float Value, float Root) { if (!Root) return INFINITY; return Pow(Value, 1 / Root); }

	// Quick square root
	float Sqrt(float Value) { return sqrt(Value); }
	// Quick square power
	float Sqr(float Value) { return (Value * Value); }

	// Returns the base integer
	int Trunc(float Value) { return int(Value); }
	// Returns the nearest integer below Value
	int Floor(float Value) { if (IsWhole(Value)) return Value; if (Value < 0) return int(Value) - 1; return int(Value); }
	// Returns the nearest integer above Value
	int Ceil(float Value) { if (IsWhole(Value)) return Value; if (Value < 0) return int(Value); return int(Value) + 1; }
	// Rounds out Value if value decimal is greater than .5, round up, else round down
	int Round(float Value) { if (IsWhole(Value)) return Value; if (Value > 0) if (GetDecimal(Value) >= .5) return int(Value) + 1; if (Value < 0) if (GetDecimal(Value) <= -.5) return int(Value) - 1; return int(Value); }

	// Normal modulous function
	float Mod(float Value, float Modulator) { return Value - Floor(Value / Modulator) * Modulator; }
	// Modulates the using fmod
	float Mod2(float Value, float Modulator) { return fmod(Value, Modulator); }

	// Factorial cannot go higher than 65
	uint64_t Fac(unsigned short int iter) { uint64_t fac = 1; for (int i = 1; i <= iter && i < 66; i++) fac *= i; return fac; }

	// Sine function
	float Sin(float Value) { return sinf(Value); }
	// Cosine function
	float Cos(float Value) { return cosf(Value); }
	// Tangent function
	float Tan(float Value) { return tanf(Value); }
	// Logarithmic function to a base
	float Log(float Base, float Value) { return logf(Value) / logf(Base); }
	// Logarithmic function to base e
	float Logln(float Value) { return logf(Value); }
	// Logarithmic function to base 10
	float Log10(float Value) { return log10f(Value); }

	// Get percentage of where Value is between Val_A and Val_B
	float InvLinearInterpolate(float Val_A, float Val_B, float Value) { return (Value - Val_A) / (Val_B - Val_A); }
	// Linear interpolate between Val_A and Val_B using percentage Value
	float LinearInterpolate(float Val_A, float Val_B, float Value) { return Val_A + (Val_B - Val_A) * Value; }

	// Bounces when Value equals length
	float PingPong(float Value, float length = 1) { Value = Clamp(0.0f, length * 2, Value - Floor(Value / (length * 2)) * (length * 2)); return length - Abs(Value - length); }

	// Smoothly interpolates from Val_A to Val_B with Value
	float SmoothStep(float Val_A, float Val_B, float Value) { Value = -2.f * Value * Value * Value + 3.f * Value * Value; return Val_B * Value + Val_A * (1.f - Value); }

	// Maps values from in-min and in-max to out-min and out-max
	template <typename Type> Type Map(Type inMin, Type inMax, Type outMin, Type outMax, Type Value) { /*if (inMax < inMin) Swap(inMin, inMax); if (outMax < outMin) Swap(outMin, outMax);*/ return (Type)LinearInterpolate(outMin, outMax, InvLinearInterpolate(inMin, inMax, Value)); }

	// Converts the Value into a std::string with a set precision
	template <typename Type> std::string ToString(const Type Value, const unsigned Precision = 6) { std::ostringstream out; out.precision(Precision); out << std::fixed << Value; return out.str(); }
	std::string ToString(const bool Value) { if (Value) return "True"; return "False"; }

	// Converts String into valuetype ( Do not use commas )

	long double ToLongDouble(const std::string Value) { return std::stold(Value); }
	long double ToLongDouble(const char* Value) { return ToLongDouble(std::string(Value)); }
	double ToDouble(const std::string Value) { return std::stod(Value); }
	double ToDouble(const char* Value) { return ToDouble(std::string(Value)); }
	float ToFloat(const std::string Value) { return std::stof(Value); }
	float ToFloat(const char* Value) { return ToFloat(std::string(Value)); }
	int ToInt(const std::string Value) { return std::stoi(Value); }
	int ToInt(const char* Value) { return ToInt(std::string(Value)); }

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
	template <typename Type> void Reverse(Type* Array, uint32_t size) { for (int32_t index = 0, revindex = size - 1; index < size * .5; index++, revindex--) { Swap(Array[index], Array[revindex]); } }

	// Randomizes an array
	template <typename Type> void Randomize(Type* Array, uint32_t size) { for (int32_t index = 0; index < size; index++) Swap(Array[index], Array[Random(0, size - 1)]); }

	// Returns if the array is sorted
	template <typename Type> bool IsSorted(Type* Array, uint32_t size) { for (int32_t index = 1; index < size; index++) if ((Array[index - 1] < Array[index])) return false; return true; }

	namespace ZLog
	{
		// Console Log functions:
		void Log(const char* c) { printf("%s\n", c); }
		void Log(std::string s) { Log(s.c_str()); }

		void Log(bool b) { if (b) { Log("True"); return; } Log("False"); }
		void Log(int i) { Log(ToString(i)); }
		void Log(long i) { Log(ToString(i)); }
		void Log(long long i) { Log(ToString(i)); }
		void Log(unsigned i) { Log(ToString(i)); }
		void Log(unsigned long i) { Log(ToString(i)); }
		void Log(unsigned long long i) { Log(ToString(i)); }
		void Log(float i) { Log(ToString(i)); }
		void Log(double i) { Log(ToString(i)); }
		void Log(long double i) { Log(ToString(i)); }

		void Log(std::string s, bool b) { if (b) { Log(s + " True"); return; } Log(s + " False"); }
		void Log(std::string s, int i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, long i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, long long i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, unsigned i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, unsigned long i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, unsigned long long i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, float i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, double i) { Log(s + " " + ToString(i)); }
		void Log(std::string s, long double i) { Log(s + " " + ToString(i)); }

		void Log(bool b, std::string s) { if (b) { Log("True " + s); return; } Log("False " + s); }
		void Log(int i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(long i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(long long i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(unsigned i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(unsigned long i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(unsigned long long i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(float i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(double i, std::string s) { Log(ToString(i) + " " + s); }
		void Log(long double i, std::string s) { Log(ToString(i) + " " + s); }

	}

	// Vector classes:

	class Vector2I
	{
	public:
		int x, y;

		Vector2I() : x(0), y(0) {}
		Vector2I(int _) : x(_), y(_) {}
		Vector2I(int _x, int _y) : x(_x), y(_y) {}

		void operator = (const Vector2I& v) { x = v.x; y = v.y; }

		static float Length(Vector2I A) { return Sqrt(Sqr(A.x) + Sqr(A.y)); }
		float Length() { return Length(*this); }
		static float Distance(Vector2I A, Vector2I B) { return Sqrt(Sqr(B.x - A.x) + Sqr(B.y - A.y)); }
		static Vector2I Abs(Vector2I A) { return Vector2I(ZCPP::Abs(A.x), ZCPP::Abs(A.y)); }
		Vector2I Abs() { return Abs(*this); }

		static std::string ToString(Vector2I A) { return ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y); }
		std::string ToString() { return ToString(*this); }


		/* Vector2I Overloaded Operators */

		Vector2I  operator +  (const Vector2I& rhs) const { return Vector2I(this->x + rhs.x, this->y + rhs.y); }
		Vector2I  operator -  (const Vector2I& rhs) const { return Vector2I(this->x - rhs.x, this->y - rhs.y); }
		Vector2I  operator +  (const int& rhs) const { return Vector2I(this->x + rhs, this->y + rhs); }
		Vector2I  operator -  (const int& rhs) const { return Vector2I(this->x - rhs, this->y - rhs); }
		Vector2I  operator *  (const int& rhs)           const { return Vector2I(this->x * rhs, this->y * rhs); }
		Vector2I  operator *  (const Vector2I& rhs) const { return Vector2I(this->x * rhs.x, this->y * rhs.y); }
		Vector2I  operator /  (const int& rhs)           const { return Vector2I(this->x / rhs, this->y / rhs); }
		Vector2I  operator /  (const Vector2I& rhs) const { return Vector2I(this->x / rhs.x, this->y / rhs.y); }

		Vector2I& operator += (const Vector2I& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		Vector2I& operator -= (const Vector2I& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		Vector2I& operator += (const int& rhs) { this->x += rhs; this->y += rhs; return *this; }
		Vector2I& operator -= (const int& rhs) { this->x -= rhs; this->y -= rhs; return *this; }
		Vector2I& operator *= (const Vector2I& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		Vector2I& operator /= (const Vector2I& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
		Vector2I& operator *= (const int& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
		Vector2I& operator /= (const int& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
	};

	Vector2I operator + (const int& lhs, const Vector2I& rhs) { return Vector2I(lhs + rhs.x, lhs + rhs.y); }
	Vector2I operator - (const int& lhs, const Vector2I& rhs) { return Vector2I(lhs - rhs.x, lhs - rhs.y); }
	Vector2I operator * (const int& lhs, const Vector2I& rhs) { return Vector2I(lhs * rhs.x, lhs * rhs.y); }
	Vector2I operator / (const int& lhs, const Vector2I& rhs) { return Vector2I(lhs / rhs.x, lhs / rhs.y); }

	/* Comparison Operators */

	bool operator == (const Vector2I& A, const Vector2I& B) { return (A.x == B.x && A.y == B.y); }
	bool operator <  (const Vector2I& A, const Vector2I& B) { return (A.x < B.x&& A.y < B.y); }
	bool operator >  (const Vector2I& A, const Vector2I& B) { return (A.x > B.x && A.y > B.y); }
	bool operator <= (const Vector2I& A, const Vector2I& B) { return (A.x <= B.x && A.y <= B.y); }
	bool operator >= (const Vector2I& A, const Vector2I& B) { return (A.x >= B.x && A.y >= B.y); }
	bool operator != (const Vector2I& A, const Vector2I& B) { return (A.x != B.x && A.y != B.y); }

	// Comparing A Vector2I to a int is like comparing a Vector2I to a Vector2I with all the same values

	bool operator == (const Vector2I& A, const int& B) { return (A.x == B && A.y == B); }
	bool operator <  (const Vector2I& A, const int& B) { return (A.x < B&& A.y < B); }
	bool operator >  (const Vector2I& A, const int& B) { return (A.x > B && A.y > B); }
	bool operator <= (const Vector2I& A, const int& B) { return (A.x <= B && A.y <= B); }
	bool operator >= (const Vector2I& A, const int& B) { return (A.x >= B && A.y >= B); }
	bool operator != (const Vector2I& A, const int& B) { return (A.x != B && A.y != B); }


	class Vector2D // Vector2D class ( X, Y )
	{
	public:
		float x, y;

		Vector2D() : x(0), y(0) {}
		Vector2D(float _) : x(_), y(_) {}
		Vector2D(float _x, float _y) : x(_x), y(_y) {}

		void operator = (const Vector2D& v) { x = v.x; y = v.y; }

		static float Length(Vector2D A) { return Sqrt(Sqr(A.x) + Sqr(A.y)); }
		float Length() { return Length(*this); }
		static float Distance(Vector2D A, Vector2D B) { return Sqrt(Sqr(B.x - A.x) + Sqr(B.y - A.y)); }
		static Vector2D Normalize(Vector2D A) { float L = 1 / Length(A); return Vector2D(A.x * L, A.y * L); }
		void Normalize() { *this = Normalize(*this); }
		static Vector2D Abs(Vector2D A) { return Vector2D(ZCPP::Abs(A.x), ZCPP::Abs(A.y)); }
		Vector2D Abs() { return Abs(*this); }
		Vector2D UnitVector() { return Normalize(*this); }
		static Vector2D Rotate(Vector2D A, float r) { float cr = Cos(r); float sr = Sin(r); Vector2D V; V.x = A.x * cr - A.y * sr; V.y = sr * A.x + cr * A.y; return V; }
		Vector2D Rotate(float r) { return Rotate(*this, r); }
		static Vector2D Random() { float r = Randomf(0, 360) * DegtoRad; return(Vector2D(Cos(r), Sin(r))); }

		static float DotProduct(Vector2D A, Vector2D B) { return A.x * B.x + A.y * B.y; }
		float DotProduct(Vector2D v) { return DotProduct(*this, v); }

		// vector must be normalized
		// Reflects a vector off of a normal
		static Vector2D Reflect(Vector2D vector, Vector2D normal) { return vector - normal * 2 * vector.DotProduct(normal); }

		// Reflects the vector off of normal
		Vector2D Reflect(Vector2D normal) { return Reflect(*this, normal); }

		// Creates a normalized direction vector of length
		static Vector2D Direction(float r, float length = 1) { return Vector2D(Cos(r), Sin(r)) * length; }

		static Vector2D Floor(Vector2D A) { return Vector2D(ZCPP::Floor(A.x), ZCPP::Floor(A.y)); }
		Vector2D Floor() { return Floor(*this); }

		static Vector2D Ceil(Vector2D A) { return Vector2D(ZCPP::Ceil(A.x), ZCPP::Ceil(A.y)); }
		Vector2D Ceil() { return Floor(*this); }

		static Vector2D Round(Vector2D A) { return Vector2D(ZCPP::Round(A.x), ZCPP::Round(A.y)); }
		Vector2D Round() { return Floor(*this); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector2D A, const unsigned Precision = 6) { return "<" + ZCPP::ToString(A.x, Precision) + ", " + ZCPP::ToString(A.y, Precision) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString(const unsigned Precision = 6) { return ToString(*this, Precision); }

		// Returns the Max of all the x's, and y's
		static Vector2D Max(Vector2D A, Vector2D B) { return Vector2D(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y)); }
		// Returns the Min of all the x's, and y's
		static Vector2D Min(Vector2D A, Vector2D B) { return Vector2D(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y)); }

		/* Vector2D Overloaded Operators */

		Vector2D  operator +  (const Vector2D& rhs) const { return Vector2D(this->x + rhs.x, this->y + rhs.y); }
		Vector2D  operator -  (const Vector2D& rhs) const { return Vector2D(this->x - rhs.x, this->y - rhs.y); }
		Vector2D  operator +  (const float& rhs) const { return Vector2D(this->x + rhs, this->y + rhs); }
		Vector2D  operator -  (const float& rhs) const { return Vector2D(this->x - rhs, this->y - rhs); }
		Vector2D  operator *  (const float& rhs)           const { return Vector2D(this->x * rhs, this->y * rhs); }
		Vector2D  operator *  (const Vector2D& rhs) const { return Vector2D(this->x * rhs.x, this->y * rhs.y); }
		Vector2D  operator /  (const float& rhs)           const { return Vector2D(this->x / rhs, this->y / rhs); }
		Vector2D  operator /  (const Vector2D& rhs) const { return Vector2D(this->x / rhs.x, this->y / rhs.y); }

		Vector2D& operator += (const Vector2D& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		Vector2D& operator -= (const Vector2D& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		Vector2D& operator += (const float& rhs) { this->x += rhs; this->y += rhs; return *this; }
		Vector2D& operator -= (const float& rhs) { this->x -= rhs; this->y -= rhs; return *this; }
		Vector2D& operator *= (const Vector2D& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		Vector2D& operator /= (const Vector2D& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
		Vector2D& operator *= (const float& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
		Vector2D& operator /= (const float& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
	};

	Vector2D operator + (const float& lhs, const Vector2D& rhs) { return Vector2D(lhs + rhs.x, lhs + rhs.y); }
	Vector2D operator - (const float& lhs, const Vector2D& rhs) { return Vector2D(lhs - rhs.x, lhs - rhs.y); }
	Vector2D operator * (const float& lhs, const Vector2D& rhs) { return Vector2D(lhs * rhs.x, lhs * rhs.y); }
	Vector2D operator / (const float& lhs, const Vector2D& rhs) { return Vector2D(lhs / rhs.x, lhs / rhs.y); }

	/* Comparison Operators */

	bool operator == (const Vector2D& A, const Vector2D& B) { return (A.x == B.x && A.y == B.y); }
	bool operator <  (const Vector2D& A, const Vector2D& B) { return (A.x < B.x&& A.y < B.y); }
	bool operator >  (const Vector2D& A, const Vector2D& B) { return (A.x > B.x && A.y > B.y); }
	bool operator <= (const Vector2D& A, const Vector2D& B) { return (A.x <= B.x && A.y <= B.y); }
	bool operator >= (const Vector2D& A, const Vector2D& B) { return (A.x >= B.x && A.y >= B.y); }
	bool operator != (const Vector2D& A, const Vector2D& B) { return (A.x != B.x && A.y != B.y); }

	// Comparing A Vector2D to a float is like comparing a Vector2D to a Vector2D with all the same values

	bool operator == (const Vector2D& A, const float& B) { return (A.x == B && A.y == B); }
	bool operator <  (const Vector2D& A, const float& B) { return (A.x < B&& A.y < B); }
	bool operator >  (const Vector2D& A, const float& B) { return (A.x > B && A.y > B); }
	bool operator <= (const Vector2D& A, const float& B) { return (A.x <= B && A.y <= B); }
	bool operator >= (const Vector2D& A, const float& B) { return (A.x >= B && A.y >= B); }
	bool operator != (const Vector2D& A, const float& B) { return (A.x != B && A.y != B); }

	// Vector2D Math functions

	// Dot Product of Vector2D
	float DP2D(Vector2D A, Vector2D B) { Vector2D C = A * B; return C.x + C.y; }
	// Cross Product of Vector2D returning a float
	float CP2D(Vector2D A, Vector2D B) { return (A.x * B.y) - (A.y * B.x); }
	// Cross Product of Vector2D returning a Vector2D
	Vector2D CP2D(Vector2D A) { return Vector2D(A.y, -A.x); }
	// Angle in radians between two Vector2D
	float Angle(Vector2D A, Vector2D B) { if (A < B) Swap(A, B); return 2 * Abs(atan2(B.x - A.x, B.y - A.y)); }

	// Find the closest point to Circle A with radius r from point P
	Vector2D PointToCircle(Vector2D P, Vector2D A, float r)
	{
		// Circle A, radius r // Point P
		float d = Vector2D::Distance(P, A);
		return Vector2D(A.x + r * (P.x - A.x) / d, A.y + r * (P.y - A.y) / d);
	}

	// Find the closest point to Circle A with radius r from point P
	Vector2D OppositePointToCircle(Vector2D P, Vector2D A, float r)
	{
		// Circle A, radius r // Point P
		float d = Vector2D::Distance(P, A);
		return Vector2D(A.x - r * (P.x - A.x) / d, A.y - r * (P.y - A.y) / d);
	}

	// Find the two points that are the intersections of two circles, returns C, D
	void CircleThroughCircle(Vector2D A, float r1, Vector2D B, float r2, Vector2D& C, Vector2D& D)
	{
		float d = Vector2D::Distance(A, B);
		if (d > r1 + r2) { C = NAN; D = NAN; return; }
		if (d < Abs(r1 - r2)) { C = NAN; D = NAN; return; }
		if (d == 0 && r1 == r2) { C = NAN; D = NAN; return; }

		float a = (Sqr(r1) - Sqr(r2) + Sqr(d)) / (2 * d);
		float h = Sqrt(Sqr(r1) - Sqr(a));

		float id = 1 / d;

		Vector2D c = A + a * (B - A) * id;

		C.x = c.x + h * (B.y - A.y) * id;
		C.y = c.y - h * (B.x - A.x) * id;
		D.x = c.x - h * (B.y - A.y) * id;
		D.y = c.y + h * (B.x - A.x) * id;
	}

	// Find two points that Line L1-L2 passes through Circle C, with radius r, returns A, B
	void LineThroughCircle(Vector2D L1, Vector2D L2, Vector2D C, float r, Vector2D& A, Vector2D& B)
	{
		auto sgn = [&](float x) {
			if (x < 0) return -1;
			return 1;
		};

		L1 -= C;
		L2 -= C;

		Vector2D d = Vector2D(L2.x - L1.x, L2.y - L1.y);
		float dr = Sqrt(Sqr(d.x) + Sqr(d.y));//Vector2D::Length(d);
		float D = L1.x * L2.y - L2.x * L1.y;

		float isdr = 1 / Sqr(dr);

		A.x = (D * d.y + sgn(d.y) * d.x * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.x;
		B.x = (D * d.y - sgn(d.y) * d.x * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.x;
		A.y = (-D * d.x + Abs(d.y) * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.y;
		B.y = (-D * d.x - Abs(d.y) * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.y;
	}

	// Find two points that Line Segment L1-L2 passes through Circle C, with radius r, returns A, B
	void LineSegmentThroughCircle(Vector2D L1, Vector2D L2, Vector2D C, float r, Vector2D& A, Vector2D& B)
	{
		auto sgn = [&](float x) { if (x < 0) return -1; return 1; };

		L1 -= C; L2 -= C;

		Vector2D d = Vector2D(L2.x - L1.x, L2.y - L1.y);
		float dr = Sqrt(Sqr(d.x) + Sqr(d.y));//Vector2D::Length(d);
		float D = L1.x * L2.y - L2.x * L1.y;

		float isdr = 1 / Sqr(dr);

		A.x = (D * d.y + sgn(d.y) * d.x * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.x;
		float t = InvLinearInterpolate(L1.x, L2.x, A.x - C.x);
		if (t >= 0 && t <= 1)
			A.y = (-D * d.x + Abs(d.y) * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.y;
		else
			A = NAN;

		B.x = (D * d.y - sgn(d.y) * d.x * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.x;
		t = InvLinearInterpolate(L1.x, L2.x, B.x - C.x);
		if (t >= 0 && t <= 1)
			B.y = (-D * d.x - Abs(d.y) * Sqrt(Sqr(r) * Sqr(dr) - Sqr(D))) * isdr + C.y;
		else
			B = NAN;
	}

	// Find the closest point to line segment AB with point P
	Vector2D PointToLineSegment(Vector2D P, Vector2D A, Vector2D B) {
		// Line AB // Point P
		if (B.x - A.x == 0)
		{
			float t = InvLinearInterpolate(A.y, B.y, P.y);
			if (t >= 0 && t <= 1)
				return Vector2D(A.x, P.y);
			float d1, d2;
			d1 = Vector2D::Distance(P, A);
			d2 = Vector2D::Distance(P, B);
			if (d1 < d2) return A;
			return B;
		}
		float m = (B.y - A.y) / (B.x - A.x); // Slope
		float b = A.y - m * A.x; // Y - interscept 
		Vector2D D = (Vector2D((2 * (m * (P.y - b) + P.x)) / (m * m + 1) - P.x, 2 * (m * (m * (P.y - b) + P.x)) / (m * m + 1) + 2 * b - P.y) + P) * .5; // Point reflected along the Line
		float t = InvLinearInterpolate(A.x, B.x, D.x); // Where the closest point is on the line
		t = Clamp(0.f, 1.f, t); // Clamp the point on the line between both points to make it a line segment
		return Vector2D(LinearInterpolate(A.x, B.x, t), LinearInterpolate(A.y, B.y, t));
	}

	// Find the closest point to line AB with point P (infinite)
	Vector2D PointToLine(Vector2D P, Vector2D A, Vector2D B) {
		// Line AB // Point P
		float m = (B.y - A.y) / (B.x - A.x); // Slope
		float b = A.y - m * A.x; // Y - interscept 
		return (Vector2D((2 * (m * (P.y - b) + P.x)) / (m * m + 1) - P.x, 2 * (m * (m * (P.y - b) + P.x)) / (m * m + 1) + 2 * b - P.y) + P) * .5;
	}

	// Find the point of intersection between Line AB and Line CD (infinite)
	Vector2D LineToLine(Vector2D A, Vector2D B, Vector2D C, Vector2D D)
	{
		return Vector2D(((A.x * B.y - A.y * B.x) * (C.x - D.x) - (A.x - B.x) * (C.x * D.y - C.y * D.x)) / ((A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x)), ((A.x * B.y - A.y * B.x) * (C.y - D.y) - (A.y - B.y) * (C.x * D.y - C.y * D.x)) / ((A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x)));
	}

	// Find the point of intersection between Line segment AB and Line segment CD
	Vector2D LineSegmentToLineSegment(Vector2D A, Vector2D B, Vector2D C, Vector2D D)
	{
		float t = ((A.x - C.x) * (C.y - D.y) - (A.y - C.y) * (C.x - D.x)) / ((A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x));
		float u = -((A.x - B.x) * (A.y - C.y) - (A.y - B.y) * (A.x - C.x)) / ((A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x));
		if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
		{
			return Vector2D(LinearInterpolate(A.x, B.x, t), LinearInterpolate(A.y, B.y, t));
		}
		return NAN;
	}

	// Returns the cloesest point to the rectangle r with size s
	Vector2D PointToRect(Vector2D P, Vector2D r, Vector2D s)
	{
		if (P > r - s && P < r + s)
		{
			bool left = P.x < r.x;
			bool top = P.y < r.y;
			if (Abs(P.x - r.x) - s.x > Abs(P.y - r.y) - s.y)
			{
				P.x += (-1 * left) * s.x + (1 * !left) * s.x;
			}
			else
			{
				P.y += (-1 * top) * s.y + (1 * !top) * s.y;
			}
		}

		float x = Clamp(r.x - s.x, r.x + s.x, P.x);
		float y = Clamp(r.y - s.y, r.y + s.y, P.y);
		return Vector2D(x, y);
	}

	Vector2I V2D_FtoI(Vector2D A) { return Vector2I(A.x, A.y); }
	Vector2D V2D_ItoF(Vector2I A) { return Vector2D(A.x, A.y); }



	class Vector3D // Vector3D class ( X, Y, Z )
	{
	public:
		float x, y, z;

		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(float _) : x(_), y(_), z(_) {}
		Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		Vector3D(Vector2D _V, float _z) : x(_V.x), y(_V.y), z(_z) {}

		void operator = (const Vector3D& vec) { x = vec.x; y = vec.y; z = vec.z; }
		void operator = (const Vector2D& vec) { x = vec.x; y = vec.y; }

		/* Casting Vector3D to Vector2D
		x, y, components are saved */
		operator Vector2D() const { return Vector2D(x, y); }

		static const Vector2D Vector2(Vector3D V) { return Vector2D(V.x, V.y); }
		Vector2D Vector2() const { return Vector2(*this); }

		static Vector2D To2D(Vector3D A) { return Vector2D(A.x, A.y); }
		Vector2D To2D() { return To2D(*this); }
		static float Length(Vector3D A) { return Sqrt(Sqr(A.x) + Sqr(A.y) + Sqr(A.z)); }
		float Length() { return Length(*this); }
		static float Distance(Vector3D A, Vector3D B) { return Sqrt(Sqr(B.x - A.x) + Sqr(B.y - A.y) + Sqr(B.z - A.z)); }
		static Vector3D Normalize(Vector3D A) { float L = 1 / Length(A); return Vector3D(A.x * L, A.y * L, A.z * L); }
		void Normalize() { *this = Normalize(*this); }
		Vector3D UnitVector() { return Normalize(*this); }
		static Vector3D Abs(Vector3D A) { return Vector3D(ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z)); }
		Vector3D Abs() { return Abs(*this); }
		static Vector3D Random() { return Normalize(Vector3D(rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector3D A, const unsigned Precision = 6) { return "<" + ZCPP::ToString(A.x, Precision) + ", " + ZCPP::ToString(A.y, Precision) + ", " + ZCPP::ToString(A.z, Precision) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString(const unsigned Precision = 6) { return ToString(*this, Precision); }

		// Returns the Max of all the x's, y's, and z's
		static Vector3D Max(Vector3D A, Vector3D B) { return Vector3D(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y), ZCPP::Max(A.z, B.z)); }
		// Returns the Min of all the x's, y's, and z's
		static Vector3D Min(Vector3D A, Vector3D B) { return Vector3D(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y), ZCPP::Min(A.z, B.z)); }

		/* Vector3D Overloaded Operators */

		Vector3D  operator +  (const Vector3D& rhs) const { return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
		Vector3D  operator -  (const Vector3D& rhs) const { return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
		Vector3D  operator +  (const float& rhs) const { return Vector3D(this->x + rhs, this->y + rhs, this->z + rhs); }
		Vector3D  operator -  (const float& rhs) const { return Vector3D(this->x - rhs, this->y - rhs, this->z - rhs); }
		Vector3D  operator *  (const float& rhs)           const { return Vector3D(this->x * rhs, this->y * rhs, this->z * rhs); }
		Vector3D  operator *  (const Vector3D& rhs) const { return Vector3D(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z); }
		Vector3D  operator /  (const float& rhs)           const { return Vector3D(this->x / rhs, this->y / rhs, this->z / rhs); }
		Vector3D  operator /  (const Vector3D& rhs) const { return Vector3D(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z); }

		Vector3D& operator += (const Vector3D& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
		Vector3D& operator -= (const Vector3D& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
		Vector3D& operator += (const float& rhs) { this->x += rhs; this->y += rhs; this->z += rhs; return *this; }
		Vector3D& operator -= (const float& rhs) { this->x -= rhs; this->y -= rhs; this->z -= rhs; return *this; }
		Vector3D& operator *= (const Vector3D& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
		Vector3D& operator /= (const Vector3D& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }
		Vector3D& operator *= (const float& rhs) { this->x *= rhs; this->y *= rhs; this->z *= rhs; return *this; }
		Vector3D& operator /= (const float& rhs) { this->x /= rhs; this->y /= rhs; this->z /= rhs; return *this; }
	};

	Vector3D operator + (const float& lhs, const Vector3D& rhs) { return Vector3D(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }
	Vector3D operator - (const float& lhs, const Vector3D& rhs) { return Vector3D(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }
	Vector3D operator * (const float& lhs, const Vector3D& rhs) { return Vector3D(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }
	Vector3D operator / (const float& lhs, const Vector3D& rhs) { return Vector3D(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }

	/* Comparison Operators */

	bool operator == (const Vector3D& A, const Vector3D& B) { return (A.x == B.x && A.y == B.y && A.z == B.z); }
	bool operator <  (const Vector3D& A, const Vector3D& B) { return (A.x < B.x&& A.y < B.y&& A.z < B.z); }
	bool operator >  (const Vector3D& A, const Vector3D& B) { return (A.x > B.x && A.y > B.y && A.z > B.z); }
	bool operator <= (const Vector3D& A, const Vector3D& B) { return (A.x <= B.x && A.y <= B.y && A.x <= B.x); }
	bool operator >= (const Vector3D& A, const Vector3D& B) { return (A.x >= B.x && A.y >= B.y && A.x >= B.x); }
	bool operator != (const Vector3D& A, const Vector3D& B) { return (A.x != B.x && A.y != B.y && A.x != B.x); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Vector3D& A, const float& B) { return (A.x == B && A.y == B && A.z == B); }
	bool operator <  (const Vector3D& A, const float& B) { return (A.x < B&& A.y < B&& A.z < B); }
	bool operator >  (const Vector3D& A, const float& B) { return (A.x > B && A.y > B && A.z > B); }
	bool operator <= (const Vector3D& A, const float& B) { return (A.x <= B && A.y <= B && A.x <= B); }
	bool operator >= (const Vector3D& A, const float& B) { return (A.x >= B && A.y >= B && A.x >= B); }
	bool operator != (const Vector3D& A, const float& B) { return (A.x != B && A.y != B && A.x != B); }

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
		static float Length(Quaternion A) { return Sqrt(Sqr(A.x) + Sqr(A.y) + Sqr(A.z) + Sqr(A.w)); }
		float Length() { return Length(*this); }
		static float Distance(Quaternion A, Quaternion B) { return Sqrt(Sqr(B.x - A.x) + Sqr(B.y - A.y) + Sqr(B.z - A.z) + Sqr(B.w - A.w)); }
		static Quaternion Normalize(Quaternion A) { float L = 1 / Length(A); return Quaternion(A.x * L, A.y * L, A.z * L, A.w * L); }
		void Normalize() { *this = Normalize(*this); }
		Quaternion UnitQuaternion() { return Normalize(*this); }
		static Quaternion Abs(Quaternion A) { return Quaternion(ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z), ZCPP::Abs(A.w)); }
		Quaternion Abs() { return Abs(*this); }
		static Quaternion Random() { return Normalize(Quaternion(rnd(rng), rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Quaternion into a std::string
		static std::string ToString(Quaternion A, const unsigned Precision = 6) { return "<" + ZCPP::ToString(A.x, Precision) + ", " + ZCPP::ToString(A.y, Precision) + ", " + ZCPP::ToString(A.z, Precision) + ", " + ZCPP::ToString(A.w, Precision) + ">"; }
		// Converts this Quaternion into a std::string
		std::string ToString(const unsigned Precision = 6) { return ToString(*this, Precision); }

		// Returns the Max of all the w's, x's, y's, and z's
		static Quaternion Max(Quaternion A, Quaternion B) { return Quaternion(ZCPP::Max(A.x, B.x), ZCPP::Max(A.y, B.y), ZCPP::Max(A.z, B.z), ZCPP::Max(A.w, B.w)); }
		// Returns the Min of all the w's, x's, y's, and z's			  																				   
		static Quaternion Min(Quaternion A, Quaternion B) { return Quaternion(ZCPP::Min(A.x, B.x), ZCPP::Min(A.y, B.y), ZCPP::Min(A.z, B.z), ZCPP::Min(A.w, B.w)); }

		/* Quaternion Overloaded Operators */

		Quaternion  operator +  (const Quaternion& rhs) const { return Quaternion(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w); }
		Quaternion  operator -  (const Quaternion& rhs) const { return Quaternion(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w); }
		Quaternion  operator +  (const float& rhs) const { return Quaternion(this->x + rhs, this->y + rhs, this->z + rhs, this->w + rhs); }
		Quaternion  operator -  (const float& rhs) const { return Quaternion(this->x - rhs, this->y - rhs, this->z - rhs, this->w - rhs); }
		Quaternion  operator *  (const float& rhs)           const { return Quaternion(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs); }
		Quaternion  operator *  (const Quaternion& rhs) const { return Quaternion(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w); }
		Quaternion  operator /  (const float& rhs)           const { return Quaternion(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs); }
		Quaternion  operator /  (const Quaternion& rhs) const { return Quaternion(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w); }

		Quaternion& operator += (const Quaternion& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this; }
		Quaternion& operator -= (const Quaternion& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this; }
		Quaternion& operator += (const float& rhs) { this->x += rhs; this->y += rhs; this->z += rhs; this->w += rhs; return *this; }
		Quaternion& operator -= (const float& rhs) { this->x -= rhs; this->y -= rhs; this->z -= rhs; this->w -= rhs; return *this; }
		Quaternion& operator *= (const Quaternion& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this; }
		Quaternion& operator /= (const Quaternion& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this; }
		Quaternion& operator *= (const float& rhs) { this->x *= rhs; this->y *= rhs; this->z *= rhs; this->w *= rhs; return *this; }
		Quaternion& operator /= (const float& rhs) { this->x /= rhs; this->y /= rhs; this->z /= rhs; this->w /= rhs; return *this; }
	};

	Quaternion operator + (const float& lhs, const Quaternion& rhs) { return Quaternion(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }
	Quaternion operator - (const float& lhs, const Quaternion& rhs) { return Quaternion(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }
	Quaternion operator * (const float& lhs, const Quaternion& rhs) { return Quaternion(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }
	Quaternion operator / (const float& lhs, const Quaternion& rhs) { return Quaternion(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/* Comparison Operators */

	bool operator == (const Quaternion& A, const Quaternion& B) { return (A.x == B.x && A.y == B.y && A.z == B.z && A.w == B.w); }
	bool operator <  (const Quaternion& A, const Quaternion& B) { return (A.x < B.x&& A.y < B.y&& A.z < B.z&& A.w < B.w); }
	bool operator >  (const Quaternion& A, const Quaternion& B) { return (A.x > B.x && A.y > B.y && A.z > B.z && A.w > B.w); }
	bool operator <= (const Quaternion& A, const Quaternion& B) { return (A.x <= B.x && A.y <= B.y && A.x <= B.x && A.w <= B.w); }
	bool operator >= (const Quaternion& A, const Quaternion& B) { return (A.x >= B.x && A.y >= B.y && A.x >= B.x && A.w >= B.w); }
	bool operator != (const Quaternion& A, const Quaternion& B) { return (A.x != B.x && A.y != B.y && A.x != B.x && A.w != B.w); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Quaternion& A, const float& B) { return (A.x == B && A.y == B && A.z == B && A.w == B); }
	bool operator <  (const Quaternion& A, const float& B) { return (A.x < B&& A.y < B&& A.z < B&& A.w < B); }
	bool operator >  (const Quaternion& A, const float& B) { return (A.x > B && A.y > B && A.z > B && A.w > B); }
	bool operator <= (const Quaternion& A, const float& B) { return (A.x <= B && A.y <= B && A.x <= B && A.w <= B); }
	bool operator >= (const Quaternion& A, const float& B) { return (A.x >= B && A.y >= B && A.x >= B && A.w >= B); }
	bool operator != (const Quaternion& A, const float& B) { return (A.x != B && A.y != B && A.x != B && A.w != B); }

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
		return V;
	}

	Vector3D QuaternionToEuler(Quaternion A)
	{
		Vector3D Euler;
		Euler.x = atan2f(2 * (A.w * A.x + A.y * A.z), 1 - 2 * (A.x * A.x + A.y * A.y));

		float p = 2 * (A.w * A.y - A.z * A.x);
		if (Abs(p) >= 1)
			Euler.y = std::copysign(Pi * .5, p);
		else
			Euler.y = asinf(p);

		Euler.z = atan2f(2 * (A.w * A.z + A.x * A.y), 1 - 2 * (A.y * A.y + A.z * A.z));

		return Euler;
	}

	Quaternion EulerToQuaternion(Vector3D A)
	{
		Quaternion quat;
		float cy = Cos(A.z * .5);
		float sy = Sin(A.z * .5);
		float cp = Cos(A.y * .5);
		float sp = Sin(A.y * .5);
		float cr = Cos(A.x * .5);
		float sr = Sin(A.x * .5);

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
		Quaternion q = Quaternion(Axis.UnitVector() * Sin(r * .5), Cos(r * .5));
		Quaternion VectorP = Multiply(Multiply(q, Quaternion(Vector, 0)), Conjugate(q));

		return VectorP;
	}

	namespace ZLog
	{
		void Log(Vector2D v, const unsigned Precision = 6) { ZLog::Log(v.ToString(Precision)); }
		void Log(Vector3D v, const unsigned Precision = 6) { ZLog::Log(v.ToString(Precision)); }
		void Log(Quaternion q, const unsigned Precision = 6) { ZLog::Log(q.ToString(Precision)); }
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

		static std::string ToString(Matrix3 A, const unsigned Precision = 6) { return "< 0: " + ZCPP::ToString(A.M[0][0], Precision) + ", " + ZCPP::ToString(A.M[0][1], Precision) + ", " + ZCPP::ToString(A.M[0][2], Precision) + "  1: " + ZCPP::ToString(A.M[1][0], Precision) + ", " + ZCPP::ToString(A.M[1][1], Precision) + ", " + ZCPP::ToString(A.M[1][2], Precision) + "  2: " + ZCPP::ToString(A.M[2][0], Precision) + ", " + ZCPP::ToString(A.M[2][1], Precision) + ", " + ZCPP::ToString(A.M[2][2], Precision) + " >"; }
		std::string ToString(const unsigned Precision = 6) { return ToString(*this, Precision); }

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
			float c = Cos(r);
			float s = Sin(r);
			Matrix3 M = Matrix3::Identity();
			M.M[0][0] = c;
			M.M[0][1] = -s;
			M.M[1][0] = s;
			M.M[1][1] = c;
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

		static std::string ToString(Matrix4 A, const unsigned Precision = 6) { return "< 0: " + ZCPP::ToString(A.M[0][0], Precision) + ", " + ZCPP::ToString(A.M[0][1], Precision) + ", " + ZCPP::ToString(A.M[0][2], Precision) + ", " + ZCPP::ToString(A.M[0][3], Precision) + "  1: " + ZCPP::ToString(A.M[1][0], Precision) + ", " + ZCPP::ToString(A.M[1][1], Precision) + ", " + ZCPP::ToString(A.M[1][2], Precision) + ", " + ZCPP::ToString(A.M[1][3], Precision) + "  2: " + ZCPP::ToString(A.M[2][0], Precision) + ", " + ZCPP::ToString(A.M[2][1], Precision) + ", " + ZCPP::ToString(A.M[2][2], Precision) + ", " + ZCPP::ToString(A.M[2][3], Precision) + "  3: " + ZCPP::ToString(A.M[3][0], Precision) + ", " + ZCPP::ToString(A.M[3][1], Precision) + ", " + ZCPP::ToString(A.M[3][2], Precision) + ", " + ZCPP::ToString(A.M[3][3], Precision) + " >"; }
		std::string ToString(const unsigned Precision = 6) { return ToString(*this, Precision); }

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
				zR.M[0][0] = Cos(r.z);
				zR.M[0][1] = Sin(r.z);
				zR.M[1][0] = -Sin(r.z);
				zR.M[1][1] = Cos(r.z);
				m = Multiply(zR, m);
			}

			if (r.x != 0)
			{
				Matrix4 xR = Identity();
				xR.M[1][1] = Cos(r.x);
				xR.M[1][2] = Sin(r.x);
				xR.M[2][1] = -Sin(r.x);
				xR.M[2][2] = Cos(r.x);
				m = Multiply(xR, m);
			}

			if (r.y != 0)
			{
				Matrix4 yR = Identity();
				yR.M[0][0] = Cos(r.y);
				yR.M[0][2] = -Sin(r.y);
				yR.M[2][0] = Sin(r.y);
				yR.M[2][2] = Cos(r.y);
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
			float tfh = Tan(rFOV * .5);
			float izfzn = 1 / (Zfar - Znear);

			m.M[0][0] = 1 / (AP * tfh);
			m.M[1][1] = -1 / (tfh);
			m.M[2][2] = (Zfar - Znear) * izfzn;
			m.M[3][2] = 1;
			m.M[2][3] = (2 * Zfar * Znear) * izfzn;
			return m;
		}

		static Matrix4 Camera_OrthographicProjection(float left, float right, float top, float bottom, float Znear, float Zfar, float AR)
		{
			left *= AR;
			right *= AR;
			Matrix4 m;
			m.M[0][0] = 2 / (right - left);
			m.M[1][1] = -2 / (top - bottom);
			m.M[2][2] = 2 / (Zfar - Znear);
			m.M[0][3] = ((right + left) / (right - left));
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

	namespace ZLog
	{
		void Log(Matrix3 m, const unsigned Precision = 6) { Log(m.ToString(Precision)); }
		void Log(Matrix4 m, const unsigned Precision = 6) { Log(m.ToString(Precision)); }

		void Log(Vector2D* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += Array[i].ToString(Precision); if (i < size - 1) a += ", "; } Log(a); }
		void Log(Vector3D* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += Array[i].ToString(Precision); if (i < size - 1) a += ", "; } Log(a); }
		void Log(Quaternion* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += Array[i].ToString(Precision); if (i < size - 1) a += ", "; } Log(a); }


		void Log(Matrix3* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += Array[i].ToString(Precision); if (i < size - 1) a += ", "; } Log(a); }
		void Log(Matrix4* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += Array[i].ToString(Precision); if (i < size - 1) a += ", "; } Log(a); }
		template <typename Type> void Log(Type* Array, int size = 1, const unsigned Precision = 6) { std::string a; for (int i = 0; i < size; i++) { a += ToString(Array[i], Precision); if (i < size - 1) a += ", "; } Log(a); }

		void Log(std::vector<Vector2D> Array, const unsigned Precision = 6) { Log(Array.data(), Array.size(), Precision); }
		void Log(std::vector<Vector3D> Array, const unsigned Precision = 6) { Log(Array.data(), Array.size(), Precision); }
		void Log(std::vector<Quaternion> Array, const unsigned Precision = 6) { Log(Array.data(), Array.size(), Precision); }

		void Log(std::vector<Matrix3> Array, const unsigned Precision = 6) { Log(Array.data(), Array.size(), Precision); }
		void Log(std::vector<Matrix4> Array, const unsigned Precision = 6) { Log(Array.data(), Array.size(), Precision); }
		template <typename Type> void Log(std::vector<Type> Array, const unsigned Precision = 6) { Log(&Array, Array.size(), Precision); }
	}
};
