/*
 * ActionShake.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: Joseph39 & OscarLeif
 */

#include "ActionShake.h"

ActionShake::ActionShake()
{}

ActionShake::~ActionShake()
{}
ActionShake* ActionShake::create()
{
    float interval = 1 / 60;
    float duration = 0.8f;
    float speed = 6.0f;
    float magnitude = 4.f;

    ActionShake* pAction = new ActionShake();
    pAction->duration = duration;
    pAction->magnitude = magnitude;
    pAction->speed = speed;
    //pAction->interval = interval;

    pAction->initWithDuration(duration);
    pAction->autorelease();
    return pAction;
}
ActionShake* ActionShake::create(float duration,float speed, float magnitude)
{
    ActionShake* pAction = new ActionShake();
    pAction->duration = duration;
    pAction->magnitude = magnitude;
    pAction->speed = speed;

    pAction->initWithDuration(duration);
    pAction->autorelease();
    return pAction;
}
void ActionShake::update(float dt)
{
    static float elapsed = 0.f;
    float randomStart = random(-1000.0f, 1000.0f);

    if(_target)
    {
        Vec2 orgPos = _target->getPosition();
        elapsed += dt;

        float percentComplete = elapsed / duration;

        // We want to reduce the shake from full power to 0 starting half way through
        float damper = 1.0f - clampf(2.0f * percentComplete - 1.0f, 0.0f, 1.0f);

        // Calculate the noise parameter starting randomly and going as fast as speed allows
        float alpha = randomStart + speed * percentComplete;

        // map noise to [-1, 1]
        float x = noise(alpha, 0.0f) * 2.0f - 1.0f;
        float y = noise(0.0f, alpha) * 2.0f - 1.0f;

        x *= magnitude * damper;
        y *= magnitude * damper;
        _target->setPosition(x, y);//Here is where the magic goes
        log("Elapsed : %4.2f",elapsed);
        if (elapsed >= duration)
        {
            elapsed = 0;
            _target->unscheduleUpdate();
            _target->setPosition(orgPos);
        }
    }
}
