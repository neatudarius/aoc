#include "task_runner.h"

struct Task {
    int n, m;
    std::vector<std::vector<char>> a;

    auto solve() {
        read();
        print(compute());
    }

    void read() {
        n = 0;
        m = 0;

        std::string line;
        while (std::getline(std::cin, line)) {
            if (!m) {
                m = line.size();
            } else {
                assert(m == (int)line.size());
            }

            a.resize(++n);
            auto& last_row = a.back();
            last_row.insert(last_row.begin(), line.begin(), line.end());
        }
    }

    auto slope(int dy, int dx) {
        auto cnt = 0;

        int x = 0, y = 0;
        while (x < n && y < m) {
            x += dx;
            y += dy;

            if (x < n && y < m && a[x][y] == '#') {
                ++cnt;
            }
        }

        return cnt;
    }

    std::pair<uint64_t, uint64_t> compute() {
        int multiple = std::max(n, 100); // big enough
        for (int i = 0; i < n; ++i) {
            std::vector<char> new_row{};
            for (int k = 0; k < multiple; ++k) {
                new_row.insert(new_row.end(), a[i].begin(), a[i].end());
            }
            a[i] = new_row;
        }
        m *= multiple;

        return {
            1ULL * slope(3, 1),
            1ULL * slope(1, 1) * slope(3, 1) * slope(5, 1) * slope(7, 1) * slope(1, 2),
        };
    }

    void print(const auto& result) {
        std::cout << result.first << "\n";
        std::cout << result.second << "\n";
    }
};

int main() {
    TaskRunner<Task>::create()->set_stream("in", std::cin).solve();
    // TaskRunner<Task>::create()->set_stream("in", std::cin).set_stream("out", std::cout).solve();
    return 0;
}
