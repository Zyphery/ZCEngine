#include <cmath>

// This math  library has no effect  on the main  ZCEngine  file.
// This  is a separate  library  that can be used  along side the
// base  engine.  The  library  holds 2D,  3D,  and  4D  classes.
// They all  have overloaded  operators to do  basic and  special
// math  functions  such  as  adding,  subtracting,  multiplying,
// dividing,  and  normalizing.  The  add and subtract  functions
// only work on  2 vectors.  The multiply  and divide  can use  a
// vector or float.  The normalize  function is  called by  using
// ~A;  A  as the  vector type.  Normalize is a void  and doesn't
// return anything. More detail can be found inside the namespace

namespace ZCPP
{
	class Vector2D // Vector2D class
	{
		float x, y;

		Vector2D() {x = 0; y = 0;}
		Vector2D(float _x, float _y) { x = _x; y = _y; }

		static float Length(Vector2D A) { return sqrt(A.x*A.x + A.y*A.y); }
		static Vector2D Normalize(Vector2D A) { float L = Length(A); return Vector2D(A.x/L, A.y/L); }

		static std::string ToString(Vector2D A) { return "<" + std::to_string(A.x)+", "+std::to_string(A.y)+">"; }
		std::string ToString() { return "< " + std::to_string(this->x)+", "+std::to_string(this->y)+" >"; }
	};

	Vector2D operator * (Vector2D const& A, float const& B) {return Vector2D(A.x * B, A.y * B);}
	Vector2D operator * (float const& B, Vector2D const& A) {return Vector2D(A.x * B, A.y * B);}
	// Multiply Vector2D by float
	// Multiplies each float inside Vector2D A by float B

	Vector2D operator * (Vector2D const& A, Vector2D const& B) {return Vector2D(A.x * B.x, A.y * B.y);}
	// Multiply Vector2D by Vector2D
	// Multiplies each same variable: X * X; Y * Y;

	Vector2D operator / (Vector2D const& A, float const& B) {return Vector2D(A.x / B, A.y / B);}
	Vector2D operator / (float const& B, Vector2D const& A) {return Vector2D(A.x / B, A.y / B);}
	// Divide Vector2D by float
	// Divides each float inside Vector2D A by float B

	Vector2D operator / (Vector2D const& A, Vector2D const& B) {return Vector2D(A.x / B.x, A.y / B.y);}
	// Divide Vector2D by Vector2D
	// Divides each same variable: X / X; Y / Y;

	Vector2D operator + (Vector2D const& A, Vector2D const& B) {return Vector2D(A.x + B.x, A.y + B.y);}
	// Add Vector2D by Vector2D
	// Adds each same variable: X + X; Y + Y;

	Vector2D operator - (Vector2D const& A, Vector2D const& B) {return Vector2D(A.x - B.x, A.y - B.y);}
	// Subtract Vector2D by Vector2D
	// Subtracts each same variable: X - X; Y - Y;

	void operator ~ (Vector2D &A) { A = Vector2D::Normalize(A);}
	// Normalizes Vector2D A
	// Sets A as normalized upon call



	class Vector3D // Vector3D class
	{
		float x, y, z;

		Vector3D() {x = 0; y = 0; z = 0;}
		Vector3D(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

		static float Length(Vector3D A) { return sqrt(A.x*A.x + A.y*A.y + A.z*A.z); }
		static Vector3D Normalize(Vector3D A) { float L = Length(A); return Vector3D(A.x/L, A.y/L, A.z/L); }

		static std::string ToString(Vector3D A) { return "<" + std::to_string(A.x)+", "+std::to_string(A.y)+", "+std::to_string(A.z)+">"; }
		std::string ToString() { return "< " + std::to_string(this->x)+", "+std::to_string(this->y)+", "+std::to_string(this->z)+" >"; }
	};

	Vector3D operator * (Vector3D const& A, float const& B) {return Vector3D(A.x * B, A.y * B, A.z * B);}
	Vector3D operator * (float const& B, Vector3D const& A) {return Vector3D(A.x * B, A.y * B, A.z * B);}
	// Multiply Vector3D by float
	// Multiplies each float inside Vector3D A by float B

	Vector3D operator * (Vector3D const& A, Vector3D const& B) {return Vector3D(A.x * B.x, A.y * B.y, A.z * B.z);}
	// Multiply Vector3D by Vector3D
	// Multiplies each same variable: X * X; Y * Y; Z * Z;

