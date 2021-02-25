#pragma once

#include "flex\Types.h"
#include "flex\Library.h"
#include "flex\Buffer.h"

namespace flex {

	class TriangleMesh {
	public:

		static TriangleMesh * create(Library * lib);

		void update(float3 * vertices, int numVertices, int * indices, int numIndices);

		int getId() { return mesh; }

	private:
		TriangleMesh(Library * l, int m) : lib(l), mesh(m) {}

		Library * lib;
		int mesh;
		BufferT<float3> vertices;
		BufferT<int> indices;
	};

}