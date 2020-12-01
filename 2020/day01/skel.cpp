#include "task_runner.h"

struct Task {
    static constexpr auto kSum = 2020;

    std::vector<int> v;

    auto solve() {
        read();
        print(compute());
    }

    void read() {
        // TODO: read from STDIN
        int x;
        while (std::cin >> x) {
            v.push_back(x);
        }
    }

    std::pair<int, int> compute() {
        // TODO: computes results

        auto solve2 = [](const auto& v) {
            auto sol = -1LL;
            for (auto i = 0u; i < v.size(); ++i) {
                for (auto j = i; j < v.size(); ++j) {
                    if (v[i] + v[j] == kSum) {
                        sol = std::max(sol, 1LL * v[i] * v[j]);
                    }
                }
            }
            return sol;
        };

        auto solve3 = [](const auto& v) {
            auto sol = -1LL;
            for (auto i = 0u; i < v.size(); ++i) {
                for (auto j = i; j < v.size(); ++j) {
                    for (auto k = j; k < v.size(); ++k) {
                        if (v[i] + v[j] + v[k] == kSum) {
                            sol = std::max(sol, 1LL * v[i] * v[j] * v[k]);
                        }
                    }
                }
            }
            return sol;
        };

        return {solve2(v), solve3(v)};
    }

    void print(const auto& result) {
        // TODO: print results to STDOUT
        std::cout << result.first << " " << result.second << "\n";
    }
};

int main() {
    TaskRunner<Task>::create()->set_stream("in", std::cin).solve();
    // TaskRunner<Task>::create()->set_stream("in", std::cin).set_stream("out", std::cout).solve();
    return 0;
}
