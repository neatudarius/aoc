#include "task_runner.h"

struct Task {
    int n;
    std::vector<int> v;

    void read() {
        // TODO: read from STDIN
        int x;
        while (std::cin >> x) {
            ++n;
            v.push_back(x);
        }
    }

    auto compute() {
        // TODO: computes results
        return std::pair{
            1ULL, // TODO: change me
            "22", // TODO: change me
        };
    }

    void print(const auto& result) {
        // TODO: print results to STDOUT
        std::cout << result.first << "\n";
        std::cout << result.second << "\n";
    }

    auto solve() {
        read();
        print(compute());
    }
};

int main() {
    TaskRunner<Task>::create()->set_stream("in", std::cin).solve();
    // TaskRunner<Task>::create()->set_stream("in", std::cin).set_stream("out", std::cout).solve();
    return 0;
}
