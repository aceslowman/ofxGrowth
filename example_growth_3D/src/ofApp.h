#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGrowth.h"

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
    
    bool debug;
    bool b_leaves;
		
    ofEasyCam cam;
    ofLight pointLight;
    
    ofxPanel gui;
    ofParameterGroup growth_group;
    ofParameterGroup light_group;
    
    ofParameter<float> growth_density;
    ofParameter<float> growth_length;
    ofParameter<int>   growth_segments;
    ofParameter<int>   growth_depth;
    ofParameter<int>   growth_leaf_level;
    ofParameter<float> growth_crookedness;
    
    ofParameter<ofFloatColor> light_color;
    ofParameter<ofVec3f> light_position;

    Growth growth;
};
