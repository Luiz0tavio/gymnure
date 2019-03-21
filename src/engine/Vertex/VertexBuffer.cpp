#define TINYOBJLOADER_IMPLEMENTATION

#include <Util/Debug.hpp>
#include "tinyobjloader/tiny_obj_loader.h"

#include "VertexBuffer.h"

namespace Engine
{
    namespace Vertex
    {
        uint32_t VertexBuffer::getVertexSize() const
        {
            return vertex_count_;
        }

        std::shared_ptr<Memory::Buffer> VertexBuffer::getVertexBuffer() const
        {
            return vertexBuffer_;
        }

        uint32_t VertexBuffer::getIndexSize() const
        {
            return index_count_;
        }

        std::shared_ptr<Memory::Buffer> VertexBuffer::getIndexBuffer() const
        {
            return indexBuffer_;
        }

        void VertexBuffer::initBuffers(const std::vector<VertexData>& vertexData, const std::vector<uint32_t>& indexBuffer)
        {
            vertex_count_ = static_cast<uint32_t>(vertexData.size());

            struct BufferData vbData = {};
            vbData.usage      = vk::BufferUsageFlagBits::eVertexBuffer;
            vbData.properties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
            vbData.size       = vertex_count_ * sizeof(VertexData);

            vertexBuffer_ = std::make_unique<Memory::Buffer>(vbData);
            Memory::Memory::copyMemory(vertexBuffer_->mem, vertexData.data(), vbData.size);

            if (!indexBuffer.empty()) {

                index_count_ = static_cast<uint32_t>(indexBuffer.size());

                vbData.usage = vk::BufferUsageFlagBits::eIndexBuffer;
                vbData.size = index_count_ * sizeof(uint32_t);

                indexBuffer_ = std::make_unique<Memory::Buffer>(vbData);
                Memory::Memory::copyMemory(indexBuffer_->mem, vertexData.data(), vbData.size);
            }
        }

        void VertexBuffer::createPrimitiveTriangle(Descriptors::UniformBuffer* uo)
        {
            auto mvp = uo->mvp.projection * uo->mvp.view * uo->mvp.model;

            auto pos  = (mvp * glm::vec4(  1.0f,  1.0f, 0.0f, 1.0f ));
            pos /= pos.w;
            auto pos2 = (mvp * glm::vec4( -1.0f,  1.0f, 0.0f, 1.0f ));
            pos2 /= pos2.w;
            auto pos3 = (mvp * glm::vec4(  0.0f, -1.0f, 0.0f, 1.0f ));
            pos3 /= pos3.w;

            std::vector<VertexData> vertexBuffer =
                {
                    //       POSITION              UV              NORMAL
                    { {pos .x, pos .y, pos .z} , {1.0f, 1.0f}, { 0.0f, 0.0f, -1.0f } },
                    { {pos2.x, pos2.y, pos2.z} , {1.0f, 1.0f}, { 0.0f, 0.0f, -1.0f } },
                    { {pos3.x, pos3.y, pos3.z} , {1.0f, 1.0f}, { 0.0f, 0.0f, -1.0f } }
                };

            // Setup indices
            std::vector<uint32_t> indexBuffer = { 0, 1, 2 };

            this->initBuffers(vertexBuffer, indexBuffer);
        }

        void VertexBuffer::loadObjModelVertices(const std::string &model_path, const std::string& obj_mtl)
        {
            std::vector <VertexData> vertex_data = {};

            auto assets_model_path = std::string(ASSETS_FOLDER_PATH_STR) + "/" + model_path;
            auto assets_obj_mtl    = std::string(ASSETS_FOLDER_PATH_STR) + "/" + obj_mtl;

            auto* obj_mtl_ptr = obj_mtl.empty() ? nullptr : assets_obj_mtl.c_str();

            tinyobj::attrib_t attrib;
            std::vector <tinyobj::shape_t> shapes;
            std::vector <tinyobj::material_t> materials;
            std::string err;

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, assets_model_path.c_str(), obj_mtl_ptr)) {
                throw std::runtime_error(err);
            }

            for (const auto &shape : shapes) {
                for (const auto &index : shape.mesh.indices) {
                    struct VertexData vertex =
                        {
                            {
                                attrib.vertices[3 * index.vertex_index + 0],
                                attrib.vertices[3 * index.vertex_index + 1],
                                attrib.vertices[3 * index.vertex_index + 2]
                            },
                            {
                                !attrib.texcoords.empty() ? attrib.texcoords[2 * index.texcoord_index + 0] : 1.0f,
                                !attrib.texcoords.empty() ? 1.0f - attrib.texcoords[2 * index.texcoord_index + 1] : 1.0f
                            },
                            {
                                index.normal_index > -1 ? attrib.normals[3 * index.normal_index + 0] : 1.0f,
                                index.normal_index > -1 ? attrib.normals[3 * index.normal_index + 1] : 1.0f,
                                index.normal_index > -1 ? attrib.normals[3 * index.normal_index + 2] : 1.0f
                            }

                        };

                    vertex_data.push_back(vertex);
                }
            }

            //@TODO INIT BUFFERS

            Debug::logInfo(assets_model_path + " object loaded! Vertex count: " +  std::to_string(vertex_data.size()));
        }
    }
}