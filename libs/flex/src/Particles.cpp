#include "flex\Particles.h"
#include "NvFlex.h"

#include <stdlib.h> // rand
#include <time.h>	// time
#include <algorithm>

using namespace flex;

void Particels::allocate(Library * flex, int numParticles) {

	positions.allocate(flex, numParticles);
	velocities.allocate(flex, numParticles);
	phases.allocate(flex, numParticles);
	active.allocate(flex, numParticles);
}

void Particels::setPositionsRandom(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) {

	srand(time(NULL));

	float4 * par = positions.map();
	for (int i = 0; i < positions.getElementCount(); i++) {
		float4 p;
		p.x = x_min + ((float)rand() / RAND_MAX) * (x_max - x_min);
		p.y = y_min + ((float)rand() / RAND_MAX) * (y_max - y_min);
		p.z = z_min + ((float)rand() / RAND_MAX) * (z_max - z_min);
		p.w = 1.f;
		par[i] = p;
	}
	positions.unmap();
}

void Particels::setVelocitiesRandom(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) {

	srand(time(NULL));

	float4 * vel = velocities.map();
	for (int i = 0; i < velocities.getElementCount(); i++) {
		float4 v;
		v.x = x_min + ((float)rand() / RAND_MAX) * (x_max - x_min);
		v.y = y_min + ((float)rand() / RAND_MAX) * (y_max - y_min);
		v.z = z_min + ((float)rand() / RAND_MAX) * (z_max - z_min);
		v.w = 0.f;
		vel[i] = v;
	}
	velocities.unmap();
}

void Particels::setPhases(int group, int phase, int first, int n) {
	int * pha = phases.map();
	n = n == -1 ? phases.getElementCount() : n;
	for (int i = first; i < n; i++) {
		pha[i] = NvFlexMakePhase(group, phase);
	}
	phases.unmap();
}

void Particels::setPhasesFluid(int group, int first, int n) {
	setPhases(group, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid, first, n);
}

void Particels::setPhasesRest(int group, int first, int n) {
	setPhases(group, eNvFlexPhaseSelfCollide | eNvFlexPhaseSelfCollideFilter, first, n);
}

void Particels::setActive(int first, int numActive) {

	this->numActive = numActive;

	int count = active.getElementCount();
	if (numActive < 0 || numActive > count)
		numActive = count;

	int * act = active.map();
	for (int i = 0; i < numActive; i++) {
		act[i] = (first + i) % count;
	}
	for (int i = numActive; i < count; i++) {
		act[i] = -1;
	}
	active.unmap();
}

void Particels::emitGrid(float4 center, float4 velocity, float spacing, int width, int height, int depth, int first) {

	int i = first == -1 ? numActive : first;
	int count = width * height * depth;
	int total = positions.getElementCount();

	if (i + count > total)
		count = total - i;

	float4 offset;
	offset.x = center.x - width * spacing * 0.5;
	offset.y = center.y - height * spacing * 0.5;
	offset.z = center.z - depth * spacing * 0.5;

	float4 * par = positions.map() + i;
	float4 * vel = velocities.map() + i;
	int * act = active.map() + i;
	float4 p;
	p.w = 1.0f;

	for (int z = 0; z < depth; z++) {
		p.z = offset.z + z * spacing;
		for (int y = 0; y < height; y++) {
			p.y = offset.y + y * spacing;
			for (int x = 0; x < width; x++) {
				p.x = offset.x + x * spacing;
				*(par++) = p;
				*(vel++) = velocity;
				*(act++) = i;
				i++;
				if (i >= total)
					goto exit_loop;
			}
		}
	}
exit_loop:
	if (i > numActive)
		numActive = i;

	active.unmap();
	velocities.unmap();
	positions.unmap();

	//setActive(0, numActive + count);
}

void Particels::setBuffers(Solver * solver) {
	solver->setParticles(positions, positions.getElementCount());
	solver->setVelocities(velocities, velocities.getElementCount());
	solver->setPhases(phases, phases.getElementCount());
	solver->setActive(active, numActive);
}

void Particels::getBuffers(Solver * solver) {
	solver->getParticles(positions, positions.getElementCount());
	solver->getVelocities(velocities, velocities.getElementCount());
}
