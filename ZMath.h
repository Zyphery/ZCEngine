#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <random>

// This math  library has no effect  on the main  ZCEngine  file.
// This  is a separate  library  that can be used  along side the
// base  engine.  The  library  holds 2D,  3D,  and  4D  classes.
// They all  have overloaded  operators to do  basic and  special
// math  functions  such  as  adding,  subtracting,  multiplying,
// dividing,  and  normalizing.  The  add and subtract  functions
// only work on  2 vectors.  The multiply  and divide  can use  a
// vector or float. More detail can be found inside the namespace

std::random_device device; std::mt19937 rng(device());
std::uniform_int_distribution<int32_t> rnd(-2147483647, 2147483647);

namespace ZCPP
{
	// The constant 𝜋
	const double Pi = 3.1415926535897932;

	// Converting Degress to Radians
	const float DegtoRad = Pi * 2. / 360.;
	// Converting Radians to Degrees
	const float RadtoDeg = 1. / DegtoRad;

	/* Int32 Random ( -2147483647, 2147483647 ) */
	// Returns a random number between -2147483647, 2147483647 in int form
	int32_t Random() { return rnd(rng); }
	// Returns a random number between the min and max in int form
	int32_t Random(int32_t min, int32_t max)
	{
		if (max < min) std::swap(min, max); if (min == max) return max;
		std::uniform_int_distribution<int32_t> nrnd(min, max); return nrnd(rng);
	}

