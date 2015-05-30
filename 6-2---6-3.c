#include <stdio.h>

#define XMAX 350
#define YMAX 400

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};

int main() {
  struct point maxpt = {XMAX, YMAX};
  printf("x: %d y: %d\n", maxpt.x, maxpt.y);

  double distance, sqrt(double);
  
  distance = sqrt((double) maxpt.x * maxpt.x + (double) maxpt.y * maxpt.y);
  printf("distance: %f\n", distance);

  struct rect screen;
  struct point middle;
  struct point makepoint(int, int);

  screen.pt1 = makepoint(0, 0);
  screen.pt2 = makepoint(XMAX, YMAX);
  middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
		     (screen.pt1.y + screen.pt2.y) / 2);  
  printf("middle ---  x: %d  y: %d\n", middle.x, middle.y);

  struct point addpoint(struct point, struct point);
  struct point p1 = {500,500};
  middle = addpoint(middle, p1);
  printf("addpoint ---  x: %d  y: %d\n", middle.x, middle.y); 
  
  screen.pt1 = addpoint(screen.pt1, p1);
  printf("addpoint --- screen pt1 x: %d y: %d pt2 x: %d y: %d\n", screen.pt1.x, screen.pt1.y, screen.pt2.x, screen.pt2.y);

  struct rect canonrect(struct rect r);
  screen = canonrect(screen);
  printf("canonrect --- screen pt1 x: %d y: %d pt2 x: %d y: %d\n", screen.pt1.x, screen.pt1.y, screen.pt2.x, screen.pt2.y);
  

  struct point origin, *pp;
  origin = makepoint(200, 200);

  pp = &origin;
  printf("origin is (%d,%d)\n", (*pp).x, (*pp).y); // (*pp).x because the precedence of the structure member operator . is higher than *

  printf("origin is (%d,%d)\n", pp->x, pp->y); //another way to access the members of the structures with pointers

  struct rect r, *rp = &r;

  //the four expressions are equvalent:
  r.pt1.x;
  rp->pt1.x;
  (r.pt1).x;
  (rp->pt1).x;

  struct {
    int len;
    char *str;
  } *p;

  ++p->len; //increments len, not p
  (++p)->len; //increments p before accessing len
  (p++)->len; //increments p afterward
  *p->str; // fetches whatever str points to
  *p->str++; //increments str after accessing whatever points to
  *p++->str; //increments p after accessing whatever str points to

  return 0;
}


/* make point: make a point form x and y components */
struct point makepoint(int x, int y)
{
  struct point temp;
  
  temp.x = x;
  temp.y = y;
  return temp;
}


/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2) 
{
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

/* ptinrect: return 1 if pin r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
  return p.x >= r.pt1.x && p.x < r.pt2.x
    && p.y >= r.pt1.y && p.y < r.pt2.y;
}

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
  struct rect temp;
  
  temp.pt1.x = min(r.pt1.x, r.pt2.x);
  temp.pt1.y = min(r.pt1.y, r.pt2.y);
  temp.pt2.x = max(r.pt1.x, r.pt2.x);
  temp.pt2.y = max(r.pt1.y, r.pt2.y);
  return temp;
}
