#pragma once
#include "GameHUDRenderer.h"
#include "TextureLoader.h"

using namespace NCL;

GameHUDRenderer::GameHUDRenderer() : OGLRenderer(*Window::GetWindow()) {
	quadModel = OGLMesh::GenerateHUDQuad();
	hudShader = new OGLShader("hud.vert", "hud.frag");
}

void GameHUDRenderer::AddHudTextures(const string& name, const Vector2& position, const Vector2& scale) {
	hudTextures.emplace_back(TextureHUD(TextureLoader::LoadAPITexture(name), position, scale));
}

void GameHUDRenderer::Render() {
	BindShader(hudShader);

	for (const auto& hudTexture : hudTextures) {
		BindTextureToShader(hudTexture.texture, "guiTexture", 0);
	}
	quadModel->Draw();
	//quadModel.draw
}
