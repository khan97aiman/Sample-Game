#pragma once
#include <vector>
#include "OGLMesh.h"
#include "OGLShader.h"
#include "Matrix4.h"

namespace NCL {
	namespace Rendering {
		class OGLSkybox {
		public:
			OGLSkybox();
			~OGLSkybox();
			OGLMesh* GetMesh() { return skyboxMesh; }
			GLuint& GetTexID() { return skyboxTex; }
			OGLShader* GetShader() { return skyboxShader; }
			void Update(float dt);
			Matrix4 GetTransformationMatrix();
		protected:
			OGLMesh* skyboxMesh;
			GLuint skyboxTex = 0;
			OGLShader* skyboxShader;
			float currentRotation = 0;
			const float ROTATE_SPEED = 5.0f;
		};
	}
}

