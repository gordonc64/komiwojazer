//
//  Delaunay-tree
//
//  Copyright (c) 1993  by  INRIA Prisme Project 
//  2004 route des Lucioles,
//  BP 93 06902 Sophia Antipolis Cedex 
//  All rights reserved.
//  Olivier.Devillers@sophia.inria.fr
//  (33) 93 65 77 63
//  Fax (33) 93 65 76 43
//  http://www.inria.fr:/prisme/personnel/devillers/devillers.html
// 
//
//  GEOMETRIC OBJECT :
//
//    The Delaunay tree is a randomized geometric data structure computing the
//    Delaunay triangulation 
//    This structure holds insertion and queries. Deletions are not supported 
//    in this version.
//
//  Reference:
//                                                              
//    Jean-Daniel Boissonnat, Monique Teillaud,
//    On the randomized construction of the Delaunay tree,
//    Theoretetical Computer Science,
//    Volume 112, pages339-354, 1993.
//
//    Olivier Devillers, Stefan Meiser, Monique Teillaud,
//    Fully dynamic Delaunay triangulation in logarithmic expected 
//    time per operation,
//    Computational Geometry: Theory and Applications,
//    Volume 2, Number 2, pages 55-80, 1992.
//
//    Olivier Devillers,
//    Robust and efficient implementation of the Delaunay tree,
//   INRIA Research Report 1619, 1992.
//
#include "delaunay_tree_2d.h"

using namespace std;

class Delaunay_tree;
class DT_node;
class DT_list;
class point;

//****************************************************************************80

inline point operator + ( point a, point b ) 

//****************************************************************************80
//
//  Purpose:
//
//    "+" is an overloading of the + operator to points.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  return point ( a.x+b.x, a.y+b.y );
}
//****************************************************************************80

inline point operator - ( point a, point b ) 

//****************************************************************************80
//
//  Purpose:
//
//    "-" is an overloading of the - operator to points.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  return point ( a.x-b.x, a.y-b.y );
}
//****************************************************************************80

inline double operator * ( point a, point b ) 

//****************************************************************************80
//
//  Purpose:
//
//    "*" is an overloading of the * operator to points.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  return a.x*b.x + a.y*b.y;
}
//****************************************************************************80

inline double operator ^ ( point a, point b ) 

//****************************************************************************80
//
//  Purpose:
//
//    "^" is an overloading of the ^ operator to points.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  return a.x*b.y - a.y*b.x;
}
//****************************************************************************80

DT_list::~DT_list ( void )

//****************************************************************************80
//
//  Purpose:
//
//    DT_list::~DT_list is the annihilator for class DT_list.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  DT_list *p,*q;

  if (!next) return;

  for ( p = this, q = this->next; q ; ) 
  {
    p->next = NULL;
    delete p;
    p = q;
    q = q->next ;
  }
}
//****************************************************************************80

ind DT_node::conflict ( point *p )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::conflict is true if the point P is inside the closed circumdisk.
//
//  Author:
//
//    Olivier Devillers
//
//  Parameters:
//
//    Input, point *P, the point to be checked.
//
//    Output, ind DT_node::conflict, is true if the point is inside the closed circumdisk.
//
{
  switch ( flag.is_infinite() )
  {
  case 4:
    return 0;
  case 3:
    return 1;
  case 2:
    return ( ( *p - *vertices[0]  ) * ( *vertices[1] + *vertices[2] ) >= 0 );
  case 1:
    return ( ( flag.is_last_finite() )
      ?(  (( *p - *vertices[2] ) ^ ( *vertices[2] - *vertices[0] )) >= 0 )
      :(  (( *p - *vertices[0] ) ^ ( *vertices[0] - *vertices[1] )) >= 0 ));
  case 0:
// 
//  compute the det 4*4 column: x,y,x**2+y**2,1 for p and vertices [0,1,2]
//
    double x,y;
    double x0,y0;
      double x1,y1;
      double x2,y2;
        double z1,z2;
        double alpha,beta,gamma;
        x  = p->X();
        y  = p->Y();
        x0 = vertices[0]->X();
        y0 = vertices[0]->Y();
        x1 = vertices[1]->X();
        y1 = vertices[1]->Y();
        x2 = vertices[2]->X();
        y2 = vertices[2]->Y();
        x1-=x0;
          y1-=y0;
          x2-=x0;
            y2-=y0;
            x-=x0;
              y-=y0;
        z1=(x1*x1)+(y1*y1);
          z2=(x2*x2)+(y2*y2);
        alpha=(y1*z2)-(z1*y2);
          beta=(x2*z1)-(x1*z2);
          gamma=(x1*y2)-(y1*x2);
        return ((alpha*x)+(beta*y)+gamma*((x*x)+(y*y))  <= 0 );
  }
  return 0;
}
//****************************************************************************80

