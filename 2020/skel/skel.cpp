#include "task_runner.h"

struct Task {
    int n;
    std::vector<int> v;

    auto solve() {
        read();
        print(compute());
    }

    void read() {
        // TODO: read from STDIN
        int x;
        while (std::cin >> x) {
            ++n;
            v.push_back(x);
        }
    }

    std::pair<uint64_t, uint64_t> compute() {
        // TODO: computes results
        return {
            1ULL, // TODO: change me
            1ULL, // TODO: change me
        };
    }

    void print(const auto& result) {
        // TODO: print results to STDOUT
        std::cout << result.first << "\n";
        std::cout << result.second << "\n";
    }
};

int main() {
    TaskRunner<Task>::create()->set_stream("in", std::cin).solve();
    // TaskRunner<Task>::create()->set_stream("in", std::cin).set_stream("out", std::cout).solve();
    return 0;
}
