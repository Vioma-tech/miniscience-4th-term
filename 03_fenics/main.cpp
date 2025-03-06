#include <dolfin.h>
#include "Poisson.h"

using namespace dolfin;

// Source term (right-hand side)
class Source : public Expression
{
  void eval(Array<double>& values, const Array<double>& x) const
  {
    values[0] = 0; // f
  }
};

// Normal derivative (Neumann boundary condition)
class dUdN : public Expression
{
  void eval(Array<double>& values, const Array<double>& x) const
  {
    values[0] = 0; // g
  }
};

// Sub domain for first Dirichlet boundary condition
class DirichletBoundary_1 : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
    // Tolerance for floating-point comparisons
    const double eps = DOLFIN_EPS;

    // Condition 1: x = 0 and 0 < y < 0.2
    if (std::abs(x[0] - 0.0) < eps && x[1] > 0.0 + eps && x[1] < 0.2 - eps)
        return true;

    // Condition 2: 0 < x < 0.3 and y = 0.2
    if (x[0] > 0.0 + eps && x[0] < 0.3 - eps && std::abs(x[1] - 0.2) < eps)
        return true;

    // If none of the conditions are met, return false
    return false;
  }
};

// Sub domain for second Dirichlet boundary condition
class DirichletBoundary_2 : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
    // Tolerance for floating-point comparisons
    const double eps = DOLFIN_EPS;

    // Condition 3: 0.15 < x < 0.3 and y = 0.15
    if (x[0] > 0.15 + eps && x[0] < 0.3 && std::abs(x[1] - 0.15) < eps)
        return true;

    // Condition 4: x = 0.15 and 0 < y < 0.15
    if (std::abs(x[0] - 0.15) < eps && x[1] > 0.0 + eps && x[1] < 0.15 - eps)
        return true;

    // If none of the conditions are met, return false
    return false;
  }
};


int main()
{
  // Load the mesh from an XDMF file
  auto mesh = std::make_shared<Mesh>();
  XDMFFile xdmf_file("../rect_channel.xdmf");
  xdmf_file.read(*mesh);
  auto V = std::make_shared<Poisson::FunctionSpace>(mesh);

  // Define boundary values
  auto u1 = std::make_shared<Constant>(0.0);
  auto u2 = std::make_shared<Constant>(18.0);

  // Define boundary regions
  auto boundary1 = std::make_shared<DirichletBoundary_1>();
  auto boundary2 = std::make_shared<DirichletBoundary_2>();
  
  // Create Dirichlet boundaries
  DirichletBC bc1(V, u1, boundary1);
  DirichletBC bc2(V, u2, boundary2);

  // Join all boundary conditions
  std::vector<const DirichletBC*> bcs = {&bc1, &bc2};

  // Define variational forms
  Poisson::BilinearForm a(V, V);
  Poisson::LinearForm L(V);
  auto f = std::make_shared<Source>();
  auto g = std::make_shared<dUdN>();
  L.f = f;
  L.g = g;

  // Compute solution
  Function u(V);
  solve(a == L, u, bcs);

  // Save solution in VTK format
  File file("u.pvd");
  file << u;

  return 0;
}
