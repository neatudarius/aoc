#include "task_runner.h"

struct Task {
    auto solve() {
        read();
        print(compute());
    }

    std::vector<std::string> lines;

    void read() {
        std::string line;

        while (std::getline(std::cin, line)) {
            lines.emplace_back(line);
        }
        assert(lines.size() == 1000u);
    }

    std::pair<int, int> compute() {
        int cnt_policy1 = 0, cnt_policy2 = 0;

        for (const auto& line : lines) {
            std::stringstream ss(line);

            int lower = 0, upper = 0;
            char c, letter = ' ';
            std::string password = "";
            ss >> lower >> c >> upper >> letter >> c >> password;

            auto occ = std::count(password.begin(), password.end(), letter);
            if (lower <= occ && occ <= upper) {
                ++cnt_policy1;
            }

            lower--;
            upper--;
            int first_occ = (lower < (int)password.size() && password[lower] == letter);
            int last_occ = (upper < (int)password.size() && password[upper] == letter);
            if (first_occ ^ last_occ) {
                ++cnt_policy2;
            }
        }

        return {cnt_policy1, cnt_policy2};
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
