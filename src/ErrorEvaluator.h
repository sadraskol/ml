#ifndef _ERROR_EVALUATOR_H_
#define _ERROR_EVALUATOR_H_

#include <vector>

namespace neurons {

  class ErrorEvaluator {
    public:
      ErrorEvaluator() {}
      virtual ~ErrorEvaluator() {}

      const std::vector<double> evaluate(const std::vector<double>& expected,
          const std::vector<double>& actual) const;

      bool isSuccess(const std::vector<double>& expected,
          const std::vector<double>& actual) const;
  };

} // namespace neurons

#endif // _ERROR_EVALUATOR_H_
