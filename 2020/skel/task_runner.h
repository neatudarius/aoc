#pragma once

#include <bits/stdc++.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

#include "stream_redirect.h"

template<typename Task>
class TaskRunner {
protected:
    TaskRunner() = default;

public:
    ~TaskRunner() { destroy(); }

    static std::unique_ptr<TaskRunner> create() {
        std::unique_ptr<TaskRunner> task_runner{new (std::nothrow) TaskRunner{}};
        if (!task_runner) {
            std::cerr << "Failed to create TaskRunner!\n";
            return {};
        }

        task_runner->m_task.reset(new (std::nothrow) Task{});
        if (!task_runner->m_task) {
            std::cerr << "Failed to create Task!\n";
            return {};
        }

        return task_runner;
    }

    void destroy() {
        for (auto& sr : m_stream_redirects) {
            sr->destroy();
        }
    }

    TaskRunner& set_stream(const auto& stream_name, auto& standard_stream) {
        auto sr = StreamRedirect::build(stream_name, standard_stream);
        assert(sr);
        m_stream_redirects.emplace_back(std::move(sr));
        return *this;
    }

    void solve() { m_task->solve(); }

protected:
    std::vector<std::unique_ptr<StreamRedirect>> m_stream_redirects;

    std::unique_ptr<Task> m_task;
};
