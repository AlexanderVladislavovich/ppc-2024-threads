// Copyright 2024 Kashirin Alexander
#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "core/task/include/task.hpp"

class StlIntRadixSortWithBatcherMerge : public ppc::core::Task {
 public:
  explicit StlIntRadixSortWithBatcherMerge(std::shared_ptr<ppc::core::TaskData> taskData_)
      : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  // int input_{}, res{};
  std::vector<int> input, result;

 public:
  bool is_equal(const std::vector<int>& expected) {
    for (int i = 0; i < result.size(); i++) {
      if (expected[i] != result[i]) return false;
    }
    return true;
  }
};

inline std::vector<int> RandomVector(int size) {
  std::vector<int> vector(size);
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 900 + 1;
  }
  return vector;
}