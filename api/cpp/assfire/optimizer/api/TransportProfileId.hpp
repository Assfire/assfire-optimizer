#pragma once

#include <string>

namespace assfire::optimizer {
    class TransportProfileId {
      public:
        TransportProfileId() = default;
        explicit TransportProfileId(std::string value) : _value(std::move(value)) {}
        TransportProfileId(const TransportProfileId& rhs) = default;
        TransportProfileId(TransportProfileId&& rhs)      = default;

        TransportProfileId& operator=(const TransportProfileId& rhs) = default;
        TransportProfileId& operator=(TransportProfileId&& rhs) = default;

        bool operator==(const TransportProfileId& rhs) const = default;

        const std::string& value() const {
            return _value;
        }

      private:
        std::string _value;
    };
} // namespace assfire::optimizer