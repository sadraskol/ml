#ifndef _ERROR_EVALUATOR_H_
#define _ERROR_EVALUATOR_H_

#include <vector>

namespace neurons {

  class ErrorEvaluator {
    public:
      ErrorEvaluator(const std::vector<double>& _expected,
          const std::vector<double>& _actual) : expected(_expected),
          actual(_actual) {}
      virtual ~ErrorEvaluator() {}

      const std::vector<double> evaluate() const;
      bool isSuccess() const;
    private:
      ErrorEvaluator() {}
      const std::vector<double> expected;
      const std::vector<double> actual;
  };

} // namespace neurons

#endif // _ERROR_EVALUATOR_H_
