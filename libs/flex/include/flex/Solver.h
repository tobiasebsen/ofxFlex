#pragma once

#include "flex\Library.h"
#include "flex\Buffer.h"

struct NvFlexSolver;
struct NvFlexParams;

namespace flex {

	class Solver {
	public:
		~Solver();

		static Solver * create(Library * lib, int maxParticles, int maxDiffuseParticles, int maxNeighborsPerParticle = 96);
		void destroy();


		// PARTICLES
		void setParticles(Buffer & particles, int n);
		void getParticles(Buffer & particles, int n);

		void setVelocities(Buffer & velocities, int n);
		void getVelocities(Buffer & velocities, int n);

		void setPhases(Buffer & phases, int n);
		void getPhases(Buffer & phases, int n);
		int makePhaseSelfCollide(int group);
		int makePhaseFluid(int group);

		void setActive(Buffer & active, int n);
		void getActive(Buffer & active, int n);
		int getActiveCount();

		void getSmoothParticles(Buffer & particles, int n);
		void getAnisotropy(Buffer & anisotropy1, Buffer & anisotropy2, Buffer & anisotropy3);


		// SHAPES
		void setShapes(Buffer & geometry, Buffer & positions, Buffer & rotations, Buffer & flags, int n);


		// RIGIDS
		void setRigids(Buffer & offsets, Buffer & indices, Buffer & restPositions, Buffer & restNormals, Buffer & stiffness, Buffer & rotations, Buffer & translations, int numRigids, int numIndices);


		// PARAMS
		void setNumIterations(int numIterations);
		void setGravity(float gravity_x, float gravity_y, float gravity_z);
		void setRadius(float radius);
		// Fluid
		void setFluidRestDistance(float fluidRestDistance);
		float getFluidRestDistance() const;
		void setSleepThreshold(float sleepThreshold);
		void setDamping(float damping);
		void setFluid(bool fluid);
		void setAdhesion(float adhesion);
		void setCohesion(float cohesion);
		void setSurfaceTension(float surfaceTension);
		void setViscosity(float viscosity);
		void setVorticityConfinement(float vorticityConfinement);
		// Rendering
		void setSmoothing(float smoothing);
		void setAnisotropyScale(float anisotropyScale);
		void setAnisotropyMin(float anisotropyMin);
		void setAnisotropyMax(float anisotropyMax);
		// Collision
		void setCollisionDistance(float collisionDistance);
		void setParticleCollisionMargin(float particleCollisionMargin);
		void setShapeCollisionMargin(float shapeCollisionMargin);

		// PLANES
		void addPlane(float x, float y, float z, float distance);


		void update(float dt = 1. / 60., int substeps = 2, bool enableTimers = false);

		const NvFlexSolver * getSolver() const { return solver; }

	private:
		Solver(NvFlexSolver * sol);

		NvFlexSolver * solver;
		NvFlexParams * params;
	};

}