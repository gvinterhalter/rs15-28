#include "ImportExport.h"
#include "nodes/Transform.h"
#include "nodes/mesh.h"
#include <fbxsdk.h>
#include "nodes/mesh.h"

namespace mfe{



Transform * ImportExport::makeTreeNode(FbxNode * pNode){
	Transform * t = new Transform(pNode);
	switch (pNode->GetNodeAttribute()->GetAttributeType()){
	case FbxNodeAttribute::eMesh:
		ImportExport::makeMesh((FbxMesh *)pNode->GetNodeAttribute(), t);
		break;
	}

	for (int j = 0; j < pNode->GetChildCount(); j++){
		t->addChild(ImportExport::makeTreeNode(pNode->GetChild(j)));
	}
	return t;
}

Mesh * ImportExport::makeMesh(FbxMesh * mesh, Node * parent){
	 Mesh * tmpMesh = new Mesh(mesh->GetName(), parent);
	 unsigned int n = mesh->GetControlPointsCount();
	 FbxVector4 * controlPoints = mesh->GetControlPoints();
	 std::cout << "broj vertexa" << n << std::endl;
	 for (int i = 0; i < n; i++){
		 //std::cout << *controlPoints[i] << ", ";
	 }
	 std::cout << std::endl;

	 return tmpMesh;
 }

}
