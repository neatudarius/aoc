#include "task_runner.h"

struct Task {
    std::vector<std::vector<std::string>> forms;

    void read() {
        std::string line;
        while (std::getline(std::cin, line)) {
            std::vector<std::string> form;
            while (!line.empty()) {
                if (line.back() == '\n') {
                    line.pop_back();
                }
                form.push_back(line);

                std::getline(std::cin, line);
            }

            forms.emplace_back(std::move(form));
        }
    }

    auto compute() {
        auto cnt_any = std::accumulate(std::begin(forms), std::end(forms), 0, [](auto sum, const auto& form) {
            std::set<char> qs;
            std::for_each(std::begin(form), std::end(form),
                [&](const auto& line) { qs.insert(std::begin(line), std::end(line)); });

            return sum + qs.size();
        });

        auto cnt_all = std::accumulate(std::begin(forms), std::end(forms), 0, [](auto sum, const auto& form) {
            std::set<char> qs;
            for (auto c = 'a'; c <= 'z'; ++c) {
                qs.insert(c);
            }

            std::for_each(std::begin(form), std::end(form), [&](const auto& line) {
                std::set<char> line_set{std::begin(line), std::end(line)};

                std::set<char> i;
                std::set_intersection(std::begin(qs), std::end(qs), std::begin(line_set), std::end(line_set),
                    std::inserter(i, std::end(i)));

                qs = std::move(i);
            });

            return sum + qs.size();
        });

        return std::pair{
            cnt_any,
            cnt_all,
        };
    }

    void print(const auto& result) {
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
