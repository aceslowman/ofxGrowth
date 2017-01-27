#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCullFace(GL_BACK);
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 255.f));
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(0, 0, 0);
    
    growth_group.add(growth_density.set("Density",0.5,0.0,1.0));
    growth_group.add(growth_length.set("Length",0.5,0.0,1.0));
    growth_group.add(growth_crookedness.set("Crookedness",0.5,0.0,1.0));
    growth_group.add(growth_segments.set("Segments",15,0,30));
    growth_group.add(growth_depth.set("Depth",4,1,10));
    growth_group.add(growth_leaf_level.set("Leaf Level",3,1,10));
    
    light_group.add(light_color.set("Light Color",ofFloatColor(0,0,0),ofFloatColor(0,0,0),ofFloatColor(1,1,1)));
    light_group.add(light_position.set("Light Position",ofVec3f(0,0,0), ofVec3f(-200,-200,-200), ofVec3f(200,200,200)));

    gui.setup();
    gui.add(growth_group);
    gui.add(light_group);
    
    growth.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    growth.setDensity(growth_density);
    growth.setLength(growth_length);
    growth.setSegments(growth_segments);
    growth.setDepth(growth_depth);
    growth.setCrookedness(growth_crookedness);
    growth.setLeafLevel(growth_leaf_level);
    
    pointLight.setPosition(light_position);
    pointLight.setDiffuseColor(light_color);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableLighting();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(ofFloatColor(0));
    ofSetColor(ofColor(0));
    
    cam.begin();
        pointLight.enable();
    
        growth.drawMeshes();
        if(b_leaves)
            growth.drawLeaves();
        if(debug)
            growth.drawDebug();
    
        ofSetColor(ofFloatColor(1));
        ofDrawSphere(pointLight.getPosition(), 5);
    cam.end();
    
    ofDisableAntiAliasing();
    ofDisableDepthTest();
    ofDisableLighting();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        growth.clearAll();
        growth.setup();
    }
    if(key == 'c'){
        growth.clearAll();
    }
    if(key == 'd'){
        debug = !debug;
    }
    if(key == 'l'){
        b_leaves = !b_leaves;
    }
    
    if(key == '1')
        growth.setColormode(0);
    if(key == '2')
        growth.setColormode(1);
    if(key == '3')
        growth.setColormode(2);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}
