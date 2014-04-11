/*
    This file is part of Double Pendulum.
    Copyright (C) 2009  Freddie Witherden

    Double Pendulum is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Double Pendulum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Double Pendulum; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "doublependulumitem.h"

#include <cmath>

DoublePendulumItem::DoublePendulumItem()
    : m_pendulum(0)
{
}

DoublePendulumItem::~DoublePendulumItem()
{
    if (m_pendulum)
    {
        stop();
    }
}

void DoublePendulumItem::start()
{
    // Create the actual pendulum object
    m_pendulum = new DoublePendulumRK4(upper(), lower(), m_dt, m_g);
}

void DoublePendulumItem::stop()
{
    delete m_pendulum;
    m_pendulum = 0;
}

Pendulum& DoublePendulumItem::upper()
{
    return m_upper;
}

Pendulum& DoublePendulumItem::lower()
{
    return m_lower;
}

double DoublePendulumItem::dt()
{
    return m_dt;
}

void DoublePendulumItem::setDt(double dt)
{
    m_dt = dt;
}

double DoublePendulumItem::g()
{
    return m_g;
}

void DoublePendulumItem::setG(double g)
{
    m_g = g;
}


int DoublePendulumItem::opacity()
{
    return m_opacity;
}

void DoublePendulumItem::setOpacity(int opacity)
{
    m_opacity = opacity;
}

void DoublePendulumItem::draw()
{
    ofPushStyle();
    ofTranslate(ofGetWindowWidth()/2, ofGetHeight()/3);
    ofScale(200, 200);
    
    ofPoint upperBob(m_pendulum->l1() * sin(m_pendulum->theta1()),
                               m_pendulum->l1() * cos(m_pendulum->theta1()));
    
    ofPoint lowerBob(upperBob.x + m_pendulum->l2() * sin(m_pendulum->theta2()),
                        upperBob.y + m_pendulum->l2() * cos(m_pendulum->theta2()));
    

    ofPoint origin(0.0, 0.0);
    
    ofSetColor(0,0,0);
    ofSetLineWidth(5);
    ofLine(origin, upperBob);
    ofLine(upperBob, lowerBob);
    ofSetColor(200, 0, 0);
    ofCircle(upperBob.x, upperBob.y, 0.05);
    ofSetColor(0, 200, 100);
    ofCircle(lowerBob.x, lowerBob.y, 0.05);
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(m_pendulum->m1()), upperBob.x, upperBob.y);
    ofDrawBitmapString(ofToString(m_pendulum->m2()), lowerBob.x, lowerBob.y);
    
    ofPopStyle();
}


void DoublePendulumItem::updateScale(double newScale)
{
    m_scale = newScale;
}

void DoublePendulumItem::updateTime(double newTime)
{
    // Actual time (s as opposed to ms)
    double actualTime = newTime / 1000.0;

    // Update the pendulum
    if (actualTime > m_pendulum->time())
    {
        m_pendulum->update(actualTime);
    }

}

void DoublePendulumItem::updateMass(float m1, float m2){
    m_pendulum->updateMass(m1, m2);
}
