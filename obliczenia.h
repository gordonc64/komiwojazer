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

#ifndef OBLICZENIA_H
#define OBLICZENIA_H

#include <QWidget>
#include <QVector>
#include <QPolygonF>
#include <QtGui/QGraphicsView>
#include <QRect>
#include <QGraphicsRectItem>
#include <QRubberBand>
#include <QGraphicsLineItem>
#include <QStatusBar>
#include <QHoverEvent>
#include <QLabel>
#include <vector>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QtConcurrentRun>
#include <QThread>
#include <QPointF>
#include <QThread>
#include <QVector>
#include <QDebug>
#include <iostream>
#include <stdio.h>

//#include "hr_time.h"
#include "punkty.h"
#include "delaunay_tree_2d.h"
#include "dot.h"

class obliczenia: public QThread
{
        public:
            obliczenia();
            void calc();
            void run();
};

#endif // OBLICZENIA_H
