load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository",)
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive",)

def g3log_repositories():
    maybe(
        new_git_repository,
        name = "net_zlib_zlib",
        build_file = "@com_github_lyu_rules_g3log//bazel/third_party:zlib.BUILD.bazel",
        remote = "https://github.com/madler/zlib.git",
        commit = "04f42ceca40f73e2978b50e93806c2a18c1281fc",
        shallow_since = "1665637615 -0700",
        # branch = "master",
    )
    maybe(
        new_git_repository,
        name = "g3log",
        build_file = "@com_github_lyu_rules_g3log//bazel/third_party:g3log.BUILD.bazel",
        remote = "https://github.com/KjellKod/g3log.git",
        commit = "dbd3d74a39d3ac09b85a124f6b2b2e12495ac9f8",
        shallow_since = "1669785395 -0700",
        # branch = "master",
    )
    maybe(
        new_git_repository,
        name = "g3sinks",
        build_file = "@com_github_lyu_rules_g3log//bazel/third_party:g3sinks.BUILD.bazel",
        remote = "https://github.com/KjellKod/g3sinks.git",
        commit = "aee2a63c2c003a7808b2a04d347cd28c0a464202",
        shallow_since = "1669852770 -0700",
        # branch = "master",
    )
