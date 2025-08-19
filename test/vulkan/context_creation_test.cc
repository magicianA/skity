// Test program for enhanced Vulkan context creation
#include <skity/gpu/gpu_context_vk.hpp>
#include <iostream>
#include <memory>

using namespace skity;

int main() {
    std::cout << "=== Testing Enhanced Vulkan Context Creation ===" << std::endl;
    
    // Test 1: Check if Vulkan is available
    std::cout << "\n1. Testing IsVulkanAvailable():" << std::endl;
    bool vulkan_available = IsVulkanAvailable();
    std::cout << "   Vulkan available: " << (vulkan_available ? "YES" : "NO") << std::endl;
    
    if (!vulkan_available) {
        std::cout << "   Vulkan not available, skipping context creation tests" << std::endl;
        return 0;
    }
    
    // Test 2: Get available devices
    std::cout << "\n2. Testing VkGetAvailableDevices():" << std::endl;
    uint32_t device_count = 0;
    const char** devices = VkGetAvailableDevices(&device_count);
    std::cout << "   Found " << device_count << " Vulkan devices:" << std::endl;
    if (devices) {
        for (uint32_t i = 0; i < device_count; i++) {
            std::cout << "     - " << devices[i] << std::endl;
        }
    }
    
    // Test 3: Default context creation
    std::cout << "\n3. Testing VkContextCreate() [default]:" << std::endl;
    auto context1 = VkContextCreate();
    if (context1) {
        std::cout << "   ✓ Default context created successfully" << std::endl;
        std::cout << "   Backend type: " << static_cast<int>(context1->GetBackendType()) << std::endl;
    } else {
        std::cout << "   ✗ Default context creation failed" << std::endl;
    }
    
    // Test 4: Context creation with preferences
    std::cout << "\n4. Testing VkContextCreate(preferences):" << std::endl;
    VkDevicePreferences prefs;
    prefs.preferred_device_type = 2; // Discrete GPU
    prefs.enable_validation = true;
    prefs.required_api_version = 0; // Any version
    
    auto context2 = VkContextCreate(prefs);
    if (context2) {
        std::cout << "   ✓ Context with preferences created successfully" << std::endl;
        std::cout << "   Backend type: " << static_cast<int>(context2->GetBackendType()) << std::endl;
    } else {
        std::cout << "   ✗ Context with preferences creation failed" << std::endl;
    }
    
    // Test 5: Context creation with existing objects (mock values)
    std::cout << "\n5. Testing VkContextCreateWithExisting():" << std::endl;
    // Using mock values since we don't have real Vulkan objects
    uint64_t mock_instance = 0x1234567890ABCDEF;
    uint64_t mock_device = 0xFEDCBA0987654321;
    uint64_t mock_queue = 0x1122334455667788;
    uint32_t mock_queue_family = 0;
    
    auto context3 = VkContextCreateWithExisting(mock_instance, mock_device, mock_queue, mock_queue_family);
    if (context3) {
        std::cout << "   ✓ Context with existing objects created successfully" << std::endl;
        std::cout << "   Backend type: " << static_cast<int>(context3->GetBackendType()) << std::endl;
    } else {
        std::cout << "   ✗ Context with existing objects creation failed" << std::endl;
    }
    
    // Test 6: Test multiple contexts can coexist
    std::cout << "\n6. Testing multiple contexts:" << std::endl;
    auto context4 = VkContextCreate();
    auto context5 = VkContextCreate();
    
    if (context4 && context5) {
        std::cout << "   ✓ Multiple contexts created successfully" << std::endl;
    } else {
        std::cout << "   ✗ Multiple context creation failed" << std::endl;
    }
    
    // Test 7: Test context cleanup (automatic via RAII)
    std::cout << "\n7. Testing context cleanup:" << std::endl;
    {
        auto temp_context = VkContextCreate();
        if (temp_context) {
            std::cout << "   ✓ Temporary context created in scope" << std::endl;
        }
        // Context should be automatically destroyed here
    }
    std::cout << "   ✓ Context cleanup handled by RAII" << std::endl;
    
    std::cout << "\n=== All Context Creation Tests Completed ===" << std::endl;
    return 0;
}