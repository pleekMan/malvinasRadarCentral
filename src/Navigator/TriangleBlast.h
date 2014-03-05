//
//  TriangleBlast.h
//  animatableTest
//
//  Created by Wanda on 12/02/14.
//
//

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class TriangleBlast {
    
    
public:
    TriangleBlast(){};
    
    void setup();
    void update(float time);
    void draw();
    void turn90();
    void setAngleCorner(int corner);
    
    void appear(float delay);
    void disappear();
    
    ofPoint anchor;
    float width, height;
    int facing;
    ofPoint vertex[3];
    
    ofxAnimatableFloat alpha;
};