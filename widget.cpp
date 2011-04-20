/***************************************************************************
 *   Copyright (C) 2011 by Daniel 'gordonc64' Gorazdowski                  *
 *   gordonc64@gmail.com                                                   *
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
#include "widget.h"
#include <QMenuBar>
#include <QGroupBox>
#include <QGraphicsItem>
#include <QDockWidget>

MainWidget::MainWidget ( QWidget *parent ) : QMainWindow(parent)
{

	//QWidget widget;
	//widget->setGeometry ( 100, 100, 500, 355 );
        setGeometry(0,0,1024,850);
        setMaximumSize(1024,850);
        setMinimumSize(1024,850);
        QDockWidget *dockwidget = new QDockWidget;
        //setSizePolicy();
        //setCentralWidget ( &widget );
	liczbapunktow=0;
        sasiedzinumber=0;
        indexmainwidget=0;
        p_render = new Render ( 0 );
        this->setCentralWidget(p_render);
        //this->setWindowFlags(Qt::WindowStaysOnTopHint);
        QWidget *docktempwidget = new QWidget;
	//punkty kolo,losowe;
	//elipsa.kolo(30);
	//QVector<QPointF> *tablica = kolo.createtable(100);
	//p_render->polygonfunction(tablica);
	vlosowe = new QVector<QPointF>;
	vkolo = new QVector<QPointF>;
        vlinia = new QVector<QPointF>;
        velipsa = new QVector<QPointF>;
        vreadloop = new QVector<QPointF>;
	//p_render->polygonfunction2(tablica2);
	
        zaznacz = new QPushButton ( "Zaznacz" );
        //zaznacz->setFont ( QFont ( "Sans Serif", 9, QFont::Bold ) );
        zaznacz->setMaximumHeight ( 25 );
        QPushButton *rysuj = new QPushButton ("Rysuj");
        //rysuj->setFont ( QFont ( "Sans Serif", 9, QFont::Bold ) );
        rysuj->setMaximumHeight(25);
        QPushButton *twoopt = new QPushButton ("Oblicz");
        QPushButton *twooptfast = new QPushButton ("Oblicz");
        QPushButton *twooptfast2 = new QPushButton ("2");
        QPushButton *twooptfast3 = new QPushButton ("3");
        QPushButton *threeopt = new QPushButton ("Oblicz");
        QPushButton *threeoptfast = new QPushButton ("Oblicz");
        QPushButton *threeoptfast2 = new QPushButton ("2");
        QPushButton *threeoptfast3 = new QPushButton ("3");

        QPushButton *usun = new QPushButton ("Usun");
        QPushButton *delaunay = new QPushButton ("Delaunay");

        //usun->setFont ( QFont ( "Sans Serif", 9, QFont::Bold ) );
        usun->setMaximumHeight(25);
	//QVector<QPointF> m_points;
	QComboBox *RodzajObiektow = new QComboBox;
        RodzajObiektow->addItem ( "Losowe - caly obszar" );
        RodzajObiektow->addItem ( "Losowe" );
	RodzajObiektow->addItem ( "Okrag" );
        RodzajObiektow->addItem ( "Elipsa" );
	RodzajObiektow->addItem ( "Linia" );
        RodzajObiektow->addItem ( "Linia - rowna odleglosc" );
        RodzajObiektow->setMaximumWidth(120);

	liczba = new QLabel ( "Liczba punktow" );
        //liczba->setFrameStyle ( QFrame::Box | QFrame::Raised );

	liczba->setObjectName ( QString::fromUtf8 ( "label" ) );
	//liczba->setGeometry(QRect(80, 80, 80, 80));

	QLineEdit *podajliczbe = new QLineEdit;
	//QString wlad = "00000000000";
	//podajliczbe->setInputMask(wlad);

        //podajliczbe->setMaximumWidth(100);

        QLineEdit *podajsasiedztwo = new QLineEdit;


	QGridLayout *gridLayout = new QGridLayout;
        gridLayout->setColumnStretch ( 1, 10 );
        QBoxLayout *rodzajobiektow = new QBoxLayout ( QBoxLayout::LeftToRight );

        //gridLayout->addWidget ( usun, 0, 4 );
        //gridLayout->addWidget ( rysuj, 0, 3 );
        QToolBar *dockw = new QToolBar;
        QMenu *fileMenu = new QMenu;

        newAct = new QAction(QIcon(":/images/new.png"), tr("&Nowy"), this);
        openAct = new QAction(QIcon(":/images/open.png"), tr("&Otworz"), this);
        saveAct = new QAction(QIcon(":/images/save.png"), tr("&Zapisz"), this);
        openMacierzAct = new QAction(QIcon(":/images/open.png"), tr("&Otworz Macierz"), this);
        saveMacierzAct = new QAction(QIcon(":/images/save.png"), tr("&Zapisz Macierz"), this);
        exitAct = new QAction(tr("&Wyjscie"),this);
        obliczenia = new QAction(tr("&Wielokrotne obliczenia"),this);

        fileMenu = menuBar()->addMenu(tr("&Plik"));
        fileMenu->addAction(newAct);
        fileMenu->addAction(openAct);
        fileMenu->addAction(saveAct);
        fileMenu->addAction(openMacierzAct);
        fileMenu->addAction(saveMacierzAct);
        fileMenu->addAction(exitAct);

        //fileMenu = menuBar()->addMenu("Testowanie algorytmow");
        //fileMenu->addAction(obliczenia);

        //dockw->addWidget(podajliczbe);
        //dockw->addWidget(liczba);
        //dockw->addWidget(RodzajObiektow);
        //dockw->addWidget(rysuj);
        //dockw->addWidget(usun);
        //dockw->addWidget(zaznacz);
        //dockw->addWidget(delaunay);
        //dockw->addWidget(twoopt);
        //dockw->addWidget(twoopt2);
        //dockw->addWidget(three-opt);
        //dockw->addWidget(koniec);

        //dockw->isLeftToRight();
        //dockw->isFloating();
        //dockw->setMaximumSize ( 800, 30 );
        //this->addToolBar( Qt::RightToolBarArea,dockw );
        /*
        QBoxLayout *boxLayout1 = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1b = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1c = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1d = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1e = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1f = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout1g = new QBoxLayout ( QBoxLayout::LeftToRight );
        */
        QLabel *templabel1 = new QLabel(" ");
        QLabel *templabel1b = new QLabel("");
        QLabel *templabel1c = new QLabel("Rozwiazanie TSP wg. 2-Opt, 3-Opt");
        QLabel *templabel1d = new QLabel(" ");
        QLabel *templabel1d1 = new QLabel("Rozwiazanie TSP wg. 2-Opt, 3-Opt");
        QLabel *templabel1d2 = new QLabel("wykorzystujac macierz sasiedztwa");
        QLabel *templabel1e = new QLabel(" ");
        QLabel *templabel1f = new QLabel(" ");
        QLabel *templabel1k = new QLabel(" ");
        QLabel *templabel1l = new QLabel(" ");
        QLabel *templabel1o = new QLabel(" ");
        QLabel *templabel1q = new QLabel(" ");
        QLabel *templabel1r = new QLabel(" ");


        templabel1->setMaximumHeight(4);
        templabel1->setFrameStyle ( QFrame::Box | QFrame::Raised );
        templabel1->setFrameShadow(QFrame::Raised);

        templabel1b->setMaximumHeight(4);
        templabel1b->setFrameStyle ( QFrame::Box | QFrame::Raised );
        templabel1b->setFrameShadow(QFrame::Raised);

        templabel1k->setMaximumHeight(4);
        templabel1k->setFrameStyle ( QFrame::Box | QFrame::Raised );
        templabel1k->setFrameShadow(QFrame::Raised);

        templabel1l->setMaximumHeight(4);
        templabel1l->setFrameStyle ( QFrame::Box | QFrame::Raised );
        templabel1l->setFrameShadow(QFrame::Raised);

        templabel1o->setMaximumHeight(4);
        templabel1o->setFrameStyle ( QFrame::Box | QFrame::Raised );
        templabel1o->setFrameShadow(QFrame::Raised);

        QBoxLayout *boxLayout2 = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2b = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2c = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2d = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2d1 = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2d2 = new QBoxLayout ( QBoxLayout::LeftToRight );

        QBoxLayout *boxLayout2e = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2f = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2g = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2r = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2q = new QBoxLayout ( QBoxLayout::LeftToRight );


        QBoxLayout *threeoptbutton = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *twooptbutton = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *threeoptbuttonfast = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *twooptbuttonfast = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *rysujobiekty= new QBoxLayout  ( QBoxLayout::LeftToRight );
        QBoxLayout *rysowanie = new QBoxLayout   ( QBoxLayout::LeftToRight );
        QBoxLayout *iloscpunktow = new QBoxLayout   ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2k = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2l = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *boxLayout2o = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *usuwanie = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *zaznaczanie = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *delaunaybox = new QBoxLayout ( QBoxLayout::LeftToRight );

        QLabel *delaunaylabel = new QLabel("Delaunay");
        QLabel *rysowanielabel = new QLabel("Rysuj punkty");
        QLabel *twooptlabel = new QLabel("2-Opt");
        QLabel *threeoptlabel = new QLabel("3-Opt");
        QLabel *twooptlabelfast = new QLabel("2-Opt fast");
        QLabel *threeoptlabelfast = new QLabel("3-Opt fast");
        QLabel *templabel2 = new QLabel("Lista obiektow");
        QLabel *usunlabel = new QLabel("Usun punkty");
        QLabel *zaznaczlabel = new QLabel ("Zaznacz punkty");
        QLabel *opiswprowadzpkt = new QLabel("Wpisz ilosc punktow");
        QLabel *opiswybierzrodzaj = new QLabel("Wybierz rodzaj obiektu");

        QLabel *badanialabel = new QLabel ("Wielokrotne wykonanie obliczen:");
        QLabel *badaniailoscpowtorzen = new QLabel("Ilosc powtorzen:");
        QLabel *badaniailoscmiast = new QLabel("Ilosc miast losowych:");
        QLabel *badaniaalgorytm = new QLabel("Testowany algorytm");

        QLabel *obliczeniagranica = new QLabel(" ");
        obliczeniagranica->setMaximumHeight(4);
        obliczeniagranica->setFrameStyle ( QFrame::Box | QFrame::Raised );
        obliczeniagranica->setFrameShadow(QFrame::Raised);

        QLabel *labelpodajmaxsasiedztwo = new QLabel("Stopien sasiedztwa:");
        QLabel *labelpowtorzenia = new QLabel(""); //("Wykonanych obliczen:");
        QLabel *labelwagatrasy = new QLabel ("Waga trasy:");
        QLabel *labelczas = new QLabel ("Ilosc krokow:");
        QLabel *labelczasbetter = new QLabel ("Ilosc krokow polepszajacych:");
        QLabel *labelsasiedzi = new QLabel ("Maksymalny stopien sasiedztwa:");
        QLabel *labelczasms = new QLabel("Czas obliczen w [s]:");
        QLabel *labelczasmsdane = new QLabel ("");

        QLabel *labelpowtorzeniadane = new QLabel("");
        QLabel *labelwagatrasydane = new QLabel("");
        QLabel *labelczasdane = new QLabel ("");
        QLabel *labelczasbetterdane = new QLabel ("");
        QLabel *labelsasiedztwo = new QLabel ("");

        QBoxLayout *labelsasiedzibox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelsasiedzibox->addWidget(labelsasiedzi);
        labelsasiedzibox->addWidget(labelsasiedztwo);

        QBoxLayout *labelpodajsasiedzibox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelpodajsasiedzibox->addWidget(labelpodajmaxsasiedztwo);
        labelpodajsasiedzibox->addWidget(podajsasiedztwo);

        QBoxLayout *obliczeniagranicabox = new QBoxLayout ( QBoxLayout::LeftToRight );
        obliczeniagranicabox->addWidget(obliczeniagranica);

        QBoxLayout *labelpowtorzeniabox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelpowtorzeniabox->addWidget(labelpowtorzenia);
        labelpowtorzeniabox->addWidget(labelpowtorzeniadane);

        QBoxLayout *labelwagatrasybox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelwagatrasybox->addWidget(labelwagatrasy);
        labelwagatrasybox->addWidget(labelwagatrasydane);

        QBoxLayout *labelczasbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelczasbox->addWidget(labelczas);
        labelczasbox->addWidget(labelczasdane);

        QBoxLayout *labelczasbetterbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelczasbetterbox->addWidget(labelczasbetter);
        labelczasbetterbox->addWidget(labelczasbetterdane);

        QBoxLayout *labelczasmsbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        labelczasmsbox->addWidget(labelczasms);
        labelczasmsbox->addWidget(labelczasmsdane);

        QComboBox *badaniaobiekty = new QComboBox;
        badaniaobiekty->addItem ( "2-Opt" );
        badaniaobiekty->addItem ( "3-Opt" );
        badaniaobiekty->addItem ( "2-Opt + macierz sasiedztwa" );
        badaniaobiekty->addItem ( "3-Opt + macierz sasiedztwa" );

        QPushButton *wykonajbadania = new QPushButton("Oblicz");
        QLabel *wykonajbadanialabel = new QLabel("Wykonaj serie obliczen");
        QBoxLayout *wykonajbadaniabox = new QBoxLayout ( QBoxLayout::LeftToRight );
        wykonajbadaniabox->addWidget(wykonajbadanialabel);
        wykonajbadaniabox->addWidget(wykonajbadania);

        QLineEdit *badaniailoscpowtorzenedit = new QLineEdit;
        QLineEdit *badaniailoscmiastedit = new QLineEdit;

        QBoxLayout *badanialabelbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *badaniailoscpowtorzenbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *badaniailoscmiastbox = new QBoxLayout ( QBoxLayout::LeftToRight );
        QBoxLayout *badaniaalgorytmbox = new QBoxLayout ( QBoxLayout::LeftToRight );

        p_render->labelilosciteracji = labelczasdane;
        p_render->labelwagatrasy = labelwagatrasydane;
        p_render->labelczasms = labelczasmsdane;
        p_render->labelilosciteracjibetter = labelczasbetterdane;
        p_render->labelsasiedztwo = labelsasiedztwo;

        badanialabelbox->addWidget(badanialabel);
        badaniailoscpowtorzenbox->addWidget(badaniailoscpowtorzen);
        badaniailoscpowtorzenbox->addWidget(badaniailoscpowtorzenedit);
        badaniailoscmiastbox->addWidget(badaniailoscmiast);
        badaniailoscmiastbox->addWidget(badaniailoscmiastedit);
        badaniaalgorytmbox->addWidget(badaniaalgorytm);
        badaniaalgorytmbox->addWidget(badaniaobiekty);

        iloscpunktow->addWidget(opiswprowadzpkt);

        rysowanie->addWidget(rysowanielabel);
        rysowanie->addWidget(rysuj);

        delaunaybox->addWidget(delaunaylabel);
        delaunaybox->addWidget(delaunay);

        rodzajobiektow->addWidget ( templabel2 );
        rodzajobiektow->addWidget ( RodzajObiektow );

        rysujobiekty->addWidget(liczba);
        rysujobiekty->addWidget(podajliczbe);

        threeoptbutton->addWidget(threeoptlabel);
        threeoptbutton->addWidget(threeopt);

        threeoptbuttonfast->addWidget(threeoptlabelfast);
        threeoptbuttonfast->addWidget(threeoptfast);
        //threeoptbuttonfast->addWidget(threeoptlabelfast);
        //threeoptbuttonfast->addWidget(threeoptfast2);
        //threeoptbuttonfast->addWidget(threeoptlabelfast);
        //threeoptbuttonfast->addWidget(threeoptfast3);

        twooptbutton->addWidget(twooptlabel);
        twooptbutton->addWidget(twoopt);

        twooptbuttonfast->addWidget(twooptlabelfast);
        twooptbuttonfast->addWidget(twooptfast);
        //twooptbuttonfast->addWidget(twooptlabelfast);
        //twooptbuttonfast->addWidget(twooptfast2);
        //twooptbuttonfast->addWidget(twooptlabelfast);
        //twooptbuttonfast->addWidget(twooptfast3);

        usuwanie->addWidget(usunlabel);
        usuwanie->addWidget(usun);

        zaznaczanie->addWidget(zaznaczlabel);
        zaznaczanie->addWidget(zaznacz);

        boxLayout2r->addWidget(templabel1r);
        boxLayout2q->addWidget(templabel1q);
        boxLayout2k->addWidget(templabel1k);
        boxLayout2l->addWidget(templabel1l);
        boxLayout2o->addWidget(templabel1o);
        boxLayout2->addWidget(templabel1);
        boxLayout2b->addWidget(templabel1b);
        boxLayout2c->addWidget(templabel1c);
        boxLayout2d->addWidget(templabel1d);
        boxLayout2d1->addWidget(templabel1d1);
        boxLayout2d2->addWidget(templabel1d2);
        boxLayout2e->addWidget(templabel1e);
        boxLayout2f->addWidget(templabel1f);
        boxLayout2g->addWidget(opiswybierzrodzaj);
        //QSpacerItem *blankspace = new QSpacerItem;

        gridLayout->addLayout ( boxLayout2k, 1, 0 );
        gridLayout->addLayout ( iloscpunktow, 3, 0 );
        gridLayout->addLayout ( rysujobiekty, 5, 0 );
        gridLayout->addLayout ( boxLayout2r, 6, 0 );
        gridLayout->addLayout ( boxLayout2, 9, 0);
        gridLayout->addLayout ( rysowanie, 21, 0 );
        gridLayout->addLayout ( zaznaczanie, 22, 0 );
        gridLayout->addLayout ( usuwanie, 23, 0 );
        gridLayout->addLayout ( boxLayout2q, 14, 0 );
        gridLayout->addLayout ( boxLayout2b, 15, 0 );
        gridLayout->addLayout ( boxLayout2g, 10, 0 );
        gridLayout->addLayout ( rodzajobiektow, 11, 0 );
        gridLayout->addLayout ( boxLayout2f, 30, 0);
        gridLayout->addLayout ( delaunaybox, 35, 0 );
        gridLayout->addLayout ( boxLayout2l, 49, 0 );
        gridLayout->addLayout ( boxLayout2c, 50, 0);
        gridLayout->addLayout ( threeoptbutton, 60, 0 );
        gridLayout->addLayout ( twooptbutton, 70, 0);
        gridLayout->addLayout ( boxLayout2d, 80, 0);
        gridLayout->addLayout ( boxLayout2o, 81, 0 );
        gridLayout->addLayout ( boxLayout2d1, 82, 0);
        gridLayout->addLayout ( boxLayout2d2, 83, 0);
        gridLayout->addLayout ( labelsasiedzibox,88,0);
        gridLayout->addLayout ( labelpodajsasiedzibox,89,0);
        gridLayout->addLayout ( threeoptbuttonfast, 90, 0 );
        gridLayout->addLayout ( twooptbuttonfast, 100, 0);
        gridLayout->addLayout ( obliczeniagranicabox, 111, 0 );
        gridLayout->addLayout ( labelpowtorzeniabox, 112, 0 );
        gridLayout->addLayout ( labelwagatrasybox, 113, 0 );
        gridLayout->addLayout ( labelczasbox, 114, 0 );
        gridLayout->addLayout ( labelczasbetterbox, 115, 0 );
        gridLayout->addLayout ( labelczasmsbox, 116, 0 );
        gridLayout->addLayout ( boxLayout2e, 119, 0);
        gridLayout->addLayout ( badanialabelbox, 120, 0 );
        gridLayout->addLayout ( badaniailoscpowtorzenbox, 125, 0 );
        gridLayout->addLayout ( badaniailoscmiastbox, 130, 0 );
        gridLayout->addLayout ( badaniaalgorytmbox, 135, 0 );
        gridLayout->addLayout ( wykonajbadaniabox, 140, 0 );
        //gridLayout->addWidget ( p_render, 1, 0, 3, 3 );

        gridLayout->setRowStretch ( 5, 1 );
        gridLayout->setRowStretch ( 9, 3 );
        gridLayout->setRowStretch ( 10, 1 );
        gridLayout->setRowStretch ( 12, 1 );
        gridLayout->setRowStretch ( 13,  1 );
        gridLayout->setRowStretch ( 20, 1 );
        gridLayout->setRowStretch ( 30, 1 );
        gridLayout->setRowStretch ( 40, 1 );
        gridLayout->setRowStretch ( 15, 1 );
        gridLayout->setRowStretch ( 60, 1 );
        gridLayout->setRowStretch ( 70, 1 );
        gridLayout->setRowStretch ( 80, 1 );
        gridLayout->setRowStretch ( 90, 1 );
        gridLayout->setRowStretch ( 100, 1 );
        gridLayout->setRowStretch ( 119, 30 );
        gridLayout->setRowStretch ( 120, 1 );
        gridLayout->setRowStretch ( 125, 1 );
        gridLayout->setRowStretch ( 130, 1 );
        gridLayout->setRowStretch ( 135, 1 );
        gridLayout->setSpacing ( 3 );
        gridLayout->setColumnStretch ( 0, 0 );
        gridLayout->setColumnStretch ( 1, 0 );

        docktempwidget->setLayout(gridLayout);
        dockwidget->setWidget(docktempwidget);
        dockwidget->setMaximumWidth(250);
        dockwidget->setMinimumWidth(250);
        dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        addDockWidget(Qt::RightDockWidgetArea,dockwidget);

        //setLayout ( gridLayout );
	QString message = tr ( "A context menu is available by right-clicking" );
        statusbar = statusBar();
        p_render->mainwidgetbar = statusBar();
        //statusBar()->showMessage ( message );


        ekran = QApplication::desktop()->availableGeometry();
        QRectF ekranf(ekran);
        x=0;
        y=0;

        w=ekran.width();
        htemp = statusBar()->height()+menuBar()->height()+dockw->height();
        h=ekran.height();
        h=h-htemp-20;
        w=w-20;
        //p_render->setSceneRect( x, y, w, h);
        p_render->setSceneRect( x, y, 763, 790);
        connect ( openAct,SIGNAL (triggered()), this,SLOT(open()) );
        connect ( saveAct,SIGNAL (triggered()), this,SLOT(save()) );
        connect ( openMacierzAct,SIGNAL (triggered()), this,SLOT(openmacierz()) );
        connect ( saveMacierzAct,SIGNAL (triggered()), this,SLOT(savemacierz()) );

        connect ( newAct,SIGNAL (triggered()), this,SLOT(newFile()) );
        connect ( exitAct, SIGNAL ( triggered() ), qApp, SLOT(quit() ) );
        connect ( RodzajObiektow, SIGNAL ( activated ( int ) ), this, SLOT(wyborobiektu (int) ) );
        connect ( rysuj, SIGNAL(clicked()), this, SLOT(rysujslot())  );
        connect ( zaznacz, SIGNAL(clicked()), this, SLOT(zaznaczslot())  );
        connect ( usun, SIGNAL(clicked()), this, SLOT(usunslot())  );
        connect ( delaunay, SIGNAL(clicked()), p_render, SLOT(delaunayslot() ) );

        connect ( twoopt, SIGNAL(clicked()), p_render, SLOT(twooptslot() ) );
        connect ( twooptfast, SIGNAL(clicked()), p_render, SLOT(twooptslotfast() ) );

        connect ( threeopt, SIGNAL(clicked()), p_render, SLOT(threeoptslot() ) );
        connect ( threeoptfast, SIGNAL(clicked()), p_render, SLOT(threeoptslotfast() ) );

        connect ( badaniailoscpowtorzenedit, SIGNAL(textEdited(QString)), this, SLOT(iloscpowtorzenslot(QString) ) );
        connect ( badaniailoscmiastedit, SIGNAL(textEdited(QString)), this, SLOT(iloscmiastslot(QString) ) );
        connect ( badaniaobiekty, SIGNAL(activated(int)), this, SLOT(badaniaalgorytmslot(int) ) );
        connect ( wykonajbadania, SIGNAL(clicked()), this, SLOT(obliczslot() ) );
        connect ( podajliczbe, SIGNAL ( textEdited ( QString ) ), this, SLOT ( punkty_slot ( QString ) ) );
        connect ( podajsasiedztwo, SIGNAL ( textEdited ( QString ) ), this, SLOT (  sasiedzi_slot( QString ) ) );

	//connect ( rysuj, SIGNAL ( clicked() ), p_render, SLOT ( punkty() ) );
	//connect ( polacz, SIGNAL ( clicked() ), this, SLOT ( etykieta() ) );
	//connect ( this, SIGNAL (pole_slot(QVector<QPointF> ) ), polePunktow, SLOT ( rysuj(QVector<QPointF> ) ) );
	//connect ( polacz, SIGNAL (clicked() ), polePunktow, SLOT ( rysuj1(test.mainptstable) ) );
	//connect ( this, SIGNAL ( losuj() ), &test, SLOT ( punkty_slot() ) );
	//connect ( &test, SIGNAL ( punkty_signal(QVector<QPointF> ) ), this, SIGNAL ( pole_slot(QVector<QPointF>)) );
        //indexmainwidget = 0;
        //algorytm = 0;
}

