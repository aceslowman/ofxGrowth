#include "ofxBranch.h"

//--------------------------------------------------------------
ofxBranch::ofxBranch(){
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
ofxBranch::~ofxBranch(){
    nodes.clear();
}

//--------------------------------------------------------------
void ofxBranch::generateBranch(ofNode *parent_branch, ofNode *parent_node, ofVec3f initial_vector, int level){
    origin = parent_node->getPosition();
    
    ofMesh t_branch;
    shared_ptr<ofNode> t_node(new ofNode());
    
    t_branch.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_branch.setupIndicesAuto();
    
    t_branch.addIndex(0);
    t_branch.addColor(ofFloatColor(0));
    t_branch.addVertex(origin);
    t_node->setPosition(origin);
    
    t_node->setParent(*parent_branch);
    
    nodes.push_back(t_node);
    
    //Diminish parameters
    int t_segments = this->segments;
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec          = initial_vector;
    ofVec3f t_point        = origin;
    ofVec3f t_point_mirror = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 1; i < t_segments; i++){
        shared_ptr<ofNode> t_node(new ofNode());
        
        float t_length_rand = ( t_length * ofRandomuf() );
        t_point = t_point + (t_vec *  t_length_rand);
        
        t_branch.addIndex(i);
        t_branch.addColor(ofFloatColor(0));
        t_branch.addVertex(t_point);
        t_node->setPosition(t_point);
        
        t_node->setParent(*parent_branch);
        
        nodes.push_back(t_node);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * this->crookedness),-1.0,1.0)
        );
    }
    
    getMesh() = t_branch;
}

void ofxBranch::setDensity(float density){this->density = density;}
void ofxBranch::setLength(float length){this->length = length;}
void ofxBranch::setScale(float scale){this->scale = scale;}
void ofxBranch::setSegments(int segments){this->segments = segments;}
void ofxBranch::setDepth(int depth){this->depth = depth;}
void ofxBranch::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void ofxBranch::setCrookedness(float crookedness){this->crookedness = crookedness;}
