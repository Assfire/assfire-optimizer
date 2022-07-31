cc_library(
    name = "assfire_optimizer_cc_worker_lib",
    srcs = [
        "assfire/optimizer/worker/HeartbeatPublisherImpl.cpp",
        "assfire/optimizer/worker/ProgressPublisherImpl.cpp",
        "assfire/optimizer/worker/StatusPublisherImpl.cpp",
        "assfire/optimizer/worker/TaskSignalListenerImpl.cpp",
        "assfire/optimizer/worker/Worker.cpp",
        "assfire/optimizer/worker/WorkerSolutionPublisherImpl.cpp",
        "assfire/optimizer/worker/WorkerSolutionPublisherProvider.cpp",
    ],
    hdrs = [
        "assfire/optimizer/worker/Exceptions.hpp",
        "assfire/optimizer/worker/HeartbeatPublisher.hpp",
        "assfire/optimizer/worker/HeartbeatPublisherImpl.hpp",
        "assfire/optimizer/worker/ProgressPublisher.hpp",
        "assfire/optimizer/worker/ProgressPublisherImpl.hpp",
        "assfire/optimizer/worker/StatusPublisher.hpp",
        "assfire/optimizer/worker/StatusPublisherImpl.hpp",
        "assfire/optimizer/worker/TaskProvider.hpp",
        "assfire/optimizer/worker/TaskSignal.hpp",
        "assfire/optimizer/worker/TaskSignalListener.hpp",
        "assfire/optimizer/worker/TaskSignalListenerImpl.hpp",
        "assfire/optimizer/worker/Worker.hpp",
        "assfire/optimizer/worker/WorkerSolutionPublisher.hpp",
        "assfire/optimizer/worker/WorkerSolutionPublisherImpl.hpp",
        "assfire/optimizer/worker/WorkerSolutionPublisherProvider.hpp",
        "assfire/optimizer/worker/WorkerTask.hpp",
    ],
    deps = [
        "//engine/cpp:assfire_optimizer_cc_engine",
        "//worker/proto:assfire_optimizer_worker_cc_proto",
        "@com_github_assfire_assfire_messenger//api/cpp:assfire_messenger_cc_api",
    ],
)

cc_binary(
    name = "assfire_optimizer_cc_worker",
    srcs = ["assfire/optimizer/worker/main.cpp"],
    deps = [
        ":assfire_optimizer_cc_worker_lib",
        "@com_github_assfire_assfire_logger//impl/cpp:assfire_logger_cc_impl_spdlog",
    ],
)
