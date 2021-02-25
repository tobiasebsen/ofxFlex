#pragma once

#include "flex\Types.h"
#include "flex\Library.h"
#include "flex\Solver.h"
#include "flex\Buffer.h"

namespace flex {

	class Shapes {
	public:
		void allocate(Library * flex, int numShapes);

		void addSphere(float radius, bool dynamic = true);
		void addCapsule(float radius, float height, bool dynamic = true);
		void addBox(float width, float height, float depth, bool dynamic = true);
		void addConvexMesh(int mesh, float scale_x = 1.f, float scale_y = 1.f, float scale_z = 1.f, bool dynamic = true);
		void addTriangleMesh(int mesh, float scale_x = 1.f, float scale_y = 1.f, float scale_z = 1.f, bool dynamic = true);

		void setSphere(int shapeIndex, float radius, bool dynamic = true);
		void setCapsule(int shapeIndex, float radius, float height, bool dynamic = true);
		void setBox(int shapeIndex, float width, float height, float depth, bool dynamic = true);
		void setConvexMesh(int shapeIndex, int mesh, float scale_x = 1.f, float scale_y = 1.f, float scale_z = 1.f, bool dynamic = true);
		void setTriangleMesh(int shapeIndex, int mesh, float scale_x = 1.f, float scale_y = 1.f, float scale_z = 1.f, bool dynamic = true);
		void setSDF(int shapeIndex, int field, float scale = 1.f, bool dynamic = true);;

		void setPosition(int shapeIndex, float x, float y, float z);
		void setRotation(int shapeIndex, float x, float y, float z, float w);
		void setRotationAxisAngle(int shapeIndex, float axis_x, float axis_y, float axis_z, float angle_rad);

		void update(Solver * solver);

	private:
		Buffer geometry;
		BufferT<float4> positions;
		BufferT<float4> rotations;
		BufferT<int> flags;
		int numShapes = 0;
	};

}