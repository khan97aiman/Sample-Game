#include "Terrain.h"
#include "RenderObject.h"
#include "PhysicsObject.h"
#include "SphereVolume.h"

using namespace NCL;
using namespace Rendering;

Terrain::Terrain(Vector2 gridPosition, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader, int size): GameObject() {
	transform.SetPosition(Vector3(gridPosition.x * size, 0, gridPosition.y * size));
	//transform.SetPosition(Vector3(0, 10, 0));

	transform.SetScale(Vector3(size, 0, size));
	name = "terrain";
	renderObject = new RenderObject(&transform, mesh, texture, shader);
	renderObject->SetColour(Vector4(1, 1, 0, 1));
	float inverseMass = 0.0f;
	physicsObject = new PhysicsObject(&transform, NULL);
	physicsObject->SetInverseMass(inverseMass);
	physicsObject->InitSphereInertia();	
}
