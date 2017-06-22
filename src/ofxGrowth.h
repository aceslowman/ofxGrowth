#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth{
    
public:

	ofxGrowth();
	~ofxGrowth();

    void setupTree();
    void updateTree();

    /*
     TREE PARAMETERS
    */
	ofVec3f growth_vector;
	ofVec3f origin;

	int node_max;		//how many nodes on each branch?
    float length;       //how long is the entire tree?
    float crookedness;  //how crooked are the branches on the tree?
    float density;      //how often do branches emerge from nodes
    float dim_f;        //how much shorter does each successive branch become?
    int   depth;        //how many levels of branches are there?
    
    bool b2d3d;

    vector<ofxGrowthNode*> nodes;
    ofxGrowthNode * root;

private:
};
