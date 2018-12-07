#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#define NMAX 2000

using namespace std;

struct Point {
    float x;
    float y;
    int indice;
};

bool convex[NMAX];
bool ear[NMAX];

int head;

vector <Point> poligon;
vector <Point> auxiliar;
vector <Point> stackk;

void read() {
    ifstream fin("date.in");
    //int n;
    float x, y;
    int i = 0;
    //fin >> n;
    //for(int i = 0; i < n; i++) {
    while(fin >> x >> y){
        //fin >> x >> y;
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
    for(i = 0; i < poligon.size(); i++) {
        auxiliar.push_back(poligon[i]);
        convex[i] = true;
    }
    sort_points();
    stackk.push_back(auxiliar[0]);
    stackk.push_back(auxiliar[1]);
    head = 2;
    for (i = 2; i < auxiliar.size(); ++i)
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
    auxiliar.clear();
}

int main()
{
    read();
    verificareVfConvexe();

    /*sort_points();
    for(int i = 0; i < poligon.size(); i++)
        cout<<poligon[i].x<<' '<<poligon[i].y<<endl;*/
    //cout<<testOrientare(poligon[10], poligon[0], poligon[1]);
    for(int i = 0; i < poligon.size(); i++)
        cout << convex[i] <<' ';
    return 0;
}
