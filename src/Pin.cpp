//
//  Pin.cpp
//  malvinasRadarCentral
//
//  Created by Zaira on 26/02/14.
//
//

#include "Pin.h"


void Pin::draw(){
    ofFill();
    ofSetColor(180,50,50);
    ofCircle(position.x, position.y, 30);
    ofSetColor(255);
    ofCircle(position.x, position.y, 15);
    
    
    ofPoint pointTo;
    if(activeQuadrant == 0){
        pointTo = ofPoint(0, 0);
    } else if(activeQuadrant == 1){
        pointTo = ofPoint(ofGetWidth(), 0);
    } else if(activeQuadrant == 2){
        pointTo = ofPoint(ofGetWidth(), ofGetHeight());
    } else{
        pointTo = ofPoint(0, ofGetHeight());

    }
    
    ofSetLineWidth(10);
    ofLine(position.x, position.y, ofLerp(position.x, pointTo.x, 0.2), ofLerp(position.y, pointTo.y, 0.2));
    ofSetLineWidth(1);

    ofSetColor(255);
    ofDrawBitmapString("Ring:" + ofToString(linkToRing) + " Titulo", position.x, position.y - 50);
    ofDrawBitmapString(data, position.x, position.y - 35);
    
}

void Pin::update(int mX, int mY){
    
    position = ofPoint(mX, mY);
    updateActiveQuadrant();
    
}

void Pin::setData(int link, string _data){
    
    linkToRing = link;
    data = _data;
    
    
}

void Pin::updateActiveQuadrant(){
    
    
    if(position.x < ofGetWidth() * 0.5 && position.y < ofGetHeight() * 0.5){
        activeQuadrant = 0;
    } else if(position.x > ofGetWidth() * 0.5 && position.y < ofGetHeight() * 0.5){
        activeQuadrant = 1;
    } else if(position.x > ofGetWidth() * 0.5 && position.y > ofGetHeight() * 0.5){
        activeQuadrant = 2;
    } else{
        activeQuadrant = 3;
    }
    
}

int Pin::getActiveQuadrant(){
    return activeQuadrant;
}

