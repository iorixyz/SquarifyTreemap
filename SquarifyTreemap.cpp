#include "./SquarifyTreemap.h"
#include <numeric>
#include <list>

using namespace std;

void PrintList(const list<double> &listSizes)
{
    for (auto it = listSizes.begin(); it != listSizes.end(); ++it)
    {
        printf("elements is %f", *it);
    }
    printf("\n");
}

void PrintList(const list<struCoordinate> &listCoordinate)
{
    for (auto it = listCoordinate.begin(); it != listCoordinate.end(); ++it)
    {
        printf("x is %f, y is %f, dx is %f, dy is %f", it->x, it->y, it->dx, it->dy);
    }
    printf("\n");
}

list<struCoordinate> SquarifyTreemap::Squafity(list<double> listSizes, struCoordinate &coordinate)
{
    if (listSizes.size() == 1)
        return layout(listSizes, coordinate);

    auto it = listSizes.begin();
    list<double> listFirst, listFirstTwo;
    listFirst.push_back(*it);
    listFirstTwo.push_back(*it);
    ++it;
    listFirstTwo.push_back(*it);
    int i = 0;
    auto newCoordinate = coordinate;
    auto newCoordinate2 = coordinate;
    while (i < listSizes.size() && (worst_ratio(listFirst, newCoordinate) >= worst_ratio(listFirstTwo, newCoordinate2)))
    {
        i++;
    }
    list<double> listCurrent;
    list<double> listRemain = listSizes;

    it = listSizes.begin();
    for (int j = 0; j <= i; j++)
    {
        listCurrent.push_back(*it);
        ++it;
        listRemain.pop_front();
    }

    //PrintList(listCurrent);
    //PrintList(listRemain);
    //printf("x is %f, y is %f, dx is %f, dy is %f\n", coordinate.x, coordinate.y, coordinate.dx, coordinate.dy);
    auto leftCoordinate = leftover(listCurrent, coordinate);
    //printf("x is %f, y is %f, dx is %f, dy is %f\n", leftCoordinate.x, leftCoordinate.y, leftCoordinate.dx, leftCoordinate.dy);
    auto layoutRet = layout(listCurrent, coordinate);
    auto squarifyRet = Squafity(listRemain, leftCoordinate);
    layoutRet.splice(layoutRet.begin(), squarifyRet);
    //PrintList(layoutRet);
    return layoutRet;
}

list<double> SquarifyTreemap::normalizeSizes(std::list<double> listSizes, double dx, double dy)
{
    list<double> normalizedSizes;

    double dTotalSize = accumulate(listSizes.begin(), listSizes.end(), 0);
    double dTotalArea = dx * dy;
    for (auto it = listSizes.begin(); it != listSizes.end(); ++it)
    {
        normalizedSizes.push_back(*it * dTotalArea / dTotalSize);
    }
    return normalizedSizes;
}

double SquarifyTreemap::worst_ratio(std::list<double> listSizes, struCoordinate &coordinate)
{
   auto ret = layout(listSizes, coordinate);
   list<double> listTemp;
   for (auto it = ret.begin(); it != ret.end(); ++it)
   {
       listTemp.push_back(max((it->dx / it->dy), (it->dy / it->dx)));
   } 
   return *max_element(listTemp.begin(), listTemp.end());
}

struCoordinate SquarifyTreemap::leftover(std::list<double> listSizes, struCoordinate &coordinate)
{
    if (coordinate.dx > coordinate.dy)
        return leftoverrow(listSizes, coordinate);
    else
        return leftovercol(listSizes, coordinate);
}

struCoordinate SquarifyTreemap::leftoverrow(list<double> listSizes, struCoordinate &coordinate)
{
    //PrintList(listSizes);
    //printf("row!!!!!x is %f, y is %f, dx is %f, dy is %f\n", coordinate.x, coordinate.y, coordinate.dx, coordinate.dy);

    double dCoveredArea = accumulate(listSizes.begin(), listSizes.end(), 0);
    double dWidth = dCoveredArea / coordinate.dy;
    struCoordinate struLeftCoordinate;
    struLeftCoordinate.x = coordinate.x + dWidth;
    struLeftCoordinate.y = coordinate.y;
    struLeftCoordinate.dx = coordinate.dx - dWidth;
    struLeftCoordinate.dy = coordinate.dy;

    return struLeftCoordinate;
}

struCoordinate SquarifyTreemap::leftovercol(list<double> listSizes, struCoordinate &coordinate)
{
    //PrintList(listSizes);
    //printf("collll!!x is %f, y is %f, dx is %f, dy is %f\n", coordinate.x, coordinate.y, coordinate.dx, coordinate.dy);
    double dCoveredArea = accumulate(listSizes.begin(), listSizes.end(), 0);
    double dHeight = dCoveredArea / coordinate.dx;
    struCoordinate struLeftCoordinate;
    struLeftCoordinate.x = coordinate.x;
    struLeftCoordinate.y = coordinate.y + dHeight;
    struLeftCoordinate.dx = coordinate.dx;
    struLeftCoordinate.dy = coordinate.dy - dHeight;

    return struLeftCoordinate;
}

list<struCoordinate> SquarifyTreemap::layout(list<double> listSizes, struCoordinate &coordinate)
{
    if (coordinate.dx > coordinate.dy)
        return layoutrow(listSizes, coordinate);
    else
        return layoutcol(listSizes, coordinate);
}

list<struCoordinate> SquarifyTreemap::layoutrow(list<double> listSizes, struCoordinate &coordinate)
{
    double dCoveredArea = accumulate(listSizes.begin(), listSizes.end(), 0);
    double dWidth = dCoveredArea / coordinate.dy;
    list<struCoordinate> listTemp;
    for (auto it = listSizes.begin(); it != listSizes.end(); ++it)
    {
        struCoordinate struTempCoordinate;
        struTempCoordinate.x = coordinate.x;
        struTempCoordinate.y = coordinate.y;
        struTempCoordinate.dx = dWidth;
        struTempCoordinate.dy = *it / dWidth;
        listTemp.push_back(struTempCoordinate);
        coordinate.y += *it / dWidth;
    }
    return listTemp;
}

list<struCoordinate> SquarifyTreemap::layoutcol(list<double> listSizes, struCoordinate &coordinate)
{
    double dCoveredArea = accumulate(listSizes.begin(), listSizes.end(), 0);
    double dHeight = dCoveredArea / coordinate.dx;
    list<struCoordinate> listTemp;
    for (auto it = listSizes.begin(); it != listSizes.end(); ++it)
    {
        struCoordinate struTempCoordinate;
        struTempCoordinate.x = coordinate.x;
        struTempCoordinate.y = coordinate.y;
        struTempCoordinate.dx = *it / dHeight;
        struTempCoordinate.dy = dHeight;
        listTemp.push_back(struTempCoordinate);
        coordinate.x += *it / dHeight;
    }
    return listTemp;

}