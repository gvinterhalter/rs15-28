#pragma once

#include <fbxsdk.h>
#include "Scene.h"

namespace mfe{

	class Importer
	{
	public:
		Importer(Scene & scn);
		~Importer();

		void importScene(const std::string  & fileName);
		void traverseFbxTree(const FbxNode *node);
		void makeMesh(const FbxMesh * mesh);


	private:
		Scene & m_scene;

		FbxManager * m_sdkManager;
		FbxIOSettings * m_ios;

	};



}
