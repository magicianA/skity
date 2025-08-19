// Copyright 2021 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include <gtest/gtest.h>
#include "skity/gpu/gpu_context.hpp"
#include "src/gpu/vk/gpu_device_vk.hpp"

class GPUDeviceVkTest : public ::testing::Test {
 protected:
  void SetUp() override {
    skity::GPUContext::Options options;
    options.backend = skity::GPUBackendType::kVulkan;
    context_ = skity::GPUContext::Make(options);
    ASSERT_NE(context_, nullptr);
  }

  void TearDown() override {
    context_.reset();
  }

  std::unique_ptr<skity::GPUContext> context_ = nullptr;
};

TEST_F(GPUDeviceVkTest, CreateBuffer) {
  ASSERT_NE(context_->GetDevice(), nullptr);

  auto buffer = context_->GetDevice()->CreateBuffer(skity::GPUBufferUsage::kVertexBuffer);

  ASSERT_NE(buffer, nullptr);
  EXPECT_EQ(buffer->GetUsage(), skity::GPUBufferUsage::kVertexBuffer);

  std::vector<uint8_t> data(1024);
  buffer->UploadData(data.data(), data.size());

  auto vk_buffer = static_cast<skity::GPUBufferVk*>(buffer.get());
  EXPECT_EQ(vk_buffer->GetSize(), 1024);
}