bool MainWidget::obliczslot()
{
    if(iloscmiast && iloscpowtorzen)
    {
        switch(algorytm)
        {
            case 0:
            {
                this->newFile();
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
                if (fileName.isEmpty())
                    return 0;
                QFile file(fileName);
                if (!file.open(QFile::WriteOnly)) {
                    QString msg = tr("Failed to open %1\n%2")
                                    .arg(fileName)
                                    .arg(file.errorString());
                    QMessageBox::warning(this, tr("Error"), msg);
                    return 0;
                }
                QTextStream stream(&file);
                stream << "2-Opt " << iloscmiast << " " << iloscpowtorzen << endl;

                mouse1 = p_render->sceneRect().bottomLeft().toPoint();
                mouse2 = p_render->sceneRect().topRight().toPoint();

                losowe.x1 = mouse1.x();
                losowe.y1 = mouse1.y();
                losowe.x2 = mouse2.x();
                losowe.y2 = mouse2.y();

                for(int i=0; i < iloscpowtorzen; i++)
                {
                    this->newFile();
                    //for(int j=0; j < 10000; j++) int a=sqrt(100.0);
                    vlosowe->clear();
                    //vlosowe = losowe.createtable ( iloscmiast);
                    //p_render->polygonfunction2 ( vlosowe );
                    //p_render->delaunay(vlosowe);
                    //p_render->twooptslot2();
                    liczbapunktow = iloscmiast;
                    indexmainwidget = 0;
                    this->rysujslot();
                    srand((unsigned)time(NULL));
                    p_render->twooptslot();
                    stream << p_render->licznikiteracji << " "
                           << p_render->licznikiteracjipoprawy << " "
                           << p_render->badaniatimer << " "
                           << p_render->wagatrasy << " "
                           << p_render->wagatrasystart << " "
                           << p_render->wagatrasystart - p_render->wagatrasy << " "
                           << 100-(p_render->wagatrasystart - p_render->wagatrasy)*100/p_render->wagatrasystart
                           << endl;
                }
                file.close();
            }
            break;

            case 1:
            {
            this->newFile();
            QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save layout"));
            if (fileName1.isEmpty())
                return 0;
            QFile file1(fileName1);
            if (!file1.open(QFile::WriteOnly)) {
                QString msg = tr("Failed to open %1\n%2")
                                .arg(fileName1)
                                .arg(file1.errorString());
                QMessageBox::warning(this, tr("Error"), msg);
                return 0;
            }
            QTextStream stream1(&file1);
            stream1 << "3-Opt " << iloscmiast << " " << iloscpowtorzen << endl;

            mouse1 = p_render->sceneRect().bottomLeft().toPoint();
            mouse2 = p_render->sceneRect().topRight().toPoint();

            losowe.x1 = mouse1.x();
            losowe.y1 = mouse1.y();
            losowe.x2 = mouse2.x();
            losowe.y2 = mouse2.y();

            for(int i=0; i < iloscpowtorzen; i++)
            {
                this->newFile();
                //for(int j=0; j < 10000; j++) int a=sqrt(100.0);
                vlosowe->clear();
                //vlosowe = losowe.createtable ( iloscmiast);
                //p_render->polygonfunction2 ( vlosowe );
                //p_render->delaunay(vlosowe);
                //p_render->twooptslot2();
                liczbapunktow = iloscmiast;
                indexmainwidget = 0;
                this->rysujslot();
                srand((unsigned)time(NULL));
                p_render->threeoptslot();
                stream1 << p_render->licznikiteracji << " "
                       << p_render->licznikiteracjipoprawy << " "
                       << p_render->badaniatimer << " "
                       << p_render->wagatrasy << " "
                       << p_render->wagatrasystart << " "
                       << p_render->wagatrasystart - p_render->wagatrasy << " "
                       << 100-(p_render->wagatrasystart - p_render->wagatrasy)*100/p_render->wagatrasystart << endl;
            }
            file1.close();
            }
            break;

            case 2:
            {
            this->newFile();
            fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
            if (fileName.isEmpty())
                return 0;
            QFile file(fileName);
            if (!file.open(QFile::WriteOnly)) {
                QString msg = tr("Failed to open %1\n%2")
                                .arg(fileName)
                                .arg(file.errorString());
                QMessageBox::warning(this, tr("Error"), msg);
                return 0;
            }
            QTextStream stream(&file);
            stream << "2-Opt fast " << iloscmiast << " " << iloscpowtorzen << endl;

            mouse1 = p_render->sceneRect().bottomLeft().toPoint();
            mouse2 = p_render->sceneRect().topRight().toPoint();

            p_render->sasiedzinumber = 1;

            losowe.x1 = mouse1.x();
            losowe.y1 = mouse1.y();
            losowe.x2 = mouse2.x();
            losowe.y2 = mouse2.y();

            for(int i=0; i < iloscpowtorzen; i++)
            {
                this->newFile();
                //for(int j=0; j < 10000; j++) int a=sqrt(100.0);
                vlosowe->clear();
                //vlosowe = losowe.createtable ( iloscmiast);
                //p_render->polygonfunction2 ( vlosowe );
                //p_render->delaunay(vlosowe);
                //p_render->twooptslot2();
                liczbapunktow = iloscmiast;
                indexmainwidget = 0;
                this->rysujslot();
                srand((unsigned)time(NULL));
                //p_render->twooptslotfast();
                p_render->twooptslotfast();
                stream << p_render->licznikiteracji << " "
                       << p_render->licznikiteracjipoprawy << " "
                       << p_render->badaniatimer << " "
                       << p_render->wagatrasy << " "
                       << p_render->wagatrasystart << " "
                       << p_render->wagatrasystart - p_render->wagatrasy << " "
                       << 100-(p_render->wagatrasystart - p_render->wagatrasy)*100/p_render->wagatrasystart << endl;
            }
            file.close();
            }
            break;

            case 3:
            {
            this->newFile();
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
            if (fileName.isEmpty())
                return 0;
            QFile file(fileName);
            if (!file.open(QFile::WriteOnly)) {
                QString msg = tr("Failed to open %1\n%2")
                                .arg(fileName)
                                .arg(file.errorString());
                QMessageBox::warning(this, tr("Error"), msg);
                return 0;
            }
            QTextStream stream(&file);
            stream << "3-Opt fast " << iloscmiast << " " << iloscpowtorzen << endl;

            mouse1 = p_render->sceneRect().bottomLeft().toPoint();
            mouse2 = p_render->sceneRect().topRight().toPoint();

            losowe.x1 = mouse1.x();
            losowe.y1 = mouse1.y();
            losowe.x2 = mouse2.x();
            losowe.y2 = mouse2.y();
            p_render->sasiedzinumber = 1;
            for(int i=0; i < iloscpowtorzen; i++)
            {
                this->newFile();
                //for(int j=0; j < 10000; j++) int a=sqrt(100.0);
                vlosowe->clear();
                //vlosowe = losowe.createtable ( iloscmiast);
                //p_render->polygonfunction2 ( vlosowe );
                //p_render->delaunay(vlosowe);
                //p_render->twooptslot2();
                liczbapunktow = iloscmiast;
                indexmainwidget = 0;
                this->rysujslot();
                //srand((unsigned)time(NULL));
                p_render->threeoptslotfast();
                stream << p_render->licznikiteracji << " "
                       << p_render->licznikiteracjipoprawy << " "
                       << p_render->badaniatimer << " "
                       << p_render->wagatrasy << " "
                       << p_render->wagatrasystart << " "
                       << p_render->wagatrasystart - p_render->wagatrasy << " "
                       << 100-(p_render->wagatrasystart - p_render->wagatrasy)*100/p_render->wagatrasystart << endl;
            }
            file.close();
            }
            break;

        }


    }
    return 0;
}

