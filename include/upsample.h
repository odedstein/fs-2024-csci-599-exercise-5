#ifndef UPSAMPLE_H
#define UPSAMPLE_H
#include <Eigen/Core>
#include <Eigen/Sparse>
/// Subdivide without moving vertices: Given the triangle mesh [V, F],
/// where n_verts = V.rows(), computes newV and a sparse matrix S s.t.
/// [newV, newF] is the subdivided mesh where newV = S*V.
///
/// @param[in] n_verts  an integer (number of mesh vertices)
/// @param[in] F  an m by 3 matrix of integers of triangle faces
/// @param[out] S  a sparse matrix (will become the subdivision matrix)
/// @param[out] newF  a matrix containing the new faces
void upsample(
  const int n_verts,
  const Eigen::MatrixXi & F,
  Eigen::SparseMatrix<double> & S,
  Eigen::MatrixXi& newF);
#endif
