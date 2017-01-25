#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
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
    
    seed.setPosition(this->origin);
}

//--------------------------------------------------------------
ofxGrowth::~ofxGrowth(){
    branches.clear();
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    setupBranches();
}

//--------------------------------------------------------------
void ofxGrowth::setupBranches(){
    ofVec3f initial_vector = this->growth_vector;
    
    shared_ptr<ofxBranch> initial_branch(new ofxBranch());
    branches.push_back(initial_branch);
    
    branches[0]->generateBranch(&seed, initial_vector, 0);
    
    for(int i = 0; i < branches[0]->nodes.size(); i++){
        shared_ptr<ofxBranch> t_branch(new ofxBranch());
        branches.push_back(t_branch);
        
        ofVec3f node_position = branches[0]->getMesh().getVertices()[i];
        ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
        
        branches.back()->generateBranch(branches[0]->nodes[i].get(), t_vec, 1);
        branches.back()->setParent(*branches[0].get());
    }
    
    std::set<ofNode*> t_children = branches[0]->getChildren();
    
    for (set<ofNode*>::iterator i = t_children.begin(); i != t_children.end(); i++) {
        auto element = *i;
    }
    
}

void ofxGrowth::draw(){
    for(int i = 0; i < branches.size(); i++){
        branches[i]->draw();
    }
}

void ofxGrowth::setDensity(float density){this->density = density;}
void ofxGrowth::setLength(float length){this->length = length;}
void ofxGrowth::setScale(float scale){this->scale = scale;}
void ofxGrowth::setSegments(int segments){this->segments = segments;}
void ofxGrowth::setDepth(int depth){this->depth = depth;}
void ofxGrowth::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void ofxGrowth::setCrookedness(float crookedness){this->crookedness = crookedness;}
