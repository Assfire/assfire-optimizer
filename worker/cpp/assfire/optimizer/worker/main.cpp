#include "assfire/logger/impl/spdlog/SpdlogLoggerFactory.hpp"

int main() {
    assfire::logger::SpdlogLoggerFactory::register_static_factory();

    return 0;
}