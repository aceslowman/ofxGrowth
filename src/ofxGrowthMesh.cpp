#include "ofxGrowthMesh.h"

//--------------------------------------------------------------
ofxGrowthMesh::ofxGrowthMesh(){
    traversal_node = 0;
    traversal_speed = 200;
    
    stroke_width= 2.0;
    
    b_traverse = false;
}

ofxGrowthMesh::~ofxGrowthMesh(){
	ofLog(OF_LOG_NOTICE, "Deleting meshes...");
	meshes.clear();
}

//--------------------------------------------------------------
void ofxGrowthMesh::setup() {
	setupTree();	//create and setup the tree
	setupLines();	//now initialize the lines (by default)
}

//--------------------------------------------------------------
void ofxGrowthMesh::update() {
	current_mesh_id = 0;
	traversal_node = ofWrap(ofGetElapsedTimeMillis()/traversal_speed,0,node_max);

	updateTree();

	if(b_traverse){
	    root->updateColor(ofGetElapsedTimeMillis()/traversal_speed);
	}

	ofSetLineWidth(stroke_width);
	updateLines(root, meshes[0].get(), 0);
}

//--------------------------------------------------------------
void ofxGrowthMesh::setupLines() {
	unique_ptr<ofVboMesh> mesh = make_unique<ofVboMesh>();
	mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
	ofSetLineWidth(stroke_width);

	meshes.push_back(move(mesh));

	createLines(root, meshes.back().get(), 0);

	cap_current_mesh_id = 0;
	cap_mesh_node_id = 0;
	cap_current_mesh = meshes[0].get();
	cap_current_node = root;
	cap_mesh_node_id = 0;
}

//--------------------------------------------------------------
void ofxGrowthMesh::updateLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id) {
	current_mesh->setVertex(mesh_node_id, current_node->location);
	current_mesh->setColor(mesh_node_id, current_node->color);

	for (int i = 0; i < current_node->children.size(); i++) {
		if (i > 0) {
			current_mesh = meshes[current_mesh_id + 1].get();
			current_mesh_id = current_mesh_id + 1;
			mesh_node_id = 0;

			current_mesh->setVertex(mesh_node_id, current_node->location);
			current_mesh->setColor(mesh_node_id, current_node->color);

			mesh_node_id = 1;

			current_node = current_node->children[i].get();

			updateLines(current_node, current_mesh, mesh_node_id);
		}
		else {
			mesh_node_id++;

			current_node = current_node->children[i].get();

			updateLines(current_node, current_mesh, mesh_node_id);
		}
	}
}

//--------------------------------------------------------------
void ofxGrowthMesh::createLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id) {
	ofVec3f current_vector;

	if (current_node->parent != NULL) {
		current_vector = current_node->parent->location.getPerpendicular(current_node->location);
	}
	else {
		current_vector = growth_vector;
	}

	current_mesh->addVertex(current_node->location);
	current_mesh->addIndex(mesh_node_id);
	current_mesh->addColor(current_node->color);

	for (int i = 0; i < current_node->children.size(); i++) {
		if (i > 0) {
			unique_ptr<ofVboMesh> new_mesh = make_unique<ofVboMesh>();
			new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);

			new_mesh->addVertex(current_node->location);
			new_mesh->addIndex(0);
			new_mesh->addColor(current_node->color);

			current_mesh = new_mesh.get();

			meshes.push_back(move(new_mesh));
			new_mesh.release();

			mesh_node_id = 0;
		}

		mesh_node_id++;

		current_node = current_node->children[i].get();
		nodes.push_back(current_node);

		createLines(current_node, current_mesh, mesh_node_id);

		num_nodes++;
	}
}

//--------------------------------------------------------------
void ofxGrowthMesh::drawLines() {
	for (int i = 0; i < meshes.size(); i++) {
		ofPushMatrix();
		ofScale(length, length, length);
		meshes[i].get()->draw();
		ofPopMatrix();
	}
}