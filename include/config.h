#ifndef CONFIG_H_
#define CONFIG_H_

const int kScreenWidth = 1920;
const int kScreenHeight = 1080;

const int kBallRadius = 4;

const int kNumBalls = 3000;
const int kNumRedBalls = 5;//NUM_BALLS / 500;

const int kModulo = 1000;

const double kBallDx = 0.04;
const double kBallDy = 0.04;

const int kCollisionOffset =  0;//in pixels

const int kTimeAdjustment = 800;

const int kQuadtreeNodeCapacity = 5;

const int KQuadtreeOutlineThickness = 1;

const int kBallOutlineThickness = 0;

const int kFrameRateLimit = 30;


#endif // CONFIG_H_
