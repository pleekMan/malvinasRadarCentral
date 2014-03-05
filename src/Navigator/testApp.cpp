#include "testApp.h"


#define NAVIGATOR_INIT_POS ofPoint(900,0)
#define NAVIGATOR_END_POS ofPoint(20,20)
//--------------------------------------------------------------
void testApp::setup(){

    background.loadImage("tempBack.png");

    navigator01.setup("Navigator_0",ofPoint(20.0,20.0));
    navigator01.fbo.setPosition(NAVIGATOR_INIT_POS);
    navigator01.fbo.setSize(0.);
    navigator01.fbo.size.setCurve(EASE_OUT);
    //navigator01.appear();
    
}

//--------------------------------------------------------------
void testApp::update(){
    float dt=1./ofGetFrameRate();
    
    //if (navigator01.isVisible()) {
        navigator01.update(dt);
    //}
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    background.draw(0, 0);

    //if (navigator01.isVisible()) {
        navigator01.draw();
    //}

    //ofDrawBitmapString("X: " + ofToString(mouseX) + " - Y: " + ofToString(mouseY), ofPoint(mouseX,mouseY));
    //ofDrawBitmapString("Navigator Translate X: " + ofToString(mouseX - navigator01.x) + " - Y: " + ofToString(mouseY - navigator01.y), ofPoint(mouseX,mouseY + 20));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == '1') {
        navigator01.fbo.size.animateTo(1.);
        navigator01.fbo.position.animateTo(NAVIGATOR_END_POS);
        navigator01.fbo.color.animateToAlpha(255);
        navigator01.appear(0.);
    }
    if (key == '2') {
        navigator01.fbo.size.animateTo(0.);
        navigator01.fbo.position.animateTo(NAVIGATOR_INIT_POS);
        navigator01.fbo.color.animateToAlpha(0);
        navigator01.disappear();
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    //navigator01.setup(ofPoint(mouseX, mouseY));
    //navigator01.initialize();

    navigator01.checkClick(mouseX, mouseY);
    if(navigator01.closePressed(mouseX, mouseY)){
        navigator01.fbo.size.animateTo(0.);
        navigator01.fbo.position.animateTo(NAVIGATOR_INIT_POS);
        navigator01.fbo.color.animateToAlpha(0);
        navigator01.disappear();
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
