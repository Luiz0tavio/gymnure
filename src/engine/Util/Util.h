//
// Created by luizorv on 6/10/17.
//

#ifndef OBSIDIAN2D_CORE_UTIL_H
#define OBSIDIAN2D_CORE_UTIL_H
#include "vulkan/vulkan.h"

#if defined(NDEBUG) && defined(__GNUC__)
#define U_ASSERT_ONLY __attribute__((unused))
#else
#define U_ASSERT_ONLY
#endif

#include <xcb/xcb.h>
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <cstring>
#include <cassert>
#include <iostream>

struct VertexData {
    float pos[3];
    float uv[2];
    float normal[3];
};

enum WindowEvent
{
	None       = 0,
	Click      = 1,
	Focus      = 2,
	Blur       = 3,
	Resize     = 4,
	Close      = 5,
	ButtonDown = 6,
	ButtonUp   = 7,
	Unknow     = 8,
};


namespace Engine
{
	namespace Util
	{
		class Util
		{
		public:

			u_int32_t						width;
			u_int32_t						height;

			Util(u_int32_t _width, u_int32_t _height)
			{
				width  = _width;
				height = _height;
			}

			Util() {}

			void* operator new(std::size_t size)
			{
				return mem::Provider::getMemory(size);
			}

			void operator delete(void* ptr)
			{
				// Do not free memory here!
			}

			void init_viewports(VkCommandBuffer cmd_buffer)
			{
				VkViewport viewport;
				viewport.height 	= static_cast<float>(height);
				viewport.width 		= static_cast<float>(width);
				viewport.minDepth 	= 0.0f;
				viewport.maxDepth 	= 1.0f;
				viewport.x 			= 0;
				viewport.y 			= 0;
				vkCmdSetViewport(cmd_buffer, 0, 1, &viewport);
			}

			std::string physicalDeviceTypeString(VkPhysicalDeviceType type)
			{
#define CASE_STR(r) case VK_PHYSICAL_DEVICE_TYPE_ ##r: return #r
				switch (type)
				{
					CASE_STR(OTHER);
					CASE_STR(INTEGRATED_GPU);
					CASE_STR(DISCRETE_GPU);
					CASE_STR(VIRTUAL_GPU);
					default: return "UNKNOWN_DEVICE_TYPE";
				}
#undef CASE_STR
			}

			void init_scissors(VkCommandBuffer cmd_buffer)
			{
				VkRect2D scissor;
				scissor.extent.width 	= (uint32_t)width;
				scissor.extent.height 	= (uint32_t)height;
				scissor.offset.x 		= 0;
				scissor.offset.y 		= 0;
				vkCmdSetScissor(cmd_buffer, 0, 1, &scissor);
			}

			VkShaderModule loadSPIRVShader(const std::string& filename, VkDevice device)
			{
				long shaderSize;
				char* shaderCode = nullptr;

				std::ifstream is(filename, std::ios::binary | std::ios::in | std::ios::ate);

				if (is.is_open())
				{
					shaderSize = is.tellg();
					assert(shaderSize > 0);

					is.seekg(0, std::ios::beg);
					// Copy file contents into a buffer
					shaderCode = new char[shaderSize];
					is.read(shaderCode, shaderSize);
					is.close();
				}
				if (shaderCode)
				{
					// Create a new shader module that will be used for pipeline creation
					VkShaderModuleCreateInfo moduleCreateInfo{};
					moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
					moduleCreateInfo.codeSize = shaderSize;
					moduleCreateInfo.pCode = (uint32_t*)shaderCode;

					VkShaderModule shaderModule;
					VkResult res = vkCreateShaderModule(device, &moduleCreateInfo, nullptr, &shaderModule);
					assert(res == VK_SUCCESS);

					delete[] shaderCode;

					return shaderModule;
				}
				else
				{
					std::cerr << "Error: Could not open shader file \"" << filename << "\"" << std::endl;
					return nullptr;
				}
			}
		};
	}
}
#endif //OBSIDIAN2D_CORE_UTIL_H