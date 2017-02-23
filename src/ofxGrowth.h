#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
    
    
public:
    ofxGrowthNode * root;
    vector<unique_ptr<ofMesh>> meshes;
    
    void setup();
    void setupMesh(ofxGrowthNode * temp_node, ofMesh * temp_mesh, int mesh_node_id, bool share_root);
    void update();
    void updateMesh(ofxGrowthNode * temp_node, ofMesh * temp_mesh, int mesh_node_id, int current_mesh);
    
    void drawMesh();
    void drawPoints();
    void animate();
    void rebuild();
    
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
