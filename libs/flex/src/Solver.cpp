#include "flex\Solver.h"
#include "flex\Buffer.h"
#include "NvFlex.h"

#include <float.h>
#include <math.h>

using namespace flex;

Solver * Solver::create(Library * lib, int maxParticles, int maxDiffuseParticles, int maxNeighborsPerParticle) {

	NvFlexSolver * sol = NvFlexCreateSolver(lib->getLibrary(), maxParticles, maxDiffuseParticles, maxNeighborsPerParticle);
	if (sol)
		return new Solver(sol);
	else
		return nullptr;
}

void Solver::destroy() {
	NvFlexDestroySolver(solver);
}

Solver::Solver(NvFlexSolver * sol) : solver(sol) {
	params = new NvFlexParams;
	NvFlexGetParams(solver, params);

	params->gravity[0] = 0.0f;
	params->gravity[1] = -9.8f;
	params->gravity[2] = 0.0f;

	params->wind[0] = 0.0f;
	params->wind[1] = 0.0f;
	params->wind[2] = 0.0f;

	params->radius = 0.15f;
	params->viscosity = 0.0f;
	params->dynamicFriction = 0.0f;
	params->staticFriction = 0.0f;
	params->particleFriction = 0.0f; // scale friction between particles by default
	params->freeSurfaceDrag = 0.0f;
	params->drag = 0.0f;
	params->lift = 0.0f;
	params->numIterations = 3;
	params->fluidRestDistance = params->radius * 0.5f;
	params->solidRestDistance = 0.0f;

	params->anisotropyScale = 1.0f;
	params->anisotropyMin = 0.1f;
	params->anisotropyMax = 2.0f;
	params->smoothing = 1.0f;

	params->dissipation = 0.0f;
	params->damping = 0.0f;
	params->particleCollisionMargin = 0.0f;
	params->shapeCollisionMargin = 0.0f;
	params->collisionDistance = 0.0f;
	params->plasticThreshold = 0.0f;
	params->plasticCreep = 0.0f;
	params->fluid = true;
	params->sleepThreshold = 0.0f;
	params->shockPropagation = 0.0f;
	params->restitution = 0.0f;

	params->maxSpeed = FLT_MAX;
	params->maxAcceleration = 100.0f;	// approximately 10x gravity

	params->relaxationMode = eNvFlexRelaxationLocal;
	params->relaxationFactor = 1.0f;
	params->solidPressure = 1.0f;
	params->adhesion = 0.0f;
	params->cohesion = 0.025f;
	params->surfaceTension = 0.0f;
	params->vorticityConfinement = 0.0f;
	params->buoyancy = 1.0f;
	params->diffuseThreshold = 100.0f;
	params->diffuseBuoyancy = 1.0f;
	params->diffuseDrag = 0.8f;
	params->diffuseBallistic = 16;
	params->diffuseSortAxis[0] = 0.0f;
	params->diffuseSortAxis[1] = 0.0f;
	params->diffuseSortAxis[2] = 0.0f;
	params->diffuseLifetime = 2.0f;

}

Solver::~Solver() {
	destroy();
}

void Solver::setParticles(Buffer & particles, int n) {
	NvFlexSetParticles(solver, particles, n);
}

void Solver::getParticles(Buffer & particles, int n) {
	NvFlexGetParticles(solver, particles, n);
}

void Solver::setVelocities(Buffer & velocities, int n) {
	NvFlexSetVelocities(solver, velocities, n);
}

void Solver::getVelocities(Buffer & velocities, int n) {
	NvFlexGetVelocities(solver, velocities, n);
}

void Solver::setPhases(Buffer & phases, int n) {
	NvFlexSetPhases(solver, phases, n);
}

void Solver::getPhases(Buffer & phases, int n) {
	NvFlexGetPhases(solver, phases, n);
}

int Solver::makePhaseSelfCollide(int group) {
	return NvFlexMakePhase(group, eNvFlexPhaseSelfCollide);
}

int Solver::makePhaseFluid(int group) {
	return NvFlexMakePhase(group, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid);
}

