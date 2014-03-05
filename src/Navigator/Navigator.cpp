//
//  Navigator.cpp
//  animatableTest
//
//  Created by Wanda on 07/02/14.
//
//
#include "ofMain.h"
#include "Navigator.h"

void Navigator::setup(string p,ofPoint initPos){
    path = p;

    width = height = 716;
    
    visible = false;
        
    fbo.allocate(width, height);

    titulo.loadImage(path + "/titulo.png");
    titulo.setAnchorPercent(0, 0);
    titulo.setPosition(ofPoint(0, 0));
    titulo.setColor(255,0);
    titulo.color.setDuration(1.);
    titulo.color.setRepeatType(PLAY_ONCE);
    titulo.color.setCurve(BLINK_AND_FADE_3);
    
    close.loadImage(path + "/../closeButton.png");
    close.setAnchorPercent(0, 0);
    close.setPosition(ofPoint(650, 10));
    close.setColor(255,0);
    close.color.setDuration(1.);
    close.color.setRepeatType(PLAY_ONCE);
    close.color.setCurve(BLINK_AND_FADE_3);

    // BOTONES y CONTENT HOLDERS
    for(int i=0; ofDirectory::doesDirectoryExist(path + "/Content_" + ofToString(i)); i++){
        cout<<i<<endl;
        buttons.push_back(ofxAnimatableObject<ofImage>());
        contents.push_back(ContentHolder());
        buttonsBackG.push_back(FunkyRect());
    }
    for(int i=0; i<buttons.size(); i++){
        buttons[i].loadImage(path + "/Content_" + ofToString(i) + "/button.png");
        buttons[i].setAnchorPercent(0.0, 0.0);
        buttons[i].setPosition(ofPoint(3, 50 + 32*i));
        buttons[i].setRotation(ofPoint(0,90,0));
        buttons[i].rotation.setDuration(0.7);
        buttons[i].rotation.setRepeatType(PLAY_ONCE);
        buttons[i].rotation.setCurve(TANH);
        buttons[i].setColor(255,0);
        buttons[i].color.setDuration(1.0);
    }
    for(int i=0; i<contents.size(); i++){
        contents[i].setup(path + "/Content_" + ofToString(i),ofPoint(3,150));
    }
    for(int i=0; i<buttonsBackG.size(); i++){
        buttonsBackG[i].setup(false, buttons[i].position.getCurrentPosition(), buttons[i].getWidth(), buttons[i].getHeight());
    }

    currentContent = nextContent = 0;
    
    //wave.setup();
    //swizzer.setup(true, ofPoint(30,230), 1, 40);
    /*
    for (int i=0; i < 3; i++) {
        FunkyRect currentBeeper = FunkyRect();
        currentBeeper.setup(i % 2, ofPoint(30 * i,20), 10, 10);
        beepers.push_back(currentBeeper);
    }
     */
    //stripper.setup();
    
    triangle.loadImage(path + "/triangle.png");
    triangle.setAnchorPercent(0.5, 0.5);
    triangle.setPosition(ofPoint(653, 690, 0));
    //triangle.position.setDuration(0.5);
    //triangle.position.setRepeatType(LOOP_BACK_AND_FORTH);
    triangle.setColor(255,0);

}

void Navigator::appear(float delay){
    
    visible = true;

    titulo.color.animateToAfterDelay(ofColor(255,255),delay);
    close.color.animateToAfterDelay(ofColor(255,255),delay);
    
    delay+=1.;

    ofPoint rotateTo = ofPoint(0,0,0);
    for(int i=0;i<buttons.size();i++){
        buttons[i].rotation.setDuration(.7);
        buttons[i].rotation.setRepeatType(PLAY_ONCE);
        buttons[i].rotation.animateToAfterDelay(ofPoint(rotateTo), delay + i*0.2);
        buttons[i].color.animateToAfterDelay(ofColor(255,255),delay);
    }
    //buttons[currentContent].color.animateToAfterDelay(ofColor(255,255), delay + currentContent*0.2);
    //stripper.appear(delay);
    
    triangle.color.animateToAfterDelay(ofColor(255,255),delay);

    delay += 0.5;

    contents[currentContent].appear(delay);

    buttonsBackG[currentContent].appear(delay);
        
}

