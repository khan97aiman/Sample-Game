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
			GLuint& GetDayTexID() { return skyboxTexDay; }
			GLuint& GetNightTexID() { return skyboxTexNight; }
			OGLShader* GetShader() { return skyboxShader; }
			void Update(float dt);
			Matrix4 GetTransformationMatrix();
		protected:
			void LoadTextures(std::string* filenames, GLuint& texID);

			OGLMesh* skyboxMesh;
			GLuint skyboxTexDay = 0;
			GLuint skyboxTexNight = 0;
			OGLShader* skyboxShader;
			float currentRotation = 0;
			const float ROTATE_SPEED = 5.0f;
		};
	}
}

