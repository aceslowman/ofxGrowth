#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
public:
    ofxGrowthNode * root;
//    vector< vector<ofMesh> > meshes;
    vector<shared_ptr<ofMesh>> meshes;
    
    void setupMesh();
    void checkChildren(ofxGrowthNode * temp_node, ofMesh * temp_mesh);
    void drawMesh();
    

    int num_nodes;
    
    float length;
    float crookedness;
    float density;
    int depth;
    ofVec3f growth_vector;
    
    ofxGrowth();
//    ~ofxGrowth();
};
