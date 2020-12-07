#include "task_runner.h"

struct Task {
    int start;
    std::unordered_map<std::string, int> node2id;
    std::unordered_map<int, std::string> id2node;

    static constexpr auto NMAX = 100'000;
    std::vector<std::pair<int, int>> g[NMAX];
    std::vector<std::pair<int, int>> g_t[NMAX];

    void read() {
        int cnt = 0;
        auto get_node = [&](const auto& n) {
            if (node2id.find(n) != node2id.end()) {
                return node2id[n];
            }

            int id = ++cnt;
            node2id[n] = id;
            id2node[id] = n;
            return id;
        };

        start = get_node("shiny gold");

        std::string line;
        while (std::getline(std::cin, line)) {
            if (!line.empty()) {
                if (line.find("no other bags.") != line.npos) {
                    continue;
                }

                std::istringstream iss{line};

                std::string base_color1, base_color2;
                std::string bags, contain;
                iss >> base_color1 >> base_color2 >> bags >> contain;
                auto b = get_node(fmt::format("{} {}", base_color1, base_color2));

                int c;
                std::string dep_color1, dep_color2;
                while (iss >> c >> dep_color1 >> dep_color2 >> bags) {
                    auto d = get_node(fmt::format("{} {}", dep_color1, dep_color2));

                    g[b].emplace_back(c, d);
                    g_t[d].emplace_back(c, b);
                }
            }
        }
    }

    auto dfs(auto node, const auto& g, auto& visited, auto& cache) {
        if (visited[node]) {
            return std::pair{0, cache[node].second};
        }
        visited[node] = 1;

        return cache[node] = std::ranges::accumulate(g[node], std::pair{1, 0}, [&](auto sum, const auto& neigbour) {
            auto [c, id] = neigbour;
            auto [c1, c2] = dfs(id, g, visited, cache);
            return std::pair{
                sum.first + c1,
                sum.second + c * (1 + c2),
            };
        });
    }

    auto compute() {
        std::vector<bool> visited(NMAX, false);
        std::vector<bool> visited_t(NMAX, false);
        std::unordered_map<int, std::pair<int, int>> cache, cache_t;

        return std::pair{
            dfs(start, g_t, visited_t, cache_t).first - 1,
            dfs(start, g, visited, cache).second,
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
