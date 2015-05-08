#pragma once
#include "nodes/Transform.h"
#include "nodes/mesh.h"
#include <fbxsdk.h>
#include "nodes/mesh.h"

namespace mfe{


static struct ImportExport
{
	
	// Relja: Gorane, ne menjaj potpis
	static Transform * makeTreeNode(FbxNode * pNode);
	static Mesh * makeMesh(FbxMesh * mesh, Node * parent);

};

}

