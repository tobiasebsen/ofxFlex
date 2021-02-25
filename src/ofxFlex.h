#pragma once

#include "flex\Library.h"
#include "flex\Solver.h"
#include "flex\Shapes.h"
#include "flex\Rigids.h"
#include "flex\TriangleMesh.h"

#include "flex\Buffer.h"

#include "flex\Particles.h"


typedef flex::Library ofxFlexLibrary;
typedef flex::Solver ofxFlexSolver;
typedef flex::Shapes ofxFlexShapes;
typedef flex::Rigids ofxFlexRigids;
typedef flex::TriangleMesh ofxFlexTriangleMesh;

typedef flex::Buffer ofxFlexBuffer;
typedef flex::BufferT<int> ofxFlexBuffer1i;
typedef flex::BufferT<float> ofxFlexBuffer1f;
typedef flex::BufferT<float3> ofxFlexBuffer3f;
typedef flex::BufferT<float4> ofxFlexBuffer4f;

typedef flex::Particels ofxFlexParticles;
