#include "task_runner.h"

struct Task {
    using password_t = std::vector<std::pair<std::string, std::string>>;
    std::vector<password_t> passwords;

    void read() {
        static const auto line2password = [](const auto& line, auto& password) {
            std::istringstream iss{line};
            std::string token{};
            while (std::getline(iss, token, ' ')) {
                auto pos = token.find_first_of(":");
                auto key = token.substr(0, pos);
                auto value = token.substr(pos + 1);

                password.emplace_back(key, value);
            }
        };

        std::string line;
        while (std::getline(std::cin, line)) {
            password_t password;
            while (!line.empty()) {
                line2password(line, password);
                std::getline(std::cin, line);
            }

            passwords.emplace_back(std::move(password));
        }
    }

    auto is_valid(const auto& password) {
        static const auto each_char = [](const auto& str, auto num_chars, auto validator) {
            return str.size() == (size_t)num_chars && std::ranges::all_of(str, validator);
        };

        static const auto num_in_range = [](const auto& num_str, auto num_digits, auto lower, auto upper) {
            if (!each_char(num_str, num_digits, &isdigit)) {
                return false;
            }

            long long value;
            auto [p, ec] = std::from_chars(num_str.data(), num_str.data() + num_str.size(), value);
            if (ec != std::errc()) {
                return false;
            }

            return lower <= value && value <= upper;
        };

        static const std::map<std::string_view, std::function<bool(std::string_view)>> field2validator = {
            {
                "byr",
                // num in [1920, 2002]
                [](const auto& value) { return num_in_range(value, 4, 1920, 2002); },
            },
            {
                "iyr",
                // num in [2010, 2020]
                [](const auto& value) { return num_in_range(value, 4, 2010, 2020); },
            },
            {
                "eyr",
                // num in [2020, 2030]
                [](const auto& value) { return num_in_range(value, 4, 2020, 2030); },
            },
            {
                "hgt",
                // ${num}cm (num in [150,193])
                // ${num}in (num in [59, 76])
                [](const auto& value) {
                    if (value.size() < 3) {
                        return false;
                    }

                    std::string_view v{value.data(), value.size() - 2};
                    std::string_view unit{value.data() + value.size() - 2, 2};

                    if (unit == "cm") {
                        return num_in_range(v, 3, 150, 193);
                    } else if (unit == "in") {
                        return num_in_range(v, 2, 59, 76);
                    } else {
                        return false;
                    }
                },
            },
            {
                "hcl",
                // 1 '#' + 6 lowercase hex digits
                [](const auto& value) {
                    if (value.size() != 7 || value[0] != '#') {
                        return false;
                    }

                    std::string_view sv{value.data() + 1, value.size() - 1};
                    return each_char(
                        sv, sv.size(), [](auto c) { return std::isdigit(c) || (std::isxdigit(c) && std::islower(c)); });
                },
            },
            {
                "ecl",
                // custom set of values
                [](const auto& value) {
                    static const auto values = std::array{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                    return std::ranges::find(values, value) != values.end();
                },
            },
            {
                "pid",
                // 9 digits, leading zeros allowed ([000.000.000, 999.999.999])
                [](const auto& value) { return num_in_range(value, 9, 0, 999'999'999); },
            },
            {
                "cid",
                // optional
                [](const auto&) { return true; },
            },
        };

        // always initialize field2value
        static std::map<std::string_view, std::optional<std::string_view>> field2value;
        field2value.clear();
        for (auto& mandatory_field : {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}) {
            field2value[mandatory_field] = {}; // empty value
        }
        for (auto& optional_field : {"cid"}) {
            field2value[optional_field] = {"<dummy>"};
        }

        // actual parse the password
        for (const auto& [key, value] : password) {
            field2value[key] = value.data();
        }

        bool exist_values = std::ranges::all_of(field2value, [](const auto& p) {
            const auto& [_, value] = p;
            return value.has_value(); // field has value
        });
        bool valid_values = exist_values && std::ranges::all_of(field2validator, [&](const auto& p) {
            const auto& [key, validator] = p;
            return validator(field2value[key].value()); // field has valid value
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
