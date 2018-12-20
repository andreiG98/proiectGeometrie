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
