
//
//  Stripper.h
//  animatableTest
//
//  Created by Wanda on 12/02/14.
//
//

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

#define NODES 8
class Stripper {
    
public:
    
    Stripper(){};
    
    void setup();
    void update(float time);
    void draw();
    
    void forward();
    
    void appear(float delay);
    void disappear();
    
    ofPoint anchor;
    ofPoint nodeSize;
    float nodeSeparation;
    
    ofxAnimatableFloat alpha;
    
    int nodeCount;
    int currentNode[NODES];
    
};