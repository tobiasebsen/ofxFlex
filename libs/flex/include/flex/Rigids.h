#pragma once

#include "flex\Types.h"
#include "flex\Library.h"
#include "flex\Buffer.h"
#include "flex\Solver.h"

#include <vector>

namespace flex {

	class Rigids {
	public:

		void allocate(Library * lib, int numRigids, int numIndices);

		void add(
			const std::vector<int> & indices,
			const std::vector<float3> & restPositions,
			const std::vector<float4> & restNormals,
			float stiffness, const float4 & rotation, const float3 & translation);

		void update(Solver * solver);

	private:
		BufferT<int> offsets;
		BufferT<int> indices;
		BufferT<float3> restPositions;
		BufferT<float4> restNormals;
		BufferT<float> stiffness;
		BufferT<float4> rotations;
		BufferT<float3> translations;
		int numRigids = 0;
		int numIndices = 0;
	};

}