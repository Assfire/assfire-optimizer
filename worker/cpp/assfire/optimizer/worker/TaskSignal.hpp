#pragma once

#include <string>

namespace assfire::optimizer {
    class TaskSignal {
      public:
        enum class Type { START, CANCEL, IGNORE };

        TaskSignal() : _type(Type::START) {}
        TaskSignal(Type type, const std::string& id) : _type(type), _task_id(id) {}
        TaskSignal(const TaskSignal& rhs) = default;
        TaskSignal(TaskSignal&& rhs)      = default;

        TaskSignal& operator=(const TaskSignal& rhs) = default;
        TaskSignal& operator=(TaskSignal&& rhs) = default;

        bool operator==(const TaskSignal& rhs) const = default;

        Type type() const {
            return _type;
        }

        void set_type(Type type) {
            _type = type;
        }

        const std::string& task_id() const {
            return _task_id;
        }

        void set_task_id(std::string task_id) {
            _task_id = std::move(task_id);
        }

      private:
        Type _type;
        std::string _task_id;
    };
} // namespace assfire::optimizer