#pragma once

#include <bits/stdc++.h>

struct StreamRedirect {
    std::string name;
    std::variant<std::ifstream, std::ofstream> stream;
    std::function<void(void)> undo_redirection;

    static auto build(const auto& stream_name, auto& standard_stream) {
        std::unique_ptr<StreamRedirect> sr{new (std::nothrow) StreamRedirect{}};
        if (!sr) {
            return sr;
        }
        sr->name = stream_name;

        auto standard_buff = standard_stream.rdbuf();
        sr->undo_redirection = [&]() {
            standard_stream.rdbuf(standard_buff);
        };

        using standard_stream_type = std::remove_cvref<decltype(standard_stream)>::type;
        if constexpr (std::is_same_v<standard_stream_type, std::istream>) {
            sr->stream.emplace<std::ifstream>(stream_name);
        } else {
            sr->stream.emplace<std::ofstream>(stream_name);
        }

        std::visit(
            [&](auto& stream) {
                using stream_type = std::remove_cvref<decltype(stream)>::type;
                assert(stream.is_open());

                constexpr auto redirect_stdin
                    = std::is_same_v<standard_stream_type, std::istream> && std::is_same_v<stream_type, std::ifstream>;
                constexpr auto redirect_stdout
                    = std::is_same_v<standard_stream_type, std::ostream> && std::is_same_v<stream_type, std::ofstream>;
                constexpr auto redirect_stderr = redirect_stdout;
                if constexpr (redirect_stdin || redirect_stdout || redirect_stderr) {
                    standard_stream.rdbuf(stream.rdbuf());
                }
            },
            sr->stream);

        return sr;
    }

    void destroy() { undo_redirection(); }
};
