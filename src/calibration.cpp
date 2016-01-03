//
//  calibration.cpp
//  emptyExample
//
//  Created by its on 2014/09/11.
//
//

#include "calibration.h"


void calibration::menuInit() {
    
    _aveCulcCount = 0;
    _caliCulcCount = 0;
    _tempCenterX = 0;
    _tempCenterY = 0;
    
    _gui.setup();
    _gui.add(_colorR.setup("red",0,0,255));
    _gui.add(_colorG.setup("green",0,0,255));
    _gui.add(_colorB.setup("blue",0,0,255));
    _gui.add(_threshold.setup("threshold",0,0,255));
    
}

void calibration::menuDraw() {
    _gui.draw();
    _gui.setPosition(640,0);
}

//切り取り座標を設定
void calibration::setpoint(float lHx,float lHy, float rHx, float rHy,float rLx, float rLy, float lLx,float lLy){
    _lH.x = lHx;
    _lH.y = lHy;
    _rH.x = rHx;
    _rH.y = rHy;
    _rL.x = rLx;
    _rL.y = rLy;
    _lL.x = lLx;
    _lL.y = lLy;
    
    _src[0] = ofPoint (_lH.x, _lH.y);
    _src[1] = ofPoint (_rH.x, _rH.y);
    _src[2] = ofPoint (_rL.x, _rL.y);
    _src[3] = ofPoint (_lL.x, _lL.y);
    _srcPnt[0] = cvPoint2D32f (0.0, 0.0);
    _srcPnt[1] = cvPoint2D32f (_width, 0.0);
    _srcPnt[2] = cvPoint2D32f (_width, _height);
    _srcPnt[3] = cvPoint2D32f (0.0, _height);
    
   // _outPutImage.warpIntoMe(_targetImage ,_src,_dst);
}

//描画の画面サイズ
void calibration::initViewSize(int w,int h){
    _width = w;
    _height = h;
    
    _targetImage.allocate(_width, _height);
    _outPutImage.allocate(_width, _height);
    
    //(0,0)->(640,300)に入れる
    _src[0] = ofPoint (_lH.x, _lH.y);
    _src[1] = ofPoint (_rH.x, _rH.y);
    _src[2] = ofPoint (_rL.x, _rL.y);
    _src[3] = ofPoint (_lL.x, _lL.y);
    _srcPnt[0] = cvPoint2D32f (0.0, 0.0);
    _srcPnt[1] = cvPoint2D32f (_width, 0.0);
    _srcPnt[2] = cvPoint2D32f (_width, _height);
    _srcPnt[3] = cvPoint2D32f (0.0, _height);
    
    
    _dst[0] = ofPoint (0.0, 0.0);
    _dst[1] = ofPoint (_width, 0.0);
    _dst[2] = ofPoint (_width, _height);
    _dst[3] = ofPoint (0.0, _height);
    _dstPnt[0] = cvPoint2D32f (0.0, 0.0);
    _dstPnt[1] = cvPoint2D32f (_width, 0);
    _dstPnt[2] = cvPoint2D32f (_width, _height);
    _dstPnt[3] = cvPoint2D32f (0, _height);
    
}

//対象の入力画像
void calibration::setimg(ofxCvColorImage Img){
    _targetImage = Img;
}



ofxCvColorImage calibration::getTransformedImage(){
    
    /*
    CvMat *map_matrix;
    map_matrix = cvCreateMat (3, 3, CV_32FC1);
    cvSetZero(map_matrix);
    map_matrix = cvCreateMat (3, 3, CV_32FC1);
    cvSetZero(map_matrix);
    cv::Mat mat = cvGetPerspectiveTransform (_srcPnt, _dstPnt, map_matrix);
    
     CvMat homography =  calcHomography(_src, _dst);
    
    double _point[] ={_rL.x,_rL.y,1};
    double _zero[] ={0,0,1};
    
    CvMat Point = cvMat(3,1,CV_64F,(void*)_point);
    CvMat result = cvMat(3,1,CV_64F,(void*)_zero);
    
    Point.data.db[0] = Point.data.db[0] * homography.data.db[0]+Point.data.db[1] * homography.data.db[1]+Point.data.db[2] * homography.data.db[2];
    
    Point.data.db[1] = Point.data.db[0] * homography.data.db[3]+Point.data.db[1] * homography.data.db[4]+Point.data.db[2] * homography.data.db[5];
    
    Point.data.db[2] = Point.data.db[0] * homography.data.db[6]+Point.data.db[1] * homography.data.db[7]+Point.data.db[2] * homography.data.db[8];
    */
    
    
    _outPutImage = _targetImage;
    _outPutImage.warpIntoMe(_targetImage ,_src,_dst);
    //analyse(_outPutImage);   //色々計算 (重心とか赤い点とか)
    return _outPutImage;    //変換&切り抜き後の映像を返す
}


