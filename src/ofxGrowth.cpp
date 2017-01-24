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
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    setupBranches();
    
}

//--------------------------------------------------------------
void ofxGrowth::setupBranches(){
    ofVec3f initial_vector = this->growth_vector;
    
    ofxGrowthBranch initial_branch;
    initial_branch.generateBranch(this->origin, initial_vector, 0);
    
    branches.push_back(initial_branch);

    for(int i = 0; i < branches[0].getMesh().getNumVertices(); i++){
        ofVec3f node_position = branches[0].getMesh().getVertices()[i];
        ofxGrowthBranch t_branch;
        
        ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
        t_branch.generateBranch(node_position, t_vec, 1);
        
        t_branch.setParent(initial_branch);
        branches.push_back(t_branch);
    }
//    
//    
//    for(int current_level = 0; current_level <= this->depth; current_level++){
//        
//        for(int current_branch = 0; current_branch < branches.size(); current_branch++){
//            
//            if(current_level != this->depth){
//                for(int current_node = 0; current_node < branches[current_level][current_branch].getVertices().size(); current_node++){
//                    
//                    ofVec3f current_node_position = branches[current_level][current_branch].getVertex(current_node);
//                    ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
//                    
//                    if(ofRandomuf() < this->density){
//                        ofMesh t_branch = generateBranch(current_node_position, t_vec, current_level+1);
//                        addChild(t_branch);
//                    }
//                }
//            }
//        }
//        branches.push_back(t_branches);
//    }
}

void ofxGrowth::draw(){
    for(int i = 0; i < branches.size(); i++){
        branches[i].draw();
        
    }
}

void ofxGrowth::setDensity(float density){this->density = density;}
void ofxGrowth::setLength(float length){this->length = length;}
void ofxGrowth::setScale(float scale){this->scale = scale;}
void ofxGrowth::setSegments(int segments){this->segments = segments;}
void ofxGrowth::setDepth(int depth){this->depth = depth;}
void ofxGrowth::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void ofxGrowth::setCrookedness(float crookedness){this->crookedness = crookedness;}
