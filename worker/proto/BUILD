load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")

proto_library(
    name = "assfire_optimizer_worker_proto",
    srcs = ["assfire/optimizer/worker/worker.proto"],
    import_prefix = "assfire/optimizer/worker/",
    strip_import_prefix = "assfire/optimizer/worker/",
    visibility = ["//visibility:public"],
    deps = ["//api/proto:assfire_optimizer_proto"],
)

cpp_proto_library(
    name = "assfire_optimizer_worker_cc_proto",
    protos = [
        ":assfire_optimizer_worker_proto",
        "//api/proto:assfire_optimizer_proto",
    ],
    visibility = ["//visibility:public"],
)
