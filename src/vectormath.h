#pragma once

#include <cmath>
#include <vector>

inline std::vector<double> add(const std::vector<double>& x,
                               const std::vector<double>& y) {
    unsigned int n = x.size();
    std::vector<double> sum(n);
    for (unsigned int i = 0; i < n; ++i)
        sum[i] = x[i] + y[i];
    return sum;
}

inline std::vector<double> sum(const std::vector<std::vector<double>>& ps) {
    std::vector<double> s = ps[0];
    unsigned n = ps.size();
    for (unsigned i = 1; i < n; ++i)
        s = add(s, ps[i]);
    return s;
}

inline std::vector<double> subtract(const std::vector<double>& x,
                                    const std::vector<double>& y) {
    unsigned int n = x.size();
    std::vector<double> difference(n);
    for (unsigned int i = 0; i < n; ++i)
        difference[i] = x[i] - y[i];
    return difference;
}

inline void multiply(std::vector<double>& v, double x) {
    for (double& d : v)
        d *= x;
}

inline void divide(std::vector<double>& v, double x) {
    for (double& d : v)
        d /= x;
}

inline double norm(const std::vector<double>& x) {
    double a = 0.0;
    for (double d : x)
        a += d*d;
    return sqrt(a);
}

inline double distance(const std::vector<double>& x,
                       const std::vector<double>& y) {
    return norm(subtract(x, y));
}

inline double distance_squared(const std::vector<double>& x,
                               const std::vector<double>& y) {
    unsigned int n = x.size();
    double result = 0.0;
    for (unsigned i = 0; i < n; ++i) {
        double d = x[i] - y[i];
        result += d*d;
    }
    return result;
}