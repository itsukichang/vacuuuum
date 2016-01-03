//
//  imageSprite.h
//  emptyExample
//
//  Created by its on 2014/09/04.
//
//

#ifndef __emptyExample__imageSprite__
#define __emptyExample__imageSprite__

#include <iostream>
#include "ofMain.h"
#include "ofxTweener.h"

class imageSprite {

    public:
    
   
    
    imageSprite(string imgSource, string seSource, string name, ofPoint pXY,ofPoint toXY, ofPoint toScaleXY, float toAlpha, float toAngle, Boolean moveFlag, int mass);
    
    
    void update();
    void draw();
    void toAnimation();
    void imageReset();
    
    void imageInit();
    
    
    void setToXY(ofPoint toXY);
    void setVibCount(int cnt);
    void setDebugMode(Boolean f);
    void setVacumePower(float pw);
    
    ofPoint getCollisionXY();
    float getCollisionR();
    
    void setAnimeFlag(Boolean f);
    Boolean getAnimeFlag();
    
    Boolean getVacumued();
    Boolean getPreVacumed();
    
    void appear();
    
    ofImage image;
    
    
    //ゴミ情報のアクセスサ
    
    void setGarbageMass(int s);
    int getGarbageMass();
    string getGarbageName();
    
    
    
    private:
    
    float _vacumePower;
    
    ofPoint _initXY;
    
    ofPoint _pXY;
    ofPoint _toXY;
    ofPoint _pScaleXY;
    ofPoint _toScaleXY;
    
    ofPoint _collisionXY;
    float _collisionR;
    
    float _pAlpha;
    float _toAlpha;
    float _pAngle;
    float _toAngle;
    
    
    float _imageWidth, _imageHeight;
    
    float _speed;
    float _initSpeed;
    
    
    //ゴミの情報
    int _mass;      //重さ
    string _sePath; //効果音
    string _name;   //名前
    
    
    int _vibCount;
    int _nowCount;
    float _arr;
    
    Boolean _animeFlag;
    Boolean _debugMode;
    
    Boolean _vacumed;
    Boolean _preVacumed;
    
    
    //サウンド
    ofSoundPlayer _vacumeSe;
    
    
    //ゴミのランダムな移動
    
    Boolean _garbageMoveFlag;
    void garbageMove(Boolean f);
    void speedChange();
    float _interval;
    float _intervalTime;
    float rota ;
    float rotaPlus ;
    float rotaMinus ;
    float rotaX ;
    float rotaY ;
};



#endif /* defined(__emptyExample__imageSprite__) */
