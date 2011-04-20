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
#include "render.h"

#include "VoronoiDiagramGenerator.h"

using namespace std;

Render::Render ( QWidget *parent ): QHoverEvent(MouseMove, pos, oldpos)
{
        labelilosciteracji = new QLabel;
        labelwagatrasy = new QLabel;
        labelczasms = new QLabel;
        labelsasiedztwo = new QLabel;
        labelilosciteracjibetter = new QLabel;
        looplimit=1000;
        stopien=0;
        mainwidgetbar = new QStatusBar;
	scene = new QGraphicsScene ( parent );
	scene->setItemIndexMethod ( QGraphicsScene::NoIndex );     
        setScene ( scene );
	setCacheMode ( CacheBackground );
	setRenderHint ( QPainter::Antialiasing );
	setTransformationAnchor ( AnchorUnderMouse );
	setAlignment ( Qt::AlignLeft | Qt::AlignBottom );
	scale ( 1.0,-1.0 );
        indexrender=0;
        zaznacz=0;
        pressed=0;
        //tescik.setVisible ( 0 );
        //scene->addItem ( &tescik );
	polygon = new QVector<QPointF>;
        //dasline = new QVector<QGraphicsLineItem>;
        tourwaga = new double;
        trasa = new QVector<int>;
        qgrect = new QGraphicsRectItem(0, scene);
        rubberBand = new QRubberBand ( QRubberBand::Rectangle, this );
        qgline = new QGraphicsLineItem( 0, scene );
        qglinebackup = new QGraphicsLineItem( 0, scene );
        qgellipse = new QGraphicsEllipseItem( 0, scene );
        qgpolygon = new QGraphicsPolygonItem( 0, scene );
        this->viewport()->setMouseTracking(true);
        /*
        QGraphicsTextItem* text = new QGraphicsTextItem("1", 0, scene);
        text->setFont(QFont("Arial", 8));
        text->moveBy(100,100);
        //text->rotate(180);
        text->scale ( 1.0,-1.0 );
        text->show();
        */
}

void Render::HoverEnter( QHoverEvent *evt)
{
    Q_UNUSED(evt);
}

void Render::mouseMoveEvent ( QMouseEvent* evt )
{
    mouseLastPosView = evt->pos();
    mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
    QString message("test");
    //long a = 200;
    //message.arg(a);
    message = QString("%1,%2").arg(mouseLastPosScene.x()).arg(mouseLastPosScene.y());

    //a++;
    //message.fromAscii(char1);
    mainwidgetbar->showMessage(message);
    if(zaznacz)
    {
        if ( evt->buttons().testFlag ( Qt::LeftButton ) )
        {
          if ( rubberBand->isVisible() )
              {
                      qgline->hide();
                      qgellipse->hide();
                      qgrect->hide();
                      mousePressView = mapFromScene ( mouseDownPos );
                      mouseLastPosView = evt->pos();
                      mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                      rubberRect.setTopLeft ( mousePressView );
                      rubberRect.setBottomRight ( mouseLastPosView );
                      rubberRect = rubberRect.normalized();
                      rubberBand->setGeometry ( rubberRect );
                      QPolygonF p = mapToScene ( rubberRect );
                      QPainterPath path;
                      path.addPolygon ( p );
                      scene->setSelectionArea ( path, Qt::IntersectsItemShape );
                      indexrender = 10;
              }
         }
    }

    switch(indexrender)
    {
        case 1:
          if ( evt->buttons().testFlag ( Qt::LeftButton ) )
          {
            if ( qgrect->isVisible() )
                {
                        qgline->hide();
                        qgellipse->hide();
                        mousePressView = mapFromScene ( mouseDownPos );
                        mouseLastPosView = evt->pos();
                        mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                        rubberRect.setTopLeft ( mouseDownPos );
                        rubberRect.setBottomRight ( mouseLastPosScene );
                        rubberRect = rubberRect.normalized();
                        qgrect->setRect(QRectF(rubberRect));
                }
           }
        break;

        case 2:
           if( evt->buttons().testFlag(Qt::LeftButton))
           {
                if(qgellipse->isVisible())
               {
                    qgline->hide();
                    //rubberBand->hide();
                    qgrect->hide();
                    mousePressView = mapFromScene ( mouseDownPos );
                    mouseLastPosView = evt->pos();
                    mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                    rubberRect.setBottomLeft ( mouseDownPos );
                    rubberRect.setTopRight ( mouseLastPosScene );
                    rubberRect = rubberRect.normalized();
                    int x = mouseDownPos.x();
                    int y = mouseDownPos.y();
                    int height = rubberRect.height();
                    int width = rubberRect.width();                    
                    if( mouseDownPos.x() > mouseLastPosScene.x() && mouseDownPos.y() > mouseLastPosScene.y() )
                    {
                        (height>width) ? qgellipse->setRect(x,y,-height,-height) : qgellipse->setRect(x,y,-width,-width);
                        rubberRect.setRect( x, y, qgellipse->rect().width(), qgellipse->rect().height() );
                    }
                    if( mouseDownPos.x() > mouseLastPosScene.x() && mouseDownPos.y() < mouseLastPosScene.y() )
                    {
                        (height>width) ? qgellipse->setRect(x,y,-height,height) : qgellipse->setRect(x,y,-width,width);
                        rubberRect.setRect( x, y, qgellipse->rect().width(), qgellipse->rect().height() );
                    }
                    if( mouseDownPos.x() < mouseLastPosScene.x() && mouseDownPos.y() < mouseLastPosScene.y() )
                    {
                        (height>width) ? qgellipse->setRect(x,y,height,height) : qgellipse->setRect(x,y,width,width);
                        rubberRect.setRect( x, y, qgellipse->rect().width(), qgellipse->rect().height() );
                    }
                    if( mouseDownPos.x() < mouseLastPosScene.x() && mouseDownPos.y() > mouseLastPosScene.y() )
                    {
                        (height>width) ? qgellipse->setRect(x,y,height,-height) : qgellipse->setRect(x,y,width,-width);
                        rubberRect.setRect( x, y, qgellipse->rect().width(), qgellipse->rect().height() );
                    }

                    testelipsa = qgellipse->rect();
                    test1 = rubberRect.topRight();
                    test2 = rubberRect.bottomLeft();

               }
           }
        break;

        case 3:
        if( evt->buttons().testFlag(Qt::LeftButton))
        {
             if(qgellipse->isVisible())
            {
                 qgline->hide();
                 rubberBand->hide();
                 qgrect->hide();
                 mousePressView = mapFromScene ( mouseDownPos );
                 mouseLastPosView = evt->pos();
                 mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                 rubberRect.setTopLeft ( mouseDownPos );
                 rubberRect.setBottomRight ( mouseLastPosScene );
                 rubberRect = rubberRect.normalized();
                 //rubberBand->setGeometry ( rubberRect );
                 qgellipse->setRect(rubberRect);
            }
        }
        break;

        case 4:

            if ( evt->buttons().testFlag ( Qt::LeftButton ) )
            {
                if (qgline->isVisible())
                {
                    rubberBand->hide();
                    qgellipse->hide();
                    qgrect->hide();
                    pressed=0;
                    mouseLastPosView = evt->pos();
                    mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                    qgline->setLine(QLineF(QLine(liniaPos1,mouseLastPosScene)));
                    //rubberRect.setTopLeft ( mouseDownPos );
                    //rubberRect.setBottomRight ( mouseLastPosScene );
                    //rubberRect = rubberRect.normalized();

                    //qgrect->setRect(QRectF(rubberRect));
                    //test2 = qgrect->rect().bottomLeft();
                    //qglinebackup->setLine(QLineF(QLine(liniaPos1,test2.toPoint())));
                }
            }
        break;

        case 5:

            if ( evt->buttons().testFlag ( Qt::LeftButton ) )
            {
                if (qgline->isVisible())
                {
                    rubberBand->hide();
                    qgellipse->hide();
                    qgrect->hide();
                    pressed=0;
                    mouseLastPosView = evt->pos();
                    mouseLastPosScene = mapToScene ( mouseLastPosView ).toPoint();
                    qgline->setLine(QLineF(QLine(liniaPos1,mouseLastPosScene)));
                }
            }
        break;
       }
       QGraphicsView::mouseMoveEvent ( evt );
}

