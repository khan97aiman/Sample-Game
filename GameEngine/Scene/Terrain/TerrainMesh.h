#pragma once
#include "MeshGeometry.h"

namespace NCL {
	class TerrainMesh: public MeshGeometry  {
	public:
		TerrainMesh(int heightVertexCount, int widthVertexCount, int size);
		~TerrainMesh(void) {};
	protected:
	};
};

