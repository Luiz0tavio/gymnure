#include <ApplicationData.hpp>
#include <Util/Util.h>
#include <memory>
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace Engine
{
    namespace Descriptors
    {
        Texture::Texture(const std::string& texture_path, vk::Queue queue)
        {
            if(texture_path.empty())
                Debug::logErrorAndDie("Fail to create Texture: string path is empty!");

            auto assets_texture_path = std::string(ASSETS_FOLDER_PATH_STR) + "/" + texture_path;

            int texWidth, texHeight, texChannels;
            stbi_uc *pixels = stbi_load(assets_texture_path.data(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

            if(!pixels)
                throw "Cannot stbi_load pixels!";

            auto pixel_count = static_cast<size_t>(texWidth * texHeight * 4); // 4 channels

            struct BufferData stagingBufferData = {};
            stagingBufferData.usage      = vk::BufferUsageFlagBits::eTransferSrc;
            stagingBufferData.properties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
            stagingBufferData.count      = pixel_count;

            auto staging_buffer = std::make_unique<Memory::Buffer<stbi_uc>>(stagingBufferData);
            staging_buffer->updateBuffer(pixels);

            stbi_image_free(pixels);

            MemoryProps mem_props = {};
            mem_props.props_flags = vk::MemoryPropertyFlagBits::eDeviceLocal;

            ImageProps img_props = {};
            img_props.width      = static_cast<uint32_t>(texWidth);
            img_props.height     = static_cast<uint32_t>(texHeight);
            img_props.usage      = vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
            img_props.aspectMask = vk::ImageAspectFlagBits::eColor;
            img_props.format     = vk::Format::eR8G8B8A8Unorm;
            img_props.tiling     = vk::ImageTiling::eOptimal;

            buffer_image_ = new Memory::BufferImage(mem_props, img_props);

            transitionImageLayout(vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, queue);

            copyBufferToImage(staging_buffer->getBuffer(), static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), queue);

            transitionImageLayout(vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, queue);

            if(!buffer_image_)
                Debug::logErrorAndDie("Fail to create Texture: unable to create TextureImage!");

            // Create sampler
            vk::SamplerCreateInfo sampler_ = {};
            sampler_.maxAnisotropy 		= 1.0f;
            sampler_.magFilter 			= vk::Filter::eLinear;
            sampler_.minFilter 			= vk::Filter::eLinear;
            sampler_.mipmapMode 		= vk::SamplerMipmapMode::eLinear;
            sampler_.addressModeU 		= vk::SamplerAddressMode::eRepeat;
            sampler_.addressModeV 		= vk::SamplerAddressMode::eRepeat;
            sampler_.addressModeW 		= vk::SamplerAddressMode::eRepeat;
            sampler_.mipLodBias 		= 0.0f;
            sampler_.compareOp 			= vk::CompareOp::eNever;
            sampler_.minLod 			= 0.0f;
            sampler_.maxLod 			= 0.0f;
            sampler_.maxAnisotropy 		= 1.0;
            sampler_.anisotropyEnable 	= VK_FALSE;
            sampler_.borderColor 		= vk::BorderColor::eFloatOpaqueWhite;
            this->sampler_ = ApplicationData::data->device.createSampler(sampler_);
        }

        vk::CommandBuffer Texture::beginSingleTimeCommands()
        {
            auto app_data = ApplicationData::data;

            vk::CommandBufferAllocateInfo allocInfo = {};
            allocInfo.level 			 = vk::CommandBufferLevel::ePrimary;
            allocInfo.commandPool 		 = app_data->graphic_command_pool;
            allocInfo.commandBufferCount = 1;

            vk::CommandBuffer commandBuffer;
            app_data->device.allocateCommandBuffers(&allocInfo, &commandBuffer);

            vk::CommandBufferBeginInfo beginInfo = {};
            beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;

            commandBuffer.begin(&beginInfo);

            return commandBuffer;
        }

        void Texture::endSingleTimeCommands(vk::CommandBuffer commandBuffer, vk::Queue graphicsQueue)
        {
            auto app_data = ApplicationData::data;

            commandBuffer.end();

            vk::SubmitInfo submitInfo = {};
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers 	  = &commandBuffer;

            graphicsQueue.submit({submitInfo}, {});
            graphicsQueue.waitIdle(); // @TODO use fence to sync

            app_data->device.freeCommandBuffers(app_data->graphic_command_pool, 1, &commandBuffer);
        }

        void Texture::transitionImageLayout(vk::ImageLayout oldLayout, vk::ImageLayout newLayout, vk::Queue graphicsQueue)
        {
            vk::CommandBuffer commandBuffer = beginSingleTimeCommands();

            vk::ImageMemoryBarrier barrier = {};
            barrier.oldLayout 							= oldLayout;
            barrier.newLayout 							= newLayout;
            barrier.srcQueueFamilyIndex 				= VK_QUEUE_FAMILY_IGNORED;
            barrier.dstQueueFamilyIndex 				= VK_QUEUE_FAMILY_IGNORED;
            barrier.image 								= buffer_image_->image;
            barrier.subresourceRange.aspectMask 		= vk::ImageAspectFlagBits::eColor;
            barrier.subresourceRange.baseMipLevel 		= 0;
            barrier.subresourceRange.levelCount 		= 1;
            barrier.subresourceRange.baseArrayLayer 	= 0;
            barrier.subresourceRange.layerCount 		= 1;

            vk::PipelineStageFlags sourceStage;
            vk::PipelineStageFlags destinationStage;

            if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal) {
                barrier.srcAccessMask 					= {};
                barrier.dstAccessMask 					= vk::AccessFlagBits::eTransferWrite;

                sourceStage 							= vk::PipelineStageFlagBits::eTopOfPipe;
                destinationStage 						= vk::PipelineStageFlagBits::eTransfer;
            } else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal) {
                barrier.srcAccessMask 					= vk::AccessFlagBits::eTransferWrite;
                barrier.dstAccessMask 					= vk::AccessFlagBits::eShaderRead;

                sourceStage                             = vk::PipelineStageFlagBits::eTransfer;
                destinationStage                        = vk::PipelineStageFlagBits::eFragmentShader;
            } else {
                return;
            }

            commandBuffer.pipelineBarrier(sourceStage, destinationStage, {}, 0, nullptr, 0, nullptr, 1, &barrier);

            endSingleTimeCommands(commandBuffer, graphicsQueue);
        }

        void Texture::copyBufferToImage(vk::Buffer buffer, uint32_t width, uint32_t height, vk::Queue graphicsQueue)
        {
            vk::CommandBuffer commandBuffer = beginSingleTimeCommands();

            vk::BufferImageCopy region = {};
            region.bufferOffset 					= 0;
            region.bufferRowLength 					= 0;
            region.bufferImageHeight 				= 0;
            region.imageOffset 						= vk::Offset3D{0, 0, 0};
            region.imageExtent 						= vk::Extent3D{width, height, 1};
            region.imageSubresource.aspectMask 		= vk::ImageAspectFlagBits::eColor;
            region.imageSubresource.mipLevel 		= 0;
            region.imageSubresource.baseArrayLayer 	= 0;
            region.imageSubresource.layerCount 		= 1;

            commandBuffer.copyBufferToImage(buffer, buffer_image_->image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

            endSingleTimeCommands(commandBuffer, graphicsQueue);
        }

        vk::ImageView Texture::getImageView() const
        {
            return this->buffer_image_->view;
        }

        vk::Sampler Texture::getSampler() const
        {
            return this->sampler_;
        }
    }
}