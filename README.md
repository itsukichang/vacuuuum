# vacuuuum
## 概要
IVRC2014に展示した掃除機型デバイスを用いたVRシステムです．
投影されたオブジェクトを専用の掃除機型デバイスで吸い込み，掃除機型デバイスのホースの膨らみや振動，投影オブジェクトの変形によって，仮想のゴミの存在を感じることが出来ます．

## システム構成
ハードウェアはArduinoと大量のサーボモータ．

ソフトウェアはC++とopenFrameworksで作成．
工夫点としては，カメラ座標をパソコンの座標に対応づけるアフィン変換部分(calibration.cpp)とArduinoとの連携部分(ofApp.cpp)が上げられる

## keywords
- VRシステム
- デバイス連携
- Arduino
- oF
- プロジェクション/キャリブレーション
- ゲーム/エンタメ

## 動画
https://www.youtube.com/watch?v=u9zds1IFFlQ