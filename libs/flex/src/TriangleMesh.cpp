#include "flex\TriangleMesh.h"
#include "NvFlex.h"

#include <algorithm>

using namespace flex;

TriangleMesh * TriangleMesh::create(Library * lib) {

	NvFlexTriangleMeshId m = NvFlexCreateTriangleMesh(lib->getLibrary());
	return m == 0 ? nullptr : new TriangleMesh(lib, m);
}

void TriangleMesh::update(float3 * vert, int numVertices, int * ind, int numIndices) {

	vertices.allocate(lib, numVertices);
	vertices.loadData(vert, numVertices);

	indices.allocate(lib, numIndices);
	indices.loadData(ind, numIndices);

	float3 lower = { FLT_MAX };
	float3 upper = { -FLT_MAX };
	for (int i = 0; i < numVertices; i++) {
		float3 & v = vert[i];
		lower.x = std::min(v.x, lower.x);
		lower.y = std::min(v.y, lower.y);
		lower.z = std::min(v.z, lower.z);
		upper.x = std::max(v.x, upper.x);
		upper.y = std::max(v.y, upper.y);
		upper.z = std::max(v.z, upper.z);
	}

	NvFlexUpdateTriangleMesh(lib->getLibrary(), mesh, vertices.getBuffer(), indices.getBuffer(), vertices.getElementCount(), indices.getElementCount() / 3, (float*)&lower, (float*)&upper);
}
