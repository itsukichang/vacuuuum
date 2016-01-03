//
//  menuWindow.cpp
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#include "garbageSetWindow.h"

void garbageSetWindow::setup() {
    _nextWindow = "garbageSetWindow";
    gui.setup();
    gui.add(_mass.setup( "objMass", 0, -100, 100 ));
    gui.add(_attr.setup( "attractiveForce",50,30,200));
}

void garbageSetWindow::init() {
    _nextWindow = "garbageSetWindow";
}

void garbageSetWindow::update() {
    
}

void garbageSetWindow::draw() {
    gui.draw();
}


string garbageSetWindow::getChangeMode() {
    return _nextWindow;
}

void garbageSetWindow::setMousePoint(ofPoint mp) {
    _mousePoint = mp;
}


float garbageSetWindow::getGarbageMass() {
    return _mass;
}
float garbageSetWindow::getVacumPower() {
    return _attr;
}

//以下keyやmouseイベント

//--------------------------------------------------------------
void garbageSetWindow::keyPressed(int key){
    if (key == 'a') {
        _nextWindow = "menuWindow";
    }
}

//--------------------------------------------------------------
void garbageSetWindow::keyReleased(int key){
}

//--------------------------------------------------------------
void garbageSetWindow::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void garbageSetWindow::mouseDragged(int x, int y, int button){
    
}


//--------------------------------------------------------------
void garbageSetWindow::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void garbageSetWindow::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------
void garbageSetWindow::windowResized(int w, int h){
    
}


//--------------------------------------------------------------
void garbageSetWindow::dragEvent(ofDragInfo dragInfo){
    
}