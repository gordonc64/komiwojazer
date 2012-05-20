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
#include <QVector>
#include <QPainter>
#include <QWidget>
#include <QVector>
#include <QPolygonF>
#include <QObject>
#include <QPainter>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <QVector>
#include <QPainter>
#include <QWidget>
#include <QVector>
#include <QPolygonF>
#include <QtGui>
#include <QObject>
#include <QApplication>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QtGui>
#include <time.h>
#include <stdlib.h>
#include <QGraphicsItem>
#include <math.h>
#include <QtGui>

class punkty
{
	
	public:
		punkty();
		~punkty();
                double x1,y1;
                double x2,y2;
                double b2,b1,a,dlugosc,distance;
                double temp,temp2nd;
                double temp2;
                QMatrix m;
                QVector<QPointF>* createtable(int count);
                QVector<QPointF>* kolo(int x, int y, int radius, int count);
                QVector<QPointF>* linia(int count);
                QVector<QPointF>* liniarowna(int count);
                QVector<QPointF>* elipsa(int x, int y, int a, int b, int angle, int steps);
                QVector<QPointF>* circle_points,*mainpunkty,*liniapunkty,*elipsapunkty;
                QVector<QPointF>* bok4( int count);
};
