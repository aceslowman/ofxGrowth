#include "ofxGrowthBranch.h"

//--------------------------------------------------------------
ofxGrowthBranch::ofxGrowthBranch(){
    this->density       = 0.2;
    this->length        = 0.7;
    this->scale         = 60;
    this->segments      = 35;
    this->depth         = 3;
    this->leaf_level    = 3;
    this->crookedness   = 0.5;
    this->origin        = ofVec3f(0,0,0);
    this->f_dim         = 0.5;
    this->color_mode    = 1;
    this->growth_vector = ofVec3f(0,1,0);
    this->dim_strokewidth = false;

    glPointSize(8);
}

//--------------------------------------------------------------
void ofxGrowthBranch::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofMesh t_branch;
    t_branch.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_branch.setupIndicesAuto();
    
    t_branch.addIndex(0);
    t_branch.addVertex(origin);
    
    //Diminish parameters
    int t_segments = this->segments;
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec          = initial_vector;
    ofVec3f t_point        = origin;
    ofVec3f t_point_mirror = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 1; i < t_segments; i++){
        float t_length_rand = ( t_length * ofRandomuf() );
        t_point = t_point + (t_vec *  t_length_rand);
        
        t_branch.addIndex(i);
        t_branch.addColor(ofFloatColor(0));
        t_branch.addVertex(t_point);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * this->crookedness),-1.0,1.0)
        );
        
    }
    
    getMesh() = t_branch;
}

void ofxGrowthBranch::setDensity(float density){this->density = density;}
void ofxGrowthBranch::setLength(float length){this->length = length;}
void ofxGrowthBranch::setScale(float scale){this->scale = scale;}
void ofxGrowthBranch::setSegments(int segments){this->segments = segments;}
void ofxGrowthBranch::setDepth(int depth){this->depth = depth;}
void ofxGrowthBranch::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void ofxGrowthBranch::setCrookedness(float crookedness){this->crookedness = crookedness;}
