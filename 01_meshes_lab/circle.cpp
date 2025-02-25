#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("circle");

    double lc = 1e-2;
    
    int center = gmsh::model::geo::addPoint(0, 0, 0, lc);
    int right = gmsh::model::geo::addPoint(.1, 0, 0, lc);
    int top = gmsh::model::geo::addPoint(0, .1, 0, lc);
    int left = gmsh::model::geo::addPoint(-.1, 0, 0, lc);
    int bottom = gmsh::model::geo::addPoint(0, -.1, 0, lc);


    gmsh::model::geo::addCircleArc(right, center, top, 1);
    gmsh::model::geo::addCircleArc(top, center, left, 2);
    gmsh::model::geo::addCircleArc(left, center, bottom, 3);
    gmsh::model::geo::addCircleArc(bottom, center, right, 4);
    

    gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
    gmsh::model::geo::addPlaneSurface({1}, 1);

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(2);

    gmsh::write("circle.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}