void point::lineto ( point *p )

//****************************************************************************80
//
//  Purpose:
//
//    point::lineto writes information about a line to the PostScript file.
//
//  Author:
//
//    Olivier Devillers
//
{ 
  /*
  cout << this->x << " " 
       << this->y << " moveto " 
       << p->x   << " "
       << p->y   << " lineto stroke\n";
  */
  *tablicapunktowtemp   << QPointF(this->x,this->y) << QPointF(p->x,p->y);

}
//****************************************************************************80

DT_node::DT_node ( void )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::DT_node ( void ) is a creation routine for class DT_node.
//
//  Author:
//
//    Olivier Devillers
//
{
  vertices[0] = new point (  1.0,  0.0       );
  vertices[1] = new point ( -0.5,  0.8660254 );
  vertices[2] = new point ( -0.5, -0.8660254 );

  flag.infinite ( 3 );
  nb = 0;
  sons = NULL;
}
//****************************************************************************80

DT_node::DT_node ( DT_node *root, ind i )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::DT_node ( DT_node* root, ind i ) is a creation routine for class DT_node.
//
//  Author:
//
//    Olivier Devillers
//
{
  vertices[0] = root->vertices[0] ;
  vertices[1] = root->vertices[1] ;
  vertices[2] = root->vertices[2] ;
  flag.infinite ( 4 );
  nb = 0;
  sons = NULL;
  neighbors[i] = root ;
  root->neighbors[i] = this ;
}
//****************************************************************************80

DT_node::DT_node ( DT_node *f, point *c, ind i )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::DT_node ( DT_node* f, point *c, ind i ) is a creation routine for class DT_node.
//
//  Discussion:
//
//    The triangle is created in ccw order.
//    The circumdisk and flatness are not computed.
//
//  Author:
//
//    Olivier Devillers
//
{
  switch ( f->flag.is_infinite() )
  {
  case 0:  flag.infinite ( 0 );
    break;
  case 1: if (f->flag.is_last_finite() ) flag.infinite ( (i==1) ? 0 : 1 );
      else                        flag.infinite ( (i==2) ? 0 : 1 );
      if ( flag.is_infinite() )
      {
        if ( f->flag.is_last_finite()  )
          { if ( i==0 ) flag.last_finite(); }
        else
          { if ( i==1 ) flag.last_finite(); }
      }
    break;
  case 2: flag.infinite ( (i==0) ? 2 : 1 );
        if (i==1) flag.last_finite();
    break;
  case 3:  flag.infinite ( 2 );
    break;
  }
  nb = 0;
  sons = NULL;
  f->sons = new DT_list(f->sons, this);
  f->neighbors[i]->sons = new DT_list(f->neighbors[i]->sons, this);
  f->neighbors[i]->neighbors[ f->neighbors[i]->neighbor_ind(f) ] = this ;
  vertices[0] = c;
  neighbors[0] = f->neighbors[i];
  switch (i) {
  case 0:
    vertices[1] = f->vertices[1];
    vertices[2] = f->vertices[2];
    break;
  case 1:
    vertices[1] = f->vertices[2];
    vertices[2] = f->vertices[0];
    break;
  case 2:
    vertices[1] = f->vertices[0];
    vertices[2] = f->vertices[1];
    break;
  }
}
//****************************************************************************80

