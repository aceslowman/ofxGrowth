#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"
#include "ofThread.h"

class ofxGrowth{
    
public:

    void setup();
    void setupMesh(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
    
    void update();
    void updateMesh(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
    void updateNodes(int l, ofVec3f gv);
    
    void drawMesh();
    void drawDebug();
    
    int num_nodes;      //how many nodes are currently in the tree?
    int current_mesh_id;
    
    ofVec3f growth_vector;
    ofVec3f origin;
    
    ofxGrowth();
    ~ofxGrowth();
    
    /*
     TREE PARAMETERS
    */
    float length;       //how long is the entire tree?
    float crookedness;  //how crooked are the branches on the tree?
    float density;      //how often do branches emerge from nodes
    float dim_f;        //how much shorter does each successive branch become?
    int   depth;        //how many levels of branches are there?
    
    bool b2d3d;

    /*
     DRAWING PARAMETERS
    */
    int stroke_width;   //how thick are the branches drawn? (line)
    

    
    /*
     TRAVERSAL PARAMETERS
    */
    int node_max;
    int traversal_node;
    int traversal_speed;
    
    int cap_mesh_node_id;
    int cap_current_mesh_id;
    ofVboMesh * cap_current_mesh;
    ofxGrowthNode * cap_current_node;
    

    
    vector<unique_ptr<ofVboMesh>> meshes;
    ofxGrowthNode * root;
    

    
    ofVboMesh mesh_ellipse;
    
    int driver;
    
    bool b_traverse;
};
