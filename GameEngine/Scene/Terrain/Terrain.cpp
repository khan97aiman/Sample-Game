#include "Terrain.h"
#include "RenderObject.h"
#include "PhysicsObject.h"
#include "SphereVolume.h"

using namespace NCL;
using namespace Rendering;

Terrain::Terrain(Vector2 gridPosition, MeshGeometry* mesh, TerrainTexturePack texturePack, ShaderBase* shader, int size): GameObject() {
	transform.SetPosition(Vector3(gridPosition.x * size, 0, gridPosition.y * size));
	//transform.SetPosition(Vector3(0, 10, 0));

	transform.SetScale(Vector3(size, 1, size));
	name = "terrain";
	renderObject = new RenderObject(&transform, mesh, shader);
	
	renderObject->AddTexture(0, texturePack.rTex, "rTex");
	renderObject->AddTexture(0, texturePack.gTex, "gTex");
	renderObject->AddTexture(0, texturePack.bTex, "bTex");
	renderObject->AddTexture(0, texturePack.bgTex, "bgTex");
	renderObject->AddTexture(0, texturePack.splatMap, "splatMapTex");

	//renderObject->SetColour(Vector4(1, 1, 0, 1));
	float inverseMass = 0.0f;
	physicsObject = new PhysicsObject(&transform, NULL);
	physicsObject->SetInverseMass(inverseMass);
	physicsObject->InitSphereInertia();	
}
