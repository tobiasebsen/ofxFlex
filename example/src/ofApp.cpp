#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(0);
	cam.setupPerspective(false, 60, 1, 100);
	cam.setDistance(10);

	flex = ofxFlexLibrary::init();

	solver = ofxFlexSolver::create(flex, 50000, 0);

	solver->addPlane(0, 1, 0, 0);
	solver->addPlane(1, 0, -0.05, 1.75);
	solver->addPlane(-1, 0, -0.05, 1.75);
	solver->addPlane(0, 0, 1, 1.7);
	solver->addPlane(0, 0, -1, 1.7);

	particles.allocate(flex, 50000);
	particles.setPhasesFluid(0);

	positionsObj.allocate(50000 * sizeof(float) * 4, GL_DYNAMIC_DRAW);
	positionsBuf.allocate(flex, 50000, sizeof(4), positionsObj.getId());
}

//--------------------------------------------------------------
void ofApp::update(){

	float4 p = { 1.f, 7.2f, 0.f };
	float4 v = { 0.f, 0.f, 0.f };
	particles.getBuffers(solver);
	particles.emitGrid(p, v, solver->getFluidRestDistance(), 10, 1, 10);
	particles.setBuffers(solver);

	solver->update();

	solver->getSmoothParticles(positionsBuf, positionsBuf.getElementCount());
	positionsVbo.setVertexBuffer(positionsObj, 3, sizeof(float) * 4);
}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();
	positionsVbo.draw(GL_POINTS, 0, solver->getActiveCount());
	cam.end();

	ofDrawBitmapString(ofToString(ofGetFrameRate(), 1) + " fps", 20, 20);
	ofDrawBitmapString(ofToString(solver->getActiveCount()) + " particles", 20, 40);
}
