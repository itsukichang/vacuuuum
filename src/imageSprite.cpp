//
//  imageSprite.cpp
//  emptyExample
//
//  Created by its on 2014/09/04.
//
//

#include "imageSprite.h"

imageSprite::imageSprite(string imgSource, string seSource, string name, ofPoint pXY,ofPoint toXY, ofPoint toScaleXY, float toAlpha, float toAngle, Boolean moveFlag, int mass){

    _garbageMoveFlag = moveFlag;    //ゴミが移動するか
    _sePath = seSource;
    _name = name;
    _mass = mass;
    
    cout << "mass:";
    cout << _mass;
    cout << "\n";
    
    _pScaleXY = ofPoint(0.0,0.0);
    _pAlpha = 0;
    _pAngle = ofRandom(-10,10);
    
    _initXY = pXY;
    _pXY = pXY;
    _toXY = toXY;
    _toScaleXY = toScaleXY;
    _toAlpha = toAlpha;
    _toAngle = toAngle;
    
    _vibCount = 0;
    _nowCount = 0;
    _arr = 4.0;
    
    _vacumed = false;
    _preVacumed = false;
    
    float dx = abs(_toXY.x-_pXY.x);
    float dy = abs(_toXY.y-_pXY.y);
    _speed = 300 - sqrt(dx*dx+dy*dy)/10;
    _initSpeed = _speed;
    
    
   // cout << "speed:";
   // cout << _speed;
    
    
    _animeFlag = false;
    _debugMode = false;
    
    _interval = ofGetElapsedTimeMillis();
    
    image.loadImage(imgSource);
    
    _imageWidth = image.getWidth();
    _imageHeight = image.getHeight();
    
    _collisionR = _imageWidth*_pScaleXY.x/2;
    
    
     rota = 0;
     rotaPlus = 0;
     rotaMinus = 0;
     rotaX = 0;
     rotaY = 0;
    _intervalTime = ofRandom(500, 1500);
    
    
    /*
    int soundNo = floor(ofRandom(1,7));
    string soundPath = "garbage/se"+ofToString(soundNo) + ".mp3";
    */
    
    /*
    cout << "sound : ";
    cout << soundPath;
    cout << "\n";
     */
    _vacumeSe.loadSound(_sePath);
    
    _vacumePower = 0;
}

//ゴミの移動


void imageSprite::garbageMove(Boolean f) {
    
    float speed;
    if (f) {
        speed = 5.0;
    } else {
        speed = 1.0;
    }
    if (_garbageMoveFlag) {
        speedChange();
        
        if (rotaX > 10) {
            _pXY.x += ofRandom(speed) * cos(PI/180 * rota);
        } else {
            _pXY.x -= ofRandom(speed) * cos(PI/180 * rota);
        }
        
        if (rotaY > 10) {
            _pXY.y += ofRandom(speed) * sin(PI/180 * rota);
        } else {
            _pXY.y -= ofRandom(speed) * sin(PI/180 * rota);
        }
    }
}


void imageSprite::speedChange() {
    if (ofGetElapsedTimeMillis() - _interval > _intervalTime) {
        _interval = ofGetElapsedTimeMillis();
        //cout << "2秒経過\n";
        
        rota = ofRandom(20.0);
        rotaX = ofRandom(20.0);
        rotaY = ofRandom(20.0);
        
        if (rota > 10) {
            rotaPlus += 1;
            rotaMinus = 0;
        } else {
            rotaMinus += 1;
            rotaPlus = 0;
        }
        
        if (rotaPlus > 5) {
            rota = 0;
        }
        if (rotaMinus > 5) {
            rota = 0;
        }
    }
}


/////

void imageSprite::update() {
    
    if (_animeFlag) {
        garbageMove(true);
    } else {
        garbageMove(false);
    }
    
    /*
    _pXY.x += ofRandom(-1.5, 1.5);
    _pXY.y += ofRandom(-1.5, 1.5);
    _pScaleXY.x += ofRandom(-0.2,0.2);
    _pScaleXY.y += ofRandom(-0.2,0.2);
    _pAngle += ofRandom(-5, 5);
    _pAlpha += ofRandom(-5, 5);
    */
    _collisionR = _imageWidth*_pScaleXY.x/2;
}

void imageSprite::draw() {
    
    if (!_vacumed) {
        ofSetColor(255, 255, 255, _pAlpha);
        ofPushMatrix();
        ofTranslate(_pXY.x,_pXY.y);
        ofRotate(_pAngle);
        image.draw(-image.width * _pScaleXY.x /2,
                   -image.height * _pScaleXY.y /2,
                   _imageWidth * _pScaleXY.x,
                   _imageHeight * _pScaleXY.y);
        
        ofPopMatrix();
        
         _collisionXY = ofPoint(_pXY.x,_pXY.y);
       
        //debug circle
        if (_debugMode) {
        //    cout << "debugmode";
            ofSetColor(255,0,0,128);
            ofCircle(_collisionXY.x,_collisionXY.y,_collisionR);
        }
        ofSetColor(255, 255, 255, 255);
    }
}


