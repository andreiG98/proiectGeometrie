<<<<<<< HEAD
#ifndef INTERSECTIESEGMENTE_H_INCLUDED
#define INTERSECTIESEGMENTE_H_INCLUDED
#include <algorithm>
using namespace std;
struct Point {
    float x;
    float y;
    int indice;
};
float det(float a1, float a2, float a3, float a4)
{
    return 1.0*(a1*a4-a2*a3);
}

int intersect(float &a, float &b, float c, float d)
{
    if (d<a || b<c)
    {
        return -1;
    }
    if (b==c)
    {
        a=c;
        return 0;
    }
    if (c<b && b<d)
    {
        if (c<=a)
            return 0;
        if (c>a)
        {
            a=c;
            return 0;
        }
    }
    if (b==d)
    {
        if (a<c)
        {
            a=c;
            return 0;
        }
    }
    if (b>d)
    {
        if (a<c)
        {
            a=c;
        }
        b=d;
        return 0;
    }
    return 0;
}
bool verificareIntersectieSegmente(Point A, Point B, Point C, Point D)
{
    float delta=det( A.x-B.x, D.x-C.x,
                      A.y-B.y, D.y-C.y);
    float lambda,miu,lambda_min,lambda_max;
    if (delta!=0.0)
    {
        //se intersecteaza
        lambda=det( D.x-B.x, D.x-C.x,
                 D.y-B.y, D.y-C.y)*1.0/delta;
        miu=det( A.x-B.x, D.x-B.x,
                 A.y-B.y, D.y-B.y)*1.0/delta;
        if (0 <= lambda && lambda <= 1 && 0 <= miu && miu <= 1)
        {
            //M.x=lambda*A.x+(1-lambda)*B.x;
            //M.y=lambda*A.y+(1-lambda)*B.y;
            //fout<<"Segmentele se intersecteaza in punctul "<<M.x<<' '<<M.y<<'\n';
            return true;
        }
        else
        {
            //dreptele determinate se intersecteaza, dar segmentele nu
            //fout<<"Segmentele nu se intersecteaza\n";
            return false;
        }

    }
    else
    {
        if ( det(A.x-B.x, D.x-B.x,
                 A.y-B.y, D.y-B.y)==0.0 )
        {
            //sistem compatibil nedeterminat
            if (A.x==B.x)
            {
                //lambda apartine [0,1]
                if (C.x==D.x)
                {
                    if (A.y==B.y && C.y==D.y)
                    {
                        //Segmentele coincid
                        //fout<<"Intersectia este segmentul "<<A.x<<' '<<A.y<<" - "<<B.x<<' '<<B.y<<'\n';
                        return true;
                    }
                    else
                        if (A.y==B.y)
                        {
                            //A=B
                            //fout<<"Segmentele se intersecteaza in punctul "<<A.x<<' '<<A.y<<'\n';
                            return true;
                        }
                        else
                            if (C.y==D.y)
                            {
                                //C=D
                                //fout<<"Segmentele se intersecteaza in punctul "<<C.x<<' '<<C.y<<'\n';
                                return true;
                            }
                            else
                            {
                                lambda_min=min((D.y-B.y+C.y-D.y)*1.0/(A.y-B.y),(D.y-B.y)*1.0/(A.y-B.y));
                                lambda_max=max((D.y-B.y+C.y-D.y)*1.0/(A.y-B.y),(D.y-B.y)*1.0/(A.y-B.y));
                                if (intersect(lambda_min,lambda_max,0,1)==-1)
                                {
                                    //fout<<"Segmentele nu se intersecteaza\n";
                                    return false;
                                }
                                else
                                {
                                    if (lambda_min==lambda_max)
                                    {
                                        //M.x=lambda_min*A.x+(1-lambda_min)*B.x;
                                        //M.y=lambda_min*A.y+(1-lambda_min)*B.y;
                                        //fout<<"Segmentele se intersecteaza in punctul "<<M.x<<' '<<M.y<<'\n';
                                        return true;
                                    }
                                    else
                                    {
                                        //M.x=lambda_min*A.x+(1-lambda_min)*B.x;
                                        //M.y=lambda_min*A.y+(1-lambda_min)*B.y;

                                        //N.x=lambda_max*A.x+(1-lambda_max)*B.x;
                                        //N.y=lambda_max*A.y+(1-lambda_max)*B.y;
                                        //fout<<"Intersectia este segmentul "<<M.x<<' '<<M.y<<" - "<<N.x<<' '<<N.y<<'\n';return true;
                                        return true;
                                    }
                                }
                            }
                }
                else
                {
                    miu=(D.x-B.x)*1.0/(D.x-C.x);
                    //intersectia e segmentul AB,unde A=B
                    //M.x=miu*C.x+(1-miu)*D.x;
                    //M.y=miu*C.y+(1-miu)*D.y;
                    //fout<<"Intersectia este punctul "<<M.x<<' '<<M.y<<'\n';
                    return true;
                }
            }
            else
            {
                lambda_min=min((D.x-B.x+C.x-D.x)*1.0/(A.x-B.x),(D.x-B.x)*1.0/(A.x-B.x));
                lambda_max=max((D.x-B.x+C.x-D.x)*1.0/(A.x-B.x),(D.x-B.x)*1.0/(A.x-B.x));
                if (intersect(lambda_min,lambda_max,0,1)==-1)
                {
                    //fout<<"Segmentele nu se intersecteaza\n";
                    return false;
                }
                else
                {
                    if (lambda_min==lambda_max)
                    {
                        //M.x=lambda_min*A.x+(1-lambda_min)*B.x;
                        //M.y=lambda_min*A.y+(1-lambda_min)*B.y;
                        //fout<<"Segmentele se intersecteaza in punctul "<<M.x<<' '<<M.y<<'\n';
                        return true;
                    }
                    else
                    {
                        //M.x=lambda_min*A.x+(1-lambda_min)*B.x;
                        //M.y=lambda_min*A.y+(1-lambda_min)*B.y;

                        //N.x=lambda_max*A.x+(1-lambda_max)*B.x;
                        //N.y=lambda_max*A.y+(1-lambda_max)*B.y;
                        //fout<<"Intersectia este segmentul "<<M.x<<' '<<M.y<<" - "<<N.x<<' '<<N.y<<'\n';
                        return true;
                    }
                }
            }

        }
        else
        {
            //nu se intersecteaza
            return false;
        }
    }
}