DT_node* DT_node::find_conflict ( point *p )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::find_conflict returns an alive node in conflict.
//
//  Author:
//
//    Olivier Devillers
//
{
  DT_list* l;
  DT_node* n;

  if ( !conflict ( p ) )
  {
    return NULL;
  }

  if ( ! flag.is_dead() ) 
  {
    return this;
  }

  for ( l = sons; l; l = l->next )
  {
    if ( l->key->nb != nb )
    {
      l->key->nb = nb;
      n=l->key->find_conflict(p);
      if ( n ) 
      {
        return n;
      }
    }
  }

  return NULL;
}
//****************************************************************************80

void DT_node::output ( void )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node:output ?
//
//  Author:
//
//    Olivier Devillers
//
{
  DT_list* l;

  if ( flag.is_dead() )
  {
    for ( l=sons; l; l = l->next )
      if ( l->key->nb != nb )
      {
        l->key->nb = nb;
        l->key->output();
      }
    return;
  }

  if (neighbors[0]->nb != nb)
        if ( ! flag.is_infinite() )  vertices[1]->lineto(vertices[2]);

  if (neighbors[1]->nb != nb)
  {
        if ( ! flag.is_infinite() )  vertices[2]->lineto(vertices[0]);
        else if ( ( flag.is_infinite() == 1)
          &&( flag.is_last_finite()))vertices[2]->lineto(vertices[0]);
  }

  if (neighbors[2]->nb != nb)
  {
        if ( ! flag.is_infinite() )vertices[0]->lineto(vertices[1]);
        else if ( ( flag.is_infinite() == 1)
          &&(!flag.is_last_finite()))vertices[0]->lineto(vertices[1]);
  }
}
//****************************************************************************80

void Delaunay_tree::output ( void )

//****************************************************************************80
//
//  Purpose:
//
//    Delaunay_tree::output outputs the Delaunay triangulation.
//
//  Author:
//
//    Olivier Devillers
//
{
  //cout << "%!\n";

  root->nb = ++nb;
  root->output();

  //cout << "showpage\n";
}
//****************************************************************************80

void DT_node::output2 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    DT_node::output2 ?
//
//  Author:
//
//    Olivier Devillers
//
{
  if (neighbors[0]->nb != nb)
        if ( ! flag.is_infinite() )  vertices[1]->lineto(vertices[2]);

  if (neighbors[1]->nb != nb)
  {
        if ( ! flag.is_infinite() )  vertices[2]->lineto(vertices[0]);
        else if ( ( flag.is_infinite() == 1)
          &&( flag.is_last_finite()))vertices[2]->lineto(vertices[0]);
  }

  if (neighbors[2]->nb != nb)
  {
        if ( ! flag.is_infinite() )vertices[0]->lineto(vertices[1]);
        else if ( ( flag.is_infinite() == 1)
          &&(!flag.is_last_finite()))vertices[0]->lineto(vertices[1]);
  }

  if (neighbors[0]->nb != nb)
  {
     neighbors[0]->nb = nb;
     neighbors[0]->output();
  }

  if (neighbors[1]->nb != nb)
  {
    neighbors[1]->nb = nb;
    neighbors[1]->output(); 
  }

  if (neighbors[2]->nb != nb)
  {
    neighbors[2]->nb = nb;
    neighbors[2]->output(); 
  }
}
//****************************************************************************80

void Delaunay_tree::output2 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    Delaunay_tree::output2 outputs the Delaunay triangulation.
//
//  Author:
//
//    Olivier Devillers
//
{
  cout << "%!\n";
  root->neighbors[0]->nb = ++nb;
  root->neighbors[0]->output();
  cout << "showpage\n";
}
//****************************************************************************80

Delaunay_tree::Delaunay_tree ( void )

