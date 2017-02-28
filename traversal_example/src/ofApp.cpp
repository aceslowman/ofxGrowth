#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    growth_gui.add(depth.set("# OF LEVELS",3,0,10));
    growth_gui.add(node_max.set("MAX # OF BR NODES",40,1,200));
    growth_gui.add(length.set("LENGTH",20.0,1.0,200.0));
    growth_gui.add(density.set("DENSITY",0.6,0.0,1.0));
    growth_gui.add(crookedness.set("CROOK",0.3,0.0,10.0));
    growth_gui.add(growth_vector.set("GROWTH VECTOR",ofVec3f(0,1,0),ofVec3f(-1,-1,-1),ofVec3f(1,1,1)));
    growth_gui.add(stroke_width.set("STROKE WIDTH",2.0,0.0,10.0));
    
    movement_gui.add(lfo_1_rate.set("LFO Crooked Rate",0.0,0.0,10.0));
    movement_gui.add(b_lfo_1.set("LFO Crooked On/Off",false));
    
    
    gui.setup();
    gui.add(growth_gui);
    gui.add(movement_gui);
    updateTree();
    growth.setup();
    
    ofAddListener(growth_gui.parameterChangedE(), this, &ofApp::onParamChange);
    ofAddListener(movement_gui.parameterChangedE(), this, &ofApp::onParamChange);
}

void ofApp::onParamChange(ofAbstractParameter& e){
    update();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(b_lfo_1)
        crookedness = (sin((ofGetElapsedTimef())/2.0)*lfo_1_rate)*10.0;
    
    updateTree();
    growth.root->updateColor(ofGetElapsedTimeMillis()/200);
    growth.update();
    
}

//--------------------------------------------------------------
void ofApp::updateTree(){
    growth.depth = depth.get();
    growth.node_max = node_max.get();
    growth.length = length.get();
    growth.density = density.get();
    growth.crookedness = crookedness.get();
    growth.growth_vector = growth_vector.get();
    growth.stroke_width = stroke_width.get();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(ofFloatColor(1.0));
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cam.begin();
    growth.drawMesh();
    cam.end();
    syphon.publishScreen();
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofDisableAntiAliasing();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'd'){
        growth.~ofxGrowth();
        new(&growth) ofxGrowth();
        
        updateTree();
        growth.setup();
    }
    if(key == 'b'){
        ofResetElapsedTimeCounter();
    }
    
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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
