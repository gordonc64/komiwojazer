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

#include "obliczenia.h"

class Render : public QGraphicsView, public QHoverEvent
{
    Q_OBJECT
    enum   swaptype   { asymmetric, symmetric, last_swaptype };
    struct swaprecord {
        int x1,x2,y1,y2,z1,z2,gain;
        swaptype choice;
    };
public:
    Render ( QWidget *parent );
    void drawBackground ( QPainter *painter, const QRectF &rect );
    void polygonfunction ( QVector<QPointF> * );
    void polygonfunction2 ( QVector<QPointF> * );
    void delaunay( QVector<QPointF> * );
    void delaunayplot( QVector<QPointF> * );
    void macierzwag(/*QList<dot*> */);
    void macierzwag2(QList<dot*> );
    int wprowadzonytext() { return _text.toInt(); }
    void mousePressEvent ( QMouseEvent * evt );
    void mouseReleaseEvent ( QMouseEvent *evt );
    void mouseMoveEvent ( QMouseEvent * evt );
    void HoverEnter( QHoverEvent *evt);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void fitsp( int ,int ,float ,QVector<QVector<float> > *,QVector<int> *,double *);

    void twooptfast( int , QVector<QVector<float> > *,QVector<int> *);
    void twoopt( int , QVector<QVector<float> > *,QVector<int> *);

    void threeoptfast( int , QVector<QVector<float> > *, QVector<int> *);
    void threeopt( int , QVector<QVector<float> > *, QVector<int> *);
    void reverse(int ,int , QVector<int> &);
    void swapcheck(swaprecord& , QVector<QVector<float> > *);

    QStatusBar *mainwidgetbar;
    QPolygonF p;
    QPainterPath path;
    QPoint pos, oldpos, mousePressScene, mousePressView, mouseLastPosScene, mouseLastPosSceneRelease, mouseLastPosView;

    QVector<QPointF> *polygon;
    QVector<QPointF> *polygon2;
    QVector<QVector<float> > *macierzw;
    char macierzwtemp[1000][1000];
    QVector<dot *> dotslist;
    QVector<QGraphicsLineItem *> dasline;
    QVector<dot> dots;
    QVector<int> *trasa;
    double wagatrasy, wagatrasystart;
    double *tourwaga;
    double badaniatimer;
    double licznik;
    int looplimit;

    QGraphicsScene *scene;
    QString _text;
    QPointF test1,test2;

    int liczbapunktow,indexrender;
    int linesize,listsize;

    QPoint mouseDownPos;
    QPoint lastMouseViewPos;
    QPoint liniaPos2,liniaPos1;

    unsigned long long licznikiteracji,licznikiteracjipoprawy;
    int sasiedzinumber;
    int stopien;
    QRect rubberRect;
    QRectF testelipsa;
    bool pressed,zaznacz;
    QLabel *labelwagatrasy;
    QLabel *labelilosciteracji;
    QLabel *labelilosciteracjibetter;
    QLabel *labelczasms;
    QLabel *labelsasiedztwo;
    QRubberBand *rubberBand;
    QGraphicsLineItem *qgline, *qglinebackup;
    QGraphicsEllipseItem *qgellipse;
    QGraphicsRectItem *qgrect;
    QGraphicsPolygonItem *qgpolygon;

public slots:
    void punkty_slot ( QString text );
    void twooptslot();
    void twooptslotfast();

    void threeoptslot();
    void threeoptslotfast();

    void delaunayslot();

signals:
    void losuj();
    void pole_slot ( QVector<QPointF> );
    void punkty_signal ( QVector<QPointF> );
};
