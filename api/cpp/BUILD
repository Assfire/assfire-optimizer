cc_library(
    name = "assfire_optimizer_cc_api",
    srcs = ["assfire/optimizer/api/OptimizerApi.cpp"],
    hdrs = [
        "assfire/optimizer/api/BasePoint.hpp",
        "assfire/optimizer/api/GeoPoint.hpp",
        "assfire/optimizer/api/OptimizationStrategyId.hpp",
        "assfire/optimizer/api/Order.hpp",
        "assfire/optimizer/api/RouteOptimizer.hpp",
        "assfire/optimizer/api/Session.hpp",
        "assfire/optimizer/api/Solution.hpp",
        "assfire/optimizer/api/Task.hpp",
        "assfire/optimizer/api/TimeWindow.hpp",
        "assfire/optimizer/api/TransportProfileId.hpp",
        "assfire/optimizer/api/Trip.hpp",
        "assfire/optimizer/api/Vehicle.hpp",
        "assfire/optimizer/api/Waypoint.hpp",
    ],
    include_prefix = "assfire/optimizer/api",
    strip_include_prefix = "assfire/optimizer/api",
    visibility = ["//visibility:public"],
    deps = ["@com_google_absl//absl/time"],
)

cc_library(
    name = "assfire_optimizer_cc_api_mock",
    hdrs = [
        "assfire/optimizer/api/test/MockRouteOptimizer.hpp",
        "assfire/optimizer/api/test/MockSession.hpp",
    ],
    include_prefix = "assfire/optimizer/api/test",
    strip_include_prefix = "assfire/optimizer/api/test",
    visibility = ["//visibility:public"],
)