void MainWidget::iloscmiastslot(QString text)
{
        iloscmiast = text.toInt();
}

void MainWidget::iloscpowtorzenslot(QString text)
{
        iloscpowtorzen = text.toInt();
}

void MainWidget::badaniaalgorytmslot(int wybor)
{
        algorytm = wybor;
}

/*
void MainWidget::etykieta()
{
	liczba->setText(p_render->_text);
}
*/
//void MainWidget::slot()
//{
//emit losuj();
//}

void MainWidget::dialog()
{
    QDialog Dialog(this);
    Dialog.setWindowTitle("Obliczenia");

    QGroupBox group(&Dialog);
    group.setMinimumSize(250,100);
    QLabel label1("label", &group);
        
}

bool MainWidget::open()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("Pliki (*.txt);;Wszystko (*)"));
    if (fileName.isEmpty()) return 0;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return 0;
    }
    //file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    bool readloopbool = 0;
    QString readloop;
    QStringList readlooplist;
    double xread=0,yread=0;
    QString templist;
    dot punkt;
    vreadloop->clear();
    while(!readloopbool)
    {
          readloop.clear();
          readlooplist.clear();
          readloop = stream.readLine();
          bool ab = readloop.isNull();
          if(ab)
          {
              file.close();
              p_render->polygonfunction2(vreadloop);
              return 1;
          }
          readlooplist = readloop.split(" ");
          templist = readlooplist.at(0);
          xread = templist.toDouble();
          templist = readlooplist.at(1);
          yread = templist.toDouble();
          *vreadloop << QPointF (xread,yread);
          readloopbool = readloop.isEmpty();
    }
    return 1;
}

