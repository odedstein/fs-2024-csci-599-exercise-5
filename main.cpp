#include "upsample.h"
#include "loop.h"
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/parula.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  // Load input meshes
  Eigen::MatrixXd V, OV;
  Eigen::MatrixXi F, OF;
  double lambda = 1e-5;
  igl::read_triangle_mesh(
    (argc>1?argv[1]:"../data/penguin.obj"),V,F);
  OV = V;
  OF = F;

  // Some function to upsample
  Eigen::MatrixXd G = OV.col(1).array() + 0.5*OV.col(2).array().pow(2);
  Eigen::MatrixXd OG = G;
  igl::opengl::glfw::Viewer viewer;
  std::cout<<R"(
  U,u  upsample mesh
  S,s  Loop subdivide mesh
  R,r  reset mesh geometry and data
  L    lighting
)";
  const auto & reset = [&]()
  {
    V = OV;
    F = OF;
    G = OG;
  };
  const auto & update = [&]()
  {
    if((V.array() != V.array()).any())
    {
      std::cout<<"Mesh degenerated. Better reset"<<std::endl;
    }
    viewer.data().clear();
    viewer.data().set_mesh(V,F);
    viewer.data().compute_normals();
    Eigen::MatrixXd C;
    igl::parula(G,G.minCoeff(),G.maxCoeff(),C);
    viewer.data().set_colors(C);
  };
  viewer.callback_key_pressed = 
    [&](igl::opengl::glfw::Viewer &, unsigned int key, int)
  {
    Eigen::SparseMatrix<double> S;
    switch(key)
    {
      case 'U':
      case 'u':
        //////////////////////////////////////////////////////////////////////
        // Upsample mesh
        //////////////////////////////////////////////////////////////////////
        upsample(V.rows(), Eigen::MatrixXi(F), S, F);
        V = S*V;
        G = S*G;
        break;
      case 'S':
      case 's':
        //////////////////////////////////////////////////////////////////////
        // Loop subdivide mesh
        //////////////////////////////////////////////////////////////////////
        loop(V.rows(), Eigen::MatrixXi(F), S, F);
        V = S*V;
        G = S*G;
        break;
      case 'L':
        // Toggle lighting
        viewer.core().lighting_factor = 1.0- viewer.core().lighting_factor;
        break;
      case 'R':
      case 'r':
        reset();
        break;
      default:
        return false;
    }
    update();
    return true;
  };

  update();
  viewer.launch();

  return EXIT_SUCCESS;
}