	Vector3D operator / (Vector3D const& A, float const& B) {return Vector3D(A.x / B, A.y / B, A.z / B);}
	Vector3D operator / (float const& B, Vector3D const& A) {return Vector3D(A.x / B, A.y / B, A.z / B);}
	// Divide Vector3D by float
	// Divides each float inside Vector3D A by float B

	Vector3D operator / (Vector3D const& A, Vector3D const& B) {return Vector3D(A.x / B.x, A.y / B.y, A.z / B.z);}
	// Divide Vector3D by Vector3D
	// Divides each same variable: X / X; Y / Y; Z / Z;

	Vector3D operator + (Vector3D const& A, Vector3D const& B) {return Vector3D(A.x + B.x, A.y + B.y, A.z + B.z);}
	// Add Vector3D by Vector3D
	// Adds each same variable: X + X; Y + Y; Z + Z;

	Vector3D operator - (Vector3D const& A, Vector3D const& B) {return Vector3D(A.x - B.x, A.y - B.y, A.z - B.z);}
	// Subtract Vector3D by Vector3D
	// Subtracts each same variable: X - X; Y - Y; Z - Z;

	void operator ~ (Vector3D &A) { A = Vector3D::Normalize(A);}
	// Normalizes Vector3D A
	// Sets A as normalized upon call

	float DP(Vector3D A, Vector3D B) { Vector3D C = A * B; return C.x+C.y+C.z; }
	Vector3D CP(Vector3D A, Vector3D B) { Vector3D C; C.x = A.y * B.z - A.z * B.y; C.y = A.z * B.x - A.x * B.z; C.z = A.x * B.y - A.y * B.x; return C; }

	// Still figuring out Quaternions, use at your own risk
	class Quaternion // Quaternion class
	{
		float w, x, y, z;

		Quaternion() { w = 1; x = 0; y = 0; z = 0; }
		Quaternion(float _w, float _x, float _y, float _z) { w = _w; x = _x; y = _y; z =_z; }

		static float Length(Quaternion A) { return sqrt(A.w*A.w + A.x*A.x + A.y*A.y + A.z*A.z); }
		static Quaternion Normalize(Quaternion A) { float L = Length(A); return Quaternion(A.w/L, A.x/L, A.y/L, A.z/L);}

		static std::string ToString(Quaternion A) { return "<" + std::to_string(A.w)+", "+std::to_string(A.x)+", "+std::to_string(A.y)+", "+std::to_string(A.z)+">"; }
		std::string ToString() { return "< " + std::to_string(this->w)+", "+std::to_string(this->x)+", "+std::to_string(this->y)+", "+std::to_string(this->z)+" >"; }
	};


	void operator - (Quaternion &A) { A.w = -A.w; A.x = -A.x; A.y = -A.y; A.z = -A.z; }
	// Turns the given Quaternion into its Conjugate

	void operator ~ (Quaternion &A) { A = Quaternion::Normalize(A);}
	// Normalizes Vector A
	// Sets A as normalized upon call

	Quaternion operator * (Quaternion const& A, Quaternion const& B) {Quaternion b = Quaternion(A.x * B.w + A.y * B.z - A.z * B.y + A.w * B.x, -A.x * B.z + A.y * B.w + A.z * B.x + A.w * B.y, A.x * B.y - A.y * B.x + A.z * B.w + A.w * B.z, -A.x * B.x - A.y * B.y - A.z * B.z + A.w * B.w); ~b; return b;}
	// Multiplies a Quaternion by a Quaternion

	Quaternion RotationQuaternion(float r, Vector A) { Quaternion q; q.w = r; q.x = A.x; q.y = A.y; q.z = A.z; ~q; return q; }
	// Creates a rotation Quaternion using r (radians) and A (Vector Axis)

	Vector QuaternionRotate(float r, Vector V, Vector A) { Quaternion q = RotationQuaternion(r, A); Vector u = Vector(q.x, q.y, q.z); return 2 * DP(u, V) * u + (pow(q.w,2) - DP(u, u)) * V + 2 * q.w * CP(u, V); }
	// Rotates V (Vector) around A (axis) by r (radians) using a Rotation Quaternion created with r & A
};
