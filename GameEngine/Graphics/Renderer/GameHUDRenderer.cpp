#pragma once
#include "GameHUDRenderer.h"
#include "TextureLoader.h"
#include "OGLTexture.h"

using namespace NCL;

GameHUDRenderer::GameHUDRenderer() : OGLRenderer(*Window::GetWindow()) {
	quadModel = OGLMesh::GenerateHUDQuad();
	hudShader = new OGLShader("hud.vert", "hud.frag");
}

void GameHUDRenderer::AddHudTextures(const string& name, const Vector2& position, const Vector2& scale) {
	hudTextures.emplace_back(TextureHUD(TextureLoader::LoadAPITexture(name), position, scale));
}

void GameHUDRenderer::Render() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(hudShader->GetProgramID());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BindShader(hudShader);
	GLint texID = 0;
	for (const auto& hudTexture : hudTextures) {
		/*GLuint slot = glGetUniformLocation(hudShader->GetProgramID(), "guiTexture");

		if (slot < 0) {
			return;
		}

		if (const OGLTexture* oglTexture = dynamic_cast<const OGLTexture*>(hudTexture.texture)) {
			texID = oglTexture->GetObjectID();
		}

		glUniform1i(slot, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);*/
		BindTextureToShader(hudTexture.texture, "guiTexture", 0);
		//quadModel->Draw();
	}
}
