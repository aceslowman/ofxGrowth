#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    length      = 30.0;
    crookedness = 1.0;
    density     = 0.5;
    depth       = 3;
    
    root = new ofxGrowthNode(*this);
    root->growth_vector = ofVec3f(0,1,0);
    root->location = ofVec3f(0,0,0);
    
    num_nodes = 0;
    
    setupMesh();
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(){
    int index = 0;

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
    
    /*
     I now have some degree of confirmation that the linked list is working, it's just that I now need to be sure that I'm traversing it correctly.
     */
    
    if(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){
            if(i > 0){
                shared_ptr<ofMesh> new_mesh = std::make_shared<ofMesh>();
                
                new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                new_mesh->addVertex(temp_node->location);
                new_mesh->addColor(ofFloatColor(0,0,0));
                
                meshes.push_back(new_mesh);
   
                checkChildren(temp_node->children[i].get(), new_mesh.get());//check all children of the child
            }else{
                /*
                 When traversed through here, it works properly
                 */
                temp_mesh->addVertex(temp_node->location);
                temp_mesh->addColor(ofFloatColor(0,0,0));
                
                ofxGrowthNode * temp_child = temp_node->children[i].get();
                checkChildren(temp_child, temp_mesh);//check all children of the child
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
