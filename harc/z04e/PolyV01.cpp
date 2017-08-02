// PolyLink.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>

#define Max(x,y)  (((x)<(y))?(y):(x))
#define Min(x,y)  (((x)>(y))?(y):(x))

/*********************************************************************\
  Linked List
\*********************************************************************/

typedef int DEG;
typedef float COF;
typedef float VAL;

struct TRS
{ struct TRS *frw;
  DEG deg;
  COF cof; 
};

typedef struct TRS TRM;
typedef TRM *TRP;

/*** Linked List - Internal Procedures ***/

TRP trmfnd(TRP trp,DEG deg)
{ while (trp && trp->frw && (trp->frw)->deg <= deg) trp=trp->frw;
  return trp; }

void trmins(TRP trp,DEG deg,COF cof)
{ if (trp)
  { TRP trn = (TRP)malloc(sizeof(TRM));
    if (trn)
    { trn->frw = trp->frw;
      trn->deg = deg;
      trn->cof = cof;
      trp->frw = trn; } } }

void trmdel(TRP trp)
{ if (trp)
  { TRP frw = trp->frw;
    if (frw)
    { trp->frw = frw->frw;
      free(frw); } } }

void trmchg(TRP trp,DEG deg,COF cof)
{ if (trp)
  { trp->deg = deg;
    trp->cof = cof; } }

/*** Linked List - External Procedures ***/

void trmprn(TRP trp)
{ while (trp)
  { printf("frw: %p  deg: %05d  cof: %05d\n",trp->frw,trp->deg,trp->cof);
    trp=trp->frw; } 
  printf("\n"); }

void trmini(TRP trp)
{ if (trp) 
  { memset(trp,0,sizeof(TRM)); } }

void trmclr(TRP trp)
{ while (trp && trp->frw) trmdel(trp);
  trmini(trp); }

int trmdeg(TRP trp)
{ int deg=0;
  while (trp)
  { deg=trp->deg;
    trp=trp->frw; }
  return deg; }

void trmset(TRP trp,DEG deg,COF cof)
{ if (trp)
  { if (cof || deg==0)
    { TRP trf = trmfnd(trp,deg);
      if (trf)
      { if (trf->deg < deg)
        { trmins(trf,deg,cof); }
        else
        { trmchg(trf,deg,cof); } } }
    else 
    { TRP trf = trmfnd(trp,deg-1);
      { if (trf->frw && (trf->frw)->deg == deg)
        { trmdel(trf); } } } } }

/*********************************************************************\
  Polynomial Class
\*********************************************************************/

typedef struct
{ DEG deg;
  COF cof;
} Mon;

class Poly
{ private:
  DEG deg;
  TRP hed;
  public:
  Poly(void);
  Poly(Poly& a);
  ~Poly(void);
  Poly operator=(Poly& a);
  Poly operator+(Poly& a);
  Poly operator-(Poly& a);
  Poly operator*(Poly& a);
  VAL  eval(VAL val);
  COF  get(DEG pwr);
  void set(DEG pwr,COF cof);
  void clear(void);
  void print(void);
  void load(Mon* mon);
};

Poly::Poly(void)
{ deg = 0;
  hed = new TRM;
  trmini(hed); }

Poly::Poly(Poly& a)
{ TRP tra = a.hed;
  deg = 0;
  hed = new TRM;
  trmini(hed);
  while (tra)
  { set(tra->deg,tra->cof);
    tra=tra->frw; } }
  
Poly::~Poly(void)
{ trmclr(hed);
  delete hed; }

Poly Poly::operator=(Poly& a)
{ TRP tra = a.hed;
  clear();
  while (tra)
  { set(tra->deg,tra->cof);
    tra=tra->frw; }
  return *this; }

Poly Poly::operator+(Poly& a)
{ Poly p;
  DEG n=Max(deg,a.deg),d=0;
  COF c=0;
  for (d=0; d<=n; d++)
  { c = get(d)+a.get(d);
    p.set(d,c); }
  return p; }

Poly Poly::operator-(Poly& a)
{ Poly p;
  DEG n=Max(deg,a.deg),d=0;
  COF c=0;
  for (d=0; d<=n; d++)
  { c = get(d)-a.get(d);
    p.set(d,c); }
  return p; }

Poly Poly::operator*(Poly& a)
{ Poly p;
  DEG n=deg+a.deg,d=0,m=0;
  COF c=0;
  for (d=0; d<=n; d++)
  { c = 0;
    for (m=0; m<=d; m++)
    { c += get(m) * a.get(d-m); }
    if (c) p.set(d,c); }
  return p; }

void Poly::load(Mon* m)
{ while (m->cof)
  { set(m->deg,m->cof);
    m++; } }

VAL Poly::eval(VAL val)
{ DEG pwr=0;
  VAL ret=0;
  if (val)
  { for (pwr=deg; pwr>=0; pwr--)
    { ret*=val;
      ret+=get(pwr); } }
  else
  { ret=get(0); }
  return ret; }

COF Poly::get(DEG pwr)
{ COF cof=0;
  if (pwr<=deg)
  { TRP trp=trmfnd(hed,pwr);
    if (trp->deg == pwr)
    { cof = trp->cof; } }
  return cof; }

void Poly::set(DEG pwr,COF cof)
{ trmset(hed,pwr,cof);
  if (cof)
  { if (deg < pwr)
    { deg = pwr; } }
  else
  { deg = trmdeg(hed); } }

void Poly::clear(void)
{ deg=0;
  trmclr(hed); }

void Poly::print(void)
{ TRP trp=hed;
  int f=0;
  int x=0;
  int l=0;
  char b[256];
  // printf("[%d]\n",deg);
  while (trp)
  { if (f++) x += printf(" + ");
    if (trp->deg < 1)
    { l=sprintf(b,"%f",trp->cof); }
    else if (trp->deg < 2)
    { if (trp->cof == 1)
      { l=sprintf(b,"x"); }
      else
      { l=sprintf(b,"%fx",trp->cof); } }
    else
    { if (trp->cof == 1)
      { l=sprintf(b,"x^%d",trp->deg); }
      else
      { l=sprintf(b,"%fx^%d",trp->cof,trp->deg); } }
    if (l+x > 64)
    { printf("\n");
      x = 0; }
    x += printf("%s",b); 
    trp=trp->frw; } 
  printf("\n"); }

/***** End of Poly Class *****/

int trmtest(void)
{ TRM trm;
  TRP trp=&trm;
  trmini(trp);
  trmset(trp,0,10);
  trmset(trp,3,13);
  trmset(trp,2,12);
  trmset(trp,9,19);
  trmset(trp,4,14);
  trmset(trp,2,22);
  trmprn(trp);
  trmclr(trp);
	return 0; }

Mon f1[] =
{ { 0, 1 },
  { 2, 3 },
  { 3, 7 },
  { 5, 1 },
  { 0, 0 } };

Mon f2[] =
{ { 2, 3 },
  { 3, 1 },
  { 0, 0 } };

int polytest(void)
{ Poly a,b,p,q;
  VAL x=0,y=0;

  a.load(f1);
  b.load(f2);
  
  p = a+b;
  q = a*b;

  printf("a(x) = "); a.print();
  printf("b(x) = "); b.print();
  printf("p(x) = "); p.print();
  printf("q(x) = "); q.print();

  for (x=0; x<=5; x++)
  { y = a.eval(x);
    printf("a(%f) = %f\n",x,y); }
  
	return 0; }

int main(int argc, char* argv[])
{ return polytest(); }
