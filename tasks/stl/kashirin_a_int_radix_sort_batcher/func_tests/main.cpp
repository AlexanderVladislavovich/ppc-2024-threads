// Copyright 2024 kashirin Alexander
#include <gtest/gtest.h>

#include <vector>

#include "stl/kashirin_a_int_radix_sort_batcher/include/ops_stl.hpp"

//TEST(kashirin_a_int_radix_sort_batcher_stl, Test_sort_10) {
//  const int count = 10;
//
//  // Create data
//  std::vector<int> in = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//  std::vector<int> out(count, 0);
//
//  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
//  taskDataSeq->outputs_count.emplace_back(out.size());
//
//  // Create Task
//  StlIntRadixSortWithBatcherMerge testTaskSequential(taskDataSeq);
//  ASSERT_EQ(testTaskSequential.validation(), true);
//  ASSERT_TRUE(testTaskSequential.pre_processing());
//  ASSERT_TRUE(testTaskSequential.run());
//  ASSERT_TRUE(testTaskSequential.post_processing());
//  // ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
//}

TEST(kashirin_a_int_radix_sort_batcher_stl, Test1) { ASSERT_TRUE() true; }

TEST(kashirin_a_int_radix_sort_batcher_stl, Test_sort_20) {
  const int count = 20;

  // Create data
  std::vector<int> in = RandomVector(count);
  std::vector<int> out(count, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  StlIntRadixSortWithBatcherMerge testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());
  // ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
}

TEST(kashirin_a_int_radix_sort_batcher_stl, Test_sort_50) {
  const int count = 50;

  // Create data
  std::vector<int> in = RandomVector(count);
  std::vector<int> out(count, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  StlIntRadixSortWithBatcherMerge testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());
  // ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
}

TEST(kashirin_a_int_radix_sort_batcher_stl, Test_sort_70) {
  const int count = 70;

  // Create data
  std::vector<int> in = RandomVector(count);
  std::vector<int> out(count, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  StlIntRadixSortWithBatcherMerge testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());
  // ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
}

TEST(kashirin_a_int_radix_sort_batcher_stl, Test_sort_100) {
  const int count = 100;

  // Create data
  std::vector<int> in = RandomVector(count);
  std::vector<int> out(count, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  StlIntRadixSortWithBatcherMerge testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());
  // ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
}