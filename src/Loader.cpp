//
//  Loader.cpp
//  malvinasRadarCentral
//
//  Created by Zaira on 05/03/14.
//
//

#include "Loader.h"

void Loader::setup(ofPoint position, int _quadrant, int _navigatorIdLink){
    pos = position;
    progress = 0.;
    progressDirection = 1;
    finished = false;
    
    quadrant = _quadrant;
    
    navigatorId = _navigatorIdLink;
    
    CrossHair crossHair;
    initCrossHair();
    
    loaderBand.loadImage("loaderBand_small.png");
    
    
    iconFont.loadFont("DIN-LightAlternate.ttf", 17);
    
    appear();
    
}

void Loader::setNavigatorLink(int _navigatorId){
    navigatorId = _navigatorId;
}

void Loader::update(){
    if (progress > 1. || progress < .0) {
        finished = true;
        //disappear();
    } else {
        progress += 0.005 * progressDirection;
        iconScale.update(1/ofGetFrameRate());
    }
}

void Loader::draw(){
    
    //ofSetColor(255,255);
    //ofDrawBitmapString("Cargando Info: " + ofSplitString(ofToString(progress * 100), ".")[0] + " %", pos);
    
    /*
    ofFill();
    ofSetColor(255,0,0,150 * progress);
    ofBeginShape();
    ofVertex(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    if (quadrant == 0) {
        ofVertex(0, ofGetHeight() * 0.25);
        ofVertex(0,0);
        ofVertex(ofGetWidth() * 0.25, 0);
    } else if(quadrant == 1){
        ofVertex(ofGetWidth() - (ofGetWidth() * 0.25), .0);
        ofVertex(ofGetWidth(), 0);
        ofVertex(ofGetWidth(), ofGetHeight() * 0.25);
    } else if(quadrant == 2) {
        ofVertex(ofGetWidth(), ofGetHeight() - (ofGetHeight() * 0.25));
        ofVertex(ofGetWidth(), ofGetHeight());
        ofVertex(ofGetWidth() - (ofGetWidth() * 0.25), ofGetHeight());
    } else {
        ofVertex(ofGetWidth() * 0.25, ofGetHeight());
        ofVertex(0, ofGetHeight());
        ofVertex(0, ofGetHeight() - (ofGetHeight() * 0.25));
    }
    ofEndShape(true);
    */
    
    
   
    ofPolyline areaIndicator;
    int aperture = 45;
    int startAngle = 225 - aperture;
    int endAngle = 225 + aperture;
    areaIndicator.arc(ofPoint(0,0), ofDist(0, 0, ofGetWidth() * 0.55, ofGetHeight() * 0.55), ofDist(0, 0, ofGetWidth() * 0.55, ofGetHeight() * 0.55), startAngle,endAngle, true, 40);
    areaIndicator.arc(ofPoint(0,0), ofDist(0, 0, ofGetWidth() * 0.30, ofGetHeight() * 0.30), ofDist(0, 0, ofGetWidth() * 0.30, ofGetHeight() * 0.30), endAngle,startAngle, false, 40);
    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ofRotate(90 * quadrant);
    
    ofFill();
    ofSetColor(0,255,255, 250 * progress);
    ofBeginShape();
    for (int i=0; i < areaIndicator.getVertices().size(); i++) {
        ofVertex(areaIndicator.getVertices()[i].x, areaIndicator.getVertices()[i].y);
    }
    
    ofEndShape(OF_CLOSE);
    
    ofPopMatrix();
    
    
    
    crossHair.draw();
    
    
    if (crossHair.isFinished()) {
        crossHair.reset();
    }
    
    drawIcon();
    

}

bool Loader::isFinished(){
    return finished && progress > 1.;
}

bool Loader::hasReturned(){
    return finished && progress < 0.;
}


bool Loader::isFinishedAnimating(){
    cout << ofToString(!iconScale.isAnimating() && hasReturned()) << endl;
    return !iconScale.isAnimating() && hasReturned();
}

void Loader::toggleProgressDirection(){
    progressDirection *= -1;
}

