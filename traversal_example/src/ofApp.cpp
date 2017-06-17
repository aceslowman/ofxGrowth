#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    growth_gui.add(depth.set("# OF LEVELS",3,0,10));
    growth_gui.add(node_max.set("MAX # OF BR NODES",40,1,200));
    growth_gui.add(length.set("LENGTH",20.0,1.0,200.0));
    growth_gui.add(density.set("DENSITY",0.6,0.0,1.0));
    growth_gui.add(diminish.set("DIM FACTOR", 0.2, 0.0, 1.0));
    growth_gui.add(crookedness.set("CROOK",0.3,0.0,2.0));
    growth_gui.add(growth_vector.set("GROWTH VECTOR",ofVec3f(0,1,0),ofVec3f(-1,-1,-1),ofVec3f(1,1,1)));
    growth_gui.add(stroke_width.set("STROKE WIDTH",2.0,0.0,10.0));
    growth_gui.add(b_traverse.set("Animated Traversal?",false));
    
    movement_gui.add(lfo_1_rate.set("LFO Crooked Rate",0.0,0.0,10.0));
    movement_gui.add(b_lfo_1.set("LFO Crooked On/Off",false));
    movement_gui.add(saw_1_rate.set("SAW Movement Rate", 77.0,1.0,1000.0));
    
    gui.setup();
    gui.add(growth_gui);
    gui.add(movement_gui);
    updateTree();
    growth.setup();
    
    ofAddListener(growth_gui.parameterChangedE(), this, &ofApp::onParamChange);
    ofAddListener(movement_gui.parameterChangedE(), this, &ofApp::onParamChange);
    
    useEasyCam = false;
}

void ofApp::onParamChange(ofAbstractParameter& e){
    updateTree();
    growth.update();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(b_traverse)
        growth.update();
}

//--------------------------------------------------------------
void ofApp::updateTree(){
    if(b_lfo_1)
        crookedness = (sin((ofGetElapsedTimef())/2.0)*lfo_1_rate)*10.0;
    
    growth.depth = depth.get();
    growth.node_max = node_max.get();
    growth.length = length.get();
    growth.density = density.get();
    growth.crookedness = crookedness.get();
    growth.growth_vector = growth_vector.get();
    growth.stroke_width = stroke_width.get();
    growth.traversal_speed = saw_1_rate.get();
    growth.b_traverse = b_traverse.get();
    growth.dim_f = diminish.get();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(ofFloatColor(0));
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cam.begin();
    if(!useEasyCam){
        cam.orbit(ofGetElapsedTimef()*15, -10, 400);
        cam.move(0,100,0);
    }
    growth.drawMesh();
    drawEuler();
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
    if(key == 'r'){
        useEasyCam = !useEasyCam;
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

void ofApp::drawEuler(){
    ofSetColor(ofColor(255,0,0));
    ofDrawLine(-100,0,0,100,0,0);
    ofSetColor(ofColor(0,255,0));
    ofDrawLine(0,-100,0,0,100,0);
    ofSetColor(ofColor(0,0,255));
    ofDrawLine(0,0,-100,0,0,100);
    
    ofSetColor(ofFloatColor(0.42,0.48,0.67));
    ofVec3f vector_line = growth_vector.get() * 100;
    ofDrawLine(0,0,0,vector_line.x,vector_line.y,vector_line.z);
}
