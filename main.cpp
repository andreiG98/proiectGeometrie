#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include <algorithm>
#include <cstring>
#include "intersectieSegmente.h"
#define NMAX 2000

using namespace std;

struct Triunghi {
    int punct1;
    int punct2;
    int punct3;
};

bool convex[NMAX];
bool ear[NMAX];
//bool Diag[NMAX][NMAX];
bool viz[NMAX];
bool vizibile[NMAX];

int head;

vector <Point> poligon;
vector <Point> auxiliar;
vector <Point> stackk;
deque <Point> lista;
vector <Triunghi> triunghiuri;
vector <Triunghi> triunghiuriVizibile;
Point punctDeVerificat;

void read() {
    ifstream fin("date.in");
    float x, y;
    int i = 0;
    fin >> punctDeVerificat.x >> punctDeVerificat.y;
    while(fin >> x >> y){
        poligon.push_back({x, y, i});
        i++;
    }
    fin.close();
}

inline float cross_product(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

inline bool cmp(const Point& p1, const Point& p2) {
    return cross_product(auxiliar[0], p1, p2) < 0;
}

bool testOrientare(const Point& p1, const Point& p2, const Point& p3) {
    return cross_product(p1, p2, p3) < 0;
}

void sort_points() {
    int pos = 0;
    for (int i = 1; i < auxiliar.size(); ++i)
        if (auxiliar[i].x < auxiliar[pos].x || (auxiliar[i].x == auxiliar[pos].x && auxiliar[i].y < auxiliar[pos].y))
            pos = i;
    swap(auxiliar[0], auxiliar[pos]);
    sort(auxiliar.begin() + 1, auxiliar.end(), cmp);
}

void verificareVfConvexe() {
    int i;
    deque<Point>::iterator pCurrent;
    for(pCurrent = lista.begin(); pCurrent != lista.end(); pCurrent++) {
        auxiliar.push_back(*pCurrent);
    }
    for (i = 0; i < poligon.size(); i++) {
        convex[i] = true;
    }
    //sort_points();
    stackk.push_back(auxiliar[auxiliar.size() - 1]); //aici am modificat, sa inceapa de la coada si sa mearga spre dreapta. Daca pornea de la 0, pe primul varf nu-l vedea ca fiind concav atunci cand era concav
    stackk.push_back(auxiliar[0]);
    head = 2;
    for (i = 1; i < auxiliar.size(); ++i)
    {
        while (head >= 2 && cross_product(stackk[head - 2], stackk[head - 1], auxiliar[i]) > 0)
        {
            convex[stackk[head - 1].indice] = false;
            stackk.pop_back();
            --head;
        }
        stackk.push_back(auxiliar[i]);
        ++head;
    }
    stackk.clear();
    auxiliar.clear();
}

/*void diagonale() {
    int i, j, k, prevI, nextJ;
    bool ok;
    for (i = 0; i < poligon.size(); i++)
        for (j = i + 2; j < poligon.size(); j++) {
            ok = true;
            prevI = i - 1;
            if (prevI == -1)
                prevI = poligon.size() - 1;
            nextJ = j + 1;
            if (nextJ == poligon.size())
                nextJ = 0;
            for (k = 1; k < poligon.size() && ok; k++) {
                if (verificareIntersectieSegmente(poligon[i], poligon[j], poligon[k-1], poligon[k]));
                    ok = false;
            }
            if (ok)
                Diag[i][j] = Diag[j][i] = true;
        }
}*/

deque<Point>::iterator findEar() {
    deque<Point>::iterator pNext, pPrev, pCurrent;
    bool found = false;
    for (pCurrent = lista.begin(); pCurrent != lista.end() && (!found); pCurrent++)
        if (convex[pCurrent->indice] && viz[pCurrent->indice] == false) {
            /*pPrev = pCurrent - 1;
            if (pCurrent == lista.begin())
                pPrev = lista.end() - 1;
            pNext = pCurrent + 1;
            if (pNext == lista.end())
                pNext = lista.begin();
            if (convex[pNext->indice] && convex[pPrev->indice]) {
                found = true;
            }
            */
            found = true;
        }
    if (found)
        return (pCurrent - 1);
    return lista.end();
}

void triangulare() {
    int i, j, stop;
    bool ok;
    for (i = 0; i < poligon.size(); i++)
        lista.push_back(poligon[i]);
    deque<Point>::iterator pNext, pPrev, pCurrent, pDiagonal;
    while (lista.size() > 4) {
        verificareVfConvexe();
        //cout<<convex[poligon.size() - 1]<<endl;
        pCurrent = findEar();
        pPrev = pCurrent - 1;
        if (pCurrent == lista.begin())
            pPrev = lista.end() - 1;
        pNext = pCurrent + 1;
        if (pNext == lista.end())
            pNext = lista.begin();
        ok = true;
        stop = pPrev->indice - 1;
        if (stop < 0)
            stop = stop + poligon.size() + 1;
        for (j = pNext->indice + 1; j != stop && ok; j++) {
            if (j == poligon.size())
                j = 0;
            if (verificareIntersectieSegmente(poligon[pPrev->indice], poligon[pNext->indice], poligon[j], poligon[j + 1]))
                ok = false;
        }

        if (ok) {
            triunghiuri.push_back({pPrev->indice, pCurrent->indice, pNext->indice});
            lista.erase(pCurrent);
            memset(viz, 0, sizeof(viz));
        }
        else {
            viz[pCurrent->indice] = true;
        }
    }
    // cand avem doar 4 puncte ramase
    ok = true;
    for (pCurrent = lista.begin(); pCurrent != lista.end() && ok; pCurrent++)
        if (!convex[pCurrent->indice])
            ok = false;
    if (ok)
    {
        // poligon convex
        pCurrent = lista.begin();
        pNext = pCurrent + 1;
        pDiagonal = pCurrent + 2;
        pPrev = pCurrent + 3;
    }
    else
    {
        pCurrent--;
        // pCurrent - varf concav
        pNext = pCurrent + 1;
        if (pNext >= lista.end())
           pNext = lista.begin() + (pNext - lista.end());
        pDiagonal = pCurrent + 2;
        if (pDiagonal >= lista.end())
           pDiagonal = lista.begin() + (pDiagonal - lista.end());
        pPrev = pCurrent + 3;
        if (pPrev >= lista.end())
           pPrev = lista.begin() + (pPrev - lista.end());
    }
    triunghiuri.push_back({pCurrent->indice, pNext->indice, pDiagonal->indice});
    triunghiuri.push_back({pDiagonal->indice, pPrev->indice, pCurrent->indice});
}

void puncteVizibile() {
    int i, j, stop, pFirst, pSecond;
    bool ok;
    Point pPrev, pCurent, pNext;
    for (i = 0; i < poligon.size(); i++) {
        pCurent = poligon[i];
        pPrev = poligon[i - 1];
        if(i == 0)
            pPrev = poligon[poligon.size() - 1];
        pNext = poligon[i + 1];
        if(i == poligon.size() - 1)
            pNext = poligon[0];
        stop = pPrev.indice - 1;
        if(pPrev.indice == 0)
            stop = poligon[poligon.size() - 1].indice;
        ok = true;
        for(j = pNext.indice; j != stop + 1 && ok; j++) {
            if (j == poligon.size())
                j = 0;
            pFirst = j;
            pSecond = j + 1;
            if(pSecond == poligon.size())
                pSecond = 0;
            if (verificareIntersectieSegmente(punctDeVerificat, pCurent, poligon[pFirst], poligon[pSecond]))
                ok = false;
        }
        vizibile[i] = ok;
    }
}

void triunghiuriVizibileDinPc() {
    puncteVizibile();
    for (int i = 0; i < triunghiuri.size(); i++) {
        if(vizibile[triunghiuri[i].punct1] && vizibile[triunghiuri[i].punct2] && vizibile[triunghiuri[i].punct3]) {
            triunghiuriVizibile.push_back({triunghiuri[i].punct1, triunghiuri[i].punct2, triunghiuri[i].punct3});
        }
    }
}

int main() {
    read();
    triangulare();
    /*for (int i = 0; i < triunghiuri.size(); i++)
        cout << triunghiuri[i].punct1 << ' ' << triunghiuri[i].punct2 << ' ' << triunghiuri[i].punct3 << '\n';*/
    /*for (int i = 0; i < poligon.size(); i++)
        cout<<vizibile[i]<<' ';*/
    //cout<<endl<<endl;
    triunghiuriVizibileDinPc();
    for (int i = 0; i < triunghiuriVizibile.size(); i++)
        cout << triunghiuriVizibile[i].punct1 << ' ' << triunghiuriVizibile[i].punct2 << ' ' << triunghiuriVizibile[i].punct3 << '\n';
    return 0;
}
