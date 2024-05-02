// Copyright 2024 Kashirin Alexander
#include "stl/kashirin_a_int_radix_sort_batcher/include/ops_stl.hpp"

#include <cmath>
#include <thread>
using namespace std::chrono_literals;

int remainder(int num, int k) { return (num / static_cast<int>(pow(10, k - 1))) % 10; }

void oddToArr(std::vector<int>& src, std::vector<int>& res) {
  std::atomic<int> j(0);
  int numThreads = 4;
  std::vector<std::thread> threads(numThreads);
  for (int th = 0; th < numThreads; th++) {
    threads[th] = std::thread([&src, &res, &j, th]() {
      for (int i = th * 2 + 1; i < static_cast<int>(src.size()); i += 2 * numThreads) {
        res[j.fetch_add(1)] = src[i];
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

void evenToArr(std::vector<int>& src, std::vector<int>& res) {
  std::atomic<int> j(0);
  const int numThreads = 4;
  std::vector<std::thread> threads(numThreads);
  for (int th = 0; th < numThreads; th++) {
    threads[th] = std::thread([&src, &res, &j, th]() {
      for (int i = th * 2; i < static_cast<int>(src.size()); i += 2 * numThreads) {
        res[j.fetch_add(1)] = src[i];
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

void radixSort(std::vector<int>& src, size_t left, size_t right) {
  std::vector<std::vector<int>> tmp(10, std::vector<int>((static_cast<int>(right - left)), 0));
  std::vector<int> amount(10, 0);
  std::vector<int> sz(10, 0);
  int k = 1;
  while (k <= 3) {
    for (int i = (int)left; i <= (int)right; i++) {
      int rem = remainder(src[i], k);
      tmp[rem][amount[rem]++] = src[i];
    }
    for (int i = 1; i < 10; i++) sz[i] = sz[i - 1] + amount[i - 1];
    std::vector<std::thread> threads(10);
    for (int th = 0; th < 10; th++) {
      threads[th] = std::thread([&, th]() {
        int n = th;
        int start = sz[n];
        int end = start + amount[n];
        for (int i = start, j = 0; i < end; i++, j++) {
          src[i] = tmp[n][j];
        }
        amount[n] = 0;
      });
    }
    for (auto& thread : threads) {
      thread.join();
    }
    k++;
  }
}

void merge2(std::vector<int>& src1, std::vector<int>& src2, std::vector<int>& res) {
  size_t i = 0;
  size_t j = 0;
  size_t end = res.size();
  size_t k = 0;
  while (k < end) {
    if ((i < src1.size()) && ((j >= src2.size()) || (src1[i] < src2[j]))) {
      res[k++] = src1[i++];
    } else if ((j < src2.size()) && ((i >= src1.size()) || (src1[i] > src2[j]))) {
      res[k++] = src2[j++];
    } else {
      res[k + 1] = res[k] = src1[i++];
      k += 2;
      j++;
    }
  }
}

void oddEvenMergeSort(std::vector<int>& src, std::vector<int>& res) {
  std::vector<int> even(src.size() / 2 + src.size() % 2);
  std::vector<int> odd(src.size() - even.size());

  oddToArr(src, odd);
  evenToArr(src, even);

  radixSort(odd, 0, odd.size() - 1);
  radixSort(even, 0, even.size() - 1);

  merge2(odd, even, res);
}

bool StlIntRadixSortWithBatcherMerge::pre_processing() {
  internal_order_test();
  // Init value for input and output
  input = std::vector<int>(taskData->inputs_count[0]);
  auto* tmp = reinterpret_cast<int*>(taskData->inputs[0]);
  for (unsigned i = 0; i < taskData->inputs_count[0]; i++) {
    input[i] = tmp[i];
  }
  result = std::vector<int>(taskData->outputs_count[0]);
  return true;
}

bool StlIntRadixSortWithBatcherMerge::validation() {
  internal_order_test();

  // Check count elements of output

  return taskData->inputs_count[0] == taskData->outputs_count[0];
  // return taskData->inputs_count.size() == taskData->outputs_count.size();
  // return true;
}

bool StlIntRadixSortWithBatcherMerge::run() {
  internal_order_test();
  try {
    oddEvenMergeSort(input, result);
  } catch (...) {
    return false;
  }
  // std::this_thread::sleep_for(20ms);
  return true;
}

bool StlIntRadixSortWithBatcherMerge::post_processing() {
  internal_order_test();
  std::copy(result.begin(), result.end(), reinterpret_cast<int*>(taskData->outputs[0]));
  return true;
  // return std::is_sorted(result.begin(), result.end());
}