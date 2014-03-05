//
//  Stripper.cpp
//  animatableTest
//
//  Created by Wanda on 12/02/14.
//
//

#include "Stripper.h"

void Stripper::setup(){
    
    anchor = ofPoint(1,210);
    nodeSize = ofPoint(1,40);
    nodeSeparation = 4;
    
    alpha.reset(0.);
    
    nodeCount = 134;
    for(int i=0; i<NODES;i++)
        currentNode[i] = i*(nodeCount/NODES);
}

void Stripper::update(float time){
    alpha.update(time);
    if(!(ofGetFrameNum()%2))
        forward();
}

void Stripper::draw(){
    
    
    
    for (int i=0; i < nodeCount; i++) {
        
        ofSetColor(255,200*alpha.val());
        ofFill();
        
        ofPoint actualPos = ofPoint(anchor.x + ((nodeSeparation + nodeSize.x) * i), anchor.y);
        ofRect(actualPos, nodeSize.x, nodeSize.y);
        
    }
    
    ofSetColor(200,54,42,255*alpha.val());
    ofFill();
    for(int i=0; i<NODES;i++){
        ofRect(anchor.x + ((nodeSeparation + nodeSize.x) * currentNode[i]), anchor.y, nodeSize.x, nodeSize.y);
    }
    
    ofSetColor(255,255);
}

void Stripper::forward(){
    for(int i=0; i<NODES;i++){
        currentNode[i]++;
        if (currentNode[i] > nodeCount - 1) {
            currentNode[i] = 0;
        }
    }
}

void Stripper::appear(float delay){
    alpha.animateToAfterDelay(1.,delay);
}

void Stripper::disappear(){
    alpha.animateTo(0.);
}