#include "nodes/Transform.h"

namespace mfe{


	Transform::Transform(const FbxNode* pNode, Transform * parent)
		: Node(pNode->GetName(), parent),
		mTranslate(fbx2vec3(pNode->LclTranslation.Get())),
		mRotate(fbx2vec3(pNode->LclRotation.Get())),
		mScale(fbx2vec3(pNode->LclScaling.Get()))
	{

	}

	void Transform::evalTransformation()
	{
		/*
		Here is how FBX SDK and Maya compute the transformation matrix for a node:
		WorldTransform = ParentWorldTransform * T * Roff * Rp * Rpre * R * Rpost * Rp-1 * Soff * Sp * S * Sp-1

		WorldTransform 			Transformation matrix of the node
		ParentWorldTransform 	Transformation matrix of the parent node
		T 		Translation
		Roff 	Rotation offset
		Rp 		Rotation pivot
		Rpre 	Pre-rotation
		R 		Rotation
		Rpost 	Post-rotation
		Rp-1	Inverse of the rotation pivot
		Soff 	Scaling offset
		Sp 		Scaling pivot
		S 		Scaling
		Sp-1	Inverse of the scaling pivot
		*/

	}

	inline std::ostream & operator<<(std::ostream & os, const glm::vec3 & v){
		return os
			<< "<" << v[0] << ", " << v[1] << ", " << v[2] << ">";
	}

	inline std::ostream & operator<<(std::ostream & os, const glm::mat4 & m){
		return os
			<< "[ " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3]
			<< " ; " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3]
			<< " ; " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3]
			<< " ; " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3]
			<< " ]";
	}

	std::ostream & operator<<(std::ostream & os, const Transform & node){
		return os
			<< "Transform name=\"" << node.mName << "\""
			<< " T=" << node.mTranslate
			<< " R=" << node.mRotate
			<< " S=" << node.mScale;
	}
}