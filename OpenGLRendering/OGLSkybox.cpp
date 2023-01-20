#include "OGLSkybox.h"
#include <string>
#include <vector>
#include "TextureLoader.h"
#include <iostream>

using namespace NCL;
using namespace NCL::Rendering;
using namespace Maths;

OGLSkybox::OGLSkybox() {
	skyboxShader = new OGLShader("skybox.vert", "skybox.frag");
	skyboxMesh = new OGLMesh();
	skyboxMesh->SetVertexPositions({ Vector3(-1, 1,-1), Vector3(-1,-1,-1) , Vector3(1,-1,-1) , Vector3(1,1,-1) });
	skyboxMesh->SetVertexIndices({ 0,1,2,2,3,0 });
	skyboxMesh->UploadToGPU();

	std::string dayFilenames[6] = {
		"/Cubemap/skyrender0004.png",
		"/Cubemap/skyrender0001.png",
		"/Cubemap/skyrender0003.png",
		"/Cubemap/skyrender0006.png",
		"/Cubemap/skyrender0002.png",
		"/Cubemap/skyrender0005.png"
	};

	std::string nightFilenames[6] = {
		"/Cubemap/Night/posx.png",
		"/Cubemap/Night/negx.png",
		"/Cubemap/Night/posy.png",
		"/Cubemap/Night/negy.png",
		"/Cubemap/Night/posz.png",
		"/Cubemap/Night/negz.png"
	};

	LoadTextures(dayFilenames, skyboxTexDay);
	LoadTextures(nightFilenames, skyboxTexNight);

}

OGLSkybox::~OGLSkybox() {
	delete skyboxShader;
	delete skyboxMesh;
	glDeleteTextures(1, &skyboxTexDay);
	glDeleteTextures(1, &skyboxTexNight);

}

void OGLSkybox::Update(float dt) {
	currentRotation += ROTATE_SPEED * dt;
}

Matrix4 OGLSkybox::GetTransformationMatrix() {
	return Matrix4::Rotation(currentRotation, Vector3(0, 1, 0));
}

void OGLSkybox::LoadTextures(std::string* filenames, GLuint& texID) {
	
	int width[6] = { 0 };
	int height[6] = { 0 };
	int channels[6] = { 0 };
	int flags[6] = { 0 };

	vector<char*> texData(6, nullptr);

	for (int i = 0; i < 6; ++i) {
		TextureLoader::LoadTexture(filenames[i], texData[i], width[i], height[i], channels[i], flags[i]);
		if (i > 0 && (width[i] != width[0] || height[0] != height[0])) {
			std::cout << __FUNCTION__ << " cubemap input textures don't match in size?\n";
			return;
		}
	}

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	GLenum type = channels[0] == 4 ? GL_RGBA : GL_RGB;

	for (int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width[i], height[i], 0, type, GL_UNSIGNED_BYTE, texData[i]);
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	for (int i = 0; i < 6; ++i) {
		TextureLoader::FreeTexture(texData[i]);
	}
}
