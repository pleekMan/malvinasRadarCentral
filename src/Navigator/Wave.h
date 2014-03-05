//
//  Wave.h
//  animatableTest
//
//  Created by Wanda on 12/02/14.
//
//

#ifndef __animatableTest__Wave__
#define __animatableTest__Wave__

#include <iostream>
#include "ofMain.h"

#define ELEMENTS 50

#endif /* defined(__animatableTest__Wave__) */

class Wave {

    public:

    Wave(){};
    void setup();
    void draw();

    int colors[ELEMENTS];
    ofPoint pos;
    float size, theta, offset, x, y;
    float width, height;



};