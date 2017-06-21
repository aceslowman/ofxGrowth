#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth{
    
public:

    void setupTree();
    void updateTree();
//    void updateNodes(int l, ofVec3f gv);
    
    int num_nodes;      //how many nodes are currently in the tree?
    int current_mesh_id;

    
    ofxGrowth();
    ~ofxGrowth();
    

    /*
     TREE PARAMETERS
    */
	ofVec3f growth_vector;
	ofVec3f origin;

    float length;       //how long is the entire tree?
    float crookedness;  //how crooked are the branches on the tree?
    float density;      //how often do branches emerge from nodes
    float dim_f;        //how much shorter does each successive branch become?
    int   depth;        //how many levels of branches are there?
    
    bool b2d3d;



    int node_max;

    
    vector<ofxGrowthNode*> nodes;
    ofxGrowthNode * root;

private:
};
