//
//  linework.h
//  emptyExample
//
//  Created by its on 2014/09/09.
//
//

#ifndef __emptyExample__linework__
#define __emptyExample__linework__

#include <iostream>

#include "ofMain.h"
class linework {
    
public:
    
    linework();
    void setup();
    void update();
    void draw();
    void setLength(float length);
    void setParentAngle(float angle);
    
    void setMousePoint(ofPoint mp);
    
private:
    
    void init();
    
    //utility
    ofPoint _mousePoint;
    
    float _alpha;
    float _length;
    float _speed;
    float _px;
    float _py;
    float _angle;
    float _parentAngle;
    float _toX;
    float _toY;
    
};

#endif /* defined(__emptyExample__linework__) */
