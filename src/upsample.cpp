#include "upsample.h"
#include <vector>

void upsample(
  const int n_verts,
  const Eigen::MatrixXi & F,
  Eigen::SparseMatrix<double> & S,
  Eigen::MatrixXi& newF)
{
  // Replace with your code
  newF = F;
  std::vector<Eigen::Triplet<double> > tripletList;
  for(int i=0; i<n_verts; ++i) {
    tripletList.emplace_back(i, i, 1.);
  }
  S = Eigen::SparseMatrix<double>(n_verts, n_verts);
  S.setFromTriplets(tripletList.begin(), tripletList.end());
}

