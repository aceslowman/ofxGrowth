#pragma once

#include "ofMain.h"
#include "ofxGrowth.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    void drawEuler();
    
    void updateTree();
    
    ofxGrowth growth;
    ofEasyCam cam;
    
    ofxPanel gui;
    ofParameterGroup growth_gui;
    
    ofParameter<int> depth;
    ofParameter<int> traversal_speed;
    ofParameter<int> node_max;
    ofParameter<int> stroke_width;
    ofParameter<float> length;
    ofParameter<float> density;
    ofParameter<float> diminish;
    ofParameter<float> crookedness;
    ofParameter<ofVec3f> growth_vector;
    ofParameter<bool> b_traverse;
    ofParameter<bool> b2d3d;
    
    ofParameterGroup movement_gui;
    ofParameter<float> lfo_1_rate;
    ofParameter<bool> b_lfo_1;
    ofParameter<float> saw_1_rate;
    
    bool useEasyCam;
    
    void onParamChange(ofAbstractParameter& e);
    
    ofxSyphonServer syphon;
};
