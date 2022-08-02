cc_library(
    name = "assfire_optimizer_cc_engine",
    srcs = [
        "assfire/optimizer/engine/BasicOptimizationStrategyProvider.cpp",
        "assfire/optimizer/engine/DiscardingStateManagerProvider.cpp",
        "assfire/optimizer/engine/EngineSession.cpp",
        "assfire/optimizer/engine/InMemorySolutionPublisherProvider.cpp",
        "assfire/optimizer/engine/LoggingProgressTrackerProvider.cpp",
        "assfire/optimizer/engine/RouteOptimizerEngine.cpp",
    ],
    hdrs = [
        "assfire/optimizer/engine/BasicOptimizationStrategyProvider.hpp",
        "assfire/optimizer/engine/DiscardingStateManagerProvider.hpp",
        "assfire/optimizer/engine/EngineSession.hpp",
        "assfire/optimizer/engine/InMemorySolutionPublisherProvider.hpp",
        "assfire/optimizer/engine/LoggingProgressTrackerProvider.hpp",
        "assfire/optimizer/engine/OptimizationContext.hpp",
        "assfire/optimizer/engine/OptimizationError.hpp",
        "assfire/optimizer/engine/OptimizationStrategy.hpp",
        "assfire/optimizer/engine/OptimizationStrategyProvider.hpp",
        "assfire/optimizer/engine/ProgressTracker.hpp",
        "assfire/optimizer/engine/ProgressTrackerProvider.hpp",
        "assfire/optimizer/engine/RouteOptimizerEngine.hpp",
        "assfire/optimizer/engine/SessionStateError.hpp",
        "assfire/optimizer/engine/SolutionPublisher.hpp",
        "assfire/optimizer/engine/SolutionPublisherProvider.hpp",
        "assfire/optimizer/engine/StateManager.hpp",
        "assfire/optimizer/engine/StateManagerProvider.hpp",
    ],
    include_prefix = "assfire/optimizer/engine/",
    strip_include_prefix = "assfire/optimizer/engine/",
    visibility = ["//visibility:public"],
    deps = [
        "//api/cpp:assfire_optimizer_cc_api",
        "@com_github_assfire_assfire_logger//api/cpp:assfire_logger_cc_api",
        "@com_github_assfire_assfire_router//api/cpp:assfire_router_cc_api",
    ],
)

cc_library(
    name = "assfire_optimizer_cc_engine_mock",
    hdrs = [
        "assfire/optimizer/engine/test/MockOptimizationStrategy.hpp",
        "assfire/optimizer/engine/test/MockProgressTracker.hpp",
        "assfire/optimizer/engine/test/MockSolutionPublisher.hpp",
        "assfire/optimizer/engine/test/MockStateManager.hpp",
    ],
    include_prefix = "assfire/optimizer/engine/test/",
    strip_include_prefix = "assfire/optimizer/engine/test/",
    visibility = ["//visibility:public"],
    deps = [
        ":assfire_optimizer_cc_engine",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "assfire_optimizer_cc_engine_test",
    srcs = [
        "assfire/optimizer/engine/test/EngineSession_Test.cpp",
    ],
    deps = [
        ":assfire_optimizer_cc_engine_mock",
    ],
)
