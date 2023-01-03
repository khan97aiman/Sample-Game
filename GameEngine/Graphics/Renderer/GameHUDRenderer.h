#pragma once
#include "OGLMesh.h"
#include "OGLShader.h"
#include "TextureHUD.h"
#include "OGLRenderer.h"

namespace NCL {
	using namespace NCL::Rendering;
	class GameHUDRenderer: public OGLRenderer {
	public:
		GameHUDRenderer();
		void AddHudTextures(const string& name, const Vector2& position, const Vector2& scale);
		void Render();
	private:
		OGLMesh* quadModel;
		OGLShader* hudShader;
		vector<TextureHUD> hudTextures;
	};
};