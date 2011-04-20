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
#include "dot.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

dot::dot()
{
	setFlags ( ItemIsMovable | ItemIsSelectable );
	setZValue ( 1 );
        flaga = 0;
}

dot::~dot()
{
}

QRectF dot::boundingRect() const
{
        qreal adjust = 5;
	return QRectF ( -2 - adjust, -2 - adjust,
	                6 + adjust, 6 + adjust );
}

void dot::movable()
{
	//setFlags ( ItemIsMovable | ItemIsSelectable );
}

void dot::paint ( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	Q_UNUSED ( widget );

	painter->setPen ( Qt::NoPen );
	painter->setBrush ( Qt::darkGray );
	painter->drawEllipse ( -1, -1, 5, 5 );
	QRadialGradient gradient ( -3, -3, 10 );
	if( this->isSelected() )
	{
		if ( option->state & QStyle::State_Sunken )
		{
			gradient.setCenter ( 3, 3 );
			gradient.setFocalPoint ( 3, 3 );
			gradient.setColorAt ( 1, QColor ( Qt::green ).light ( 100 ) );
			gradient.setColorAt ( 0, QColor ( Qt::darkGreen ).light ( 100 ) );
		}
		else
		{
			gradient.setColorAt ( 0, Qt::green );
			gradient.setColorAt ( 1, Qt::darkGreen );
		}
	}
	else
	{
		if ( option->state & QStyle::State_Sunken )
		{
			gradient.setCenter ( 3, 3 );
			gradient.setFocalPoint ( 3, 3 );
			gradient.setColorAt ( 1, QColor ( Qt::yellow ).light ( 100 ) );
			gradient.setColorAt ( 0, QColor ( Qt::darkYellow ).light ( 100 ) );
		}
		else
		{
			gradient.setColorAt ( 0, Qt::yellow );
			gradient.setColorAt ( 1, Qt::darkYellow );
		}
	}
	painter->setBrush ( gradient );
	painter->setPen ( QPen ( Qt::black, 0 ) );
	painter->drawEllipse ( -2, -2, 6, 6 );

        painter->scale ( 1.0,-1.0 );

        painter->setFont(QFont("Arial", 14));
        //QRectF textrect (0,0,50.0,50.0);
        painter->drawText(0,10,message);
}
