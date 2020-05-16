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
	const long double Pi = 3.1415926535897932;

	// Converting Degress to Radians
	const float DegtoRad = Pi * 2. / 360.;
	// Converting Radians to Degrees
	const float RadtoDeg = 1. / DegtoRad;

	/* Int32 Random ( -2147483647, 2147483647 ) */
	// Returns a random number between -2147483647, 2147483647 in int form
	int32_t Random() { return rnd(rng); }
	// Returns a random number between the min and max in int form
	int32_t Random(int32_t min, int32_t max)
	{if (max < min) std::swap(min, max); if (min == max) return max;
	std::uniform_int_distribution<int32_t> nrnd(min, max); return nrnd(rng);}

	/* Float Random ( -1, 1 ) */
	// 25 decimal point precision
	// Returns a random number between -1 and 1 in float form
	float Randomf() { std::uniform_real_distribution<float> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in float form
	float Randomf(float min, float max) { if (max < min) std::swap(min, max); if (min == max) return max; 
	std::uniform_real_distribution<float> nrnd(min, max); return nrnd(rng); }

	/* Double Random ( -1, 1 ) */
	// 50 decimal point precision
	// Returns a random number between -1 and 1 in double form
	double Randomd() { std::uniform_real_distribution<double> nrnd(-1, 1); return nrnd(rng); }
	// Returns a random number between the min and max in double form
	double Randomd(double min, double max) { if (max < min) std::swap(min, max); if (min == max) return max;
	std::uniform_real_distribution<double> nrnd(min, max); return nrnd(rng);}

	// Get percentage of where value is between min and max
	template <typename Type> Type PercentagefromValue(Type min, Type max, Type value) { return (value - min) / (max - min); }
	// Get value from percentage between min and max
	template <typename Type> Type PercentagetoValue(Type min, Type max, Type percentage) { return max*percentage+min; }

	// Clamps any type of Value between min and max
	template <typename Type> Type Clamp(Type min, Type max, Type Value) { if (max < min) std::swap(min, max); if (Value < min) return min; else if (Value > max) return max; else return Value; }

	// Maps values from in-min and in-max to out-min and out-max
	template <typename Type> Type Map(Type inMin, Type inMax, Type outMin, Type outMax, Type Value){ return PercentagetoValue(outMin, outMax, PercentagefromValue(inMin, inMax, Value)); }

	// Vector classes:

	class Vector2D // Vector2D class ( X, Y )
	{
	public:
		float x, y;

		Vector2D() { x = 0; y = 0; }
		Vector2D(float _) { x = _; y = _; }
		Vector2D(float _x, float _y) { x = _x; y = _y; }

		static float Length(Vector2D A) { return sqrt(A.x * A.x + A.y * A.y); }
		float Length() { return Length(Vector2D(this->x,this->y)); }
		static float Distance(Vector2D A, Vector2D B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }
		static Vector2D Normalize(Vector2D A) { float L = Length(A); return Vector2D(A.x / L, A.y / L); }
		void Normalize() { Vector2D V = { this->x, this->y}; Vector2D VN = Normalize(V); this->x = VN.x; this->y = VN.y; }
		static Vector2D Abs(Vector2D A) { return Vector2D(abs(A.x), abs(A.y)); }
		void Abs() { Vector2D V = Abs(Vector2D(this->x, this->y)); this->x = V.x; this->y = V.y; }
		static Vector2D Rotate(Vector2D A, float r) { Vector2D V; V.x = A.x * cos(r) - A.y * sin(r); V.y = sin(r) * A.x + cos(r) * A.y; return V; }
		void Rotate(float r) { Vector2D V = Rotate(Vector2D(this->x, this->y), r); this->x = V.x; this->y = V.y; }
		static Vector2D Random() { return Normalize(Vector2D(rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector2D A) { return "<" + std::to_string(A.x) + ", " + std::to_string(A.y) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return "< " + std::to_string(this->x) + ", " + std::to_string(this->y) + " >"; }

		// Returns the Max of both x's and both y's
		static Vector2D Max(Vector2D A, Vector2D B) { Vector2D C; C.x = std::fmax(A.x, B.x); C.y = std::fmax(A.y, B.y); return C; }
		// Returns the Min of both x's and both y's
		static Vector2D Min(Vector2D A, Vector2D B) { Vector2D C; C.x = std::fmin(A.x, B.x); C.y = std::fmin(A.y, B.y); return C; }
	};

	/* Comparison Operators */

	bool operator == (const Vector2D& A, const Vector2D& B) { return (A.x == B.x && A.y == B.y); }
	bool operator <  (const Vector2D& A, const Vector2D& B) { return (A.x <  B.x && A.y <  B.y); }
	bool operator >  (const Vector2D& A, const Vector2D& B) { return (A.x >  B.x && A.y >  B.y); }
	bool operator <= (const Vector2D& A, const Vector2D& B) { return (A.x <= B.x && A.y <= B.y); }
	bool operator >= (const Vector2D& A, const Vector2D& B) { return (A.x >= B.x && A.y >= B.y); }
	bool operator != (const Vector2D& A, const Vector2D& B) { return (A.x != B.x && A.y != B.y); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Vector2D& A, const float& B) { return (A.x == B && A.y == B); }
	bool operator <  (const Vector2D& A, const float& B) { return (A.x <  B && A.y <  B); }
	bool operator >  (const Vector2D& A, const float& B) { return (A.x >  B && A.y >  B); }
	bool operator <= (const Vector2D& A, const float& B) { return (A.x <= B && A.y <= B); }
	bool operator >= (const Vector2D& A, const float& B) { return (A.x >= B && A.y >= B); }
	bool operator != (const Vector2D& A, const float& B) { return (A.x != B && A.y != B); }

	// Add a Vector2D to a Vector2D
	Vector2D operator + (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x + B.x, A.y + B.y); }

	// Subtract a Vector2D by a Vector2D
	Vector2D operator - (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x - B.x, A.y - B.y); }

	// Multiply a Vector2D by a Vector2D in the form of Ax * Bx, Ay * By
	Vector2D operator * (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x * B.x, A.y * B.y); }

	// Multiply a Vector2D by a float
	Vector2D operator * (const Vector2D& A, const float& B) { return Vector2D(A.x * B, A.y * B); }
	// Multiply a Vector2D by a float
	Vector2D operator * (const float& A, const Vector2D& B) { return(B * A); }

	// Divide a Vector2D by a Vector2D in the form of Ax / Bx, Ay / By
	Vector2D operator / (const Vector2D& A, const Vector2D& B) { return Vector2D(A.x / B.x, A.y / B.y); }

	// Divide a Vector2D by a float
	Vector2D operator / (const Vector2D& A, const float& B) { return Vector2D(A.x / B, A.y / B); }
	// Divide a Vector2D by a float
	Vector2D operator / (const float& A, const Vector2D& B) { return (B / A); }

	Vector2D& operator += (Vector2D& A, const Vector2D& B) { A.x += B.x; A.y += B.y; return A; }
	Vector2D& operator -= (Vector2D& A, const Vector2D& B) { A.x -= B.x; A.y -= B.y; return A; }
	Vector2D& operator *= (Vector2D& A, const float& B) { A.x *= B; A.y *= B; return A; }
	Vector2D& operator /= (Vector2D& A, const float& B) { A.x /= B; A.y /= B; return A; }

	// Normalizes Vector2D A to a unit Vector
	Vector2D operator ~ (Vector2D& A) { return Vector2D::Normalize(A); }

	// Absolute value of Vector2D A
	Vector2D operator ! (Vector2D& A) { A.Abs();  return A; }

	// Dot Product of Vector2D
	float DP2D(Vector2D A, Vector2D B) { Vector2D C = A * B; return C.x + C.y; }
	// Cross Product of Vector2D returning a float
	float fCP2D(Vector2D A, Vector2D B) { return (A.x * B.y) - (A.y * B.x); }
	// Cross Product of Vector2D returning a Vector2D
	Vector2D vCP2D(Vector2D A) { return Vector2D(A.y, -A.x); }



	class Vector3D // Vector3D class ( X, Y, Z )
	{
	public:
		float x, y, z;

		Vector3D() { x = 0; y = 0; z = 0; }
		Vector3D(float _) { x = _; y = _; z = _; }
		Vector3D(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

		/* Casting Vector3D to Vector2D */
		operator Vector2D() const { return Vector2D(x, y); }

		static float Length(Vector3D A) { return sqrt(A.x * A.x + A.y * A.y + A.z * A.z); }
		float Length() { return Length(Vector3D(this->x, this->y, this->z)); }
		static float Distance(Vector3D A, Vector3D B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2)); }
		static Vector3D Normalize(Vector3D A) { float L = Length(A); return Vector3D(A.x / L, A.y / L, A.z / L); }
		void Normalize() { Vector3D V = { this->x, this->y, this->z }; Vector3D VN = Normalize(V); this->x = VN.x; this->y = VN.y; this->z = VN.z; }
		static Vector3D Abs(Vector3D A) { return Vector3D(abs(A.x), abs(A.y), abs(A.z)); }
		void Abs() { Vector3D V = Abs(Vector3D(this->x, this->y, this->z)); this->x = V.x; this->y = V.y; this->z = V.z; }
		static Vector3D Random() { return Normalize(Vector3D(rnd(rng), rnd(rng), rnd(rng))); }

		// Converts A Vector2D into a std::string
		static std::string ToString(Vector3D A) { return "<" + std::to_string(A.x) + ", " + std::to_string(A.y) + ", " + std::to_string(A.z) + ">"; }
		// Converts this Vector2D into a std::string
		std::string ToString() { return "< " + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + " >"; }

		// Returns the Max of both x's and both y's and both z's
		static Vector3D Max(Vector3D A, Vector3D B) { Vector3D C; C.x = std::fmax(A.x, B.x); C.y = std::fmax(A.y, B.y); C.z = std::fmax(A.z, B.z); return C; }
		// Returns the Min of both x's and both y's and both z's
		static Vector3D Min(Vector3D A, Vector3D B) { Vector3D C; C.x = std::fmin(A.x, B.x); C.y = std::fmin(A.y, B.y); C.z = std::fmin(A.z, B.z); return C; }
	};

	/* Comparison Operators */

	bool operator == (const Vector3D& A, const Vector3D& B) { return (A.x == B.x && A.y == B.y && A.z == B.z); }
	bool operator <  (const Vector3D& A, const Vector3D& B) { return (A.x <  B.x && A.y <  B.y && A.z <  B.z); }
	bool operator >  (const Vector3D& A, const Vector3D& B) { return (A.x >  B.x && A.y >  B.y && A.z >  B.z); }
	bool operator <= (const Vector3D& A, const Vector3D& B) { return (A.x <= B.x && A.y <= B.y && A.x <= B.x); }
	bool operator >= (const Vector3D& A, const Vector3D& B) { return (A.x >= B.x && A.y >= B.y && A.x >= B.x); }
	bool operator != (const Vector3D& A, const Vector3D& B) { return (A.x != B.x && A.y != B.y && A.x != B.x); }

	// Comparing A Vector3D to a float is like comparing a Vector3D to a Vector3D with all the same values

	bool operator == (const Vector3D& A, const float& B) { return (A.x == B && A.y == B && A.z == B); }
	bool operator <  (const Vector3D& A, const float& B) { return (A.x <  B && A.y <  B && A.z <  B); }
	bool operator >  (const Vector3D& A, const float& B) { return (A.x >  B && A.y >  B && A.z >  B); }
	bool operator <= (const Vector3D& A, const float& B) { return (A.x <= B && A.y <= B && A.x <= B); }
	bool operator >= (const Vector3D& A, const float& B) { return (A.x >= B && A.y >= B && A.x >= B); }
	bool operator != (const Vector3D& A, const float& B) { return (A.x != B && A.y != B && A.x != B); }

	// Add a Vector3D to a Vector3D
	Vector3D operator + (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x + B.x, A.y + B.y, A.z + B.z); }

	// Subtract a Vector3D by a Vector3D
	Vector3D operator - (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x - B.x, A.y - B.y, A.z - B.z); }

	// Multiply a Vector3D by a Vector3D in the form of Ax * Bx, Ay * By, Az * Bz
	Vector3D operator * (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x * B.x, A.y * B.y, A.z * B.z); }

	// Multiply a Vector3D by a float
	Vector3D operator * (const Vector3D& A, const float& B) { return Vector3D(A.x * B, A.y * B, A.z * B); }
	// Multiply a Vector3D by a float
	Vector3D operator * (const float& A, const Vector3D& B) { return(B * A); }

	// Divide a Vector3D by a Vector3D in the form of Ax / Bx, Ay / By, Az / Bz
	Vector3D operator / (const Vector3D& A, const Vector3D& B) { return Vector3D(A.x / B.x, A.y / B.y, A.z / B.z); }

	// Divide a Vector3D by a float
	Vector3D operator / (const Vector3D& A, const float& B) { return Vector3D(A.x / B, A.y / B, A.z / B); }
	// Divide a Vector3D by a float
	Vector3D operator / (const float& A, const Vector3D& B) { return (B / A); }

	Vector3D& operator += (Vector3D& A, const Vector3D& B) { A.x += B.x; A.y += B.y; A.z += B.z; return A; }
	Vector3D& operator -= (Vector3D& A, const Vector3D& B) { A.x -= B.x; A.y -= B.y; A.z += B.z; return A; }
	Vector3D& operator *= (Vector3D& A, const float& B) { A.x *= B; A.y *= B; A.z *= B; return A; }
	Vector3D& operator /= (Vector3D& A, const float& B) { A.x /= B; A.y /= B; A.z /= B; return A; }

	// Normalizes Vector3D A to a unit Vector
	Vector3D operator ~ (Vector3D& A) { return Vector3D::Normalize(A); }

	// Absolute value of Vector3D A
	Vector3D operator ! (Vector3D& A) { A.Abs(); return A; }
	
	// Dot Product of Vector3D
	float DP3D(Vector3D A, Vector3D B) { Vector3D C = A * B; return C.x + C.y + C.z; }
	// Cross Product of Vector3D returning a Vector3
	Vector3D CP3D(Vector3D A, Vector3D B) { Vector3D C; C.x = A.y * B.z - A.z * B.y; C.y = A.z * B.x - A.x * B.z; C.z = A.x * B.y - A.y * B.x; return C; }



	// Still figuring out Quaternions, use at your own risk
	class Quaternion // Quaternion class ( W, X, Y, Z )
	{
	public:
		float w, x, y, z;

		Quaternion() { w = 1; x = 0; y = 0; z = 0; }
		Quaternion(float _) { w = _; x = _; y = _; z = _; }
		Quaternion(float _w, float _x, float _y, float _z) { w = _w; x = _x; y = _y; z = _z; }

		/* Casting Quaternion to Vector3D or Vector2D */
		operator Vector2D() const { return Vector2D(x, y); }
		operator Vector3D() const { return Vector3D(x, y, z); }

		static float Length(Quaternion A) { return sqrt(A.w * A.w + A.x * A.x + A.y * A.y + A.z * A.z); }
		float Length() { return Length(Quaternion(this->w, this->x, this->y, this->z)); }
		static float Distance(Quaternion A, Quaternion B) { return sqrt(pow(B.w - A.w, 2) + pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2)); }
		static Quaternion Normalize(Quaternion A) { float L = Length(A); return Quaternion(A.w / L, A.x / L, A.y / L, A.z / L); }
		void Normalize() { Quaternion V = { this->w, this->x, this->y, this->z }; Quaternion QN = Normalize(V); this->w = QN.w; this->x = QN.x; this->y = QN.y; this->z = QN.z; }
		static Quaternion Abs(Quaternion A) { return Quaternion(abs(A.w), abs(A.x), abs(A.y), abs(A.z)); }
		void Abs() { Quaternion Q = Abs(Quaternion(this->w, this->x, this->y, this->z)); this->w = Q.w;  this->x = Q.x; this->y = Q.y; this->z = Q.z; }

		static std::string ToString(Quaternion A) { return "<" + std::to_string(A.w) + ", " + std::to_string(A.x) + ", " + std::to_string(A.y) + ", " + std::to_string(A.z) + ">"; }
		std::string ToString() { return "< " + std::to_string(this->w) + ", " + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + " >"; }
	};

	/* Comparison Operators */
	bool operator == (const Quaternion& A, const Quaternion& B) { return (A.w == B.w && A.x == B.x && A.y == B.y && A.z == B.z); }
	bool operator < (const Quaternion& A, const Quaternion& B) { return (A.w < B.w && A.x < B.x && A.y < B.y && A.z < B.z); }
	bool operator > (const Quaternion& A, const Quaternion& B) { return (A.w > B.w && A.x > B.x&& A.y > B.y&& A.z > B.z); }
	bool operator <= (const Quaternion& A, const Quaternion& B) { return (A.w <= B.w && A.x <= B.x && A.y <= B.y && A.x <= B.x); }
	bool operator >= (const Quaternion& A, const Quaternion& B) { return (A.w >= B.w && A.x >= B.x && A.y >= B.y && A.x >= B.x); }
	bool operator != (const Quaternion& A, const Quaternion& B) { return (A.w != B.w && A.x != B.x && A.y != B.y && A.x != B.x); }

	// Normalizes Vector3D A as a unit Quaternion
	Quaternion operator ~ (Quaternion& A) { return Quaternion::Normalize(A); }
	
	// Turns the given Quaternion into its Conjugate
	Quaternion operator - (Quaternion& A) { Quaternion Q = Quaternion(-A.w, -A.x, -A.y, -A.z); Q = ~Q; return Q; }

	// Multiplies a Quaternion by a Quaternion
	Quaternion operator * (Quaternion const& A, Quaternion const& B) { return Quaternion(A.x * B.w + A.y * B.z - A.z * B.y + A.w * B.x, -A.x * B.z + A.y * B.w + A.z * B.x + A.w * B.y, A.x * B.y - A.y * B.x + A.z * B.w + A.w * B.z, -A.x * B.x - A.y * B.y - A.z * B.z + A.w * B.w); }

	/* order of quaternion multiplication
	A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z
	A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y
	A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x
	A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w
	*/

	// Creates a rotation Quaternion using r (radians) and A (Vector3D Axis)
	Quaternion RotationQuaternion(float r, Vector3D A) { Quaternion q = Quaternion(r, A.x, A.y, A.z); ~q; return q; }

	// Rotates V (Vector3D) around A (axis) by r (radians) using a Rotation Quaternion created with r & A
	Vector3D QuaternionRotate(float r, Vector3D V, Vector3D A)
	{
		Quaternion RQ = RotationQuaternion(r, A);		// Rotation  Quaternion
		Quaternion CQ = -RQ;							// Conjugate Quaternion
		Quaternion VQ = Quaternion(0, V.x, V.y, V.z);	// Vector to Quaternion
		RQ = RQ * VQ * CQ;	// Rotation Quaternion * Vector (quaternion form) * Conjugate of Rotation Quaternion
		RQ = ~RQ;
		return Vector3D(RQ.x, RQ.y, RQ.z);

	}
	//return 2 * DP3D(u, V) * u + (pow(q.w, 2) - DP3D(u, u)) * V + 2 * q.w * CP3D(u, V); }
	
	// Absolute value of Vector3D A
	Quaternion operator ! (Quaternion& A) { A.Abs(); return A; }
};
