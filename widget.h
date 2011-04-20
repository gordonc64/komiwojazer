/***************************************************************************
 *   Copyright (C) 2011 by Daniel 'gordonc64' Gorazdowski   *
 *   gordonc64@gmail.com   *
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

#include <QWidget>
#include <QVector>
#include <QSpacerItem>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <QComboBox>
#include <QString>
#include <QWidget>
#include <QVector>
#include <QPolygonF>

#include <QObject>
#include <QApplication>
#include <QFileDialog>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QtGui>
#include <QHoverEvent>

#include "render.h"
//#include "punkty.h"

class MainWidget : public QMainWindow
{
	Q_OBJECT
	public:
		MainWidget( QWidget *parent = 0 );
                void resizeEvent(QResizeEvent *event);
                QLabel *liczba;
                QRect ekran;
                double x,y,w,h,htemp,bla;
                QStatusBar *statusbar;
		Render *p_render;
                punkty losowe;
                QVector<QPointF> *vlosowe,*vkolo,*vlinia,*velipsa,*vreadloop;
		QString _text;
                int liczbapunktow,indexmainwidget,xnew,ynew,height,width,sasiedzinumber;
                int iloscmiast, iloscpowtorzen, algorytm;
                float xdot,ydot;
                QAction *newAct;
                QAction *openAct;
                QAction *saveAct;
                QAction *openMacierzAct;
                QAction *saveMacierzAct;
                QAction *clearAct;
                QAction *exitAct;
                QAction *obliczenia;
                QRect temp2;
                QPoint mouse1,mouse2,pos,oldpos;
                QPointF punkttemp;
                QPushButton *zaznacz;
                QString fileName;
        private slots:
                void newFile();
                bool open();
                bool openmacierz();
                bool save();
                bool savemacierz();
                void dialog();

	public slots:
		//void slot();
		//void etykieta();
                void wyborobiektu( int );
                void punkty_slot( QString  );
                void sasiedzi_slot ( QString  );
                void rysujslot();
                void zaznaczslot();
                void usunslot();
                void iloscmiastslot(QString );
                void iloscpowtorzenslot(QString );
                void badaniaalgorytmslot(int );
                bool obliczslot();
};
