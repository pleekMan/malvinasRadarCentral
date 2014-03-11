#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ringManager.setup();
    
    //glEnable(GL_DEPTH_TEST);
    //ofEnableAlphaBlending();
    //ofEnableDepthTest();
    ofSetCircleResolution(6);
    
    pause = false;
    
    backImage.loadImage("background.png");
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    if (!pause) {
        ringManager.update(mouseX, mouseY);
        
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255);
    backImage.draw(0, 0);
    
    //ringManager.rings[4].ringImage.draw(100,100);

    ringManager.draw();
    
    ofDrawBitmapString("X: " + ofToString(mouseX) + " / Y: " + ofToString(mouseY), mouseX, mouseY + 30);
    
    //ofDrawBitmapString("LowSide: " + ofToString((int)(ringManager.rings[0].angle + ringManager.rings[0].halfAngularLimit)), mouseX, mouseY + 40);
    //ofDrawBitmapString("HighSide: " + ofToString((int)(ringManager.rings[0].angle - ringManager.rings[0].halfAngularLimit)), mouseX, mouseY + 55);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == ' ') {
        pause = !pause;
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
    
    //ringManager.setRadius(x);
    //ringManager.checkRingsDragged(ofPoint(x,y));
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    ringManager.startDrag(ofPoint(x,y));
    
    /*
    for (int i=0; ringManager.navigators.size(); i++) {
        ringManager.navigators[i].checkClick(x, y);
    }
     */
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    /*
    if(ringManager.checkRingsDragged(ofPoint(x,y)) != -1){
        ringManager.stopDrag(ringManager.checkRingsDragged(ofPoint(x,y)));
    }
     */
    
    ringManager.stopDrag();
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