void calibration::analyse(ofxCvColorImage image){
    
    /*
     _outPutHueImg.allocate(_width, _height);
     _outPutSatImg.allocate(_width, _height);
     _outPutBriImg.allocate(_width, _height);
     //HSV系に変換した映像情報
     ofxCvColorImage _targetImageHSV;
     //HSV系の色相、彩度、明度のマップ
     ofxCvGrayscaleImage hueImg;
     ofxCvGrayscaleImage satImg;
     ofxCvGrayscaleImage briImg;
     hueImg.allocate(_width,_height);
     satImg.allocate(_width,_height);
     briImg.allocate(_width,_height);
     unsigned char * Pixels = image.getPixels();
     unsigned char * huePixels = hueImg.getPixels();
     unsigned char * satPixels = satImg.getPixels();
     unsigned char * briPixels = briImg.getPixels();
     //HSV系に変換
     _targetImageHSV = image;
     _targetImageHSV.convertRgbToHsv();
     //色相、彩度、明度にマッピング
     _targetImageHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
     //使ってないけどなんか明度とかとれるかも
     hueImg.flagImageChanged();
     satImg.flagImageChanged();
     briImg.flagImageChanged();
     */
    
    //ピクセルの数
    int nPixels = image.getHeight() * image.getWidth() *3;
    unsigned char * colorPixels = image.getPixels();
    
    
    //赤検知
    
    int baseColorR = _colorR;
    int baseColorG = _colorG;
    int baseColorB = _colorB;
    
    int x = 0,y = 0,count = 0;
    
    for (int i=0; i< nPixels ; i++) {
        if ( i % 3 == 0){
            
            
            int R = colorPixels[i];
            int G = colorPixels[i+1];
            int B = colorPixels[i+2];
            
            float diff = sqrt(
                              (R - baseColorR)*(R - baseColorR)+
                              (G - baseColorG)*(G - baseColorG)+
                              (B - baseColorB)*(B - baseColorB)
                              );
            
            if (diff < _threshold) {
                x +=(i / 3) % _width;
                y +=(i / 3) / _width;
                count++;
                colorPixels[i] = 255;
                colorPixels[i+1] = 0;
                colorPixels[i+2] = 0;
            }
        }
    }
    
    
    //重心計算
    //_centerX = xの重心, _centerX = yの重心
    
    if (count >0) {
        if (_aveCulcCount++ < 2) {
            _tempCenterX += (x/count);
            _tempCenterY += (y/count);
        } else {
            _centerX = _tempCenterX / 2;
            _centerY = _tempCenterY / 2;
            _aveCulcCount = 0;
            _tempCenterX = 0;
            _tempCenterY = 0;
        }
    }
    
    
    //セットしている
    _outPutImage.setFromPixels(colorPixels,_width,_height);
}

//重心のアクサスサ
float calibration::getPx(){return _centerX;}
float calibration::getPy(){return _centerY;}


//計算用
CvMat calibration::calcHomography( const ofPoint src[4], const ofPoint dst[4]){
    CvPoint2D32f cvsrc[4];
    CvPoint2D32f cvdst[4];
    CvMat* translate = cvCreateMat( 3, 3, CV_32FC1 );
    cvSetZero( translate );
    for (int i = 0; i < 4; i++ ) {
        cvsrc[i].x = src[i].x;
        cvsrc[i].y = src[i].y;
        cvdst[i].x = dst[i].x;
        cvdst[i].y = dst[i].y;
    }
    cvWarpPerspectiveQMatrix( cvsrc, cvdst, translate );  // calculate homography
    return *translate;
};

void calibration::setTargetColor(int r, int g, int b) {
    _colorR = r;
    _colorG = g;
    _colorB = b;
}

void calibration::keyPressed(int key) {
    
}