load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library", "cpp_proto_library")

proto_library(
    name = "assfire_optimizer_proto",
    srcs = ["assfire/api/v1/optimizer/optimizer.proto"],
    import_prefix = "assfire/api/v1/optimizer/",
    strip_import_prefix = "assfire/api/v1/optimizer/",
    visibility = ["//visibility:public"]
)

cpp_proto_library(
    name = "assfire_optimizer_cc_proto",
    protos = [
        ":assfire_optimizer_proto"
    ],
    visibility = ["//visibility:public"],
)

cpp_grpc_library(
    name = "assfire_optimizer_cc_grpc",
    protos = [
        ":assfire_optimizer_proto",
    ],
    visibility = ["//visibility:public"],
    deps = [":assfire_optimizer_cc_proto"],
)
