#pragma once

#include "ofMain.h"

class ofxGrowth;

class ofxGrowthNode {
    
public:

    ofxGrowth &tree;
    ofVec3f location;
    ofVec3f growth_vector;

    int level;
    int distance_from_center;
    
    ofxGrowthNode * parent;
    vector<unique_ptr<ofxGrowthNode>> children;

    
    void setupNode();
    void generateChildren();
    
    
    ofxGrowthNode(ofxGrowth &t);
    ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl);
    ~ofxGrowthNode();
};
