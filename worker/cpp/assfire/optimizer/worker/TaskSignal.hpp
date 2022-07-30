#pragma once

namespace assfire::optimizer {
    class TaskSignal {
      public:
        enum class Type { START, CANCEL };

        Type type() const {
            return _type;
        }

        const std::string& task_id() const {
            return _task_id;
        }

      private:
        Type _type;
        std::string _task_id;
    };
} // namespace assfire::optimizer