void imageSprite::toAnimation() {
    
    _preVacumed = _vacumed;
    
    if (_name=="boss1")  {
        if (_vacumePower > 100) {
            if (_animeFlag && _vacumed == false) {
                _nowCount++;
                float dx = abs(_toXY.x-_pXY.x);
                float dy = abs(_toXY.y-_pXY.y);
                _speed = sqrt(dx*dx+dy*dy)/20;
                
                if (_nowCount > _mass+_vibCount) {
                    _pXY.x      += (_toXY.x - _pXY.x)           / _speed;
                    _pXY.y      += (_toXY.y - _pXY.y)           / _speed;
                    _pAngle     += (_toAngle - _pAngle)         / _speed;
                    _pScaleXY.x += (_toScaleXY.x - _pScaleXY.x) / _speed;
                    _pScaleXY.y += (_toScaleXY.y - _pScaleXY.y) / _speed;
                    _pAlpha     += (_toAlpha - _pAlpha)         / _speed    /   2;
                    
                    if (abs(_pAlpha-_toAlpha) < 0.05) {
                        _vacumed = true;
                        _pAlpha = 0;
                        
                        _vacumeSe.play();
                    }
                    
                } else {
                    
                    if (_pAngle < -30 || _pAngle > 30) {
                        if (_nowCount % 12 == 0) {
                            _arr *= 1;
                        }
                        _arr *= -1;
                        _pXY.x += (_toXY.x - _pXY.x) / _initSpeed*1.5;
                        _pXY.y += (_toXY.y - _pXY.y) / _initSpeed*1.5;
                    }
                    _pAngle += _arr;
                }
            }
        }
        
        if (_animeFlag == false) {
            _nowCount = 0;
        }
        
        if (_preVacumed == false && _vacumed == true) {
            cout << "吸い込まれた\n";
        }

    
        
        
    }else {
        if (_animeFlag && _vacumed == false) {
            _nowCount++;

    //        cout << _nowCount;
    //        cout << "\n";

            float dx = abs(_toXY.x-_pXY.x);
            float dy = abs(_toXY.y-_pXY.y);
            _speed = sqrt(dx*dx+dy*dy)/20;

    //        cout << "speed:";
    //        cout << _speed;
            


            if (_nowCount > _mass+_vibCount) {
                _pXY.x      += (_toXY.x - _pXY.x)           / _speed;
                _pXY.y      += (_toXY.y - _pXY.y)           / _speed;
                _pAngle     += (_toAngle - _pAngle)         / _speed;
                _pScaleXY.x += (_toScaleXY.x - _pScaleXY.x) / _speed;
                _pScaleXY.y += (_toScaleXY.y - _pScaleXY.y) / _speed;
                _pAlpha     += (_toAlpha - _pAlpha)         / _speed    /   2;
                
                if (abs(_pAlpha-_toAlpha) < 0.05) {
                    _vacumed = true;
                    _pAlpha = 0;
                    
                    _vacumeSe.play();
                }
                
            } else {
                
                if (_pAngle < -15 || _pAngle > 15) {
                    if (_nowCount % 4 == 0) {
                        _arr *= 1.1;
                    }
                    _arr *= -1;
                    _pXY.x += (_toXY.x - _pXY.x) / _initSpeed*1.5;
                    _pXY.y += (_toXY.y - _pXY.y) / _initSpeed*1.5;
                }
                _pAngle += _arr;
            }
        }
        
        if (_animeFlag == false) {
            _nowCount = 0;
        }
        
        if (_preVacumed == false && _vacumed == true) {
                cout << "吸い込まれた\n";
        }
    }
}


void imageSprite::imageReset() {
    _pXY = _initXY;
    _pScaleXY = ofPoint(0.0,0.0);
    _pAlpha = 0;
    _pAngle = ofRandom(-10,10);
    _arr = 4.0;
    _nowCount = 0;
    _animeFlag = false;
    _vacumed = false;
    _preVacumed = false;
    
    rota = 0;
    rotaPlus = 0;
    rotaMinus = 0;
    rotaX = 0;
    rotaY = 0;
    
    _interval = ofGetElapsedTimeMillis();
    _intervalTime = ofRandom(500, 1500);
}

//appear

void imageSprite::appear() {
    //cout << "appear \n";
    
    float delay = ofRandom(0.3, 2.0);
    Tweener.addTween(_pAlpha, 255, 3, &ofxTransitions::easeOutElastic, delay);
    Tweener.addTween(_pScaleXY.x, 0.5, 3, &ofxTransitions::easeOutElastic,  delay);
    Tweener.addTween(_pScaleXY.y, 0.5, 3, &ofxTransitions::easeOutElastic,  delay);
}


//getter, setter

void imageSprite::setVacumePower(float pw) {
    
    _vacumePower = pw;
}

void imageSprite::setToXY(ofPoint toXY) {
    _toXY = toXY;
    _toXY.x -= _imageWidth * _pScaleXY.x;
    _toXY.y -= _imageHeight * _pScaleXY.y;
}

void imageSprite::setVibCount(int cnt) {
    _vibCount = cnt;
}

void imageSprite::setAnimeFlag(Boolean f) {
    _animeFlag = f;
}

Boolean imageSprite::getAnimeFlag() {
    return _animeFlag;
}

ofPoint imageSprite::getCollisionXY() {
    return _collisionXY;
}

float imageSprite::getCollisionR() {
    return _collisionR;
}

void imageSprite::setDebugMode(Boolean f) {
    _debugMode = f;
}

Boolean imageSprite::getVacumued() {
    return _vacumed;
}

Boolean imageSprite::getPreVacumed() {
    return _preVacumed;
}

void imageSprite::setGarbageMass(int s) {
    _mass = s;
}

int imageSprite::getGarbageMass() {
    return _mass;
}

string imageSprite::getGarbageName() {
    return _name;
}