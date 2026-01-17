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

    size_t chunk_size = tasks.size() / actual_pools;
    size_t remainder = tasks.size() % actual_pools;

    size_t start = 0;
    for (int i = 0; i < actual_pools; i++) {
        size_t current_chunk_size = chunk_size + (i < remainder ? 1 : 0);

        pooledTasks[i].assign(
            tasks.begin() + start,
            tasks.begin() + start + current_chunk_size
        );

        start += current_chunk_size;
    }

    return pooledTasks;
}