void Render::mouseReleaseEvent ( QMouseEvent* evt )
{
        liniaPos2 = mapToScene ( evt->pos() ).toPoint();
        mouseLastPosSceneRelease = mapToScene ( mouseLastPosView ).toPoint();

        rubberBand->hide();
	QGraphicsView::mouseReleaseEvent ( evt );
}

void Render::mousePressEvent ( QMouseEvent* evt )
{
  if( scene->itemAt ( mapToScene ( evt->pos() ) ))
  {
      rubberBand->hide();
      qgellipse->hide();
      qgrect->hide();
      qgline->hide();
  }
  if(evt->buttons().testFlag ( Qt::RightButton ) && !scene->itemAt ( mapToScene ( evt->pos() ) ))
  {
        mouseDownPos = mapToScene ( evt->pos() ).toPoint();
        dot *punkt = new dot;
        punkt->setPos(mouseDownPos.x(), mouseDownPos.y());
        scene->addItem(punkt);

  }

  if(evt->buttons().testFlag ( Qt::LeftButton ) && !scene->itemAt ( mapToScene ( evt->pos() ) ))
  {
   if(zaznacz)
   {
       if ( !scene->itemAt ( mapToScene ( evt->pos() ) ) )
       {
               mouseDownPos = mapToScene ( evt->pos() ).toPoint();
               mouseLastPosView = evt->pos();
               rubberBand->setGeometry (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
               rubberBand->show();
               indexrender = 10;
       }
   }

   switch(indexrender)
   {
    case 1:
     {
        if ( !scene->itemAt ( mapToScene ( evt->pos() ) ) )
        {
                mouseDownPos = mapToScene ( evt->pos() ).toPoint();
                mouseLastPosView = evt->pos();
                qgrect->setRect (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
                qgrect->show();
                //rubberBand->setGeometry (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
                //rubberBand->show();
        }
     }

    break;

    case 2:
    {
        if ( !scene->itemAt ( mapToScene ( evt->pos() ) ) )
        {
            mouseDownPos = mapToScene ( evt->pos() ).toPoint();
            mouseLastPosView = evt->pos();
            qgellipse->setRect( mouseDownPos.x(), mouseDownPos.y(), 0,0);
            qgellipse->show();
            //rubberBand->setGeometry (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
            //rubberBand->show();
        }
    }
    break;

   case 3:
   {
       if ( !scene->itemAt ( mapToScene ( evt->pos() ) ) )
       {
           mouseDownPos = mapToScene ( evt->pos() ).toPoint();
           mouseLastPosView = evt->pos();
           qgellipse->setRect( mouseDownPos.x(), mouseDownPos.y(), 0,0);
           qgellipse->show();
           //rubberBand->setGeometry (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
           //rubberBand->show();
       }
   }
   break;

    case 4:
     {
        if(!scene->itemAt ( mapToScene ( evt->pos() ) ))
        {
            if(pressed)
            {
                pressed=0;

                liniaPos2 = mapToScene ( evt->pos() ).toPoint();
                qgline->setLine(QLineF(QLine(liniaPos1,liniaPos2)));
                //qglinebackup->setLine(QLineF(QLine(liniaPos1,test2.toPoint())));

            }
            else
            {
                qgline->show();
                qglinebackup->show();
                //qgrect->show();
                mouseDownPos = mapToScene ( evt->pos() ).toPoint();
                mouseLastPosView = evt->pos();
                //qgrect->setRect (  mouseDownPos.x(),  mouseDownPos.y(), 0,0 );
                liniaPos1 = mapToScene ( evt->pos() ).toPoint();
                qgline->setLine(QLineF(QLine(liniaPos1,liniaPos1)));
                //qglinebackup->setLine(QLineF(QLine(liniaPos1,liniaPos1)));
                pressed=1;

            }
        }
     }
    break;

   case 5:
    {
       if(!scene->itemAt ( mapToScene ( evt->pos() ) ))
       {
           if(pressed)
           {
               pressed=0;
               liniaPos2 = mapToScene ( evt->pos() ).toPoint();
               qgline->setLine(QLineF(QLine(liniaPos1,liniaPos2)));

           }
           else
           {
               qgline->show();
               liniaPos1 = mapToScene ( evt->pos() ).toPoint();
               qgline->setLine(QLineF(QLine(liniaPos1,liniaPos1)));
               pressed=1;

           }
       }
    }
   break;
   }
 }

 QGraphicsView::mousePressEvent ( evt );
}

void Render::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event);
    //QMenu menu;
    //QAction *removeAction = menu.addAction("Remove");
}

