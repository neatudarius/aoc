#include "task_runner.h"

struct Task {
    std::vector<std::string> passwords;

    void read() {
        std::string line;
        while (std::getline(std::cin, line)) {
            std::string password;
            while (!line.empty()) {
                if (line.back() == '\n') {
                    line.pop_back();
                }
                password = fmt::format("{:s} {:s} ", password, line);

                std::getline(std::cin, line);
            }

            passwords.emplace_back(std::move(password));
        }
    }

    auto match(const auto& pattern, const auto& password) {
        return std::regex_search(password, std::regex{pattern, std::regex::extended});
    }

    auto is_valid(const auto& password) {
        static const auto rgs = std::array{
            "byr:((19[2-9][0-9])|(200[0-2]))",
            "iyr:(20(1[0-9])|(2020))",
            "eyr:(20(2[0-9])|(2030))",
            "hgt:((((1[5-8][0-9])|(19[0-3]))cm)|(((59)|(6[0-9])|(7[0-6]))in))",
            "hcl:#[0-9a-f]{6}",
            "ecl:((amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth))",
            "pid:[0-9]{9}",
        }; // cid it's optional

        auto exist_values = std::all_of(std::begin(rgs), std::end(rgs), [&](auto& rg) {
            auto pattern = std::string{rg}.substr(0, 3);
            return match(pattern, password);
        });
        auto valid_values = exist_values && std::all_of(std::begin(rgs), std::end(rgs), [&](auto& rg) {
            auto pattern = std::string{rg} + "[ \n]+";
            return match(pattern, password);
        });

        return std::pair{exist_values, valid_values};
    }

    auto compute() {
        auto cnt_values = 0, cnt_valid_values = 0;
        for (const auto& password : passwords) {
            auto [exist_values, valid_values] = is_valid(password);
            cnt_values += exist_values;
            cnt_valid_values += valid_values;
        }

        return std::pair{
            cnt_values, // #valid passwords: passwords with required fields
            cnt_valid_values, // #valid passwords: passwords with required & valid fields
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
