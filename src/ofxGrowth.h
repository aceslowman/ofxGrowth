#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
public:
    ofxGrowthNode * root;
    vector<shared_ptr<ofMesh>> meshes;
    
    void setup();
    void setupMesh();
    void checkChildren(ofxGrowthNode * temp_node, ofMesh * temp_mesh);
    void drawMesh();
    
    void updateNodes();
    void updateMesh();

    int num_nodes;
    
    float length;
    float crookedness;
    float density;
    float dim_f;
    int depth;
    int node_max;
    ofVec3f growth_vector;
    
    ofxGrowth();
    ~ofxGrowth();
};