void Render::polygonfunction ( QVector<QPointF> *temp )
{
        //polygon = temp;
}

void Render::polygonfunction2 ( QVector<QPointF> *temp )
{
        //polygon->clear();
	polygon2 = temp;
        int vsize = polygon2->size();
        dot *test2 = new dot[vsize];
        //dots.clear();
        for ( int i=0 ;i < vsize ;i++ )
	{
		QPointF w2 = ( *polygon2 ).at ( i );
                //dot punktw;
                //dots.push_back(punktw);
                test2[i].setPos ( w2 );
                test2[i].flaga = 1;
                //test2[i].message = QString("%1").arg(i);
                //dots.at(i).setPos(w2);
                scene->addItem ( &test2[i] );
        };

        delaunay(polygon2);

        QString tempstring;
        tempstring = QString("%1").arg(stopien);
        labelsasiedztwo->setText(tempstring);
}

void Render::twooptslotfast()
{
    QString tempstring;

    polygon->clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( QGraphicsLineItem *dots = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
           dots->hide();
           scene->removeItem(dots);
        }
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else *polygon << dots->pos();
        }
    }
    delaunay(polygon);
    twooptfast(listsize, macierzw, trasa);
    badaniatimer = licznik;
    //twoopt(listsize, macierzw, trasa);
    wagatrasy = 0.0;
    QPointF start,end;
    float x,y,x2,y2;
    int size = dotslist.size();
    int p;
    for(int e=0; e < size-1; e++)
    {
        if(e==size-2)
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
            scene->addLine(QLineF(e1,e2));
            e1 = dotslist.at(trasa->at(e+1))->pos();
            e2 = dotslist.at(trasa->at(0))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }
        else
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            p=e; p++;
            QPointF e2 = dotslist.at(trasa->at(p))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }

    }

    tempstring = QString("%1").arg(badaniatimer);
    labelczasms->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracji);
    labelilosciteracji->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracjipoprawy);
    labelilosciteracjibetter->setText(tempstring);
    tempstring = QString("%1").arg(wagatrasy);
    labelwagatrasy->setText(tempstring);
}

void Render::twooptslot()
{
    polygon->clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( QGraphicsLineItem *dots = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
            dots->hide();
            scene->removeItem(dots);
        }

        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else *polygon << dots->pos();
        }
    }
    delaunay(polygon);
    twoopt(listsize, macierzw, trasa);
    badaniatimer = licznik;
    wagatrasy = 0.0;
    QPointF start,end;
    float x,y,x2,y2;
    int size = dotslist.size();
    int p;
    for(int e=0; e < size-1; e++)
    {
        if(e==size-2)
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
            scene->addLine(QLineF(e1,e2));
            e1 = dotslist.at(trasa->at(e+1))->pos();
            e2 = dotslist.at(trasa->at(0))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }
        else
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            p=e; p++;
            QPointF e2 = dotslist.at(trasa->at(p))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }

    }
    QString tempstring;
    tempstring = QString("%1").arg(wagatrasy);
    labelwagatrasy->setText(tempstring);

    tempstring = QString("%1").arg(badaniatimer);
    labelczasms->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracji);
    labelilosciteracji->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracjipoprawy);
    labelilosciteracjibetter->setText(tempstring);
}

void Render::threeoptslot()
{
    polygon->clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( QGraphicsLineItem *dots = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
           dots->hide();
           scene->removeItem(dots);
        }

        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else *polygon << dots->pos();
        }
    }
    delaunay(polygon);
    threeopt(listsize, macierzw, trasa);
    badaniatimer = licznik;
    wagatrasy = 0.0;
    QPointF start,end;
    float x,y,x2,y2;
    int size = dotslist.size();
    int p;
    for(int e=0; e < size-1; e++)
    {
        if(e==size-2)
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
            scene->addLine(QLineF(e1,e2));
            e1 = dotslist.at(trasa->at(e+1))->pos();
            e2 = dotslist.at(trasa->at(0))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }
        else
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            p=e; p++;
            QPointF e2 = dotslist.at(trasa->at(p))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }

    }
    QString tempstring;
    tempstring = QString("%1").arg(wagatrasy);
    labelwagatrasy->setText(tempstring);

    tempstring = QString("%1").arg(badaniatimer);
    labelczasms->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracji);
    labelilosciteracji->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracjipoprawy);
    labelilosciteracjibetter->setText(tempstring);
}

