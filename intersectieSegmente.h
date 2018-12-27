#ifndef INTERSECTIESEGMENTE_H_INCLUDED
#define INTERSECTIESEGMENTE_H_INCLUDED
#include <algorithm>

using namespace std;

struct Point 
{
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
        lambda=det( D.x-B.x, D.x-C.x,
                 D.y-B.y, D.y-C.y)*1.0/delta;
        miu=det( A.x-B.x, D.x-B.x,
                 A.y-B.y, D.y-B.y)*1.0/delta;
        if (0 <= lambda && lambda <= 1 && 0 <= miu && miu <= 1)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        if ( det(A.x-B.x, D.x-B.x,
                 A.y-B.y, D.y-B.y)==0.0 )
        {
            if (A.x==B.x)
            {
                if (C.x==D.x)
                {
                    if (A.y==B.y && C.y==D.y)
                    {
                        return true;
                    }
                    else
                        if (A.y==B.y)
                        {
                            return true;
                        }
                        else
                            if (C.y==D.y)
                            {
                                return true;
                            }
                            else
                            {
                                lambda_min=min((D.y-B.y+C.y-D.y)*1.0/(A.y-B.y),(D.y-B.y)*1.0/(A.y-B.y));
                                lambda_max=max((D.y-B.y+C.y-D.y)*1.0/(A.y-B.y),(D.y-B.y)*1.0/(A.y-B.y));
                                if (intersect(lambda_min,lambda_max,0,1)==-1)
                                {
                                    return false;
                                }
                                else
                                {
                                    if (lambda_min==lambda_max)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return true;
                                    }
                                }
                            }
                }
                else
                {
                    return true;
                }
            }
            else
            {
                lambda_min=min((D.x-B.x+C.x-D.x)*1.0/(A.x-B.x),(D.x-B.x)*1.0/(A.x-B.x));
                lambda_max=max((D.x-B.x+C.x-D.x)*1.0/(A.x-B.x),(D.x-B.x)*1.0/(A.x-B.x));
                if (intersect(lambda_min,lambda_max,0,1)==-1)
                {
                    return false;
                }
                else
                {
                    if (lambda_min==lambda_max)
                    {
                        return true;
                    }
                    else
                    {
                        return true;
                    }
                }
            }

        }
        else
        {
            return false;
        }
    }
}

#endif // INTERSECTIESEGMENTE_H_INCLUDED
