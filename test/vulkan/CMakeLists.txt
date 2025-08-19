# Vulkan test executable
if(${SKITY_VK_BACKEND})
  add_executable(vulkan_test vulkan_test.cc)
  target_link_libraries(vulkan_test PRIVATE skity)
  target_include_directories(vulkan_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
    ${CMAKE_SOURCE_DIR}/third_party/VulkanMemoryAllocator/include
    ${CMAKE_SOURCE_DIR}/module/wgx/include
    ${CMAKE_SOURCE_DIR}/third_party/glm
    ${CMAKE_SOURCE_DIR}/third_party/volk
  )
  
  # Vulkan integration test executable
  add_executable(vulkan_integration_test vulkan_integration_test.cc)
  target_link_libraries(vulkan_integration_test PRIVATE skity)
  target_include_directories(vulkan_integration_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
    ${CMAKE_SOURCE_DIR}/third_party/VulkanMemoryAllocator/include
    ${CMAKE_SOURCE_DIR}/module/wgx/include
    ${CMAKE_SOURCE_DIR}/third_party/glm
    ${CMAKE_SOURCE_DIR}/third_party/volk
  )
  
  # Context creation test executable
  add_executable(context_creation_test context_creation_test.cc)
  target_link_libraries(context_creation_test PRIVATE skity)
  target_include_directories(context_creation_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
    ${CMAKE_SOURCE_DIR}/third_party/VulkanMemoryAllocator/include
    ${CMAKE_SOURCE_DIR}/module/wgx/include
    ${CMAKE_SOURCE_DIR}/third_party/glm
    ${CMAKE_SOURCE_DIR}/third_party/volk
  )
  
  # Set RPATH for macOS
  if(APPLE)
    set_target_properties(vulkan_test vulkan_integration_test context_creation_test PROPERTIES
      BUILD_RPATH "${CMAKE_BINARY_DIR}"
      INSTALL_RPATH "@executable_path"
    )
  endif()
endif()