// Copyright 2024 Kashirin Alexander
#include <omp.h>

#include <cmath>

#include "omp/kashirin_a_int_radix_sort_batcher/include/ops_omp.hpp"
using namespace std::chrono_literals;

int remainder(int num, int k) { return (num / static_cast<int>(pow(10, k - 1))) % 10; }

 void oddToArr(std::vector<int>& src, std::vector<int>& res) {
   int j = 0;
#pragma omp parallel for
   for (int i = 1; i < (int)src.size(); i += 2) {
     res[j++] = src[i];
   }
 }

void evenToArr(std::vector<int>& src, std::vector<int>& res) {
  int j = 0;
#pragma omp parallel for
  for (int i = 0; i < (int)src.size(); i += 2) {
    res[j++] = src[i];
  }
}

void radixSort(std::vector<int>& src, size_t left, size_t right) {
  std::vector<std::vector<int>> tmp(10, std::vector<int>(((int)(right - left)), 0));
  std::vector<int> amount(10, 0);
  int k = 1;
  while (k <= 3) {
    for (int i = (int)left; i <= (int)right; i++) {
      int rem = remainder(src[i], k);
      tmp[rem][amount[rem]++] = src[i];
    }
    std::vector<int> sz(10, 0);
    for (int i = 1; i < 10; i++) sz[i] = sz[i - 1] + amount[i - 1];
#pragma omp parallel num_threads(10)
    {
      int n = omp_get_thread_num();
      for (int i = sz[n], j = 0; j < amount[n]; i++, j++) {
        src[i] = tmp[n][j];
      }
      amount[n] = 0;
    }
#pragma omp barrier
    k++;
  }
}


void merge2(std::vector<int>& src1, std::vector<int>& src2, std::vector<int>& res) {
  size_t i = 0, j = 0, end = res.size();
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

void oddEvenMergeSort(std::vector<int>& src, std::vector<int>& res, size_t left, size_t right) {
  std::vector<int> odd(src.size() / 2 + src.size() % 2);
  std::vector<int> even(src.size() - odd.size());

  oddToArr(src, odd);
  evenToArr(src, even);

  radixSort(odd, 0, odd.size() - 1);
  radixSort(even, 0, even.size() - 1);

  merge2(odd, even, res);
}

bool OmpIntRadixSortWithBatcherMerge::pre_processing() {
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

bool OmpIntRadixSortWithBatcherMerge::validation() {
  internal_order_test();

  // Check count elements of output

  return taskData->inputs_count[0] == taskData->outputs_count[0];
  // return taskData->inputs_count.size() == taskData->outputs_count.size();
  // return true;
}

bool OmpIntRadixSortWithBatcherMerge::run() {
  internal_order_test();
  try {
    double start = omp_get_wtime();
    oddEvenMergeSort(input, result, 0, input.size() - 1);
    double end = omp_get_wtime();
    std::cout << "time = " << end - start << std::endl;
  } catch (...) {
    return false;
  }
  // std::this_thread::sleep_for(20ms);
  return true;
}

bool OmpIntRadixSortWithBatcherMerge::post_processing() {
  internal_order_test();
  std::copy(result.begin(), result.end(), reinterpret_cast<int*>(taskData->outputs[0]));
  return true;
  // return std::is_sorted(result.begin(), result.end());
}
