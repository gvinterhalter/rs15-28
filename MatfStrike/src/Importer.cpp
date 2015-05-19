#include "Importer.h"

namespace mfe{


	Importer::Importer(Scene & scn) : m_scene(scn)
	{

		// Initialize the SDK manager. This object handles all our memory management.kk
		m_sdkManager = FbxManager::Create();

		// Create the IO settings object.
		m_ios = FbxIOSettings::Create(m_sdkManager, IOSROOT);
		m_sdkManager->SetIOSettings(m_ios);

	}


	Importer::~Importer()
	{
		// Destroy the SDK manager and all the other objects it was handling.
		m_sdkManager->Destroy();
	}


	void Importer::importScene(const std::string  & fileName){
		// Create an importer using the SDK manager.
		FbxImporter * importer = FbxImporter::Create(m_sdkManager, "");

		// Use the first argument as the filename for the importer.
		if (!importer->Initialize(fileName.c_str(), -1, m_sdkManager->GetIOSettings())) {
			std::cerr << "Call to FbxImporter::Initialize() failed." << std::endl;
			std::cerr << "Error returned: " <<  importer->GetStatus().GetErrorString() << std::endl;
			exit(EXIT_FAILURE);
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* fbxScene = FbxScene::Create(m_sdkManager, "tmpScene");
		importer->Import(fbxScene); // Import the contents of the file into the scene.

		// The file is imported; so get rid of the importer.
		importer->Destroy();

		FbxNode * rootNode = fbxScene->GetRootNode();
		if (rootNode){
			for (int i = 0; i < rootNode->GetChildCount(); i++)
				traverseFbxTree(rootNode->GetChild(i));
		}
	}

	void Importer::traverseFbxTree(const FbxNode * node){
		switch (node->GetNodeAttribute()->GetAttributeType()){
		case FbxNodeAttribute::eMesh:
			std::cout <<"Importing mesh "<< node->GetName();
			makeMesh((FbxMesh *)node->GetNodeAttribute());
			break;
		}

		for (int j = 0; j < node->GetChildCount(); j++){
			traverseFbxTree(node->GetChild(j));
		}
	}

	void Importer::makeMesh(const FbxMesh * mesh){
		unsigned int polygonCount = mesh->GetPolygonCount();
		FbxVector4 * controlPoints = mesh->GetControlPoints();

		std::cout << ": polygonCount=" << polygonCount << std::endl;

		FbxStringList uvSetNames;
		mesh->GetUVSetNames(uvSetNames);

		unsigned int offset = 3 * (3 + 3 + 2);
		GLfloat * buff = new GLfloat[polygonCount*offset];
		GLfloat * b = buff;

		unsigned int n = polygonCount * offset;

		for (unsigned int polygon = 0; polygon < polygonCount; polygon++){
			for (int vertex = 0; vertex < 3; vertex++){
				//std::cout << "Triangle " << polygon << "." << vertex << ": ";
				// ********************************
				int id = mesh->GetPolygonVertex(polygon, vertex);
				//std::cout << "<" << controlPoints[id][0] << " " << controlPoints[id][1] << " " << controlPoints[id][2] << ">, " ;
				*b   = controlPoints[id][0];
				*++b = controlPoints[id][1];
				*++b = controlPoints[id][2];
				
				// ********************************
				FbxVector4 normal;
				mesh->GetPolygonVertexNormal(polygon, vertex, normal);
				//std::cout << "<" << normal[0] << " " << normal[1] << " " << normal[2] << ">, ";
				*++b = normal[0];
				*++b = normal[1];
				*++b = normal[2];
				// ********************************
				FbxVector2 uv;
				bool bla = true;
				mesh->GetPolygonVertexUV(polygon, vertex, uvSetNames[0], uv, bla);
				//std::cout << "<" << uv[0] << " " << uv[1] << ">";
				*++b = uv[0];
				*++b = uv[1];
				b++;
				// ********************************
				//std::cout << std::endl;
			}
		}

		m_scene.addMesh(new Mesh(buff, n));
	}

}
