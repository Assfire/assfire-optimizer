cc_library(
    name = "assfire_optimizer_cc_worker_lib",
    srcs = [
        "assfire/optimizer/worker/MessageProcessor.cpp",
        "assfire/optimizer/worker/Worker.cpp",
    ],
    hdrs = [
        "assfire/optimizer/worker/Exceptions.hpp",
        "assfire/optimizer/worker/MessageProcessor.hpp",
        "assfire/optimizer/worker/SupervisorChannel.hpp",
        "assfire/optimizer/worker/SupervisorEnvelope.hpp",
        "assfire/optimizer/worker/Worker.hpp",
    ],
    deps = ["//engine/cpp:assfire_optimizer_cc_engine"],
)

cc_binary(
    name = "assfire_optimizer_cc_worker",
    srcs = ["assfire/optimizer/worker/main.cpp"],
    deps = [
        ":assfire_optimizer_cc_worker_lib",
        "@com_github_assfire_assfire_logger//impl/cpp:assfire_logger_cc_impl_spdlog",
    ],
)
