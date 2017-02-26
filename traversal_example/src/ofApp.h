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
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void updateTree();
    
    ofxGrowth growth;
    ofEasyCam cam;
    
    ofxPanel gui;
    ofParameterGroup growth_gui;
    
    
    ofParameter<int> depth;
    ofParameter<int> node_max;
    ofParameter<int> stroke_width;
    ofParameter<float> length;
    ofParameter<float> density;
    ofParameter<float> crookedness;
    ofParameter<ofVec3f> growth_vector;
    
    ofParameterGroup movement_gui;
    ofParameter<float> lfo_1_rate;
    ofParameter<bool> b_lfo_1;

    void onParamChange(ofAbstractParameter& e);
    
    ofxSyphonServer syphon;
};
