#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "ZMath.h"


// This  is an  object library for  use with  the  ZCEngine file.
// This file requires the "ZMath.h" Header file to work properly.
// It offers both 2D and 3D objects. An Object vector for both 2D
// and 3D  should make sorting objects easier in  your main game.

namespace ZCPP
{

	class Triangle // Can be used for both 2D and 3D meshes
	{
		public:
			int _tp[3];
	};

	/* 2D types */

	class BoundingBox2D
	{
		public:
			Vector2D TL, BR;

		static BoundingBox2D CalculateBoundingBox(Mesh2D _MeshtoBB2D)
		{
			BoundingBox2D _CalculatedBoundingBox;
			_CalculatedBoundingBox.TL = Vector2D(FLT_MAX);

			for (int _MeshVector = 0; _MeshVector < _MeshtoBB2D._tri.size(); _MeshVector++)
			{
				for (int _iteration = 0; _iteration < 3; _iteration++)
				{
					_CalculatedBoundingBox.TL.x = std::fmin(_CalculatedBoundingBox.TL.x, _MeshtoBB2D._vec[_MeshtoBB2D._tri[_MeshVector]._tp[_iteration]].x);
					_CalculatedBoundingBox.TL.y = std::fmin(_CalculatedBoundingBox.TL.y, _MeshtoBB2D._vec[_MeshtoBB2D._tri[_MeshVector]._tp[_iteration]].y);

					_CalculatedBoundingBox.BR.x = std::fmax(_CalculatedBoundingBox.BR.x, _MeshtoBB2D._vec[_MeshtoBB2D._tri[_MeshVector]._tp[_iteration]].x);
					_CalculatedBoundingBox.BR.y = std::fmax(_CalculatedBoundingBox.BR.y, _MeshtoBB2D._vec[_MeshtoBB2D._tri[_MeshVector]._tp[_iteration]].y);
				}
			}

			return _CalculatedBoundingBox;
		}

		static bool IntersectBoundingBox(BoundingBox2D A, BoundingBox2D B)
		{
			if (!((A.TL.x > B.BR.x) || (A.BR.x < B.TL.x) || (A.TL.y > B.BR.y) || (A.BR.y < B.TL.y)))
				return true;

			return false;
		}

		bool IntersectBoundingBox(BoundingBox2D A) { return IntersectBoundingBox({ this->TL,this->BR }, A); }

		// Triangle Collision

		static bool PointInTri2D(Vector2D _Point, Vector2D _OutsideP[3])
		{
			float _P1 = (_OutsideP[0].x * (_OutsideP[2].y - _OutsideP[0].y) + (_Point.y - _OutsideP[0].y) * (_OutsideP[2].x - _OutsideP[0].x) - _Point.x * (_OutsideP[2].y - _OutsideP[0].y)) / ((_OutsideP[1].y - _OutsideP[0].y) * (_OutsideP[2].x - _OutsideP[0].x) - (_OutsideP[1].x - _OutsideP[0].x) * (_OutsideP[2].y - _OutsideP[0].y));
			float _P2 = (_Point.y - _OutsideP[0].y - _P1 * (_OutsideP[1].y - _OutsideP[0].y)) / (_OutsideP[2].y - _OutsideP[0].y);

			if (_P1 >= 0 && _P2 >= 0 && _P1 + _P2 <= 1)
				return true;
			return false;
		}

		static bool TriangleIntersect2D(Vector2D Triangle_A[3], Vector2D Triangle_B[3])
		{
			for (int i = 0; i < 3; i++)
			{
				if (PointInTri2D(Triangle_A[i], Triangle_B))
					return true;
				if (PointInTri2D(Triangle_B[i], Triangle_A))
					return true;
			}

			return false;
		}
	};
	
	class Transform2D
	{
	public:
		Vector2D Position, Scale;
		float rotation;
		std::string name;

		BoundingBox2D boundingbox;
	};

	class Mesh2D
	{
	public:
		std::vector<Triangle> _tri;
		std::vector<Vector2D> _vec;
	};

	class Object2D
	{
	public:
		Transform2D transform;
		Mesh2D mesh;
		bool collided = false;
	};

