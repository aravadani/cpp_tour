load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    srcs = glob(["**/*.cc"]),
    deps = [
        "//src/lib:SolutionLib",
        "//src/lib:vector_union_lib",
        "//src/lib/sort:SortLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "vector_union_test",
    deps = [
        "//src/lib:SolutionLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "sort_test",
    deps = [
        "//src/lib/sort:SortLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "solution_test",
    deps = [
        "//src/lib:SolutionLib",
        "@googletest//:gtest_main",
    ],
)
