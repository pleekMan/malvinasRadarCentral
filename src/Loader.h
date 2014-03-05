//
//  Loader.h
//  malvinasRadarCentral
//
//  Created by Zaira on 05/03/14.
//
//

#ifndef __malvinasRadarCentral__Loader__
#define __malvinasRadarCentral__Loader__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__malvinasRadarCentral__Loader__) */

class Loader {
    
    
public:
    Loader(){};
    
    void setup(ofPoint position, int _quadrant, string navigatorReference);
    void draw();
    void update();
    void setLinkReference(string NavigatorReference);
    bool isFinished();
    bool hasReturned();
    void toggleProgressDirection();
    string getNavigatorLink();
    int getQuadrant();
    
    ofPoint pos;
    float progress;
    int progressDirection;
    bool finished;
    int quadrant;
    string navigatorLink;
    
    
};