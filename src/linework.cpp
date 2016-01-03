//
//  linework.cpp
//  emptyExample
//
//  Created by its on 2014/09/09.
//
//

#include "linework.h"



linework::linework() {
    
}

void linework::setup() {
    _mousePoint = ofPoint(0,0);
    
    _px = ofRandom(100, 200);
    _py = -ofRandom(10, 100);
    
    _length = ofRandom(50,150);
    _toX = 0;
    _angle = ofRandom(-80,80);
    _parentAngle = 0;
    _alpha = 255;
}

void linework::update() {
    
}

void linework::init() {
    _px = ofRandom(30, _length+50);
    _py = -ofRandom(10, 100);
    
    //_length = ofRandom(50,150);
    //_angle = ofRandom(-80,80);
    _angle = ofRandom(0,360);
    _alpha = 255;
    
}

void linework::draw() {
    
    
    ofSetColor(255,255,255,_alpha);
    ofPushMatrix();
    ofTranslate(_mousePoint.x,_mousePoint.y);
    ofRotate(_angle+_parentAngle);
    ofSetLineWidth(3);
    ofRect(_px,0,_length,3);
    ofPopMatrix();
    ofSetColor(255,255,255,255);
    
    if (abs(_px - _toX) > 1) {
        _px += (_toX - _px) / 8;
        _alpha += (0 - _alpha) / 12;
    } else {
        init();
    }
}

void linework::setLength(float length) {
    _length = length;
}

void linework::setMousePoint(ofPoint mp) {
    _mousePoint = mp;
}

void linework::setParentAngle(float angle) {
    _parentAngle = angle;
}