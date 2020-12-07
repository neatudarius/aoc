#pragma once

#include <bits/stdc++.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <ranges>

namespace std::ranges {

auto accumulate(const auto& container, auto init, auto op) {

    return std::accumulate(std::begin(container), std::end(container), std::move(init), op);
}

} // namespace ranges
