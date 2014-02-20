//
//  RingManager.cpp
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#include "RingManager.h"

#define CENTER ofPoint(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5)
#define RING_COUNT 12
#define RING_WIDTH 20

void RingManager::setup(){
    
    createRings();
    
    
    
}

void RingManager::draw(){
    
    
    for (int i=0; i < RING_COUNT; i++) {
        rings[i].update();
        rings[i].draw();
    }
    
}

void RingManager::createRings(){
    
    float centerBaseOffset = 200;
    float radiusIncrement = 0;
    
    for (int i=0; i < RING_COUNT; i++) {
        Ring currentRing;
        rings.push_back(currentRing);
    }
    
    for (int i=0; i < RING_COUNT; i++) {
        
        string currentPath = "rings/ring_" + ofToString(i) + ".png";
        
        float currentRadius = 0;
        currentRadius = centerBaseOffset + (radiusIncrement);
        
        rings[i].setup(currentPath, CENTER, currentRadius);
        
        if (i % 2 == 1) {
            radiusIncrement += RING_WIDTH + 3;
        }
        
    }
}

void RingManager::checkRingsDragged(ofPoint pointer){
    
    for (int i=0; i < RING_COUNT; i++) {
        if(rings[i].inside(pointer) && !rings[i].isActive()){
            rings[i].setActive(true);
        }
    
    }
    
}

void RingManager::setRadius(float newRadius) {
    // SET A GLOBAL radius, AND RE-SET RINGS
}