void Render::threeoptslotfast()
{
    QString tempstring;

    polygon->clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( QGraphicsLineItem *dots = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
           dots->hide();
           scene->removeItem(dots);
        }

        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else *polygon << dots->pos();
        }
    }
    delaunay(polygon);
    threeoptfast(listsize, macierzw, trasa);
    //threeopt(listsize, macierzw, trasa);
    badaniatimer = licznik;
    wagatrasy = 0.0;
    QPointF start,end;
    float x,y,x2,y2;
    int size = dotslist.size();
    int p;
    for(int e=0; e < size-1; e++)
    {
        if(e==size-2)
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
            scene->addLine(QLineF(e1,e2));
            e1 = dotslist.at(trasa->at(e+1))->pos();
            e2 = dotslist.at(trasa->at(0))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }
        else
        {
            QPointF e1 = dotslist.at(trasa->at(e))->pos();
            p=e; p++;
            QPointF e2 = dotslist.at(trasa->at(p))->pos();
            scene->addLine(QLineF(e1,e2));
            start = e1;
            end = e2;
            x = start.x();
            y = start.y();
            x2 = end.x();
            y2 = end.y();
            wagatrasy += sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        }

    }

    tempstring = QString("%1").arg(wagatrasy);
    labelwagatrasy->setText(tempstring);

    tempstring = QString("%1").arg(badaniatimer);
    labelczasms->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracji);
    labelilosciteracji->setText(tempstring);

    tempstring = QString("%1").arg(licznikiteracjipoprawy);
    labelilosciteracjibetter->setText(tempstring);
}

void Render::delaunayslot()
{
    //QPointF punkt_test;
    polygon->clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( QGraphicsLineItem *dots = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
           dots->hide();
           scene->removeItem(dots);
        }

        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else
            {
                *polygon << dots->pos();
                //punkt_test = dots->pos();
                //qDebug() << punkt_test;
            }
        }
    }

    delaunay(polygon);
    delaunayplot(polygon);
}

void Render::delaunayplot( QVector<QPointF> *temp )
{
        Delaunay_tree Dt;
        dasline.clear();
        polygon2 = temp;
        int vsize = polygon2->size();
        float xValues[vsize];
        float yValues[vsize];
        for(int i=0; i<vsize; i++)
        {
            QPointF w2 = ( *polygon2 ).at ( i );
            xValues[i]=w2.x();
            yValues[i]=w2.y();
        }
        VoronoiDiagramGenerator vdg;
        vdg.generateVoronoi(xValues,yValues,vsize, -100,100,-100,100,3);

        vdg.resetIterator();
        vdg.resetDelaunayEdgesIterator();
        float x1,y1,x2,y2;
        int o=0;
        while(vdg.getNextDelaunay(x1,y1,x2,y2))
        {
                //printf("GOT Line (%f,%f)->(%f,%f)\n",x1,y1,x2, y2);
                QPointF w1(x1,y1);
                QPointF w2(x2,y2);
                dasline << new QGraphicsLineItem(QLineF(w1,w2));
                scene->addItem ( dasline.at(o));
                dasline.at(o)->show();
                o++;
        }
        /*
        for ( int i=0 ;i < vsize ;i++ )
        {
                QPointF w2 = ( *polygon2 ).at ( i );
                Dt += new point ( (double)w2.x(), (double)w2.y() );
        };

        dasline.clear();
        Dt.output();
        polygon2 = Dt.tablicapunktow;
        vsize = polygon2->size();

        for ( int i=0,j=0 ;i < vsize ;i++,j++ )
        {
                QPointF w1 = ( *polygon2 ).at ( i );
                i++;
                QPointF w2 = ( *polygon2 ).at ( i );
                dasline << new QGraphicsLineItem(QLineF(w1,w2));
                scene->addItem ( dasline.at(j));
                dasline.at(j)->show();
        };

        //macierzwag();
        //fitsp(listsize,0,4000,macierzw,trasa,tourwaga);
        //wagatrasystart = *tourwaga;
        //twooptfast(listsize, macierzw, trasa);
        //threeoptfast(listsize, macierzw, trasa);
        //twooptfast(listsize, macierzw, trasa);
        //twoopt(listsize, macierzw, trasa);
        int y = dotslist.size();
        int p;


        for(int e=0; e < y-1; e++)
        {
            if(e==y-2)
            {
                QPointF e1 = dotslist.at(trasa->at(e))->pos();
                QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
                scene->addLine(QLineF(e1,e2));
                e1 = dotslist.at(trasa->at(e+1))->pos();
                e2 = dotslist.at(trasa->at(0))->pos();
                scene->addLine(QLineF(e1,e2));
            }
            else
            {
                QPointF e1 = dotslist.at(trasa->at(e))->pos();
                p=e; p++;
                QPointF e2 = dotslist.at(trasa->at(p))->pos();
                scene->addLine(QLineF(e1,e2));
            }

        }
        */

        //qgpolygon->show();
}

