#include "flex\Shapes.h"
#include "NvFlex.h"

#include <math.h>

using namespace flex;

void Shapes::allocate(Library * flex, int numShapes) {
	geometry.allocate(flex, numShapes, sizeof(NvFlexCollisionGeometry));
	positions.allocate(flex, numShapes);
	rotations.allocate(flex, numShapes);
	flags.allocate(flex, numShapes);
}

void Shapes::addSphere(float radius, bool dynamic) {

	int i = numShapes++;
	setSphere(i, radius, dynamic);
}

void Shapes::addCapsule(float radius, float height, bool dynamic) {

	int i = numShapes++;
	setCapsule(i, radius, height, dynamic);
}

void Shapes::addBox(float width, float height, float depth, bool dynamic) {

	int i = numShapes++;
	setBox(i, width, height, depth, dynamic);
}

void Shapes::addConvexMesh(int mesh, float scale_x, float scale_y, float scale_z, bool dynamic) {
}

void Shapes::addTriangleMesh(int mesh, float scale_x, float scale_y, float scale_z, bool dynamic) {
	int i = numShapes++;
	setTriangleMesh(i, mesh, scale_x, scale_y, scale_z, dynamic);
}

void Shapes::setSphere(int shapeIndex, float radius, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeSphere, dynamic);
	geo[shapeIndex].sphere.radius = radius;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setCapsule(int shapeIndex, float radius, float height, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeCapsule, dynamic);
	geo[shapeIndex].capsule.radius = radius;
	geo[shapeIndex].capsule.halfHeight = height / 2.f;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setBox(int shapeIndex, float width, float height, float depth, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeBox, dynamic);
	geo[shapeIndex].box.halfExtents[0] = width / 2.f;
	geo[shapeIndex].box.halfExtents[1] = height / 2.f;
	geo[shapeIndex].box.halfExtents[2] = depth / 2.f;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setConvexMesh(int shapeIndex, int mesh, float scale_x, float scale_y, float scale_z, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeConvexMesh, dynamic);
	geo[shapeIndex].convexMesh.mesh = mesh;
	geo[shapeIndex].convexMesh.scale[0] = scale_x;
	geo[shapeIndex].convexMesh.scale[1] = scale_y;
	geo[shapeIndex].convexMesh.scale[2] = scale_z;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setTriangleMesh(int shapeIndex, int mesh, float scale_x, float scale_y, float scale_z, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeTriangleMesh, dynamic);
	geo[shapeIndex].triMesh.mesh = mesh;
	geo[shapeIndex].triMesh.scale[0] = scale_x;
	geo[shapeIndex].triMesh.scale[1] = scale_y;
	geo[shapeIndex].triMesh.scale[2] = scale_z;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setSDF(int shapeIndex, int field, float scale, bool dynamic) {

	NvFlexCollisionGeometry * geo = (NvFlexCollisionGeometry*)geometry.map();
	int * fla = (int*)flags.map();

	fla[shapeIndex] = NvFlexMakeShapeFlags(eNvFlexShapeSDF, dynamic);
	geo[shapeIndex].sdf.field = field;
	geo[shapeIndex].sdf.scale = scale;

	geometry.unmap();
	flags.unmap();
}

void Shapes::setPosition(int shapeIndex, float x, float y, float z) {
	float4 * pos = positions.map();
	if (pos) {
		pos[shapeIndex].x = x;
		pos[shapeIndex].y = y;
		pos[shapeIndex].z = z;
		pos[shapeIndex].w = 0.f;
		positions.unmap();
	}
}

void Shapes::setRotation(int shapeIndex, float x, float y, float z, float w) {
	float4 * rot = rotations.map();
	rot[shapeIndex].x = x;
	rot[shapeIndex].y = y;
	rot[shapeIndex].z = z;
	rot[shapeIndex].w = w;
	rotations.unmap();
}

void Shapes::setRotationAxisAngle(int shapeIndex, float axis_x, float axis_y, float axis_z, float angle_rad) {
	float half_angle = angle_rad * 0.5f;
	float s = sinf(half_angle);
	float l = sqrt(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
	if (l > 0.f) {
		setRotation(shapeIndex,
			axis_x / l * s,
			axis_y / l * s,
			axis_z / l * s,
			cosf(half_angle));
	}
}

void Shapes::update(Solver * solver) {
	solver->setShapes(geometry, positions, rotations, flags, numShapes);
}
