#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    node_max    = 20;
    length      = 30.0;
    crookedness = 0.2;
    density     = 0.08;
    depth       = 3;
    dim_f       = 0.5;
    growth_vector = ofVec3f(0,1,0);
}

ofxGrowth::~ofxGrowth(){}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    root = new ofxGrowthNode(*this);
    num_nodes = 0;
    
    setupMesh();
}

//--------------------------------------------------------------
void ofxGrowth::rebuild(){
    root = new ofxGrowthNode(*this);
    num_nodes = 0;
    
//    for (auto & element : meshes) {
//        element.reset();
//    }
    
    meshes.clear();
    setupMesh();
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(){
    unique_ptr<ofMesh> mesh = make_unique<ofMesh>();
    mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
    
    meshes.push_back(std::move(mesh));
    
    generateMesh(root, meshes.back().get(),0,false);
}

//--------------------------------------------------------------
void ofxGrowth::generateMesh(ofxGrowthNode * temp_node, ofMesh * temp_mesh, int mesh_index, bool share_root){
    temp_mesh->addVertex(temp_node->location);
    
    if(temp_node->level == 0)
        temp_mesh->addColor(ofFloatColor(1,0,0));
    
    if(temp_node->level == 1)
        temp_mesh->addColor(ofFloatColor(0,1,0));
    
    if(temp_node->level == 2)
        temp_mesh->addColor(ofFloatColor(0,0,1));
    
    if(temp_node->level > 2)
        temp_mesh->addColor(ofFloatColor(1,1,0));
    
    for(int i = 0; i < temp_node->children.size(); i++){
        if(i > 0){
            unique_ptr<ofMesh> new_mesh = make_unique<ofMesh>();
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
            
            temp_mesh = new_mesh.get();
            meshes.push_back(move(new_mesh));
        }

        temp_node = temp_node->children[i].get();
        generateMesh(temp_node, temp_mesh, mesh_index++, share_root);

        num_nodes++;
    }
}

void ofxGrowth::updateMesh(){
    
    ofxGrowthNode * temp_node = root;
    ofMesh * temp_mesh = meshes.front().get();
    
    int current_mesh = 0;
    int mesh_index = 0;
    
    while(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){
            
            if(i > 0){
                temp_mesh = meshes[current_mesh+1].get();
//                mesh_index = 0;
            }
            
            temp_mesh->setVertex(mesh_index, temp_node->location);
            temp_mesh->setColor(mesh_index, ofFloatColor(0,1,0));
            temp_node = temp_node->children[i].get();
            
            mesh_index++;
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::animate(){
    int t_driver = ofGetElapsedTimeMillis()/15;
    
    if(t_driver != driver){
    }
    
    driver = t_driver;
}

//--------------------------------------------------------------
void ofxGrowth::drawMesh(){
    
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].get()->draw();
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawPoints(){
    
    ofxGrowthNode * temp_node = root;
    ofDrawSphere(temp_node->location, 5.0);
    
    while(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){
            if(temp_node->children[i].get()->level == 0)
                ofSetColor(ofFloatColor(1,0,0));
            
            if(temp_node->children[i].get()->level == 1)
                ofSetColor(ofFloatColor(0,1,0));
            
            if(temp_node->children[i].get()->level == 2)
                ofSetColor(ofFloatColor(0,0,1));
            
            if(temp_node->children[i].get()->level > 2)
                ofSetColor(ofFloatColor(1,1,0));
            
            ofDrawSphere(temp_node->children[i].get()->location, 5.0);
            temp_node = temp_node->children[i].get();
        }
    }
}