void Render::delaunay( QVector<QPointF> *temp )
{

        for(int bla=0; bla < looplimit; bla++)
        {
            for(int bla2=0; bla2 < looplimit; bla2++)
            {
                macierzwtemp[bla][bla2] = 0;
                //printf("%i ",tempbla);
                //qDebug() << tempbla << " ";
            }
            //printf("\n");
            //qDebug() <<  endl;
        }
        Delaunay_tree Dt;
        dasline.clear();
        polygon2 = temp;
        int vsize = polygon2->size();
        float xValues[vsize];
        float yValues[vsize];
        QList<QPointF> listapunktow;
        for(int i=0; i<vsize; i++)
        {
            QPointF punkt = ( *polygon2 ).at ( i );
            xValues[i]=punkt.x();
            yValues[i]=punkt.y();
            listapunktow << punkt;
        }
        /*
        VoronoiDiagramGenerator vdg;
        vdg.generateVoronoi(xValues,yValues,vsize, -100,100,-100,100,3);

        vdg.resetIterator();
        vdg.resetDelaunayEdgesIterator();
        float x1,y1,x2,y2;
        int o=0;
        //qDebug() << "narf 1";
        while(vdg.getNextDelaunay(x1,y1,x2,y2))
        {
                //printf("GOT Line (%f,%f)->(%f,%f)\n",x1,y1,x2, y2);
                QPointF w1(x1,y1);
                QPointF w2(x2,y2);
                int count = 0;
                foreach(QPointF temppoint, listapunktow)
                {
                    if(temppoint == w1 )
                        //qDebug() << "narf 2";
                    if(temppoint == w2 )
                        //qDebug() << "narf 2";
                    count++;


                }
                dasline << new QGraphicsLineItem(QLineF(w1,w2));
                scene->addItem ( dasline.at(o));
                dasline.at(o)->show();
                o++;
        }
        */
        for ( int i=0 ;i < vsize ;i++ )
        {
                QPointF w2 = ( *polygon2 ).at ( i );
                Dt += new point ( (double)w2.x(), (double)w2.y() );
        };

        dasline.clear();

        Dt.output();
        polygon2 = Dt.tablicapunktow;

        vsize = polygon2->size();


        for ( int i=0,j=0 ;i < vsize ;i++,j++ )
        {
                QPointF w1 = ( *polygon2 ).at ( i );
                i++;
                QPointF w2 = ( *polygon2 ).at ( i );
                //dasline << new QGraphicsLineItem(QLineF(w1,w2));
                int count = 0;
                //int w1count = 0;

                foreach(QPointF temppoint, listapunktow)
                {
                    if(temppoint == w1 )
                    {
                        int w2count = 0;
                        foreach(QPointF temppoint2, listapunktow)
                        {
                            if(temppoint2 == w2 )
                            {
                                macierzwtemp[count][w2count]=1;
                                macierzwtemp[w2count][count]=1;
                                //qDebug() << "   1 ";

                            }
                            w2count++;
                        }
                    }
                    if(temppoint == w2 )
                    {
                        int w1count = 0;
                        foreach(QPointF temppoint1, listapunktow)
                        {
                            if(temppoint1 == w1 )
                            {
                                macierzwtemp[count][w1count]=1;
                                macierzwtemp[w1count][count]=1;
                                //qDebug() << "   1 ";
                            }
                            w1count++;
                        }
                    }
                    count++;
                }
                //scene->addItem ( dasline.at(j));
                //dasline.at(j)->show();
        }

        /*
        for(int bbb=0; bbb < looplimit; bbb++ )
        {
           macierzwtemp[bbb][bbb]=0;
        }

        for( int b=0; b < looplimit; b++ )
        {
            for( int a=0; a < looplimit; a++)
            {
                if(macierzwtemp[b][a]==1)
                {
                    for(int p=0; p < looplimit; p++  )
                    {
                        if(macierzwtemp[a][p]==1 && !p==b)
                        {
                            if(macierzwtemp[b][p]==0)
                            {
                                macierzwtemp[b][a]=2;
                                macierzwtemp[a][b]=2;
                            }
                        }
                    }
                }
            }

        }

        for(int bbbb=0; bbbb < looplimit; bbbb++ )
        {
            macierzwtemp[bbbb][bbbb]=0;
        }

        for( int thirdb=0; thirdb < looplimit; thirdb++ )
        {
            for( int thirda=0; thirda < looplimit; thirda++)
            {
                if(macierzwtemp[thirdb][thirda]==2)
                {
                    for(int thirdp=0; thirdp < looplimit; thirdp++  )
                    {
                        if(macierzwtemp[thirda][thirdp]==2 && !thirdp==thirdb)
                        {

                            if(macierzwtemp[thirdb][thirdp]==0)
                            {
                                macierzwtemp[thirdb][thirdp]=3;
                                macierzwtemp[thirdp][thirdb]=3;
                            }
                        }
                    }
                }
            }

        }


        */
        bool goloop=1;
        int first=1;
        int second=2;


        while(goloop)
        {
            goloop = 0;
            for( int b=0; b < looplimit; b++ )
            {
                for( int a=0; a < looplimit; a++ )
                {
                    if( macierzwtemp[b][a]==first )
                    {
                        for( int p=0; p < looplimit; p++ )
                        {
                            if( macierzwtemp[a][p]==1 && !(p==b) )
                            {
                                if( macierzwtemp[b][p]==0 )
                                {
                                    macierzwtemp[b][p]=second;
                                    macierzwtemp[p][b]=second;
                                    goloop = 1;
                                }
                            }
                        }
                    }
                }
             }

             stopien = first;
             if( goloop==1 )
             {
                first++;
                second++;
             }
        }

        //for(int bbo=0; bbo < looplimit; bbo++ )
        {
            //macierzwtemp[bbo][bbo]=0;
        }

        macierzwag();
        fitsp(listsize,0,5000,macierzw,trasa,tourwaga);
        wagatrasystart = *tourwaga;
        //twooptfast(listsize, macierzw, trasa);
        //threeoptfast(listsize, macierzw, trasa);
        //twooptfast(listsize, macierzw, trasa);
        //twoopt(listsize, macierzw, trasa);
        //int y = dotslist.size();
        //int p;

        /*
        for(int e=0; e < y-1; e++)
        {
            if(e==y-2)
            {
                QPointF e1 = dotslist.at(trasa->at(e))->pos();
                QPointF e2 = dotslist.at(trasa->at(e+1))->pos();
                scene->addLine(QLineF(e1,e2));
                e1 = dotslist.at(trasa->at(e+1))->pos();
                e2 = dotslist.at(trasa->at(0))->pos();
                scene->addLine(QLineF(e1,e2));
            }
            else
            {
                QPointF e1 = dotslist.at(trasa->at(e))->pos();
                p=e; p++;
                QPointF e2 = dotslist.at(trasa->at(p))->pos();
                scene->addLine(QLineF(e1,e2));
            }

        }
        */

        //qgpolygon->show();
}

