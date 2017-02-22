#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
    
    
public:
    ofxGrowthNode * root;
//    vector<shared_ptr<ofMesh>> meshes;
    vector<unique_ptr<ofMesh>> meshes;
    
    void setup();
    void rebuild();
    void setupMesh();
    void generateMesh(ofxGrowthNode * temp_node, ofMesh * temp_mesh, int mesh_index, bool share_root);
    void updateChildren(ofxGrowthNode * temp_node);
    void drawMesh();
    void drawPoints();
    void updateMesh();
    
    void animate();

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
    
private:
    
    int driver;
};
