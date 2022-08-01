load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "com_google_protobuf",
    sha256 = "ca983c9d2c8f8c935513642bcc4b2cbc64e4046e0bb16bf2ff893128577ece8c",
    strip_prefix = "protobuf-21.2",
    url = "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v21.2.tar.gz",
)

http_archive(
    name = "io_bazel_rules_go",
    sha256 = "685052b498b6ddfe562ca7a97736741d87916fe536623afb7da2824c0211c369",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.33.0/rules_go-v0.33.0.zip",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.33.0/rules_go-v0.33.0.zip",
    ],
)

git_repository(
    name = "upb",
    commit = "de3b396bd88afc8104bcb12b8897b9fd7f3220c1",
    remote = "https://github.com/protocolbuffers/upb",
    shallow_since = "1641840631 -0800",
)

git_repository(
    name = "com_google_googleapis",
    commit = "4753861dfd2bd3463b263fcda4074a3c92c3bb3d",
    remote = "https://github.com/googleapis/googleapis",
)

http_archive(
    name = "rules_proto_grpc",
    sha256 = "8383116d4c505e93fd58369841814acc3f25bdb906887a2023980d8f49a0b95b",
    strip_prefix = "rules_proto_grpc-4.1.0",
    url = "https://github.com/rules-proto-grpc/rules_proto_grpc/archive/refs/tags/4.1.0.tar.gz",
)

http_archive(
    name = "io_bazel_rules_python",
    sha256 = "a3a6e99f497be089f81ec082882e40246bfd435f52f4e82f37e89449b04573f6",
    strip_prefix = "rules_python-0.10.2",
    url = "https://github.com/bazelbuild/rules_python/archive/refs/tags/0.10.2.tar.gz",
)

http_archive(
    name = "com_google_googletest",
    sha256 = "ab78fa3f912d44d38b785ec011a25f26512aaedc5291f51f3807c592b506d33a",
    strip_prefix = "googletest-58d77fa8070e8cec2dc1ed015d66b454c8d78850",
    urls = ["https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip"],
)

http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "b1e80761a8a8243d03ebca8845e9cc1ba6c82ce7c5179ce2b295cd36f7e394bf",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.25.0/rules_docker-v0.25.0.tar.gz"],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

go_rules_dependencies()

go_register_toolchains(version = "1.18.3")

http_archive(
    name = "bazel_gazelle",
    sha256 = "501deb3d5695ab658e82f6f6f549ba681ea3ca2a5fb7911154b5aa45596183fa",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.26.0/bazel-gazelle-v0.26.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.26.0/bazel-gazelle-v0.26.0.tar.gz",
    ],
)

http_archive(
    name = "rules_cc",
    sha256 = "9a446e9dd9c1bb180c86977a8dc1e9e659550ae732ae58bd2e8fd51e15b2c91d",
    strip_prefix = "rules_cc-262ebec3c2296296526740db4aefce68c80de7fa",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/262ebec3c2296296526740db4aefce68c80de7fa.zip"],
)

git_repository(
    name = "com_github_assfire_assfire_router",
    commit = "9a4acb68ef4023fca3ade8342f8cd4b2949b7958",
    remote = "https://github.com/Assfire/assfire-router.git",
    shallow_since = "1658053260 +0300",
)

git_repository(
    name = "com_github_assfire_assfire_logger",
    commit = "5fd0492c148a4c677a73e86355c9f54f08bf538a",
    remote = "https://github.com/Assfire/assfire-logger.git",
    shallow_since = "1659044522 +0300",
)

git_repository(
    name = "com_github_assfire_assfire_messenger",
    commit = "ddedf101a2a330ceb2df8e596ab8ca1a94772c3a",
    remote = "https://github.com/Assfire/assfire-messenger.git",
    shallow_since = "1659383642 +0300",
)

load("@com_github_assfire_assfire_logger//:bazel/dependencies.bzl", "assfire_logger_dependencies_spdlog")

assfire_logger_dependencies_spdlog("@com_github_assfire_assfire_logger")

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

gazelle_dependencies()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_repos", "rules_proto_grpc_toolchains")

rules_proto_grpc_toolchains()

rules_proto_grpc_repos()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

load("@rules_proto_grpc//cpp:repositories.bzl", "cpp_repos")

cpp_repos()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load(
    "@io_bazel_rules_docker//cc:image.bzl",
    _cc_image_repos = "repositories",
)

_cc_image_repos()
