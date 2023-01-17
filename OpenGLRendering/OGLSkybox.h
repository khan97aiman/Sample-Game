#pragma once
#include <vector>
#include "OGLMesh.h"
#include "OGLShader.h"

namespace NCL {
	namespace Rendering {
		class OGLSkybox {
		public:
			OGLSkybox();
			~OGLSkybox();
			OGLMesh* GetMesh() { return skyboxMesh; }
			GLuint& GetTexID() { return skyboxTex; }
			OGLShader* GetShader() { return skyboxShader; }
		protected:
			OGLMesh* skyboxMesh;
			GLuint skyboxTex = 0;
			OGLShader* skyboxShader;
		};
	}
}

