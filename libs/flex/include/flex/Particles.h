#pragma once

#include "flex\Types.h"
#include "flex\Library.h"
#include "flex\Buffer.h"
#include "flex\Solver.h"

namespace flex {

	class Particels {
	public:
		void allocate(Library * flex, int numParticles);

		void setPositionsRandom(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
		void setVelocitiesRandom(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);

		void setPhases(int group, int phase, int first = 0, int n = -1);
		void setPhasesFluid(int group, int first = 0, int n = -1);
		void setPhasesRest(int group, int first = 0, int n = -1);
		void setActive(int first = 0, int numActive = -1);

		void emitGrid(float4 center, float4 velocity, float spacing, int width, int height, int depth, int first = -1);

		void setBuffers(Solver * solver);
		void getBuffers(Solver * solver);

		const Buffer & getPositions() const { return positions; }
		const Buffer & getVelocities() const { return velocities; }

	private:
		BufferT<float4> positions;
		BufferT<float4> velocities;
		BufferT<int> phases;
		BufferT<int> active;
		int numActive = 0;
	};

}