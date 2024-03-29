// Copyright 2024 Ivanchenko Aleksei
#include "seq/ivanchenko_a_gauss_filter_vertical/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

bool GaussFilterSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  input = taskData->inputs[0];
  output = taskData->outputs[0];
  width = taskData->inputs_count[0];
  height = taskData->inputs_count[1];
  image.reserve(width*height*3);
  for(size_t i = 0; i < width*height*3; i+=3) {
    image.push_back({input[i], input[i + 1], input[i + 2]});
  }
  createKernel();
  return true;
}

bool GaussFilterSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] >= 3 && taskData->inputs_count[1] >= 3 &&
  taskData->outputs_count[0] == taskData->inputs_count[0] &&
  taskData->outputs_count[1] == taskData->inputs_count[1];
}

bool GaussFilterSequential::run() {
  internal_order_test();
  applyKernel();
  return true;
}

bool GaussFilterSequential::post_processing() {
  internal_order_test();
  for(size_t j = 0; j < width*height; j++) {
    size_t i = 3*j;
    output[i] = image[j].R;
    output[i + 1] = image[j].G;
    output[i + 2] = image[j].B; 
  }
  return true;
}
void GaussFilterSequential::createKernel(float sigma) {
  uint32_t radius = kernelSize / 2;
  uint32_t size = kernelSize;
  float norm = 0; // коэффициент нормировки ядра
  for(int i = -radius; i <= (int)radius; i++) {
    for(int j = -radius; j <= (int)radius; j++) {
      kernel[i + radius][j + radius] = (double)(exp(-(i*i + j*j) / (2*sigma*sigma)));
      norm += kernel[i + radius][j + radius];
    }  
  }
  // нормируем ядро
  for(uint32_t i = 0; i < size; i++) {
    for(uint32_t j = 0; j < size; j++) {
      kernel[i][j] /= norm;
    }
  }
}
void GaussFilterSequential::applyKernel() {
  for(uint32_t j = 0; j < height; j++) {
    for(uint32_t i = 0; i < width; i++) {
      image[i*width + j] = calculateNewPixelColor(i, j);
    }
  }
}
Color GaussFilterSequential::calculateNewPixelColor(size_t x, size_t y) {
  uint32_t radius = kernelSize / 2;
  float resultR = 0, resultG = 0, resultB = 0;
  for(int l = -radius; l <= (int)radius; l++) {
    for(int k = -radius; k <= (int)radius; k++) {
      size_t idX = x + k, idY = y + l;
      if(idX < 0) idX = 0;
      if(idX >= width) idX = width - 1;
      if(idY < 0) idY = 0;
      if(idY >= height) idY = height - 1;
      Color neighborColor = image[idX*width + idY];
      resultR += neighborColor.R * kernel[k + radius][l + radius];
      resultG += neighborColor.G * kernel[k + radius][l + radius];
      resultB += neighborColor.B * kernel[k + radius][l + radius];
    }
  }
  Color result((uint8_t)std::ceil(resultR), (uint8_t)std::ceil(resultG), (uint8_t)std::ceil(resultB));
  return result;
}