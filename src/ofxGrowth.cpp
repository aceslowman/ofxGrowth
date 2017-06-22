#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
	origin = ofVec3f(0, 0, 0);

    node_max    = 10.0;
    crookedness = 0.2;
    density     = 0.08;
    depth       = 2;
    dim_f       = 0.2;
    growth_vector = ofVec3f(0,1,0);
    length      = 30.0;
    
    b2d3d = true;
}

ofxGrowth::~ofxGrowth(){
	ofLog(OF_LOG_NOTICE, "Deleting tree...");
}

//--------------------------------------------------------------
void ofxGrowth::setupTree(){
    root = new ofxGrowthNode(*this);
}

//--------------------------------------------------------------
void ofxGrowth::updateTree(){
    root->update();
}

