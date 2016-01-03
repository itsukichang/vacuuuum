//
//  calibration.h
//  emptyExample
//
//  Created by its on 2014/09/11.
//
//

#ifndef __emptyExample__calibration__
#define __emptyExample__calibration__

#include <iostream>

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <vector>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"


class calibration {
    
public:
    //keyevent
    void keyPressed(int key);
    
    //gui描画用
    void menuInit();
    void menuDraw();
    
    //元となる色の取得
    Boolean getColorFlag;
    void setTargetColor(int r, int g, int b);
    
    
    //キャリブレーション領域セット
    void setpoint(float lHx , float lHy, float rHx, float rHy,float rLx, float rLy, float lLx,float lLy);
    
    //画面サイズセット
    void initViewSize(int w,int h);
    
    //対象Image設定
    void setimg(ofxCvColorImage Img);
    
    //現在座標取得
    float getPx();
    float getPy();
    
    //変換後のImage取得
    ofxCvColorImage getTransformedImage();
    
private:
    //画面サイズ
    int _width;
    int _height;
    
    //gui
    ofxPanel _gui;
    ofxIntSlider _colorR;
    ofxIntSlider _colorG;
    ofxIntSlider _colorB;
    ofxFloatSlider _threshold;
    
    //キャリブレーション領域用
    ofPoint _lH, _rH, _rL, _lL;  //l:left r:right H:high L:Low
    ofPoint _src[4], _dst[4];   //src:元画面の四角形の座標 dst:キャリブレーション後の4点座標
    CvPoint2D32f _srcPnt[4], _dstPnt[4];
    ofxCvColorImage _targetImage;
    double _point[3];// = {0,0,1};
    CvMat _cvMatPoint;
    
    int _caliCulcCount;
    int _aveCulcCount;
    float _tempCenterX;
    float _tempCenterY;
    
    //出力用Image
    ofxCvColorImage _outPutImage;
    ofxCvGrayscaleImage _outPutHueImg;
	ofxCvGrayscaleImage _outPutSatImg;
	ofxCvGrayscaleImage _outPutBriImg;
    
    
    //特徴点検出
    void analyse(ofxCvColorImage image);
    CvMat calcHomography( const ofPoint src[4], const ofPoint dst[4]);
    
    //zyuusin
    float _centerX = 0;
    float _centerY = 0;
    
};
#endif /* defined(__emptyExample__calibration__) */
