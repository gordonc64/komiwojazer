/***************************************************************************
 *   Copyright (C) 2011 by Daniel 'gordonc64' Gorazdowski   		   *
 *   gordonc64@gmail.com   						   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "punkty.h"

punkty::punkty ()
{
	mainpunkty = new QVector<QPointF>;
        circle_points = new QVector<QPointF>;
        liniapunkty = new QVector<QPointF>;
        elipsapunkty = new QVector<QPointF>;
}

punkty::~punkty()
{
}

QVector<QPointF>* punkty::bok4( int count)
{
    a = (y1-y2)/(x1-x2);
    b1 = -(a*x1)+y1;
    b2 = -(a*x2)+y2;
    QRect bok4rect(QPoint(x1,y1),QPoint(x2,y2));

    temp = 0;
    temp2 = 0;
    srand((unsigned)time(NULL));
    liniapunkty->clear();
    (x1<x2)? temp2=x1: temp2=x2;
    temp = x1-x2;
    temp2nd = fabs(temp);
    distance = temp2nd / count;
    for(int i=0; i < count; i++)
    {
        double x = temp2;
        temp2 = temp2 + distance;
        double y = (a*x)+b1;
        *liniapunkty << QPointF ( x, y );
    }
    return liniapunkty;
}

QVector<QPointF>* punkty::linia( int count)
{
        a = (y1-y2)/(x1-x2);
        b1 = -(a*x1)+y1;
        b2 = -(a*x2)+y2;

        temp = 0;
        temp2 = 0;
        srand((unsigned)time(NULL));
        liniapunkty->clear();

        (x1<x2)? temp2=x1: temp2=x2;
        temp = x1-x2;
        temp2nd = fabs(temp);
        for(int i=0; i < count; i++)
        {
            double x = temp2 + (temp2nd * (rand() / (RAND_MAX + 1.0)) );
            double y = (a*x)+b1;
            *liniapunkty << QPointF ( x, y );
        }
        return liniapunkty;
}

QVector<QPointF>* punkty::liniarowna( int count)
{
        a = (y1-y2)/(x1-x2);
        b1 = -(a*x1)+y1;
        b2 = -(a*x2)+y2;      
        temp = 0;
        temp2 = 0;
        srand((unsigned)time(NULL));
        liniapunkty->clear();
        (x1<x2)? temp2=x1: temp2=x2;
        temp = x1-x2;
        temp2nd = fabs(temp);
        distance = temp2nd / count;
        for(int i=0; i < count; i++)
        {
            double x = temp2;
            temp2 = temp2 + distance;
            double y = (a*x)+b1;
            *liniapunkty << QPointF ( x, y );
        }
        return liniapunkty;
}

QVector<QPointF>* punkty::elipsa(int x, int y, int a, int b, int angle, int steps)
{
      if (steps == 0) steps = 36;
      elipsapunkty->clear();
      float pi = 3.14;
      // Angle is given by Degree Value
      float beta = -angle * (pi / 180); //(Math.PI/180) converts Degree Value into Radians
      float sinbeta = sin(beta);
      float cosbeta = cos(beta);

      for (int i = 0; i < 360; i += 360 / steps)
      {
        double alpha = i * (pi / 180) ;
        double sinalpha = sin(alpha);
        double cosalpha = cos(alpha);

        double X = x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta);
        double Y = y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta);

        *elipsapunkty << QPointF(X,Y);
       }

      return elipsapunkty;


}

QVector<QPointF>* punkty::kolo(int x, int y, int radius, int count)
{
        circle_points->clear();
	qreal rot = 360.0 / count;
        QPointF center(x, y);	
	for ( int i=0; i < count; i++ )
	{
                *circle_points << QPointF(radius, radius) * m + center;
		m.rotate(rot);
	}	
        return circle_points;
}

QVector<QPointF>* punkty::createtable(int count)
{
	mainpunkty->clear();
	srand((unsigned)time(NULL));
	for (int i=0; i < count; ++i)
	{
		
            *mainpunkty << QPointF( x1 + (double) ( (x2-x1) * (rand() / (RAND_MAX + 1.0))),
                                    y1 + (double) ( (y2-y1) * (rand() / (RAND_MAX + 1.0))) );
	}	
	return mainpunkty;
}
