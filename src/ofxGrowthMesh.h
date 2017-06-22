#pragma once

#include "ofMain.h"
#include "ofxGrowth.h"
#include "ofxGrowthNode.h"

class ofxGrowthMesh : public ofxGrowth{
    
public:
	ofxGrowthMesh();
	~ofxGrowthMesh();

	vector<unique_ptr<ofVboMesh>> meshes;

	/*
	SETUP AND UPDATING
	*/
	void setup();
	void update(); 

	/*
	LINE DRAWING
	*/
	void setupLines();
	void updateLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
	void createLines(ofxGrowthNode * current_node, ofVboMesh * current_mesh, int mesh_node_id);
	void drawLines();

	/*
	DRAWING PARAMETERS
	*/
	int stroke_width;   //how thick are the lines drawn?

private:
	int current_mesh_id;
};
