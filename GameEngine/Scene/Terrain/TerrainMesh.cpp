#include "TerrainMesh.h"
#include "TextureLoader.h"

using namespace NCL;

TerrainMesh::TerrainMesh(int size, const std::string& filename) {
	int iWidth, iHeight, iChans, iflags;
	char* data; 
	if (!TextureLoader::LoadTexture(filename, data, iWidth, iHeight, iChans, iflags)) {
		std::cout << "Can’t load Terrain Heightmap file!\n";
		return;
	}
	for (int z = 0; z < iHeight; ++z) {
		for (int x = 0; x < iWidth; ++x) {
			positions.emplace_back(Vector3((float)x / ((float)iWidth - 1) * size, 0, (float)z / ((float)iHeight - 1) * size));
			texCoords.emplace_back((float)x / ((float)iWidth - 1), (float)z / ((float)iHeight - 1));
		}
	}

	int i = 0;
	for (int z = 0; z < iHeight - 1; ++z) {
		for (int x = 0; x < iWidth - 1; ++x) {
			int a = (z * (iWidth)) + x;
			int b = (z * (iWidth)) + (x + 1);
			int c = ((z + 1) * (iWidth)) + (x + 1);
			int d = ((z + 1) * (iWidth)) + x;
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