#endif // INTERSECTIESEGMENTE_H_INCLUDED
=======
#ifndef INTERSECTIESEGMENTE_H_INCLUDED
#define INTERSECTIESEGMENTE_H_INCLUDED

#define swap(a, b) {Point aux = a; a = b; b = aux; }

struct Point {
    float x;
    float y;
    int indice;
};

struct ecDreptei{
    double a;
    double b;
    double c;
};

ecDreptei calcul(Point A,Point B)
{
    double a,b,c;
    a=A.y-B.y;
    b=B.x-A.x;
    c=A.x*(B.y-A.y)-A.y*(B.x-A.x);
    return {a,b,c};
}

double determinant(double a1,double b1,double a2,double b2)
{
    return a1*b2 - a2*b1;
}

double distanta(Point A,Point B)
{
    return sqrt(pow(B.x-A.x,2) + pow(B.y-A.y,2));
}

bool verificareIntersectieSegmente(Point A1, Point A2, Point A3, Point A4) //1 - nu se intersecteaza 0 - se itnersecteaza
{
    if(A1.x > A2.x || A1.x == A2.x && A1.y > A2.y)
        swap(A1, A2);
    if(A3.x > A4.x || A3.x == A4.x && A3.y > A4.y)
        swap(A3, A4);
    ecDreptei n,m;
    n = calcul(A1, A2);
    m = calcul(A3, A4);
    double delta = determinant(n.a, n.b, m.a, m.b);
    if (delta)
    {
        double X = determinant(-n.c, n.b, -m.c, m.b) / delta;
        double Y = determinant(n.a, -n.c, m.a, -m.c) / delta;
        Point C;
        double distA1A2, distA1C, distCA2, distA3A4, distA3C, distCA4;
        C.x = X;
        C.y = Y;

        distA1A2 = ceil(distanta(A1,A2)*100)/100; //aici trebuie revenit
        distA1C = distanta(A1, C);
        distCA2 = distanta(C, A2);
        double dist1 = ceil((distA1C+distCA2)*100)/100;

        distA3A4 = ceil(distanta(A3, A4)*100)/100;
        distA3C = distanta(A3, C);
        distCA4 = distanta(C, A4);
        double dist2 = ceil((distA3C + distCA4)*100)/100;

        if((distA1A2 == dist1) && (distA3A4 == dist2))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (!delta)
    {
        double detX, detY;
        detX = determinant(n.a, -n.c, m.a, -m.c);
        detY = determinant(n.b, -n.c, m.b, -m.c);
        if(detX || detY)
        {
            return 1;
        }
        if(detX == 0 && detY == 0)
        {
            if((A2.x < A3.x) || (A2.x == A3.x && A2.y < A3.y))
                return 1;
            /*if( ! ( ( A2.x < A3.x ) || ( A2.x == A3.x && A2.y < A3.y ) ) )
            {
                if((A2.x > A3.x && A2.x < A4.x) || (A2.x == A3.x && A2.x < A4.x))
                {
                    g<<A3.x<<' '<<A3.y<<endl<<A2.x<<' '<<A2.y<<endl;
                }
                else
                {
                    g<<A3.x<<' '<<A3.y<<endl<<A4.x<<' '<<A4.y<<endl;
                }
                return 0;
            }*/
            return 0;
        }
    }
}

#endif // INTERSECTIESEGMENTE_H_INCLUDED
>>>>>>> 3977c97ffabbb27e50556d033119547c7f2948e7