	/* Float Random ( -1, 1 ) */
	// 25 decimal point precision
	// Returns a random number between -1 and 1 in float form
	float Randomf() { std::uniform_real_distribution<float> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in float form
	float Randomf(float min, float max) {
		if (max < min) std::swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<float> nrnd(min, max); return nrnd(rng);
	}

	/* Double Random ( -1, 1 ) */
	// 50 decimal point precision
	// Returns a random number between -1 and 1 in double form
	double Randomd() { std::uniform_real_distribution<double> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in double form
	double Randomd(double min, double max) {
		if (max < min) std::swap(min, max); if (min == max) return max;
		std::uniform_real_distribution<double> nrnd(min, max); return nrnd(rng);
	}

	// Get percentage of where value is between min and max
	float PercentagefromValue(float min, float max, float value) { return (value - min) / (max - min); }
	// Get value from percentage between min and max
	float PercentagetoValue(float min, float max, float percentage) { return max * percentage + min; }

	// Clamps any type of Value between min and max
	template <typename Type> Type Clamp(Type min, Type max, Type Value) { if (max < min) std::swap(min, max); if (Value < min) return min; else if (Value > max) return max; else return Value; }

	// Maps values from in-min and in-max to out-min and out-max
	template <typename Type> Type Map(Type inMin, Type inMax, Type outMin, Type outMax, Type Value) { return Type(PercentagetoValue(outMin, outMax, PercentagefromValue(inMin, inMax, Value))); }

	// Swap two values with eachother
	template <typename Type> void Swap(Type& Val_A, Type& Val_B) { Type temp = Val_A; Val_A = Val_B; Val_B = temp; }

	// Returns the Min of the two, doesn't account if they are equal
	template <typename Type> Type Min(Type Val_A, Type Val_B) { if (Val_A < Val_B) return Val_A; else return Val_B; }
	// Returns the Max of the two, doesn't account if they are equal
	template <typename Type> Type Max(Type Val_A, Type Val_B) { if (Val_A > Val_B) return Val_A; else return Val_B; }

	// Returns the absolute Value of Value
	template <typename Type> Type Abs(Type Value) { if (Value < 0) return (Value * -1); else return Value; }

	// Converts the Value into a std::string
	template <typename Type> std::string ToString(Type Value) { return std::to_string(Value); }

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
		static Vector2D Normalize(Vector2D A) { float L = Length(A); return Vector2D(A.x / L, A.y / L); }
		void Normalize() { *this = Normalize(*this); }
		static Vector2D Abs(Vector2D A) { return Vector2D(ZCPP::Abs(A.x), ZCPP::Abs(A.y)); }
		void Abs() { *this = Abs(*this); }
		static Vector2D Rotate(Vector2D A, float r) { Vector2D V; V.x = A.x * cos(r) - A.y * sin(r); V.y = sin(r) * A.x + cos(r) * A.y; return V; }
		void Rotate(float r) { *this = Rotate(*this, r); }
		static Vector2D Random() { return Normalize(Vector2D(rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector2D A) { return "<" + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return "< " + ZCPP::ToString(this->x) + ", " + ZCPP::ToString(this->y) + " >"; }

		// Returns the Max of all the x's, and y's
		static Vector2D Max(Vector2D A, Vector2D B) { Vector2D C; C.x = ZCPP::Max(A.x, B.x); C.y = ZCPP::Max(A.y, B.y); return C; }
		// Returns the Min of all the x's, and y's
		static Vector2D Min(Vector2D A, Vector2D B) { Vector2D C; C.x = ZCPP::Min(A.x, B.x); C.y = ZCPP::Min(A.y, B.y); return C; }
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

		void operator = (const Vector3D& vec) { x = vec.x; y = vec.y; z = vec.z; }

		/* Casting Vector3D to Vector2D
		x, y, components are saved */
		operator Vector2D() const { return Vector2D(x, y); }

		static const Vector2D Vector2(Vector3D V) { return Vector2D(V.x, V.y); }
		Vector2D Vector2() const { return Vector2(*this); }

		static float Length(Vector3D A) { return sqrt(A.x * A.x + A.y * A.y + A.z * A.z); }
		float Length() { return Length(*this); }
		static float Distance(Vector3D A, Vector3D B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2)); }
		static Vector3D Normalize(Vector3D A) { float L = Length(A); return Vector3D(A.x / L, A.y / L, A.z / L); }
		void Normalize() { *this = Normalize(*this); }
		static Vector3D Abs(Vector3D A) { return Vector3D(ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z)); }
		void Abs() { *this = Abs(*this); }
		static Vector3D Random() { return Normalize(Vector3D(rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector3D A) { return "<" + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ", " + ZCPP::ToString(A.z) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return "< " + ZCPP::ToString(this->x) + ", " + ZCPP::ToString(this->y) + ", " + ZCPP::ToString(this->z) + " >"; }

		// Returns the Max of all the x's, y's, and z's
		static Vector3D Max(Vector3D A, Vector3D B) { Vector3D C; C.x = ZCPP::Max(A.x, B.x); C.y = ZCPP::Max(A.y, B.y); C.z = ZCPP::Max(A.z, B.z); return C; }
		// Returns the Min of all the x's, y's, and z's
		static Vector3D Min(Vector3D A, Vector3D B) { Vector3D C; C.x = ZCPP::Min(A.x, B.x); C.y = ZCPP::Min(A.y, B.y); C.z = ZCPP::Min(A.z, B.z); return C; }
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



	class Quaternion // Quaternion class ( W, X, Y, Z )
	{
	public:
		float w, x, y, z;

		Quaternion() : w(0), x(0), y(0), z(0) {}
		Quaternion(float _) : w(_), x(_), y(_), z(_) {}
		Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

		void operator = (const Quaternion& q) { w = q.w; x = q.x; y = q.y; z = q.z; }

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

		static float Length(Quaternion A) { return sqrt(A.w * A.w + A.x * A.x + A.y * A.y + A.z * A.z); }
		float Length() { return Length(*this); }
		static float Distance(Quaternion A, Quaternion B) { return sqrt(pow(B.w - A.w, 2) + pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2)); }
		static Quaternion Normalize(Quaternion A) { float L = 1 / Length(A); return Quaternion(A.w *= L, A.x *= L, A.y *= L, A.z *= L); }
		void Normalize() { *this = Normalize(*this); }
		static Quaternion Abs(Quaternion A) { return Quaternion(ZCPP::Abs(A.w), ZCPP::Abs(A.x), ZCPP::Abs(A.y), ZCPP::Abs(A.z)); }
		void Abs() { *this = Abs(*this); }
		static Quaternion Random() { return Normalize(Quaternion(rnd(rng), rnd(rng), rnd(rng), rnd(rng))); }

		static std::string ToString(Quaternion A) { return "<" + ZCPP::ToString(A.w) + ", " + ZCPP::ToString(A.x) + ", " + ZCPP::ToString(A.y) + ", " + ZCPP::ToString(A.z) + ">"; }
		std::string ToString() { return "< " + ZCPP::ToString(this->w) + ", " + ZCPP::ToString(this->x) + ", " + ZCPP::ToString(this->y) + ", " + ZCPP::ToString(this->z) + " >"; }

		// Returns the Max of all the w's, x's, y's, and z's
		static Quaternion Max(Quaternion A, Quaternion B) { Quaternion C; C.w = ZCPP::Max(A.w, B.w); C.x = ZCPP::Max(A.x, B.x); C.y = ZCPP::Max(A.y, B.y); C.z = ZCPP::Max(A.z, B.z); return C; }
		// Returns the Min of all the w's, x's, y's, and z's
		static Quaternion Min(Quaternion A, Quaternion B) { Quaternion C; C.w = ZCPP::Min(A.w, B.w); C.x = ZCPP::Min(A.x, B.x); C.y = ZCPP::Min(A.y, B.y); C.z = ZCPP::Min(A.z, B.z); return C; }
	};

	/* Comparison Operators */
	bool operator == (const Quaternion& A, const Quaternion& B) { return (A.w == B.w && A.x == B.x && A.y == B.y && A.z == B.z); }
	bool operator <  (const Quaternion& A, const Quaternion& B) { return (A.w <  B.w && A.x <  B.x && A.y <  B.y && A.z <  B.z); }
	bool operator >  (const Quaternion& A, const Quaternion& B) { return (A.w >  B.w && A.x >  B.x && A.y >  B.y && A.z >  B.z); }
	bool operator <= (const Quaternion& A, const Quaternion& B) { return (A.w <= B.w && A.x <= B.x && A.y <= B.y && A.x <= B.x); }
	bool operator >= (const Quaternion& A, const Quaternion& B) { return (A.w >= B.w && A.x >= B.x && A.y >= B.y && A.x >= B.x); }
	bool operator != (const Quaternion& A, const Quaternion& B) { return (A.w != B.w && A.x != B.x && A.y != B.y && A.x != B.x); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Quaternion& A, const float& B) { return (A.w == B && A.x == B && A.y == B && A.z == B); }
	bool operator <  (const Quaternion& A, const float& B) { return (A.w <  B && A.x <  B && A.y <  B && A.z <  B); }
	bool operator >  (const Quaternion& A, const float& B) { return (A.w >  B && A.x >  B && A.y >  B && A.z >  B); }
	bool operator <= (const Quaternion& A, const float& B) { return (A.w <= B && A.x <= B && A.y <= B && A.x <= B); }
	bool operator >= (const Quaternion& A, const float& B) { return (A.w >= B && A.x >= B && A.y >= B && A.x >= B); }
	bool operator != (const Quaternion& A, const float& B) { return (A.w != B && A.x != B && A.y != B && A.x != B); }

	// Add a Quaternion to a Quaternion
	Quaternion operator + (const Quaternion& A, const Quaternion& B) { return Quaternion(A.w + B.w, A.x + B.x, A.y + B.y, A.z + B.z); }

	// Subtract a Quaternion from a Quaternion
	Quaternion operator - (const Quaternion& A, const Quaternion& B) { return Quaternion(A.w - B.w, A.x - B.x, A.y - B.y, A.z - B.z); }

	// Multiply a Quaternion by a Quaternion
	Quaternion operator * (const Quaternion& A, const Quaternion& B) { return Quaternion(A.w * B.w, A.x * B.x, A.y * B.y, A.z * B.z); }

	// Divide a Quaternion by a Quaternion
	Quaternion operator / (const Quaternion& A, const Quaternion& B) { return Quaternion(A.w / B.w, A.x / B.x, A.y / B.y, A.z / B.z); }

	// Multiply a Quaternion by a float (Scalar)
	Quaternion operator * (const Quaternion& A, const float& B) { return Quaternion(A.w * B, A.x * B, A.y * B, A.z * B); }
	// Multiply a Quaternion by a float (Scalar)
	Quaternion operator * (const float& A, const Quaternion& B) { return B * A; }

	// Divide a Quaternion by a float (Scalar)
	Quaternion operator / (const Quaternion& A, const float& B) { return Quaternion(A.w / B, A.x / B, A.y / B, A.z / B); }
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
	
	//Quaternion Conjugate(Quaternion A) { return Quaternion(A.w, -A.x, -A.y, -A.z); }
	//Quaternion Inverse(Quaternion A) { float a = 1 / (A.Length() * A.Length()); Quaternion c = Conjugate(A); return Quaternion(c.w * a, c.x * c.w * a, c.y * c.w * a, c.z * c.w * a); }
	//Quaternion ToUnitQuaternion(Quaternion A) { A.Normalize(); float f = sinf(A.w * .5);  return Quaternion(cosf(A.w * .5), A.x * f, A.y * f, A.z * f); } // Something wrong

	//Vector3D RotateVector(Vector3D Vector, Vector3D Axis, float r)
	//{
	//	Quaternion p = Quaternion(0, Vector.x, Vector.y, Vector.z);
	//	p = ~p;
	//	Vector3D AxisN = Vector3D::Normalize(Axis);
	//	Quaternion q = Quaternion(r, AxisN.x, AxisN.y, AxisN.z);
	//	q = ToUnitQuaternion(q);
	//	Quaternion qInverse = !q; Quaternion rVector = q * p * qInverse;
	//	return rVector.Vector3();
	//}

};
