#pragma once

#include "ofMain.h"
#include "ofxGrowth.h"
#include "ofxGrowthNode.h"

class ofxGrowthMesh : public ofxGrowth{
    
public:
	ofxGrowthMesh();
	~ofxGrowthMesh();

	/*
	SETUP AND UPDATING
	*/
	void setup();
	void update();

	/*
	LINE DRAWING
	*/
	void setupLines();
	void createLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
	void updateLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
	void drawLines();

	/*
	DRAWING PARAMETERS
	*/
	int stroke_width;   //how thick are the branches drawn? (line)

	/*
	TRAVERSAL PARAMETERS
	*/
	int traversal_node;
	int traversal_speed;
	int cap_mesh_node_id;
	int cap_current_mesh_id;
	ofVboMesh * cap_current_mesh;
	ofxGrowthNode * cap_current_node;

	vector<unique_ptr<ofVboMesh>> meshes;

	int driver;
	bool b_traverse;

private:
};
