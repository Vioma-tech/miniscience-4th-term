#include <set>
#include <vector>
#include <gmsh.h>

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("donut");

    double R1 = 3;
    double R2 = 1.5;
    double width = .5;

    double lc = 1e-1;

    // constructing outer circle
    int center = gmsh::model::geo::addPoint(0, R1, 0, lc);
    int right = gmsh::model::geo::addPoint(0, R1 + R2, 0, lc);
    int top = gmsh::model::geo::addPoint(0, R1, R2, lc);
    int left = gmsh::model::geo::addPoint(0, R1 - R2, 0, lc);
    int bottom = gmsh::model::geo::addPoint(0, R1, -R2, lc);

    gmsh::model::geo::addCircleArc(right, center, top, 1);
    gmsh::model::geo::addCircleArc(top, center, left, 2);
    gmsh::model::geo::addCircleArc(left, center, bottom, 3);
    gmsh::model::geo::addCircleArc(bottom, center, right, 4);

    int outer_circle_loop = gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);

    // constructing inner circle
    int right2 = gmsh::model::geo::addPoint(0, R1 + R2 - width, 0, lc);
    int top2 = gmsh::model::geo::addPoint(0, R1, R2 - width, lc);
    int left2 = gmsh::model::geo::addPoint(0, R1 - R2 + width, 0, lc);
    int bottom2 = gmsh::model::geo::addPoint(0, R1, -R2 + width, lc);

    gmsh::model::geo::addCircleArc(right2, center, top2, 5);
    gmsh::model::geo::addCircleArc(top2, center, left2, 6);
    gmsh::model::geo::addCircleArc(left2, center, bottom2, 7);
    gmsh::model::geo::addCircleArc(bottom2, center, right2, 8);

    int inner_circle_loop = gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 2);

    // constructing ring surface
    int ring_surface = gmsh::model::geo::addPlaneSurface({outer_circle_loop, -inner_circle_loop});
    

    // 360 revolve doesn't work ¯\_(ツ)_/¯
    // constructing donut with four parts
    // 1st rotation
    double angle = M_PI / 2;
    std::vector<std::pair<int, int>> dimTags1 = {{2, ring_surface}};
    std::vector<std::pair<int, int>> outDimTags1;
    gmsh::model::geo::revolve(dimTags1, 0, 0, 0, // Point on the axis
                              0, 0, 1, // Axis direction
                              angle, outDimTags1);

    // 2nd rotation
    std::vector<std::pair<int, int>> dimTags2 = {{2, outDimTags1[0].second}};
    std::vector<std::pair<int, int>> outDimTags2;
    gmsh::model::geo::revolve(dimTags2, 0, 0, 0, // Point on the axis
                              0, 0, 1, // Axis direction
                              angle, outDimTags2);

    // 3rd rotation
    std::vector<std::pair<int, int>> dimTags3 = {{2, outDimTags2[0].second}};
    std::vector<std::pair<int, int>> outDimTags3;
    gmsh::model::geo::revolve(dimTags3, 0, 0, 0, // Point on the axis
                              0, 0, 1, // Axis direction
                              angle, outDimTags3);

    // 4th rotation
    std::vector<std::pair<int, int>> dimTags4 = {{2, outDimTags3[0].second}};
    std::vector<std::pair<int, int>> outDimTags4;
    gmsh::model::geo::revolve(dimTags4, 0, 0, 0, // Point on the axis
                              0, 0, 1, // Axis direction
                              angle, outDimTags4);

    
    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    gmsh::write("donut.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}