bool MainWidget::openmacierz()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("Pliki (*.txt);;Wszystko (*)"));
    if (fileName.isEmpty()) return 0;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return 0;
    }
    //file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    bool readloopbool = 0;
    QString readloop;
    QStringList readlooplist;
    int read=0;
    QString templist;
    vreadloop->clear();
    while(!readloopbool)
    {
          readloop.clear();
          readlooplist.clear();
          readloop = stream.readLine();
          bool ab = readloop.isNull();
          if(ab)
          {
              file.close();
              p_render->polygonfunction2(vreadloop);
              return 1;
          }
          readlooplist = readloop.split(" ");
          for( int b=0; b < p_render->looplimit; b++)
          {
              for( int a=0; a < p_render->looplimit; a++)
              {
                templist = readlooplist.at(a);
                read = templist.toInt();
                p_render->macierzwtemp[b][a]=read;
              }
          }
          readloopbool = readloop.isEmpty();
    }
    return 1;
}

void MainWidget::newFile()
{

    //QList<dot *> dotslist;

    foreach(QGraphicsItem *item, p_render->scene->items())
    {
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            dots->setSelected(1);
            if(dots->isSelected())
                p_render->scene->removeItem( dots );
        }
        if( QGraphicsLineItem *lines = qgraphicsitem_cast<QGraphicsLineItem *>(item) )
        {
             p_render->scene->removeItem( lines);
            //lines->hide();

        }
    }

    //QList<QGraphicsLineItem *> dotslist;
    //foreach(QGraphicsItem *item, p_render->scene->items())
    {

    }
    /*
    foreach(QGraphicsItem *item, p_render->scene->items())
    {
                p_render->scene->removeItem( item );
    }
    */
}

