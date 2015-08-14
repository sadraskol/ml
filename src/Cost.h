#ifndef COST_H
#define COST_H
#include "Matrix.h"

namespace neurons {
  class Cost {
    public:
      static const Cost* newQuadratic();
      static const Cost* newCrossEntropy();

      virtual double cost(const Matrix& a, const Matrix& y) const = 0;
      virtual const Matrix delta(const Matrix& z, const Matrix& a, const Matrix& y) const = 0;
  };

  class QuadraticCost : public Cost {
    public:
      double cost(const Matrix& a, const Matrix& y) const;
      const Matrix delta(const Matrix& z, const Matrix& a, const Matrix& y) const;
  };

  class CrossEntropyCost : public Cost {
    public:
      double cost(const Matrix& a, const Matrix& y) const;
      const Matrix delta(const Matrix& z, const Matrix& a, const Matrix& y) const;
  };
} // namespace neurons

#endif
