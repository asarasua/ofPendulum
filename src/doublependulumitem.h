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

#ifndef DOUBLEPENDULUMITEM_H
#define DOUBLEPENDULUMITEM_H


#include "doublependulum.h"
#include "doublependulumrk4.h"
#include "ofMain.h"

class DoublePendulumItem
{
public:
    DoublePendulumItem();
    ~DoublePendulumItem();

    void start();
    void stop();

    Pendulum& upper();
    Pendulum& lower();

    double dt();
    void setDt(double dt);

    double g();
    void setG(double g);

    int opacity();
    void setOpacity(int opacity);
    
    int type() const;

    void draw();

    void updateScale(double newScale);
    void updateTime(double newTime);
    void updateMass(float m1, float m2);


private:
    DoublePendulum *m_pendulum;

//    QString m_solver;
    double m_dt;
    double m_g;

    double m_scale;

    /**
     * Initial states of the upper and lower pendulums.
     */
    Pendulum m_upper, m_lower;
    
    int m_opacity;
};

//Q_DECLARE_METATYPE(DoublePendulumItem*);

#endif // DOUBLEPENDULUMITEM_H
