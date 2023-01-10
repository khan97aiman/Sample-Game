#pragma once
#include "MeshGeometry.h"

namespace NCL {
	class TerrainMesh: public MeshGeometry  {
	public:
		TerrainMesh(int size, const std::string& filename);
		~TerrainMesh(void) {};
	protected:
	};
};