void Render::swapcheck(swaprecord& zamiana, QVector<QVector<float> > *macierzwag)
{
       int waga,max;

                {
      zamiana.gain=0;
      waga=(*macierzwag)[zamiana.x1][zamiana.x2]+(*macierzwag)[zamiana.y1][zamiana.y2]+(*macierzwag)[zamiana.z1][zamiana.z2];
      max=waga-((*macierzwag)[zamiana.y1][zamiana.x1]+(*macierzwag)[zamiana.z1][zamiana.x2]+(*macierzwag)[zamiana.z2][zamiana.y2]);
      if (max > zamiana.gain)  {
         zamiana.gain=max;  zamiana.choice=asymmetric;
      }
      max=waga-((*macierzwag)[zamiana.x1][zamiana.y2]+(*macierzwag)[zamiana.z1][zamiana.x2]+(*macierzwag)[zamiana.y1][zamiana.z2]);
      if (max > zamiana.gain)  {
         zamiana.gain=max;  zamiana.choice =symmetric;
      }
   }
}

void Render::reverse(int start,int finish, QVector<int> &poczatkowatrasa)
{
       int wyprzedzajacy,ostatni,natsepny;

   if (start != finish)  {
      ostatni=start;  natsepny=poczatkowatrasa[ostatni];
      do {
         wyprzedzajacy=poczatkowatrasa[natsepny];  poczatkowatrasa[natsepny]=ostatni;
         ostatni=natsepny;  natsepny=wyprzedzajacy;
      } while (!(ostatni == finish));
   }
}

void Render::threeoptfast( int iloscmiast, QVector<QVector<float> > *macierzwag, QVector<int> *trasastartowa)
{
   swaprecord bestswap,swap;
   int ib,indexb,jb,kb;
   QVector<int> ptrb(iloscmiast,0);
   //CStopWatch stoper;
   //stoper.startTimer();
   licznikiteracji = 0;
   licznikiteracjipoprawy = 0;
   for( ib=0; ib < iloscmiast-1; ib ++) ptrb[(*trasastartowa)[ib]]=(*trasastartowa)[ib+1];
   ptrb[(*trasastartowa)[iloscmiast-1]]=(*trasastartowa)[0];
   do {
      bestswap.gain=0;
      swap.x1=1;
      for( ib=0; ib < iloscmiast; ib ++)
      {
        swap.x2=ptrb[swap.x1];
        swap.y1=swap.x2;

         for( jb=2; jb < iloscmiast-3; jb ++)
         {
           swap.y2=ptrb[swap.y1];
           swap.z1=ptrb[swap.y2];
           if(
                 (   macierzwtemp[swap.x2][swap.x1] <= sasiedzinumber
                  && macierzwtemp[swap.x1][swap.x2] <= sasiedzinumber
                  && macierzwtemp[swap.x2][swap.y1] <= sasiedzinumber
                  && macierzwtemp[swap.y1][swap.x2] <= sasiedzinumber )
             )
           {
            for( kb=jb+2; kb < iloscmiast-1; kb ++)
            {
               licznikiteracji++;
               swap.z2=ptrb[swap.z1];
               swapcheck(swap, macierzwag);
               if (swap.gain > bestswap.gain)
               {
                   bestswap=swap;
                   licznikiteracjipoprawy++;
               }
               swap.z1=swap.z2;
            }
           }
           swap.y1=swap.y2;
         }
         swap.x1=swap.x2;

      }
      if (bestswap.gain > 0)
      {
            if (bestswap.choice == asymmetric)  {
               reverse(bestswap.z2,bestswap.x1, ptrb);
               ptrb[bestswap.y1]=bestswap.x1;  ptrb[bestswap.z2]=bestswap.y2;
            }
            else {
               ptrb[bestswap.x1]=bestswap.y2;  ptrb[bestswap.y1]=bestswap.z2;
            }
            ptrb[bestswap.z1]=bestswap.x2;
      }
   } while (!(bestswap.gain == 0));
   indexb=1;
   for( ib=0; ib < iloscmiast; ib ++) {
      (*trasastartowa)[ib]=indexb;  indexb=ptrb[indexb];
   }
   //stoper.stopTimer();
   //licznik = stoper.getElapsedTime();
   //printf("%f \n",licznik);
   //cout << licznik << endl;
}

void Render::threeopt( int nn, QVector<QVector<float> > *wb, QVector<int> *routeb)
{
   swaprecord bestswap,swap;
   int ib,indexb,jb,kb;
   QVector<int> ptrb(nn,0);
   //CStopWatch stoper;
   //stoper.startTimer();
   licznikiteracji = 0;
   licznikiteracjipoprawy = 0;
   for( ib=0; ib < nn-1; ib ++) ptrb[(*routeb)[ib]]=(*routeb)[ib+1];
   ptrb[(*routeb)[nn-1]]=(*routeb)[0];
   do {
      bestswap.gain=0;
      swap.x1=1;
      for( ib=0; ib < nn; ib ++)
      {
         swap.x2=ptrb[swap.x1];
         swap.y1=swap.x2;

         for( jb=2; jb < nn-3; jb ++)
         {
           swap.y2=ptrb[swap.y1];
           swap.z1=ptrb[swap.y2];

            for( kb=jb+2; kb < nn-1; kb ++)
            {
                licznikiteracji++;
                swap.z2=ptrb[swap.z1];
                swapcheck(swap, wb);
                if (swap.gain > bestswap.gain)
                {
                    bestswap=swap;
                    licznikiteracjipoprawy++;
                }
            }

           swap.y1=swap.y2;
         }
         swap.x1=swap.x2;

      }
      if (bestswap.gain > 0)
      {
            if (bestswap.choice == asymmetric)  {
               reverse(bestswap.z2,bestswap.x1, ptrb);
               ptrb[bestswap.y1]=bestswap.x1;  ptrb[bestswap.z2]=bestswap.y2;
            }
            else {
               ptrb[bestswap.x1]=bestswap.y2;  ptrb[bestswap.y1]=bestswap.z2;
            }
            ptrb[bestswap.z1]=bestswap.x2;
      }
   } while (!(bestswap.gain == 0));
   indexb=1;
   for( ib=0; ib < nn; ib ++) {
      (*routeb)[ib]=indexb;  indexb=ptrb[indexb];
   }
   //stoper.stopTimer();
   //licznik = stoper.getElapsedTime();
   //printf("%f \n",licznik);
   //cout << licznik << endl;
}

