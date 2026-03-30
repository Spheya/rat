#include "mesh_loader.hpp"

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

#define TINYOBJLOADER_IMPLEMENTATION
#include <glm/glm.hpp>
#include <mikktspace.h>
#include <tiny_obj_loader.h>

#include "rat/core/logger.hpp"

namespace tinyobj {
	static bool operator==(const index_t& a, const index_t& b) {
		return a.vertex_index == b.vertex_index && a.normal_index == b.normal_index && a.texcoord_index == b.texcoord_index;
	}
} // namespace tinyobj

namespace std {
	template<>
	struct hash<tinyobj::index_t> {
		size_t operator()(const tinyobj::index_t& idx) const noexcept {
			size_t h1 = std::hash<int>{}(idx.vertex_index);
			size_t h2 = std::hash<int>{}(idx.normal_index);
			size_t h3 = std::hash<int>{}(idx.texcoord_index);
			size_t s = h1;
			s ^= h2 + 0x9e3779b9 + (s << 6) + (s >> 2);
			s ^= h3 + 0x9e3779b9 + (s << 6) + (s >> 2);
			return s;
		}
	};
} // namespace std

namespace rat {

	static int getNumFaces(const SMikkTSpaceContext* pContext) {
		return int(static_cast<const MeshData*>(pContext->m_pUserData)->indices.size() / 3);
	}

	static int getNumVerticesOfFace([[maybe_unused]] const SMikkTSpaceContext* pContext, [[maybe_unused]] const int iFace) {
		return 3;
	}

	static void getPosition(const SMikkTSpaceContext* pContext, float* fvPosOut, const int iFace, const int iVert) {
		const auto* mesh = static_cast<const MeshData*>(pContext->m_pUserData);
		unsigned index = mesh->indices[size_t(iFace) * 3 + iVert];
		glm::vec3 position = mesh->vertices[index].position;

		fvPosOut[0] = position.x;
		fvPosOut[1] = position.y;
		fvPosOut[2] = position.z;
	}

	static void getNormal(const SMikkTSpaceContext* pContext, float* fvNormOut, const int iFace, const int iVert) {
		const auto* mesh = static_cast<const MeshData*>(pContext->m_pUserData);
		unsigned index = mesh->indices[size_t(iFace) * 3 + iVert];
		glm::vec3 normal = mesh->vertices[index].normal;

		fvNormOut[0] = normal.x;
		fvNormOut[1] = normal.y;
		fvNormOut[2] = normal.z;
	}

	static void getTexCoord(const SMikkTSpaceContext* pContext, float* fvTexcOut, const int iFace, const int iVert) {
		const auto* mesh = static_cast<const MeshData*>(pContext->m_pUserData);
		unsigned index = mesh->indices[size_t(iFace) * 3 + iVert];
		glm::vec2 uv = mesh->vertices[index].uv;

		fvTexcOut[0] = uv.x;
		fvTexcOut[1] = uv.y;
	}

	static void setTSpaceBasic(const SMikkTSpaceContext* pContext, const float* fvTangent, const float fSign, const int iFace, const int iVert) {
		auto* mesh = static_cast<MeshData*>(pContext->m_pUserData);
		unsigned index = mesh->indices[size_t(iFace) * 3 + iVert];

		mesh->vertices[index].tangent = glm::vec4(fvTangent[0], fvTangent[1], fvTangent[2], fSign);
	}

	static MeshData loadObjMesh(const tinyobj::shape_t& mesh, const tinyobj::attrib_t& attrib) {
		std::unordered_map<tinyobj::index_t, size_t> recorded;
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;

		indices.reserve(mesh.mesh.indices.size());

		for(const auto& index : mesh.mesh.indices) {
			auto existing = recorded.find(index);
			if(existing != recorded.end()) {
				indices.push_back(existing->second);
				continue;
			}

			indices.push_back(vertices.size());
			recorded.emplace(index, vertices.size());

			Vertex vertex = {};
			vertex.color = glm::vec4(1.0f);

			if(index.vertex_index != -1) {
				vertex.position = glm::vec3(
				    attrib.vertices[3 * index.vertex_index + 0],
				    attrib.vertices[3 * index.vertex_index + 1],
				    attrib.vertices[3 * index.vertex_index + 2]
				);

				if(!attrib.colors.empty()) {
					vertex.color = glm::vec4(
					    attrib.colors[3 * index.vertex_index + 0],
					    attrib.colors[3 * index.vertex_index + 1],
					    attrib.colors[3 * index.vertex_index + 2],
					    1.0f
					);
				}
			}

			if(index.normal_index != -1) {
				vertex.normal = glm::vec3(
				    attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1], attrib.normals[3 * index.normal_index + 2]
				);
			}

			if(index.texcoord_index != -1) {
				vertex.uv = glm::vec2(attrib.texcoords[2 * index.texcoord_index + 0], attrib.texcoords[2 * index.texcoord_index + 1]);
			}

			vertices.emplace_back(vertex);
		}

		MeshData data = { .vertices = std::move(vertices), .indices = std::move(indices) };
		calculateTangents(data);
		return data;
	}

	std::vector<MeshData> loadObj(const char* path) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path);

		if(!warn.empty()) rat::warn("TinyOBJ: {}", warn);
		if(!err.empty()) rat::error("TinyOBJ: {}", err);
		if(!ret) error("Could not load OBJ mesh at: \"{}\"", path);

		std::vector<MeshData> meshes;
		meshes.reserve(shapes.size());

		for(const auto& mesh : shapes) meshes.emplace_back(loadObjMesh(mesh, attrib));

		return meshes;
	}

	void calculateTangents(MeshData& mesh) {
		static SMikkTSpaceInterface interface = { .m_getNumFaces = getNumFaces,
			                                      .m_getNumVerticesOfFace = getNumVerticesOfFace,
			                                      .m_getPosition = getPosition,
			                                      .m_getNormal = getNormal,
			                                      .m_getTexCoord = getTexCoord,
			                                      .m_setTSpaceBasic = setTSpaceBasic,
			                                      .m_setTSpace = nullptr };

		SMikkTSpaceContext context = { .m_pInterface = &interface, .m_pUserData = &mesh };
		genTangSpaceDefault(&context);
	}

} // namespace rat
