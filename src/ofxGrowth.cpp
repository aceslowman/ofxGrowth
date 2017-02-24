#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    node_max    = 5;
    length      = 30.0;
    crookedness = 0.2;
    density     = 0.08;
    depth       = 2;
    dim_f       = 0.5;
    growth_vector = ofVec3f(0,1,0);
}

ofxGrowth::~ofxGrowth(){}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    root = new ofxGrowthNode(*this);
    num_nodes = 0;
    
    unique_ptr<ofMesh> mesh = make_unique<ofMesh>();
    mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
    
    meshes.push_back(std::move(mesh));
    
    setupMesh(root, meshes.back().get(),0);
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(ofxGrowthNode * current_node, ofMesh * current_mesh, int mesh_node_id){
    current_mesh->addVertex(current_node->location);
    current_mesh->addIndex(mesh_node_id);
    
    if(current_node->level == 0)
        current_mesh->addColor(ofFloatColor(1,0,0));
    
    if(current_node->level == 1)
        current_mesh->addColor(ofFloatColor(0,1,0));
    
    if(current_node->level == 2)
        current_mesh->addColor(ofFloatColor(0,0,1));
    
    if(current_node->level > 2)
        current_mesh->addColor(ofFloatColor(1,1,0));
    
    for(int i = 0; i < current_node->children.size(); i++){
        if(i > 0){
            unique_ptr<ofMesh> new_mesh = make_unique<ofMesh>();
            new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
            
            new_mesh->addVertex(current_node->location);
            new_mesh->addIndex(0);
            
            if(current_node->children[i].get()->level == 0)
                new_mesh->addColor(ofFloatColor(1,0,0));
            
            if(current_node->children[i].get()->level == 1)
                new_mesh->addColor(ofFloatColor(0,1,0));
            
            if(current_node->children[i].get()->level == 2)
                new_mesh->addColor(ofFloatColor(0,0,1));
            
            if(current_node->children[i].get()->level > 2)
                new_mesh->addColor(ofFloatColor(1,1,0));
            
            current_mesh = new_mesh.get();
            
            meshes.push_back(move(new_mesh));
            new_mesh.release();
            mesh_node_id = 0;
        }
        
        mesh_node_id++;

        current_node = current_node->children[i].get();
        setupMesh(current_node, current_mesh, mesh_node_id);

        num_nodes++;
    }
}

//--------------------------------------------------------------
void ofxGrowth::update(){
    current_mesh_id = 0;
    updateMesh(root, meshes[0].get(),0);
}

//--------------------------------------------------------------
void ofxGrowth::updateMesh(ofxGrowthNode * current_node, ofMesh * current_mesh, int mesh_node_id){
    current_mesh->setVertex(mesh_node_id, current_node->location);
    current_mesh->setColor(mesh_node_id, ofFloatColor(1,0,0));
    
    for(int i = 0; i < current_node->children.size(); i++){
        if(i > 0){
            current_mesh = meshes[current_mesh_id + 1].get();
            current_mesh_id = current_mesh_id + 1;
            mesh_node_id = 0;
            
            current_node = current_node->children[i].get();
            updateMesh(current_node, current_mesh, mesh_node_id);
        }else{
            mesh_node_id++;
            
            current_node = current_node->children[i].get();
            updateMesh(current_node, current_mesh, mesh_node_id);
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawMesh(){
    
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].get()->draw();
    }
}
