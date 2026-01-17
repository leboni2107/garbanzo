#pragma once

#include <vector>
#include "File.h"

class TaskPooler {
public:
    std::vector<File> tasks;
    std::vector<std::vector<File>> pooledTasks;

    int findThreadAmount(std::vector<File> tasks);
    std::vector<std::vector<File>> poolTasks(const std::vector<File>& tasks, int amount);
};