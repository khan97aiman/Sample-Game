#pragma once
//#include "TerrainMesh.h"
#include "Vector2.h"
#include "GameObject.h"
#include "MeshGeometry.h"
#include "TextureBase.h"
#include "ShaderBase.h"

namespace NCL {
	using namespace Maths;
	using namespace CSC8503;
	using namespace Rendering;

	class Terrain: public GameObject {
	public:
		Terrain(Vector2 gridPosition, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader, int size = 200);
		~Terrain(void) {
		};
	protected:
	};
};

