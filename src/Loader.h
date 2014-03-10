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
#include "CrossHair.h"
#include "ofxAnimatableFloat.h"

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
    bool isFinishedAnimating();
    void toggleProgressDirection();
    string getNavigatorLink();
    int getQuadrant();
    
    void appear();
    void disappear();
    
    ofPoint pos;
    float progress;
    int progressDirection;
    bool finished;
    int quadrant;
    string navigatorLink;
    
    CrossHair crossHair;
    
    ofImage loaderBand;
    ofxAnimatableFloat iconScale;
    ofTrueTypeFont iconFont;
    
private:
    
    void initCrossHair();
    void drawIcon();
};