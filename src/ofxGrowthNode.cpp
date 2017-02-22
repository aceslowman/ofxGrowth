#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    distance_from_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    
    generateChildren();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl): tree(t), parent(p) {
    distance_from_center = parent->distance_from_center + 1;
    level              = lvl;
    
    setupNode();
}

ofxGrowthNode::~ofxGrowthNode(){}

//--------------------------------------------------------------
void ofxGrowthNode::setupNode(){
    growth_vector = ofVec3f(
        ofClamp(parent->growth_vector.x + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.y + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.z + (ofRandomf() * tree.crookedness),-1.0,1.0)
    );
    
    float length = (tree.length * pow(tree.dim_f,level))*ofRandomuf();
    
    location = parent->location + (growth_vector * length);
    
    if(level < tree.depth && distance_from_center < tree.node_max){
        generateChildren();
    }
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
