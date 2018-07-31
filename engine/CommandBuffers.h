//
// Created by luizorv on 9/2/17.
//

#ifndef OBSIDIAN2D_COMMANDBUFFERS_H
#define OBSIDIAN2D_COMMANDBUFFERS_H

#include <vector>
#include <cassert>
#include <GraphicPipeline/GraphicPipeline.h>
#include "RenderPass/RenderPass.h"
#include "Descriptors/DescriptorSet.h"
#include "SyncPrimitives/SyncPrimitives.h"
#include "Vertex/VertexBuffer.h"

namespace Engine
{

    struct ProgramData {
        Descriptors::Texture                texture             = {};
        Vertex::VertexBuffer*               vertex_buffer       = nullptr;
		Descriptors::DescriptorSet*         descriptor_set      = nullptr;
    };

    struct Program {
        std::vector<ProgramData*>           data                = {};
        GraphicPipeline::GraphicPipeline*   graphic_pipeline    = nullptr;
    };

    enum ProgramType {
        SKYBOX,
        OBJECT,
        TEXT,
    };

	class CommandBuffers
	{

	private:

		VkDevice 							_instance_device;

		VkCommandPool 						_command_pool = nullptr;
		VkCommandBuffer 					_command_buffer = nullptr;

	public:

		CommandBuffers(VkDevice device, VkCommandPool command_pool)
		{
			_instance_device = device;
			_command_pool = command_pool;

			VkCommandBufferAllocateInfo cmd = {};
			cmd.sType 						= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			cmd.pNext 			 			= nullptr;
			cmd.commandPool 	 			= command_pool;
			cmd.level 			 			= VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			cmd.commandBufferCount  		= 1;

			assert(vkAllocateCommandBuffers(_instance_device, &cmd, &_command_buffer) == VK_SUCCESS);
		}

		~CommandBuffers()
		{
			vkFreeCommandBuffers(_instance_device, _command_pool, 1, &_command_buffer);
		}

		void bindGraphicCommandBuffer (
                std::map<ProgramType, Program>  programs,
				RenderPass::RenderPass* 	    render_pass,
				uint32_t 		                width,
				uint32_t 		                height,
				SyncPrimitives::SyncPrimitives* sync_primitives
		) {
			VkResult res;
			const VkDeviceSize offsets[1] = {0};

			VkClearValue clear_values[2];
			clear_values[0].color.float32[0] 			= 0.f;
			clear_values[0].color.float32[1] 			= 0.f;
			clear_values[0].color.float32[2] 			= 0.f;
			clear_values[0].color.float32[3] 			= 1.f;
			clear_values[1].depthStencil.depth 			= 1.f;
			clear_values[1].depthStencil.stencil 		= 0;

			VkRenderPassBeginInfo rp_begin = {};
			rp_begin.sType 								= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			rp_begin.pNext 								= nullptr;
			rp_begin.renderPass 						= render_pass->getRenderPass();
			rp_begin.renderArea.offset.x 				= 0;
			rp_begin.renderArea.offset.y 				= 0;
			rp_begin.renderArea.extent.width 			= width;
			rp_begin.renderArea.extent.height 			= height;
			rp_begin.clearValueCount 					= 2;
			rp_begin.pClearValues 						= clear_values;

			VkCommandBufferBeginInfo cmd_buf_info = {};
			cmd_buf_info.sType 							= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			cmd_buf_info.pNext 							= nullptr;
			cmd_buf_info.flags 							= 0;
			cmd_buf_info.pInheritanceInfo 				= nullptr;

			auto* util = new Util::Util(width, height);
			res = vkBeginCommandBuffer(_command_buffer, &cmd_buf_info);
			assert(res == VK_SUCCESS);

			for(uint32_t i = 0; i < render_pass->getSwapChain()->getImageCount(); i++)
			{
				rp_begin.framebuffer =  render_pass->getFrameBuffer()[i];
				vkCmdBeginRenderPass(_command_buffer, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);

                for(auto& [key, program_obj]: programs) {

                    ulong vertex_size = 0;
                    std::vector<VkBuffer> vertex_buffers = {};
                    std::vector<VkDescriptorSet > descriptors = {};
                    for(auto &data : program_obj.data) {
                        vertex_size += data->vertex_buffer->getVertexSize();
                        vertex_buffers.push_back(data->vertex_buffer->buf);
                        descriptors.push_back(data->descriptor_set->getDescriptorSet());
                    }

                    vkCmdBindPipeline(_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, program_obj.graphic_pipeline->getPipeline());
                    vkCmdBindDescriptorSets(_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                            program_obj.data[0]->descriptor_set->getPipelineLayout(), 0,
											static_cast<uint32_t>(descriptors.size()), descriptors.data(), 0, nullptr);
                    vkCmdBindVertexBuffers(_command_buffer, 0, static_cast<uint32_t>(vertex_buffers.size()), vertex_buffers.data(), offsets);

                    util->init_viewports(_command_buffer);
                    util->init_scissors(_command_buffer);

                    vkCmdDraw(_command_buffer, static_cast<uint32_t>(vertex_size), 1, 0, 0);
                }

				vkCmdEndRenderPass(_command_buffer);
			}

			res = vkEndCommandBuffer(_command_buffer);
			assert(res == VK_SUCCESS);

			delete util;
		}

        VkCommandBuffer getCommandBuffer()
		{
			return _command_buffer;
		}

	};
}

#endif //OBSIDIAN2D_COMMANDBUFFERS_H
