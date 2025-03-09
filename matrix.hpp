#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

class Matrix {
 public:
  std::vector<std::vector<double>> data;

  Matrix(const std::vector<std::vector<double>>& data) : data(data) {}

  Matrix() {}
  void AddRow(const std::vector<double>& row) {
    if (data.empty() || row.size() == data[0].size()) {
      data.push_back(row);
    } else {
      throw std::invalid_argument(
          "Error: Row size does not match matrix column size.");
    }
  }

  void MergeMatrix(const Matrix& other) {
    if (data[0].size() != other.data[0].size()) {
      throw std::invalid_argument(
          "Error: Matrices should have the same number of columns for "
          "merging.");
    }

    data.insert(data.end(), other.data.begin(), other.data.end());
  }

  int CalculateRankUsingMinors() {
    int rank = 0;
    int rows = data.size();
    int cols = data[0].size();

    for (int i = 0; i < std::min(rows, cols); i++) {
      if (data[i][i] != 0) {
        rank++;
        for (int j = i + 1; j < rows; j++) {
          double factor = data[j][i] / data[i][i];
          for (int k = i; k < cols; k++) {
            data[j][k] -= factor * data[i][k];
          }
        }
      }
    }

    return rank;
  }

  std::vector<double> SolveLinearSystem() {
    int rows = data.size();
    int cols = data[0].size() - 1;

    for (int i = 0; i < rows; i++) {
      if (data[i][i] == 0) {
        int nonZeroRow = -1;
        for (int j = i + 1; j < rows; j++) {
          if (data[j][i] != 0) {
            nonZeroRow = j;
            break;
          }
        }
        if (nonZeroRow != -1) {
          std::swap(data[i], data[nonZeroRow]);
        } else {
          throw std::runtime_error("No unique solution exists");
        }
      }

      double divisor = data[i][i];
      for (int k = i; k <= cols; k++) {
        data[i][k] /= divisor;
      }

      for (int j = 0; j < rows; j++) {
        if (j != i) {
          double factor = data[j][i];
          for (int k = i; k <= cols; k++) {
            data[j][k] -= factor * data[i][k];
          }
        }
      }
    }

    std::vector<double> solutions(rows);
    for (int i = 0; i < rows; i++) {
      solutions[i] = data[i][cols];
    }

    return solutions;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data) {
      for (const auto& element : row) {
        os << element << "\t";
      }
      os << std::endl;
    }
    return os;
  }

  const double& operator()(size_t i, size_t j) const { return data[i][j]; }
};

#endif  // MATRIX_HPP