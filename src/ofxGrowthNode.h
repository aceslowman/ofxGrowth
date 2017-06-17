#pragma once

#include "ofMain.h"

class ofxGrowth;

class ofxGrowthNode {
    
public:
    
    bool isRoot;

    ofxGrowth &tree;
    ofVec3f location;
    ofVec3f growth_vector;
    ofColor color;

    int level;
    int distance_from_center;
    
    ofxGrowthNode * parent;
    vector<unique_ptr<ofxGrowthNode>> children;

    void setup();
    void update();
    void generateChildren();
    void updateChildren();
    
    ofColor setColor();
    void updateColor();
    
    void updateColor(int driver);
    
    float lengthRandom;
    ofVec3f growthVectorRandom;
    
    
    ofxGrowthNode(ofxGrowth &t);
    ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl);
    ~ofxGrowthNode();
};
