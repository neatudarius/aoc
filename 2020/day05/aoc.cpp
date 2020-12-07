#include "task_runner.h"

struct Task {
    std::vector<std::string> tickets;

    void read() {
        std::string line;
        while (std::getline(std::cin, line)) {
            tickets.push_back(line);
        }
    }

    auto str2num(const auto& str) {
        long long x = 0;
        for (size_t i = 0; i < str.size(); ++i) {
            long long b = (str.size() - i) - 1;
            x |= (str[i] == 'L' ? 0 : str[i] == 'F' ? 0 : 1) * (1LL << b);
        }
        return x;
    }

    long long get_row(const auto& ticket) { return str2num(ticket.substr(0, 7)); }

    long long get_col(const auto& ticket) { return str2num(ticket.substr(7, 3)); }

    long long get_id(const auto& ticket) { return 1LL * get_row(ticket) * 8 + get_col(ticket); }

    auto compute() {
        std::vector<int> ids;
        std::ranges::transform(tickets, std::back_inserter(ids), [&](const auto& t) { return get_id(t); });

        auto [min_ticket_id, max_ticket_id] = std::ranges::minmax_element(ids);
        auto max_id = *max_ticket_id;

        auto min = *min_ticket_id;
        auto max = *max_ticket_id;
        auto sum = std::ranges::accumulate(ids, 0, std::plus<int>());
        auto my_id = max * (max + 1) / 2 - (min - 1) * min / 2 - sum;

        return std::pair{
            max_id,
            my_id,
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
