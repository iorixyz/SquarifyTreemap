#include "./SquarifyTreemap.h"
#include <list>
using namespace std;

int main()
{
    list<double> dTemp;
    dTemp.push_back(500);
    dTemp.push_back(433);
    dTemp.push_back(78);
    dTemp.push_back(25);
    dTemp.push_back(25);
    dTemp.push_back(7);

    double dWidth = 700.0;
    double dHeight = 433.0;

    SquarifyTreemap treemap;
    auto normalListRet = treemap.normalizeSizes(dTemp, dWidth, dHeight);
    for (auto it = normalListRet.begin(); it != normalListRet.end(); ++it)
    {
        printf("list is %f", *it);
    }
    printf("\n");
    struCoordinate coordinate;
    coordinate.x = 0;
    coordinate.y = 0;
    coordinate.dx = dWidth;
    coordinate.dy = dHeight;
    auto squarifyRet = treemap.Squafity(normalListRet, coordinate);

    for (auto it = squarifyRet.begin(); it != squarifyRet.end(); ++it)
    {
        printf("x is %f, y is %f, dx is %f, dy is %f\n", it->x, it->y, it->dx, it->dy);
    }
    getchar();
    return 0;
}