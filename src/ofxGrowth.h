#pragma once

#include "ofMain.h"

class ofxGrowth {

public:

    void setup();
    void update();
    void drawPoints();
    void drawMeshes();
    void drawLeaves();
    void drawDebug();
    void clearAll();

    void setupBranches();
    ofMesh generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    ofPath generateLeaf(ofPolyline poly, int level);

    void colorMesh(int coloring_type);
    void updateNodeSize();
    int  getNodeSize();

    void setDensity(float density);
    void setLength(float length);
    void setScale(float scale);
    void setSegments(int segments);
    void setDepth(int depth);
    void setLeafLevel(int leaf_level);
    void setCrookedness(float crookedness);
    void setColormode(int color_mode);
    
    /*
     branches[level][branch_id]
     */
    vector< vector<ofMesh> > branches;
    vector< vector<ofPath> > leaves;
    
    int node_size;

    ofxGrowth();

private:

    float   density;
    float   length;
    float   scale;
    int     segments;
    int     depth;
    int     leaf_level;
    float   crookedness;
    int     color_mode;
    ofVec3f origin;
    ofVec3f growth_vector;
    
    
    
    bool dim_strokewidth;

    float f_dim;
};
