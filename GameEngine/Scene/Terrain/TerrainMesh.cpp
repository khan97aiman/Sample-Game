#include "TerrainMesh.h"
using namespace NCL;

TerrainMesh::TerrainMesh(int heightVertexCount, int widthVertexCount, int size) {
	for (int z = 0; z < heightVertexCount; ++z) {
		for (int x = 0; x < widthVertexCount; ++x) {
			positions.emplace_back(Vector3((float)x / ((float)widthVertexCount - 1) * size, 0, (float)z / ((float)heightVertexCount - 1) * size));
			texCoords.emplace_back((float)x / ((float)widthVertexCount - 1), (float)z / ((float)heightVertexCount - 1));
		}
	}

	int i = 0;
	for (int z = 0; z < heightVertexCount - 1; ++z) { 
		for (int x = 0; x < widthVertexCount - 1; ++x) {
			int a = (z * (widthVertexCount)) + x;
			int b = (z * (widthVertexCount)) + (x + 1);
			int c = ((z + 1) * (widthVertexCount)) + (x + 1);
			int d = ((z + 1) * (widthVertexCount)) + x;
			indices.emplace_back(a);
			indices.emplace_back(c);
			indices.emplace_back(b);
			indices.emplace_back(c);
			indices.emplace_back(a);
			indices.emplace_back(d);
		}
	}

	CalculateNormals();
	CalculateTangents();
}