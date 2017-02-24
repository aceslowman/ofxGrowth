#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    lengthRandom = ofRandomuf();
    growthVectorRandom = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    distance_from_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    
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
        growth_vector = ofVec3f(
                                ofClamp(tree.growth_vector.x + (growthVectorRandom.x * tree.crookedness),-1.0,1.0),
                                ofClamp(tree.growth_vector.y + (growthVectorRandom.y * tree.crookedness),-1.0,1.0),
                                ofClamp(tree.growth_vector.z + (growthVectorRandom.z * tree.crookedness),-1.0,1.0)
                                );
    
    
    float length = (tree.length * pow(tree.dim_f,level))*lengthRandom;
    
    location = parent->location + (growth_vector * length);
    
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