	bool CollisionUpdate(std::vector<Object2D> objects)
	{
		// Calculate the Bounding box for the mesh of each object
		for (auto& _Obj : objects)
		{
			_Obj.collided = false;
			Mesh2D _TransformedMesh;
			_TransformedMesh._tri = _Obj.mesh._tri;
			for (int _MeshVector = 0; _MeshVector < _Obj.mesh._vec.size(); _MeshVector++)
			{
				Vector2D _newVector;
				_newVector = _Obj.mesh._vec[_MeshVector] * _Obj.transform.Scale;
				_newVector = Vector2D(_newVector.x * cos(_Obj.transform.rotation) - _newVector.y * sin(_Obj.transform.rotation), _newVector.x * sin(_Obj.transform.rotation) + _newVector.y * cos(_Obj.transform.rotation));
				_newVector += _Obj.transform.Position;
				_TransformedMesh._vec.push_back(_newVector);
			}
			_Obj.transform.boundingbox = BoundingBox2D::CalculateBoundingBox(_TransformedMesh);
		}

		// Main collision detection
		uint32_t iteration = 0;
		for (auto& O : objects)
		{
			uint32_t iteration2 = 0;
			for (auto& O2 : objects)
			{
				if (iteration != iteration2)
				{
					if (BoundingBox2D::IntersectBoundingBox(O.transform.boundingbox, O2.transform.boundingbox))
					{
						for (int _MeshVector_O = 0; _MeshVector_O < O.mesh._tri.size(); _MeshVector_O++)
						{
							Vector2D _newTriangle_O[3];
							for (int i = 0; i < 3; i++)
							{
								_newTriangle_O[i] = O.mesh._vec[O.mesh._tri[_MeshVector_O]._tp[i]] * O.transform.Scale;
								_newTriangle_O[i] = Vector2D(_newTriangle_O[i].x * cos(O.transform.rotation) - _newTriangle_O[i].y * sin(O.transform.rotation), _newTriangle_O[i].x * sin(O.transform.rotation) + _newTriangle_O[i].y * cos(O.transform.rotation));
								_newTriangle_O[i] += O.transform.Position;
							}

							for (int _MeshVector_O2 = 0; _MeshVector_O2 < O2.mesh._tri.size(); _MeshVector_O2++)
							{
								Vector2D _newTriangle_O2[3];
								for (int i = 0; i < 3; i++)
								{
									_newTriangle_O2[i] = O2.mesh._vec[O2.mesh._tri[_MeshVector_O2]._tp[i]] * O2.transform.Scale;
									_newTriangle_O2[i] = Vector2D(_newTriangle_O2[i].x * cos(O2.transform.rotation) - _newTriangle_O2[i].y * sin(O2.transform.rotation), _newTriangle_O2[i].x * sin(O2.transform.rotation) + _newTriangle_O2[i].y * cos(O2.transform.rotation));
									_newTriangle_O2[i] += O2.transform.Position;
								}

								if (BoundingBox2D::TriangleIntersect2D(_newTriangle_O, _newTriangle_O2))
								{
									O.collided = true; O2.collided = true;
								}
							}
						}
					}
				} iteration2++;
			} iteration++;
		}

		return true;
	}


	/* 3D types */

	class BoundingBox3D
	{
	public:
		Vector3D TL, BR;

		BoundingBox3D CalculateBoundingBox(Mesh3D _MeshtoBB3D)
		{
			BoundingBox3D _CalculatedBoundingBox;
			_CalculatedBoundingBox.TL = Vector3D(FLT_MAX);

			for (int _MeshVector = 0; _MeshVector < _MeshtoBB3D._tri.size(); _MeshVector++)
			{
				for (int _iteration = 0; _iteration < 3; _iteration++)
				{
					_CalculatedBoundingBox.TL.x = std::fmin(_CalculatedBoundingBox.TL.x, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].x);
					_CalculatedBoundingBox.TL.y = std::fmin(_CalculatedBoundingBox.TL.y, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].y);
					_CalculatedBoundingBox.TL.x = std::fmin(_CalculatedBoundingBox.TL.z, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].z);

					_CalculatedBoundingBox.BR.x = std::fmax(_CalculatedBoundingBox.BR.x, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].x);
					_CalculatedBoundingBox.BR.y = std::fmax(_CalculatedBoundingBox.BR.y, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].y);
					_CalculatedBoundingBox.BR.y = std::fmax(_CalculatedBoundingBox.BR.z, _MeshtoBB3D._vec[_MeshtoBB3D._tri[_MeshVector]._tp[_iteration]].z);
				}
			}

			return _CalculatedBoundingBox;
		}

		bool IntersectBoundingBox(BoundingBox3D A, BoundingBox3D B)
		{
			if (!((A.TL.x > B.BR.x) || (A.BR.x < B.TL.x) || (A.TL.y > B.BR.y) || (A.BR.y < B.TL.y) || (A.TL.z > B.BR.z) || (A.BR.z < B.TL.z)))
				return true;

			return false;
		}

		bool IntersectBoundingBox(BoundingBox3D A) { return IntersectBoundingBox({ this->TL,this->BR }, A); }
	};

	class Transform3D
	{
	public:
		Vector3D Position, Scale;
		float rotation;
		std::string name;

		BoundingBox3D boundingbox;
	};

	class Mesh3D
	{
	public:
		std::vector<Triangle> _tri;
		std::vector<Vector3D> _vec;
	};

	class Object3D
	{
	public:
		Transform3D transform;
		Mesh3D mesh;
		bool collided = false;
	};

	/* Object sorting */

	std::vector<Object2D> Objects2D;
	std::vector<Object3D> Objects3D;

	void operator ! (Object2D& _Object_2D) { Objects2D.push_back(_Object_2D); }
	void operator ! (Object3D& _Object_3D) { Objects3D.push_back(_Object_3D); }
};
