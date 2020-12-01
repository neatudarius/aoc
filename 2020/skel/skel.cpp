#include "task_runner.h"

struct Task {
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

    int compute() {
        // TODO: computes results
        return v.size();
    }

    void print(const auto& result) {
        // TODO: print results to STDOUT
        std::cout << result << "\n";
    }
};

int main() {
    // TaskRunner<Task>::create()->set_stream("in", std::cin).solve();
    // TaskRunner<Task>::create()->set_stream("in", std::cin).set_stream("out", std::cout).solve();
    return 0;
}