void Solver::setActive(Buffer & active, int n) {
	NvFlexSetActive(solver, active, n);
}

void Solver::getActive(Buffer & active, int n) {
	NvFlexGetActive(solver, active);
}

int Solver::getActiveCount() {
	return NvFlexGetActiveCount(solver);
}

void Solver::getSmoothParticles(Buffer & particles, int n) {
	NvFlexGetSmoothParticles(solver, particles, n);
}

void Solver::getAnisotropy(Buffer & anisotropy1, Buffer & anisotropy2, Buffer & anisotropy3) {
	NvFlexGetAnisotropy(solver, anisotropy1, anisotropy2, anisotropy3);
}

void Solver::setShapes(Buffer & geometry, Buffer & positions, Buffer & rotations, Buffer & flags, int n) {
	NvFlexSetShapes(solver, geometry, positions, rotations, NULL, NULL, flags, n);
}

void Solver::setRigids(Buffer & offsets, Buffer & indices, Buffer & restPositions, Buffer & restNormals, Buffer & stiffness, Buffer & rotations, Buffer & translations, int numRigids, int numIndices) {
	NvFlexSetRigids(solver, offsets, indices, restPositions, restNormals, stiffness, rotations, translations, numRigids, numIndices);
}

void Solver::setNumIterations(int numIterations) {
	params->numIterations = numIterations;
}

void Solver::setGravity(float gravity_x, float gravity_y, float gravity_z) {
	params->gravity[0] = gravity_x;
	params->gravity[1] = gravity_y;
	params->gravity[2] = gravity_z;
}

void Solver::setRadius(float radius) {
	params->radius = radius;
}

void Solver::setFluidRestDistance(float fluidRestDistance) {
	params->fluidRestDistance = fluidRestDistance;
}

float Solver::getFluidRestDistance() const {
	return params->fluidRestDistance;
}

void Solver::setSleepThreshold(float sleepThreshold) {
	params->sleepThreshold = sleepThreshold;
}

void Solver::setDamping(float damping) {
	params->damping = damping;
}

void Solver::setFluid(bool fluid) {
	params->fluid = fluid;
}

void Solver::setAdhesion(float adhesion) {
	params->adhesion = adhesion;
}

void Solver::setCohesion(float cohesion) {
	params->cohesion = cohesion;
}

void Solver::setSurfaceTension(float surfaceTension) {
	params->surfaceTension = surfaceTension;
}

void Solver::setViscosity(float viscosity) {
	params->viscosity = viscosity;
}

void Solver::setVorticityConfinement(float vorticityConfinement) {
	params->vorticityConfinement = vorticityConfinement;
}

void Solver::setSmoothing(float smoothing) {
	params->smoothing = smoothing;
}

void Solver::setAnisotropyScale(float anisotropyScale) {
	params->anisotropyScale = anisotropyScale;
}

void Solver::setAnisotropyMin(float anisotropyMin) {
	params->anisotropyMin = anisotropyMin;
}

void Solver::setAnisotropyMax(float anisotropyMax) {
	params->anisotropyMax = anisotropyMax;
}

void Solver::setCollisionDistance(float collisionDistance) {
	params->collisionDistance = collisionDistance;
}

void Solver::setParticleCollisionMargin(float particleCollisionMargin) {
	params->particleCollisionMargin = particleCollisionMargin;
}

void Solver::setShapeCollisionMargin(float shapeCollisionMargin) {
	params->shapeCollisionMargin = shapeCollisionMargin;
}

void Solver::addPlane(float x, float y, float z, float distance) {
	int i = params->numPlanes;
	float l = sqrt(x*x + y*y + z*z);
	params->planes[i][0] = x / l;
	params->planes[i][1] = y / l;
	params->planes[i][2] = z / l;
	params->planes[i][3] = distance;
	params->numPlanes++;
}

void Solver::update(float dt, int substeps, bool enableTimers) {
	NvFlexSetParams(solver, params);
	NvFlexUpdateSolver(solver, dt, substeps, enableTimers);
}
