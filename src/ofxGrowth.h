#pragma once

#include "ofMain.h"
#include "ofxBranch.h"

class ofxGrowth{

public:
    ofxGrowth();

    void setup();
    void setupBranches();
    void draw();

    void setDensity(float density);
    void setLength(float length);
    void setScale(float scale);
    void setSegments(int segments);
    void setDepth(int depth);
    void setLeafLevel(int leaf_level);
    void setCrookedness(float crookedness);
    void setColormode(int color_mode);
    
    vector<shared_ptr<ofxBranch>> branches;
    vector<ofMesh> meshes;
    
    ofNode seed;

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