int Loader::getNavigatorLink(){
    return navigatorId;
}

int Loader::getQuadrant(){
    return quadrant;
}

void Loader::initCrossHair(){
    

    ofPoint center;
    
    switch (quadrant) {
        case 0:
            center = ofPoint(0,0);
            break;
        case 1:
            center = ofPoint(ofGetWidth(),0);
            break;
        case 2:
            center = ofPoint(ofGetWidth(), ofGetHeight());
            break;
        case 3:
            center = ofPoint(0,ofGetHeight());
            break;
        default:
            break;
    }
    
    crossHair.setup(center);
    
}

void Loader::drawIcon(){
    

    ofSetCircleResolution(50);

    loaderBand.setAnchorPercent(0.5, 0.1);
    
    ofPoint topCenter = ofPoint(ofGetMouseX(), ofGetMouseY());
    float circleSize = 40;
    
    ofSetColor(150,30,30,255);
    ofCircle(topCenter.x, topCenter.y + (loaderBand.getHeight() * 1.2), circleSize * iconScale.getCurrentValue());
    
    // PROGRESS BAR - BEGIN
    
    ofPolyline progressBar;
    int aperture = 45;
    int startAngle = 0;
    int endAngle = 0 + (360 * progress);
    
    progressBar.arc(ofPoint(0,0), (circleSize * 0.95)  * iconScale.getCurrentValue(), (circleSize * 0.95)  * iconScale.getCurrentValue(), startAngle,endAngle, true, 50);
    
    //void ofPolyline::arc(const ofPoint &center, float radiusX, float radiusY, float angleBegin, float angleEnd, bool clockwise, int circleResolution=20)
    
    //areaIndicator.draw();
    
    
    ofPushMatrix();
    ofTranslate(ofPoint(topCenter.x, topCenter.y + (loaderBand.getHeight() * 1.2)));
    ofRotate(-90);
    
    ofFill();
    ofSetColor(200);
    ofBeginShape();
    for (int i=0; i < progressBar.getVertices().size(); i++) {
        ofVertex(progressBar.getVertices()[i].x, progressBar.getVertices()[i].y);
    }
    
    ofEndShape(OF_CLOSE);
    
    ofPopMatrix();
    // PROGRESS BAR - END
        
    
    ofSetColor(255);
    ofCircle(topCenter.x, topCenter.y + (loaderBand.getHeight() * 1.2), (circleSize * 0.75) * iconScale.getCurrentValue());
    
    ofSetColor(150,30,30,iconScale.getCurrentValue() * 255);
    iconFont.drawString(ofToString((int)(progress * 100)) + "%", topCenter.x - (circleSize * 0.4), topCenter.y + (loaderBand.getHeight() * 1.6));
    
    ofSetColor(255);
    loaderBand.draw(topCenter, loaderBand.getWidth() * iconScale.getCurrentValue(), loaderBand.getHeight() * iconScale.getCurrentValue());
    
    int triangleRadius = 5;
    ofSetColor(150,30,30,iconScale.getCurrentValue() * 255);
    ofTriangle(topCenter.x - triangleRadius, topCenter.y + (loaderBand.getHeight() * 0.8), topCenter.x + triangleRadius, topCenter.y + (loaderBand.getHeight() * 0.8), topCenter.x, topCenter.y + (loaderBand.getHeight() * 0.8) + triangleRadius);
    ofTriangle(topCenter.x - triangleRadius, topCenter.y + (loaderBand.getHeight() * 2), topCenter.x + triangleRadius, topCenter.y + (loaderBand.getHeight() * 2), topCenter.x, topCenter.y + (loaderBand.getHeight() * 2) - triangleRadius);
    
    
}


void Loader::appear(){
    iconScale.setDuration(0.5);
    iconScale.setCurve(TANH);
    iconScale.setPercentDone(0);
    iconScale.animateTo(1);
}

void Loader::disappear(){
    iconScale.setDuration(0.5);
    iconScale.setCurve(TANH);
    //iconScale.setPercentDone(0);
    iconScale.animateTo(0);
}