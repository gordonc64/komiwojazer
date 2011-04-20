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

//QVector<QPointF> &punkty::returntable()
//{
//	return mainpunkty;
//}
/*
void punkty::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);

    painter->drawEllipse(-7, -7, 20, 20);
}

QRectF punkty::boundingRect() const
{
    qreal adjust = 0;
    return QRectF(-7 - adjust, -7 - adjust,
                  20 + adjust, 20 + adjust);

}
*/

QVector<QPointF>* punkty::bok4( int count)
{
    a = (y1-y2)/(x1-x2);
    b1 = -(a*x1)+y1;
    b2 = -(a*x2)+y2;
    QRect bok4rect(QPoint(x1,y1),QPoint(x2,y2));

    //qDebug() << "x1" << x1 << "y1" << y1 << "x2" << x2 << "y2" << y2 << endl;
    //b1 = fabs(b1);
    //dlugosc = sqrt( (y1-y2)*(y1-y2) + (x1-x2)*(x1-x2) );
    //qDebug() << "dlugosc" << dlugosc << endl;
    //distance = dlugosc / count;
    //qDebug() << "distance" << distance << endl;
    temp = 0;
    temp2 = 0;


    srand((unsigned)time(NULL));
    liniapunkty->clear();

    (x1<x2)? temp2=x1: temp2=x2;
    //(x1<x2)? temp=temp: temp = x1-x2;
    temp = x1-x2;
    temp2nd = fabs(temp);
    distance = temp2nd / count;
    for(int i=0; i < count; i++)
    {
        //double x = temp2 + (temp2nd * (rand() / (RAND_MAX + 1.0)) );
        double x = temp2;
        temp2 = temp2 + distance;
        //x = fabs(x);
        double y = (a*x)+b1;
        //y = fabs(y);
        *liniapunkty << QPointF ( x, y );

    }
    return liniapunkty;
}

QVector<QPointF>* punkty::linia( int count)
{
        a = (y1-y2)/(x1-x2);
        b1 = -(a*x1)+y1;
        b2 = -(a*x2)+y2;
        //b1 = fabs(b1);

        temp = 0;
        temp2 = 0;

        srand((unsigned)time(NULL));
        liniapunkty->clear();

        (x1<x2)? temp2=x1: temp2=x2;
        //(x1<x2)? temp=temp: temp = x1-x2;
        temp = x1-x2;
        temp2nd = fabs(temp);
        for(int i=0; i < count; i++)
        {
            double x = temp2 + (temp2nd * (rand() / (RAND_MAX + 1.0)) );
            //x = fabs(x);
            double y = (a*x)+b1;
            //y = fabs(y);
            *liniapunkty << QPointF ( x, y );

        }
        return liniapunkty;
}

QVector<QPointF>* punkty::liniarowna( int count)
{
        a = (y1-y2)/(x1-x2);
        b1 = -(a*x1)+y1;
        b2 = -(a*x2)+y2;
        //qDebug() << "x1" << x1 << "y1" << y1 << "x2" << x2 << "y2" << y2 << endl;
        //b1 = fabs(b1);
        //dlugosc = sqrt( (y1-y2)*(y1-y2) + (x1-x2)*(x1-x2) );
        //qDebug() << "dlugosc" << dlugosc << endl;
        //distance = dlugosc / count;
        //qDebug() << "distance" << distance << endl;
        temp = 0;
        temp2 = 0;


        srand((unsigned)time(NULL));
        liniapunkty->clear();

        (x1<x2)? temp2=x1: temp2=x2;
        //(x1<x2)? temp=temp: temp = x1-x2;
        temp = x1-x2;
        temp2nd = fabs(temp);
        distance = temp2nd / count;
        for(int i=0; i < count; i++)
        {
            //double x = temp2 + (temp2nd * (rand() / (RAND_MAX + 1.0)) );
            double x = temp2;
            temp2 = temp2 + distance;
            //x = fabs(x);
            double y = (a*x)+b1;
            //y = fabs(y);
            *liniapunkty << QPointF ( x, y );

        }
        return liniapunkty;
}

QVector<QPointF>* punkty::elipsa(int x, int y, int a, int b, int angle, int steps)
{
    //function calculateEllipse()

      if (steps == 0)
        steps = 36;
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
	//srand((unsigned)time(NULL));

        circle_points->clear();
	//setPos(QPointF(100,100));

	qreal rot = 360.0 / count;
        QPointF center(x, y);

	//QMatrix vm;
	//vm.shear(2, -1);
	//vm.scale(3, 3);
	//QPolygonF points;
	
	for ( int i=0; i < count; i++ )
	{
                *circle_points << QPointF(radius, radius) * m + center;
		m.rotate(rot);
	}
	/*
	int angle = 6;
	float cosa=cos(angle);
	float sina=sin(angle);
	int points = 60;
	float x=50.0,y=50.0,dx=x,dy=y;
	for( int i=0; i<points; i++)
	{
		*m_points << QPointF(dx,dy)+ center;
		dx=(x*cosa)-(y*sina);
		dy=(x*sina)+(y*cosa);
		x=dx; y=dy;
	}
	*/
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
            //*mainpunkty << QPointF( rand() % (x2 - x1 + 1) + x1, rand() % (y2 - y1 + 1) + y1 );
	}
	//std::cout<<"Original table: " << &mainpunkty << "\n";
	//QVector<QPointF> &reftable = mainpunkty;
	//qreal d = (*mainpunkty)[1].x();
	//std::cout << d ;
	return mainpunkty;
}
