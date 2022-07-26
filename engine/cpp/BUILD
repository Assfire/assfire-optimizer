cc_library(
    name = "assfire_optimizer_cc_engine",
    srcs = [
        "assfire/optimizer/engine/BasicOptimizationStrategyProvider.cpp",
        "assfire/optimizer/engine/EngineSession.cpp",
        "assfire/optimizer/engine/RouteOptimizerEngine.cpp",
    ],
    hdrs = [
        "assfire/optimizer/engine/BasicOptimizationStrategyProvider.hpp",
        "assfire/optimizer/engine/EngineSession.hpp",
        "assfire/optimizer/engine/OptimizationContext.hpp",
        "assfire/optimizer/engine/OptimizationError.hpp",
        "assfire/optimizer/engine/OptimizationStrategy.hpp",
        "assfire/optimizer/engine/OptimizationStrategyProvider.hpp",
        "assfire/optimizer/engine/ProgressTracker.hpp",
        "assfire/optimizer/engine/RouteOptimizerEngine.hpp",
        "assfire/optimizer/engine/SessionStateError.hpp",
        "assfire/optimizer/engine/SolutionPublisher.hpp",
        "assfire/optimizer/engine/StateManager.hpp",
    ],
    deps = [
        "//api/cpp:assfire_optimizer_cc_api",
        "@assfire_router//api/cpp:assfire_router_cc_api",
    ],
)