void Render::twooptfast( int iloscmiast, QVector<QVector<float> > *macierzwag,QVector<int> *trasapoczatkowa)
{
    int ahead=0,i=0,i1=0,i2=0,index=0,j=0,j1=0,j2=0,last=0,limit=0,next=0,s1=0,s2=0,t1=0,t2=0;
    float max=0,max1=0;
    QVector<int> ptr(iloscmiast,0);
    //CStopWatch stoper;
    //stoper.startTimer();
    licznikiteracji = 0;
    licznikiteracjipoprawy = 0;
    for( i=0; i < iloscmiast-1; i ++) ptr[(*trasapoczatkowa)[i]]=(*trasapoczatkowa)[i+1];
    ptr[(*trasapoczatkowa)[iloscmiast-1]]=(*trasapoczatkowa)[0];
    do {
       max=0.0;
       i1=0;
       for( i=0; i < iloscmiast-2; i ++) {
         if (i == 0)  limit=iloscmiast-1;
         else limit=iloscmiast;
         i2=ptr[i1];
         j1=ptr[i2];
         if(
              ( macierzwtemp[i1][i2] <= sasiedzinumber
                && macierzwtemp[i2][j1] <= sasiedzinumber
              )
           )
         {
          for( j=i+2; j < limit; j ++)
          {
              j2=ptr[j1];
              licznikiteracji++;
                max1=((*macierzwag)[i1][i2]+(*macierzwag)[j1][j2])-((*macierzwag)[i1][j1]+(*macierzwag)[i2][j2]);
                if (max1 > max)
                {
                   licznikiteracjipoprawy++;
                   s1=i1;  s2=i2;
                   t1=j1;  t2=j2;
                   max=max1;
                }
                j1=j2;
          }
         }
         i1=i2;
       }
       if (max > 0)  {
           ptr[s1]=t1;
          next=s2;  last=t2;
          do {
             ahead=ptr[next];  ptr[next]=last;
             last=next;  next=ahead;
          }while (!(next == t2));
       }
    }while (!(max == 0));

    index=0;
    for( i=0; i < iloscmiast; i ++) {
       (*trasapoczatkowa)[i]=index;  index=ptr[index];
    }
    //stoper.stopTimer();
    //licznik = stoper.getElapsedTime();
    //printf("%f \n",licznik);
    //cout << licznik << endl;
}

void Render::twoopt( int nc, QVector<QVector<float> > *wc,QVector<int> *routec)
{
    int ahead=0,i=0,i1=0,i2=0,index=0,j=0,j1=0,j2=0,last=0,limit=0,next=0,s1=0,s2=0,t1=0,t2=0;
    float max=0,max1=0;
    QVector<int> ptr(nc,0);
    //CStopWatch stoper;
    //stoper.startTimer();
    licznikiteracji = 0;
    licznikiteracjipoprawy = 0;
    for( i=0; i < nc-1; i ++) ptr[(*routec)[i]]=(*routec)[i+1];
    ptr[(*routec)[nc-1]]=(*routec)[0];
    do
    {
       max=0.0;
       i1=0;
       for( i=0; i < nc-2; i ++)
       {
                if (i == 0)
                    limit=nc-1;
                else
                    limit=nc;

                i2=ptr[i1];
                j1=ptr[i2];

                for( j=i+2; j < limit; j ++)
                {
                   j2=ptr[j1];
                   {
                      licznikiteracji++;
                      max1=(*wc)[i1][i2]+(*wc)[j1][j2]-((*wc)[i1][j1]+(*wc)[i2][j2]);
                      if (max1 > max)
                      {
                         licznikiteracjipoprawy++;
                         s1=i1;  s2=i2;
                         t1=j1;  t2=j2;
                         max=max1;
                      }
                   }
                   j1=j2;
                }

                 i1=i2;
       }
       if (max > 0)  {
           ptr[s1]=t1;
          next=s2;  last=t2;
          do
          {
             ahead=ptr[next];  ptr[next]=last;
             last=next;  next=ahead;
          }while (!(next == t2));
       }
    }while (!(max == 0));

    index=0;
    for( i=0; i < nc; i ++) {
       (*routec)[i]=index;  index=ptr[index];
    }
    //stoper.stopTimer();
    //licznik = stoper.getElapsedTime();
    //printf("%f \n",licznik);
    //cout << licznik << endl;
}

