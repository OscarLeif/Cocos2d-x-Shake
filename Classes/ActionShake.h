/*
 * ActionShake.h
 *
 *  Created on: Mar 18, 2016
 *      Author: OscarLeif
 */

#ifndef ACTIONSHAKE_H_
#define ACTIONSHAKE_H_

#include "cocos2d.h"

USING_NS_CC;

class ActionShake:public cocos2d::ActionInterval
{
public:
    ActionShake();
    virtual ~ActionShake();
    static ActionShake* create();
    static ActionShake* create(float duration,float speed, float magnitude);

    inline double interpolate(double a, double b, double x)
    {
        double ft = x * 3.1415927;
        double f = (1.0 - cos(ft))* 0.5;
        return a*(1.0 - f) + b*f;
    }

    inline double findnoise(double x, double y)
    {
        int n = (int)x + (int)y * 57;
        n = (n << 13) ^ n;
        int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
        return 1.0 - ((double)nn / 1073741824.0);
    }


    double noise(double x, double y)
    {
        double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
        double floory = (double)((int)y);
        double s, t, u, v;//Integer declaration
        s = findnoise(floorx, floory);
        t = findnoise(floorx + 1, floory);
        u = findnoise(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
        v = findnoise(floorx + 1, floory + 1);

        double int1 = MathUtil::lerp(s, t, x - floorx);
        double int2 = MathUtil::lerp(u, v, x - floorx);
        return MathUtil::lerp(int1, int2, y - floory);
    }
private:
    float interval = 1/60 ;
    float duration;
    float speed;
    float magnitude;
protected:
    virtual void update(float d);
};


#endif /* ACTIONSHAKE_H_ */
