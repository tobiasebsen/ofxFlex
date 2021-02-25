#pragma once

#include "ofMain.h"
#include "ofxFlex.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

private:

	ofEasyCam cam;

	ofxFlexLibrary * flex;
	ofxFlexSolver * solver;
	ofxFlexParticles particles;

	ofBufferObject positionsObj;
	ofxFlexBuffer positionsBuf;
	ofVbo positionsVbo;
};