void Render::macierzwag()
{
    linesize=dasline.size();
    //QLineF linef;
    QPointF start,end;
    float x,y,x2,y2,waga;
    dotslist.clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
            }
            else dotslist << dots;
        }
    }
    listsize = dotslist.size();
    macierzw = new QVector<QVector<float> >(listsize,QVector<float>(listsize,0));
    {
     for(int f=0; f < listsize; f++)
     {
       for(int g=0; g < listsize; g++)
       {
        start = dotslist.at(f)->pos();
        end = dotslist.at(g)->pos();
        x = start.x();
        y = start.y();
        x2 = end.x();
        y2 = end.y();
        waga = sqrt( ((x-x2)*(x-x2)) + ((y-y2)*(y-y2)) );
        (*macierzw)[f][g] = waga;
       }
     }
    }


        //macierzwtemp = new QVector<QVector<int> >(listsize,QVector<int>(listsize,0));

        //int macierzsasiadow[listsize][listsize];
        /*
        for(int bla=0; bla < 50; bla++)
        {
            for(int bla2=0; bla2 < 50; bla2++)
            {
                macierzwtemp[bla][bla2] = false;
                //printf("%i ",tempbla);
                //qDebug() << tempbla << " ";
            }
            //printf("\n");
            //qDebug() <<  endl;
        }
        */
        /*
        for(int g=0; g < linesize; g++)
        {
            for(int h=0; h < listsize; h++)
            {
                if(start == dotslist.at(h)->pos() || end == dotslist.at(h)->pos() )
                {
                    if( start == dotslist.at(h)->pos() )
                    {                        
                        for(int j=0; j < listsize;j++)
                        {
                            if(end == dotslist.at(j)->pos())
                            {
                                macierzwtemp[h][j] = true;
                                macierzwtemp[j][h] = true;
                                j = listsize;
                                h = listsize;
                                qDebug() << "narf 1";
                            }
                        }
                    }
                    else
                    {
                        for(int j=0; j < listsize;j++)
                        {
                            if(start == dotslist.at(j)->pos())
                            {
                                macierzwtemp[j][h] = true;
                                macierzwtemp[h][j] = true;
                                j = listsize;
                                h = listsize;
                                qDebug() << "narf 2";
                            }
                        }
                    }
                }
            }
        }
        */

        /*
        for(int bla=0; bla < listsize; bla++)
        {
            for(int bla2=0; bla2 < listsize; bla2++)
            {
                int tempbla = macierzsasiadow[bla][bla2];
                //printf("%i ",tempbla);
                qDebug() << tempbla << " ";
            }
            //printf("\n");
            qDebug() <<  endl;
        }
        */

}

void Render::fitsp( int iloscmiast,int punktstartowy,float najwiekszawartoscpolaczenia,
                    QVector<QVector<float> > * macierzwag,QVector<int> *trasa,double *tweight)
{
   float inscost=0.0,maxdist=0.0,newcost=0.0;
   int index=0,nextindex=0,farthest=0,i=0,j=0,end1=0,end2=0;
   QVector<int> cycle (iloscmiast,0);
   QVector<float> *dist = new QVector<float>(iloscmiast,0);
   //macierzwag->clear();
   trasa->clear();
   trasa->resize(iloscmiast);

   for( i=0; i < iloscmiast; i++) cycle[i]=0;
   cycle[punktstartowy]=punktstartowy;
   for( i=0; i < iloscmiast; i++) (*dist)[i]=(*macierzwag)[punktstartowy][i];
   *tweight=0;
   for( i=0; i < iloscmiast; i++) {
      maxdist=-najwiekszawartoscpolaczenia;
      for( j=0; j < iloscmiast; j++)
      {
         if (cycle[j] == 0)
            if ((*dist)[j] > maxdist)  {
               maxdist=(*dist)[j];  farthest=j;
            }
      }
      inscost=najwiekszawartoscpolaczenia;  index=punktstartowy;
      for( j=0; j < i; j++)  {
         nextindex=cycle[index];
         newcost=(*macierzwag)[index][farthest]+(*macierzwag)[farthest][nextindex]-
                  (*macierzwag)[index][nextindex];
         if (newcost < inscost)  {
            inscost=newcost;
            end1=index;  end2=nextindex;
         }
         index=nextindex;
      }
      cycle[farthest]=end2;
      cycle[end1]=farthest;
      *tweight=*tweight+inscost;
      for( j=0; j < iloscmiast; j++)
      {
         if (cycle[j] == 0)
            if ((*macierzwag)[farthest][j] < (*dist)[j])
             {
               (*dist)[j]=(*macierzwag)[farthest][j];
             }
      }
   }
   index=punktstartowy;
   for( i=0; i < iloscmiast; i++)
   {
      (*trasa)[i]=index;
      index=cycle.at(index);
   }
}

void Render::macierzwag2(QList<dot*> tempdot)
{
    Q_UNUSED(tempdot);
    /*
    macierzw.clear();
    dotslist.clear();
    foreach(QGraphicsItem *item, scene->items())
    {
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->isVisible())
                dotslist << dots;
        }
    }
    int vsize = dotslist.size();

    bool done=1;
    int i=0;
    int b=0;
    double x,y,x1,y1;
    for(int kk=0; kk <  vsize; kk++)
    {
        done=1;
        while( done )
        {
           foreach(QPointF pointloop, Dt.tablicapunktow )
           {

            if( dotslist.at(kk)->pos() == pointloop )
            {
              for(int ww=0; ww < vsize; ww++)
              {
                if(ww=kk) macierzw[kk][ww]= -1;

                if(i==0)
                {
                    b=i; b++;
                    x=dotslist.at(kk)->pos().x();
                    y=dotslist.at(kk)->pos().y();
                    x1=Dt.tablicapunktow->at(i).x();
                    y1=Dt.tablicapunktow->at(i).y();
                    macierzw[kk][ww]=sqrt( ((x-x1)*(x-x1)) + ((y-y1)*(y-y1)) );
                }
                done=0;
              }
              i++;
            }
           }
           done=0;

        }
    }
    */
}

void Render::drawBackground ( QPainter *painter, const QRectF &rect )
{
	Q_UNUSED ( rect );
	painter->setPen ( Qt::blue );
	update();
}

void Render::punkty_slot ( QString text )
{
	_text=text;
	liczbapunktow=text.toInt();
}
