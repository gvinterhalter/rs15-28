#pragma once

#include <fbxsdk.h>
#include "node.h"

/*
glm\detail\func_common.inl
u ovom zagalvalju sam dodao : #undef GLM_HAS_CXX11_STL
jer u suprotnom pokusava da koristi std::isnan koji ne postoji...
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

#include <iostream>
#include <vector>
#include <string>

namespace mfe {

class Transform : public Node
{
public:
	Transform(const FbxNode * pNode, Transform * parent = 0);

	Transform & setTranslate(glm::vec3 t) { mTranslate = t; }
	Transform & setRotate(glm::vec3 r) { mRotate = r; }
	Transform & setScale(glm::vec3 s) { mScale = s; }
	Transform & setPivot(glm::vec3 p) { mPivot = p; }

	void evalTransformation();

	friend std::ostream & operator<<(std::ostream & os, const Transform & node);

private:

	glm::mat4 mWorldMatrix;     // final world transformation =  parent.mWorldMatrix * mLocalMatrix
	glm::mat4 mLocalMatrix;     // for object space transformation
	glm::vec3 mTranslate;
	glm::vec3 mRotate;
	glm::vec3 mScale;
	glm::vec3 mPivot;      //  pivot

};


inline glm::vec3 fbx2vec3(const FbxDouble3 & v){
	return glm::vec3(v[0], v[1], v[2]);
}

}

