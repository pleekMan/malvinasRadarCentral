//
//  Loader.cpp
//  malvinasRadarCentral
//
//  Created by Zaira on 05/03/14.
//
//

#include "Loader.h"

void Loader::setup(ofPoint position, int _quadrant, string _navigatorReference){
    pos = position;
    progress = 0.;
    progressDirection = 1;
    finished = false;
    
    quadrant = _quadrant;
    
    navigatorLink = _navigatorReference;
    
}

void Loader::setLinkReference(string _navigatorReference){
    navigatorLink = _navigatorReference;
}

void Loader::update(){
    if (progress > 1. || progress < .0) {
        finished = true;
    } else {
        progress += 0.005 * progressDirection;
    }
}

void Loader::draw(){
    ofSetColor(255,255);
    ofDrawBitmapString("Cargando Info: " + ofSplitString(ofToString(progress * 100), ".")[0] + " %", pos);
    
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
    
    
}

bool Loader::isFinished(){
    return finished && progress > 1.;;
}

bool Loader::hasReturned(){
    return finished && progress < 0.;
}

void Loader::toggleProgressDirection(){
    progressDirection *= -1;
}

string Loader::getNavigatorLink(){
    return navigatorLink;
}

int Loader::getQuadrant(){
    return quadrant;
}