#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    node_max    = 40.0;
    
    traversal_node = 0;
    traversal_speed = 200;
    
    crookedness = 0.2;
    density     = 0.08;
    depth       = 2;
    dim_f       = 0.5;
    growth_vector = ofVec3f(0,1,0);
    length      = 30.0;
    
    origin = ofVec3f(0,0,0);
    stroke_width= 2.0;
    
    b_traverse = false;
    
    //ptf testing
    mesh_ellipse.setMode(OF_PRIMITIVE_LINE_LOOP);
    unsigned numVerts = 20;
    float w = 5;
    float h = 5;
    for (unsigned i = 0; i < numVerts; ++i)
    {
        mesh_ellipse.addVertex(ofVec3f(0.f, w * cos(TWO_PI * i / (float)numVerts), h * sin(TWO_PI * i / (float)numVerts)));
    }
}
ofxGrowth::~ofxGrowth(){}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    root = new ofxGrowthNode(*this);
    num_nodes = 0;
    
    unique_ptr<ofVboMesh> mesh = make_unique<ofVboMesh>();
    mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
    ofSetLineWidth(stroke_width);
    
    unique_ptr<ofxPtf> ptf = make_unique<ofxPtf>();
    meshes.push_back(move(mesh));
    
    ptfs.push_back(move(ptf));
    
    setupMesh(root, meshes.back().get(), ptfs.back().get(),0);
    
    cap_current_mesh_id = 0;
    cap_mesh_node_id = 0;
    cap_current_mesh = meshes[0].get();
    cap_current_node = root;
    cap_mesh_node_id = 0;
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(ofxGrowthNode * current_node, ofVboMesh * current_mesh, ofxPtf * current_ptf, int mesh_node_id){
    ofVec3f current_vector;
    
    if(current_node->parent != NULL){
        current_vector = current_node->parent->location.getPerpendicular(current_node->location);
    }else{
        current_vector = growth_vector;
    }
    
    current_mesh->addVertex(current_node->location);
    current_mesh->addIndex(mesh_node_id);
    current_mesh->addColor(current_node->color);
    
    current_ptf->addPoint(current_node->location);
    
    
    for(int i = 0; i < current_node->children.size(); i++){
        if(i > 0){
            unique_ptr<ofVboMesh> new_mesh = make_unique<ofVboMesh>();
            new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
            
            new_mesh->addVertex(current_node->location);
            new_mesh->addIndex(0);
            new_mesh->addColor(current_node->color);
            
            unique_ptr<ofxPtf> new_ptf = make_unique<ofxPtf>();
            new_ptf->addPoint(current_node->location);
            
            current_mesh = new_mesh.get();
            current_ptf = new_ptf.get();
            
            meshes.push_back(move(new_mesh));
            new_mesh.release();
            
            ptfs.push_back(move(new_ptf));
            new_ptf.release();
            
            mesh_node_id = 0;
        }
        
        mesh_node_id++;

        current_node = current_node->children[i].get();
        setupMesh(current_node, current_mesh, current_ptf, mesh_node_id);

        num_nodes++;
    }
}

//--------------------------------------------------------------
void ofxGrowth::update(){
    
    /* */
    traversal_node = ofWrap(ofGetElapsedTimeMillis()/traversal_speed,0,node_max);
    /* */
    
    current_mesh_id = 0;
    for (auto & ptf : ptfs) {
        ptf->clear();
    }
    root->update();
    
    if(b_traverse){
        root->updateColor(ofGetElapsedTimeMillis()/traversal_speed);
    }
    
    ofSetLineWidth(stroke_width);
    updateMesh(root, meshes[0].get(), ptfs[0].get(), 0);
}

//--------------------------------------------------------------
void ofxGrowth::updateMesh(ofxGrowthNode * current_node, ofVboMesh * current_mesh, ofxPtf * current_ptf, int mesh_node_id){
    current_ptf->addPoint(current_node->location);
    
    current_mesh->setVertex(mesh_node_id, current_node->location);
    current_mesh->setColor(mesh_node_id, current_node->color);
    
    for(int i = 0; i < current_node->children.size(); i++){
        if(i > 0){
            current_mesh = meshes[current_mesh_id + 1].get();
            current_ptf = ptfs[current_mesh_id + 1].get();
            current_mesh_id = current_mesh_id + 1;
            mesh_node_id = 0;
            
            current_ptf->addPoint(current_node->location);
            
            current_mesh->setVertex(mesh_node_id, current_node->location);
            current_mesh->setColor(mesh_node_id, current_node->color);
            
            mesh_node_id = 1;
            
            current_node = current_node->children[i].get();

            updateMesh(current_node, current_mesh, current_ptf, mesh_node_id);
        }else{
            mesh_node_id++;
            
            current_node = current_node->children[i].get();
            
            updateMesh(current_node, current_mesh, current_ptf, mesh_node_id);
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawMesh(){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].get()->draw();
        
        ofPushMatrix();
        
        for (int j = 0; j < ptfs[i].get()->framesSize(); ++j)
        {
            ofPushMatrix();
            
            ofMultMatrix(ptfs[i].get()->frameAt(j));
            
            mesh_ellipse.draw();
            
            ofPopMatrix();
        }
        
        ofPopMatrix();
    }
}