bool MainWidget::save()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save File..."),
                                       QString(), tr("Pliki (*.txt);;Wszystko (*)"));
    if (fileName.isEmpty())
        return 0;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return 0;
    }
    QTextStream stream(&file);
    QVector<dot *> dotslist;
    dotslist.clear();
    foreach(QGraphicsItem *item, p_render->scene->items())
    {
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else dotslist << dots;
        }
    }

    for(int i=0; i < dotslist.size(); i++)
    {
        xdot = dotslist.at(i)->x();
        ydot = dotslist.at(i)->y();
        stream << xdot << " " << ydot << endl;
    }

    file.close();
    return 1;
}

bool MainWidget::savemacierz()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save File..."),
                                       QString(), tr("Pliki (*.txt);;Wszystko (*)"));
    if (fileName.isEmpty())
        return 0;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return 0;
    }
    QTextStream stream(&file);
    QVector<dot *> dotslist;
    dotslist.clear();
    int stopien=0;
    foreach(QGraphicsItem *item, p_render->scene->items())
    {
        if( dot *dots = qgraphicsitem_cast<dot *>(item) )
        {
            if(dots->pos().isNull())
            {
                //dots->setVisible(0);
            }
            else dotslist << dots;
        }
    }

    for( int bb=0; bb < p_render->looplimit; bb++)
    {
        for( int aa=0; aa < p_render->looplimit; aa++)
        {
            stopien = p_render->macierzwtemp[bb][aa];
            stream << stopien << " ";
        }
        stream << endl;
    }

    file.close();
    return 1;
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
        //p_render->setSceneRect( 0,0,this->width()-statusbar->width(), this->height()-statusbar->height() );
        //p_render->resize( this->size() );
        //QMainWindow::resizeEvent(event);
}