//****************************************************************************80
//
//  Purpose:
//
//    Delaunay_tree::Delaunay_tree ( void ) initializes the Delaunay tree.
//
//  Author:
//
//    Olivier Devillers
//
{
  nb = 0;
  tablicapunktow = new QVector<QPointF>;
  root = new DT_node();
  new DT_node(root, 0);
  new DT_node(root, 1);
  new DT_node(root, 2);
  root->neighbors[0]->neighbors[1] =  root->neighbors[1];
  root->neighbors[0]->neighbors[2] =  root->neighbors[2];
  root->neighbors[1]->neighbors[0] =  root->neighbors[0];
  root->neighbors[1]->neighbors[2] =  root->neighbors[2];
  root->neighbors[2]->neighbors[0] =  root->neighbors[0];
  root->neighbors[2]->neighbors[1] =  root->neighbors[1];
}
//****************************************************************************80

Delaunay_tree::~Delaunay_tree ( void )

//****************************************************************************80
//
//  Purpose:
//
//    Delaunay_tree::~Delaunay_tree is the destructor for class Delaunay_tree.
//
//  Author:
//
//    Olivier Devillers
//
{
  nb++;
}
//****************************************************************************80

Delaunay_tree &Delaunay_tree::operator += ( point *p )

//****************************************************************************80
//
//  Purpose:
//
//    Delaunay_tree::operator=+ is the insertion operator for class Delaunay_tree.
//
//  Author:
//
//    Olivier Devillers
//
{
  DT_node* n;
  DT_node* created;
  DT_node* last;
  DT_node* first;
  point* q;
  point* r;
  ind i;
  p->tablicapunktowtemp = tablicapunktow;
  root->nb = ++nb;

  if ( ! ( n = root->find_conflict(p) ) ) 
  {
    return *this ;
  }
//
// test if p is already inserted
//
    for ( i=0; (int) i < 3- (int) n->flag.is_infinite(); i++ )
    if ( ( p->X()==n->vertices[i]->X() )&&( p->Y()==n->vertices[i]->Y() ) )
                                return *this;
  n->flag.kill();
    // we will turn cw around first vertex of n, till next triangle
    // is not in conflict
    q = n->vertices[0];
    while( n->neighbors[ i=n->cw_neighbor_ind(q) ]->conflict(p) )
                {n = n->neighbors[i];n->flag.kill();}

  first = last = new DT_node(n,p,i);
    // we will turn cw around r, till next triangle is not in conflict
    r = n->vertices[(((int) i)+2)%3];
    while( 1){
        i = n->cw_neighbor_ind(r);
        if (n->neighbors[i]->flag.is_dead()){
              n = n->neighbors[i]; continue;
        }
        if (n->neighbors[i]->conflict(p) ){
            n = n->neighbors[i];
            n->flag.kill();
            continue;
        }
        break;
    }
  // n is killed by p
  // n->neighbors[i] is not in conflict with p
  // r is vertex i+1 of n
  while ( 1 ) {

    created = new DT_node(n,p,i);
    created->neighbors[2]=last;
    last->neighbors[1]=created;
    last=created;
    r = n->vertices[(((int) i)+2)%3];   // r turn in n ccw
    if (r==q) break;
    // we will turn cw around r, till next triangle is not in conflict
    while( 1){
        i = n->cw_neighbor_ind(r);
        if (n->neighbors[i]->flag.is_dead()){
              n = n->neighbors[i]; continue;
        }
        if (n->neighbors[i]->conflict(p) ){
            n = n->neighbors[i];
            n->flag.kill();
            continue;
        }
        break;
    }
  }
  first->neighbors[2]=last;
  last->neighbors[1]=first;
  return *this;
}

point::point ( double xx, double yy )
{
  x=xx;
  y=yy;
  tablicapunktowtemp = new QVector<QPointF>;
}
//****************************************************************************80

void timestamp ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//
//  Example:
//
//    May 31 2001 09:45:54 AM
//
//  Modified:
//
//    24 September 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    None
//
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cerr << time_buffer << "\n";

  return;
# undef TIME_SIZE
}
