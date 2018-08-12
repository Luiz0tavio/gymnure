//
// Created by luiz0tavio on 8/12/18.
//

#ifndef GYMNURE_PHONG_H
#define GYMNURE_PHONG_H

#include "Program.h"

namespace Engine
{
    namespace Programs
    {
        class Phong : public Program
        {

        public:

            void init(VkDevice device) override
            {
                auto vert = Engine::GraphicPipeline::Shader{};
                vert.type = VK_SHADER_STAGE_VERTEX_BIT;
                vert.path = "../../shaders/phong.vert.spv";

                auto frag = Engine::GraphicPipeline::Shader{};
                frag.type = VK_SHADER_STAGE_FRAGMENT_BIT;
                frag.path = "../../shaders/phong.frag.spv";

                descriptor_layout = new Descriptors::DescriptorSet(device, Descriptors::Type::GRAPHIC);
                graphic_pipeline  = new GraphicPipeline::GraphicPipeline(device, {vert, frag});
            }

        };
    }
}

#endif //GYMNURE_PHONG_H