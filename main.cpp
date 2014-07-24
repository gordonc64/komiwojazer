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
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>

#include "widget.h"

int main ( int argc, char *argv[] )
{
	QApplication app ( argc, argv );

        MainWidget widget;
        widget.setGeometry ( 20, 20, 100, 100 );
        widget.show();
        printf("fdsfsdf");
        qDebug() << "narf";

        return app.exec();
}
