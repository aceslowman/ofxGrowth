#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    node_max    = 20;
    length      = 30.0;
    crookedness = 0.2;
    density     = 0.5;
    depth       = 4;
    dim_f       = 0.75;
    growth_vector = ofVec3f(0,1,0);
}

ofxGrowth::~ofxGrowth(){
    meshes.clear();
    ofxGrowthNode * temp_node = root;

    while(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){
            root = temp_node->children[i].get();
            delete temp_node;
            
            temp_node = root;
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    root = new ofxGrowthNode(*this);
    root->growth_vector = growth_vector;
    root->location = ofVec3f(0,0,0);
    
    num_nodes = 0;
    
    setupMesh();
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(){
    shared_ptr<ofMesh> shared_mesh = std::make_shared<ofMesh>();
    shared_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
    shared_mesh->setupIndicesAuto();
    shared_mesh->addVertex(root->location);
    shared_mesh->addColor(ofColor(0));
    
    meshes.push_back(shared_mesh);
    
    checkChildren(root, shared_mesh.get());
}

//--------------------------------------------------------------
void ofxGrowth::checkChildren(ofxGrowthNode * temp_node, ofMesh * temp_mesh){
    if(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){
            if(i > 0){
                shared_ptr<ofMesh> new_mesh = std::make_shared<ofMesh>();
                
                new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                new_mesh->addVertex(temp_node->location);
                
                if(temp_node->children[i].get()->level == 0)
                    new_mesh->addColor(ofFloatColor(1,0,0));
                
                if(temp_node->children[i].get()->level == 1)
                    new_mesh->addColor(ofFloatColor(0,1,0));
                
                if(temp_node->children[i].get()->level == 2)
                    new_mesh->addColor(ofFloatColor(0,0,1));
                
                if(temp_node->children[i].get()->level > 2)
                    new_mesh->addColor(ofFloatColor(1,1,0));
                
                meshes.push_back(new_mesh);
                checkChildren(temp_node->children[i].get(), new_mesh.get());
            }else{
                
                temp_mesh->addVertex(temp_node->location);
                if(temp_node->children[i].get()->level == 0)
                    temp_mesh->addColor(ofFloatColor(1,0,0));
                
                if(temp_node->children[i].get()->level == 1)
                    temp_mesh->addColor(ofFloatColor(0,1,0));
                
                if(temp_node->children[i].get()->level == 2)
                    temp_mesh->addColor(ofFloatColor(0,0,1));
                
                if(temp_node->children[i].get()->level > 2)
                    temp_mesh->addColor(ofFloatColor(1,1,0));
                
                ofxGrowthNode * temp_child = temp_node->children[i].get();
                checkChildren(temp_child, temp_mesh);
            }
            temp_node = temp_node->children[i].get();
            num_nodes++;
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawMesh(){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].get()->draw();
    }
}
