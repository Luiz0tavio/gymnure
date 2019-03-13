//
// Created by luiz0tavio on 8/12/18.
//

#ifndef GYMNURE_PROGRAM_H
#define GYMNURE_PROGRAM_H

#include <GraphicPipeline/GraphicPipeline.h>
#include <Descriptors/DescriptorSet.h>
#include <Vertex/VertexBuffer.h>
#include <memancpp/Provider.hpp>
#include <ApplicationData.hpp>

struct GymnureObjData
{
    std::string             path_obj        = "";
    std::string             path_texture    = "";
    std::vector<VertexData> vertex_data     = {};
    char*                   obj_mtl         = nullptr;
};

namespace Engine
{
    namespace Programs
    {
        struct ProgramData
        {
            Descriptors::Texture  texture         = {};
            Vertex::VertexBuffer* vertex_buffer   = nullptr;
            VkDescriptorPool      descriptor_pool = nullptr;
            VkDescriptorSet       descriptor_set  = nullptr;
        };

        class Program
        {

        public:

            Descriptors::DescriptorSet*         descriptor_set   = nullptr;
            std::vector<ProgramData*>           data             = {};
            GraphicPipeline::GraphicPipeline*   graphic_pipeline = nullptr;
            VkQueue                             queue_{};

            ~Program()
            {
                auto device = Engine::ApplicationData::data->device;

                delete graphic_pipeline;
                delete descriptor_set;
                for(auto &d : data) {
                    vkDestroyDescriptorPool(device, d->descriptor_pool, nullptr);
                    delete d->vertex_buffer;
                    delete d->texture.buffer;
                    vkDestroySampler(device, d->texture.sampler, nullptr);
                }
            }

            void* operator new (std::size_t size)
            {
                return mem::Provider::getMemory(size);
            }

            void operator delete(void* ptr)
            {
                // Do not free memory here!
            }

            virtual void init(VkRenderPass render_pass) = 0;

            virtual void addObjData(const GymnureObjData& obj_data) = 0;
        };
    }
}

#endif //GYMNURE_PROGRAM_H
