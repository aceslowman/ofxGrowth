#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    parent = NULL;
    isRoot = true;
    b2d3d  = tree.b2d3d;
    
    lengthRandom         = ofRandomuf();
    growthVectorRandom   = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    distance_from_center = 0;
    level                = 0;
    growth_vector        = t.growth_vector;
    location             = tree.origin;
    color				 = setColor();
    
	setup();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p, int lvl): tree(t), parent(p) {
	isRoot = false;
    b2d3d  = tree.b2d3d;

    lengthRandom		 = ofRandomuf();
    growthVectorRandom	 = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    growth_vector		 = ofVec3f(
        ofClamp(parent->growth_vector.x + (growthVectorRandom.x * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.y + (growthVectorRandom.y * tree.crookedness),-1.0,1.0),
        (b2d3d) ? ofClamp(parent->growth_vector.z + (growthVectorRandom.z * tree.crookedness),-1.0,1.0): 0);

    distance_from_center = parent->distance_from_center + 1;
    level                = lvl;
    length			     = pow(tree.dim_f,level)*lengthRandom;
    location			 = parent->location + (growth_vector * length);
    color				 = setColor();
    
    setup();
}

ofxGrowthNode::~ofxGrowthNode(){
	ofLog(OF_LOG_NOTICE, "Deleting node...");
}

//--------------------------------------------------------------
void ofxGrowthNode::setup(){
    if(level < tree.depth && distance_from_center < tree.node_max){
        generateChildren();
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::update(){
    length = pow(tree.dim_f,level)*lengthRandom;
    
    if(isRoot){
        growth_vector = tree.growth_vector;
        
        location = tree.origin + (growth_vector * length);
    }else{
        
        growth_vector = ofVec3f(  // (parent vector) + (random crookedness)
            ofClamp(parent->growth_vector.x + (growthVectorRandom.x * tree.crookedness),-1.0,1.0),
            ofClamp(parent->growth_vector.y + (growthVectorRandom.y * tree.crookedness),-1.0,1.0),
            (b2d3d) ? ofClamp(parent->growth_vector.z + (growthVectorRandom.z * tree.crookedness),-1.0,1.0)
            : 0);
        
        location = parent->location + (growth_vector * length);
    }

    updateChildren();
}

//--------------------------------------------------------------
ofColor ofxGrowthNode::setColor(){
    ofColor c;
    
    switch (level) {
        case 0:
            c = ofColor(255,221,25,205); //yellowish
            break;
        case 1:
            c = ofColor(143,177,178,205);//gray blue
            break;
        case 2:
            c = ofColor(20,198,204,205); //blue
            break;
        case 3:
            c = ofColor(255,0,170,205);  //pink
            break;
        default:
            c = ofColor(178,18,125,205); //dark pink
            break;
    }

    return c;
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