void MainWidget::zaznaczslot()
{
        if(p_render->zaznacz)
        {
            p_render->zaznacz = 0;
            zaznacz->setFlat(0);
        }
        else
        {
            p_render->zaznacz = 1;
            zaznacz->setFlat(1);
        }
}

void MainWidget::usunslot()
{
        QList<dot *> dotslist;
        foreach(QGraphicsItem *item, p_render->scene->items())
        {
            if( dot *dots = qgraphicsitem_cast<dot *>(item) )
                if(dots->isSelected())
                    p_render->scene->removeItem( dots );
        }
}

void MainWidget::sasiedzi_slot ( QString text )
{
        _text=text;
        sasiedzinumber=text.toInt();
        //sasiedzinumber++;
        p_render->sasiedzinumber = sasiedzinumber;
}

void MainWidget::punkty_slot ( QString text )
{
	_text=text;
	liczbapunktow=text.toInt();
	//std::cout << "Copy of table: " << &polygon << "\n";
	//emit punkty_signal(this->m_points);
}

void MainWidget::rysujslot ()
{
    if ( liczbapunktow > 0 )
    {
            switch ( indexmainwidget )
            {
                            //deafault:
                    case 0:
                            mouse1 = p_render->sceneRect().bottomLeft().toPoint();
                            mouse2 = p_render->sceneRect().topRight().toPoint();

                            losowe.x1 = mouse1.x();
                            losowe.y1 = mouse1.y();
                            losowe.x2 = mouse2.x();
                            losowe.y2 = mouse2.y();

                            vlosowe = losowe.createtable ( liczbapunktow );
                            p_render->polygonfunction2 ( vlosowe );
                            //p_render->delaunay(vlosowe);
                            break;

                    case 1:
                            mouse1 = p_render->mouseDownPos;
                            mouse2 = p_render->mouseLastPosSceneRelease;

                            losowe.x1 = mouse1.x();
                            losowe.y1 = mouse1.y();
                            losowe.x2 = mouse2.x();
                            losowe.y2 = mouse2.y();

                            vlosowe = losowe.createtable ( liczbapunktow );
                            p_render->polygonfunction2 ( vlosowe );
                            //p_render->delaunay(vlosowe);
                            break;
/*
                    case 1:
                            //losowe.m = p_render->qgellipse->transform().toAffine();
                            punkttemp = p_render->mouseDownPos;
                            xnew = punkttemp.x()+(p_render->testelipsa.height()/2);
                            ynew = punkttemp.y()+(p_render->testelipsa.height()/2);
                            height = p_render->testelipsa.height()/2;

                            vkolo = losowe.kolo ( xnew, ynew, abs(height), liczbapunktow );
                            p_render->polygonfunction2 ( vkolo );
                            break;
*/
                    case 2:
                            punkttemp = p_render->test1 + ((p_render->test2 - p_render->test1)/2);
                            xnew = punkttemp.x();
                            ynew = punkttemp.y();
                            height = p_render->rubberRect.height();
                            width = p_render->rubberRect.width();
                            velipsa = losowe.elipsa( xnew, ynew, width/2, width/2, 360, liczbapunktow );
                            p_render->polygonfunction2(velipsa);
                            //p_render->delaunay(velipsa);
                            break;

                    case 3:
                            punkttemp = p_render->mouseLastPosSceneRelease+((p_render->mouseDownPos - p_render->mouseLastPosSceneRelease)/2);
                            xnew = punkttemp.x();
                            ynew = punkttemp.y();
                            height = p_render->rubberRect.height();
                            width = p_render->rubberRect.width();
                            velipsa = losowe.elipsa(xnew,ynew,width/2,height/2,360,liczbapunktow);
                            p_render->polygonfunction2(velipsa);
                            //p_render->delaunay(velipsa);
                            break;

                    case 4:
                            mouse1 = p_render->liniaPos1;
                            mouse2 = p_render->liniaPos2;

                            losowe.x1 = mouse1.x();
                            losowe.y1 = mouse1.y();
                            losowe.x2 = mouse2.x();
                            losowe.y2 = mouse2.y();
                            vlinia = losowe.linia( liczbapunktow );
                            p_render->polygonfunction2( vlinia );
                            break;
                    case 5:
                            mouse1 = p_render->liniaPos1;
                            mouse2 = p_render->liniaPos2;

                            losowe.x1 = mouse1.x();
                            losowe.y1 = mouse1.y();
                            losowe.x2 = mouse2.x();
                            losowe.y2 = mouse2.y();
                            vlinia = losowe.liniarowna( liczbapunktow );
                            p_render->polygonfunction2( vlinia );
                            break;
            }
     }
}

void MainWidget::wyborobiektu ( int index )
{
        indexmainwidget = index;
        p_render->indexrender = index;
}
