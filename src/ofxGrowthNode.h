#pragma once

#include "ofMain.h"

class ofxGrowth;

class ofxGrowthNode {
    
public:
    
    bool isRoot;
    bool b2d3d;

    ofxGrowth &tree;
    ofVec3f location;
    ofVec3f growth_vector;
    ofColor color;

    int level;
    float length;
    int distance_from_center;
    
    ofxGrowthNode * parent;
    vector<unique_ptr<ofxGrowthNode>> children;

    void setup();
    void update();
    void generateChildren();
    void updateChildren();
    
    ofColor setColor();  
    
    ofxGrowthNode(ofxGrowth &t);
    ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl);
    ~ofxGrowthNode();

private:

	float lengthRandom;
	ofVec3f growthVectorRandom;
};
