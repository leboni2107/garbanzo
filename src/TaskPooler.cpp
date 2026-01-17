#include "../include/TaskPooler.h"

#include <thread>

using namespace std;

int TaskPooler::findThreadAmount(std::vector<File> tasks) {
    unsigned int hw_threads = std::thread::hardware_concurrency();

    if (hw_threads == 0) {
        hw_threads = 4;
    }

    unsigned int optimal_threads = hw_threads * 2;

    unsigned int task_count = tasks.size();
    if (task_count < optimal_threads) {
        return task_count;
    }

    const unsigned int MAX_THREADS = 32;
    return std::min(optimal_threads, MAX_THREADS);
}

std::vector<std::vector<File>> TaskPooler::poolTasks(const std::vector<File>& tasks, int amount) {
    std::vector<std::vector<File>> pooledTasks;

    if (tasks.empty() || amount <= 0) {
        return pooledTasks;
    }

    int actual_pools = std::min(amount, static_cast<int>(tasks.size()));
    pooledTasks.resize(actual_pools);

    for (size_t i = 0; i < tasks.size(); i++) {
        int pool_index = i % actual_pools;
        pooledTasks[pool_index].push_back(tasks[i]);
    }

    return pooledTasks;
}