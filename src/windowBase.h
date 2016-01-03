//
//  gameWindow.h
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#ifndef __emptyExample__gameWindow__
#define __emptyExample__gameWindow__

#include <iostream>
#include "ofMath.h"
#include "imageSprite.h"
#include "ofxTweener.h"
#include "ofxGui.h"

class windowBase {
    
public:
    void setup();
    void update();
    void draw();
    
    void setMousePoint(ofPoint mp);
    
private:
    
    //default
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    
    //utility
    ofPoint _mousePoint;

};

#endif /* defined(__emptyExample__gameWindow__) */
