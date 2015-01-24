#include <catch.hpp>

#include <algorithm.h>

using std::vector;

TEST_CASE("arg_max and arg_min work for a polynomial") {
    auto f = [](double x) {
        return (x+4)*(x+1)*(x-2);
    };

    CHECK(arg_max( -4,  3, f) == -3);
    CHECK(arg_max( -3,  3, f) == -3);
    CHECK(arg_max(-10, -2, f) == -3);

    CHECK(arg_min(-4, 3, f) == 1);
    CHECK(arg_min( 1, 3, f) == 1);
    CHECK(arg_min(-4, 2, f) == 1);
}
