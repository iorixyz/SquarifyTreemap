#include <list>
#include <stdio.h>

struct struCoordinate
{
    double x;
    double y;
    double dx;
    double dy;
};

class SquarifyTreemap
{
public:
    std::list<double> listSized;
    std::list<struCoordinate> Squafity(std::list<double> listSizes, struCoordinate &coordinate);
    std::list<double> normalizeSizes(std::list<double> listSizes, double dx, double dy);
private:
    double worst_ratio(std::list<double> listSizes, struCoordinate &coordinate);
    struCoordinate leftover(std::list<double> listSizes, struCoordinate &coordinate);
    struCoordinate leftoverrow(std::list<double> listSizes, struCoordinate &coordinate);
    struCoordinate leftovercol(std::list<double> listSizes, struCoordinate &coordinate);

    std::list<struCoordinate> layout(std::list<double> listSizes, struCoordinate &coordinate);
    std::list<struCoordinate> layoutrow(std::list<double> listSizes, struCoordinate &coordinate);
    std::list<struCoordinate> layoutcol(std::list<double> listSizes, struCoordinate &coordinate);
};