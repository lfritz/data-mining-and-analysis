#pragma once

// Some general-purpose algorithms.

// Given a range of values and a function, return the value for which the
// function's return value is maximal.
//
// Example:
// arg_max(-5, 5, [](double x) { return -x*x; });
// returns 0
template <typename I, typename UnaryFunction>
I arg_max(I first, I last, UnaryFunction f) {
    I best = first;
    I i = first;
    auto best_value = f(i);
    for (++i; i != last; ++i) {
        auto value = f(i);
        if (value > best_value) {
            best_value = value;
            best = i;
        }
    }
    return best;
}

// Given a range of values and a function, return the value for which the
// function's return value is minimal.
//
// Example:
// arg_min(-5, 5, [](double x) { return x*x; });
// returns 0
template <typename I, typename UnaryFunction>
I arg_min(I first, I last, UnaryFunction f) {
    I best = first;
    I i = first;
    auto best_value = f(i);
    for (++i; i != last; ++i) {
        auto value = f(i);
        if (value < best_value) {
            best_value = value;
            best = i;
        }
    }
    return best;
}
