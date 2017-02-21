#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    distance_to_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    
    generateChildren();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p): tree(t), parent(p) {
    distance_to_center = parent->distance_to_center + 1;
    level = parent->level;
    
    
    setupNode();
}

//--------------------------------------------------------------
void ofxGrowthNode::setupNode(){
    growth_vector = ofVec3f(
        ofClamp(parent->growth_vector.x + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.y + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.z + (ofRandomf() * tree.crookedness),-1.0,1.0)
    );
    
    float length = tree.length * ofRandomuf();
    
    //update location
    location = parent->location + (growth_vector * length);
    
    if(level < tree.depth){
        generateChildren();
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::generateChildren(){
    //generate next in branch
    if(distance_to_center < 20){
        shared_ptr<ofxGrowthNode> child(new ofxGrowthNode(tree,this));
        children.push_back(child);
        
        //generate next in new branch
        if(ofRandomuf() < tree.density){
            shared_ptr<ofxGrowthNode> child(new ofxGrowthNode(tree,this));
            //what are some of the differences when I go into a further branch?
            //I have to apply alterations to the chain here:
            
            child->level = level + 1;
            children.push_back(child);
        }
    }
}
