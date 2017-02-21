#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    distance_to_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    
    generateChildren();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl): tree(t), parent(p) {
    distance_to_center = parent->distance_to_center + 1;
    level              = lvl;
    
    setupNode();
}

//--------------------------------------------------------------
void ofxGrowthNode::setupNode(){
    growth_vector = ofVec3f(
        ofClamp(parent->growth_vector.x + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.y + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.z + (ofRandomf() * tree.crookedness),-1.0,1.0)
    );
    
    float length = tree.length * ofRandomuf()*(tree.dim_f / (level + 1));
    
    location = parent->location + (growth_vector * length);
    
    if(level < tree.depth){
        generateChildren();
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::generateChildren(){
    
    if(distance_to_center < tree.node_max){
        shared_ptr<ofxGrowthNode> child(new ofxGrowthNode(tree, this, level));
        children.push_back(child);
        
        //generate next in new branch
        if(ofRandomuf() < tree.density){
            shared_ptr<ofxGrowthNode> child(new ofxGrowthNode(tree,this,level + 1));
            children.push_back(child);
        }
    }
}
