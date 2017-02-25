#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    parent = NULL;
    lengthRandom = ofRandomuf();
    growthVectorRandom = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    distance_from_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    location = tree.origin;
    
    isRoot = true;
    
    generateChildren();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl): tree(t), parent(p) {
    lengthRandom = ofRandomuf();
    growthVectorRandom = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    distance_from_center = parent->distance_from_center + 1;
    level              = lvl;
    
    growth_vector = ofVec3f(
                            ofClamp(parent->growth_vector.x + (growthVectorRandom.x * tree.crookedness),-1.0,1.0),
                            ofClamp(parent->growth_vector.y + (growthVectorRandom.y * tree.crookedness),-1.0,1.0),
                            ofClamp(parent->growth_vector.z + (growthVectorRandom.z * tree.crookedness),-1.0,1.0)
                            );
    
    float length = (tree.length * pow(tree.dim_f,level))*lengthRandom;
    
    location = parent->location + (growth_vector * length);
    
    isRoot = false;
    
    setup();
}

ofxGrowthNode::~ofxGrowthNode(){}

//--------------------------------------------------------------
void ofxGrowthNode::setup(){
    if(level < tree.depth && distance_from_center < tree.node_max){
        generateChildren();
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::update(){
    float length = (tree.length * pow(tree.dim_f,level))*lengthRandom;
    
    if(isRoot){
        growth_vector = tree.growth_vector;
        
        location = tree.origin + (growth_vector * length);
    }else{
        growth_vector = ofVec3f(
            ofClamp(parent->growth_vector.x + (growthVectorRandom.x * tree.crookedness),-1.0,1.0),
            ofClamp(parent->growth_vector.y + (growthVectorRandom.y * tree.crookedness),-1.0,1.0),
            ofClamp(parent->growth_vector.z + (growthVectorRandom.z * tree.crookedness),-1.0,1.0)
        );
        
        location = parent->location + (growth_vector * length);
    }
    
    
    
    updateChildren();
}

//--------------------------------------------------------------
void ofxGrowthNode::generateChildren(){
    unique_ptr<ofxGrowthNode> child = std::make_unique<ofxGrowthNode>(tree, this, level);
    children.push_back(std::move(child));

    if(ofRandomuf() < tree.density && (level+1) < tree.depth){
        unique_ptr<ofxGrowthNode> child = std::make_unique<ofxGrowthNode>(tree, this, level+1);
        children.push_back(std::move(child));
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::updateChildren(){
    for (auto & child : children) {
        child->update();
    }
}
