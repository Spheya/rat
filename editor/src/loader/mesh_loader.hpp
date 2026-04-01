#pragma once

#include <vector>

#include "rat/rendering/vertex.hpp"

namespace rat {

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;
	};

	std::vector<MeshData> loadObj(const char* path);

	void calculateNormals(MeshData& mesh);
	void calculateTangents(MeshData& mesh);

} // namespace rat