void Navigator::disappear(){
    
    titulo.color.animateToAlpha(0);
    close.color.animateToAlpha(0);

    ofPoint rotateTo = ofPoint(0,90,0);
    for(int i=0;i<buttons.size();i++){
        buttons[i].rotation.setDuration(.7);
        buttons[i].rotation.animateTo(ofPoint(rotateTo));
        buttons[i].color.animateToAlpha(0);
    }
    
    //stripper.disappear();
    
    triangle.color.animateTo(ofColor(255,0));
    
    contents[currentContent].disappear();
    
    for(int i=0;i < buttonsBackG.size();i++){
        buttonsBackG[i].disappear();;
    }
    
    visible = false;
    
}

void Navigator::update(float time){
    
    //buttons[i].color.animateToAlpha(0);
    
    ofSetColor(255);
    
    fbo.update(time);

    titulo.update(time);
    close.update(time);

    if(nextContent != currentContent){
        if( !contents[currentContent].isOrWillBeAnimating() ){
            currentContent = nextContent;
            contents[currentContent].appear(0.0);
            
            triangle.color.animateTo(ofColor(255,255));
        }
    }

    for(int i=0;i < buttonsBackG.size();i++){
        buttonsBackG[i].update(time);
    }
    
    for(int i=0;i<buttons.size();i++){
        buttons[i].update(time);
    }

    contents[currentContent].update(time);

    swizzer.rotate(ofMap(ofGetFrameNum() % 70, 0, 70, 0, TWO_PI));
    swizzer.update(time);
    
    //stripper.update(time);
    triangle.update(time);

    
    /*
    for(int i=0;i<beepers.size();i++){
        
        if (ofGetFrameNum() % 10 == 0) {
            beepers[i].setToStateColor(ofGetFrameNum() % 2);
        }
        
        beepers[i].update(time);
    }
     */

   
    //cout << ofToString(buttons[0].color.getCurrentColor().a) << endl;
    
    // DRAW INTO FBO
    fbo.begin();
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    ofClear(0,0);    

    titulo.draw();
    close.draw();

    for(int i=0;i < buttonsBackG.size();i++){
        buttonsBackG[i].draw();
    }
    for(int i=0;i<buttons.size();i++){
        buttons[i].draw();
    }
    contents[currentContent].draw();

    //ofNoFill();
    //ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
    
    drawMisc();

    fbo.end();
    

}

void Navigator::draw(){
    fbo.draw();
}

void Navigator::checkClick(int mx, int my){

    // CHECK IF MOUSE IS INSIDE NAVIGATOR BEFORE CONTINUING
    if(fbo.inside(ofPoint(mx,my))){
        ofPoint mouse = ( ofPoint(mx,my) - fbo.position.getCurrentPosition() ) / fbo.size.val();
        
        for(int i=0;i<buttons.size();i++){
            
            if (buttons[i].inside(mouse)) {
                cout << "Boton " << i << " - Pressed" << endl;
                optionPressed(i);
                return;
            }
        }


        for(int i=0;i<contents[currentContent].thumbs.size();i++){
            if (contents[currentContent].thumbs[i].inside(mouse)) {
                cout << "Thumb " << i << " - Pressed" << endl;
                contents[currentContent].thumbPressed(i);
            }
        }
        
        if (contents[currentContent].text.inside(mouse)) {
            cout << "Text - Pressed" << endl;
            contents[currentContent].text.tex.setMouse(true);
        }

    }

}

bool Navigator::closePressed(int mx, int my){
    
    ofPoint mouse = ( ofPoint(mx,my) - fbo.position.getCurrentPosition() ) / fbo.size.val();
    
    return close.inside(mouse)?true:false;
}

void Navigator::optionPressed(int selection){
    if(selection == currentContent || selection == nextContent){
        return;
    }
    else{
        if(currentContent != nextContent){
            contents[nextContent].disappear();
            buttonsBackG[nextContent].disappear();
        }
        contents[currentContent].disappear();
        buttonsBackG[currentContent].disappear();
        nextContent = selection;
        
        buttons[nextContent].rotation.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
        buttons[nextContent].rotation.setDuration(.2);
        buttons[nextContent].rotation.animateTo(ofPoint(-45,0,0));
        buttonsBackG[nextContent].appear(0.);
        
        triangle.color.animateTo(ofColor(255,0));
        //buttons[currentContent].color.animateTo(ofColor(255,255));
        //buttons[nextContent].color.animateTo(ofColor(255,255));
    }
}

bool Navigator::isVisible(){
    return visible;
}

void Navigator::drawMisc(){
    
        //wave.draw();
        
        //swizzer.draw();

        triangle.draw();
        //stripper.draw();
    
}
