# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <ctime>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

typedef unsigned char ind;  // used for flag and ind in array
class Delaunay_tree;
class DT_node;
class DT_list;
class point;

class Delaunay_tree
{
  private :
  // number of the current operation
    int nb;
  // the root of the delaunay_tree
    DT_node* root;

  public :
    QVector<QPointF> *tablicapunktow;
    Delaunay_tree ( void );                        // initialization as empty
    ~Delaunay_tree ( void );                       // destructor
    Delaunay_tree& operator+=(point*);      // insertion
    void output ( void );              // the Delaunay triangulation
    void output2 ( void );
};

class point
{
  private :
    double x;
    double y;
  public :
    QVector<QPointF> *tablicapunktowtemp;
    point ( double , double );
    double X ( void ) {return x;}
    double Y ( void ) {return y;}
    void lineto ( point *p );
    friend point operator + ( point, point );
    friend point operator - ( point, point );
    friend double operator * ( point, point );
    friend double operator ^ ( point, point );
};

class DT_flag
{
  private :
    ind f;
    DT_flag ( void ) { f = (ind) 0 ; }
    void infinite ( int i ) { f |= (ind) i ; }
    void last_finite ( void ) { f |= 8;}
    void kill ( void ) { f |= 16;}
    ind is_infinite ( void ) { return f & 7;}
    ind is_last_finite ( void )   { return f & 8;}
    ind is_dead ( void )         { return f & 16;}
    ind is_degenerate ( void )    { return f & 32;}
  public :
    friend class DT_node;
    friend class Delaunay_tree;
};

class DT_list
{
  private :
    DT_list *next;
    DT_node *key;
    DT_list ( DT_list* l, DT_node* k ) {next=l; key=k;}
    ~DT_list ( void );
  public :
    friend class DT_node;
    friend class Delaunay_tree;
};

class DT_node
{
  private :
      // the first vertex is the creator, that is finite
      // except for the root and its neighbors
    DT_flag      flag;
    unsigned int  nb;
    point*      vertices[3];
    DT_node*        neighbors[3];
    DT_list*    sons;
    DT_node ( void );          // initialize the root
    DT_node(DT_node*, ind);  // initialize nowhere
    DT_node(DT_node*, point*, ind);
            // father, creator, direction of stepfather
    ind conflict(point *);
    DT_node* find_conflict(point* p);
    void output ( void );
    void output2 ( void );
    ind cw_neighbor_ind(point *p)
        { return ((p==vertices[0]) ? 2 : ((p==vertices[1]) ? 0 : 1)); }
    ind neighbor_ind(DT_node *n)
        { return ( (neighbors[0]==n)?0:((neighbors[1]==n)?1:2) );}
  public :
    friend class Delaunay_tree;
};
