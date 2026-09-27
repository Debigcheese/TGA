#pragma once
#include "Model/Mesh.h"
#include "Shader/Shader.h"

#include "CommonUtilities/math/Matrix4x4.h"
#include "CommonUtilities/math/Vector3.h"

using namespace Tga;

class GameObject
{
public:
	void SetMesh(Mesh* aMesh);
	void SetPosition(Vector3f aPosition);
	void SetRotation(float aPitch, float aYaw, float aRoll);
	void SetScale(float aScale);

	Mesh* GetMesh() { return myMesh; }

	void SetShader(Shader* aShader) { myShader = aShader; }
	Shader* GetShader() { return myShader; }

	void SetTexture(Texture* aTexture) { myTexture = aTexture; }
	Texture* GetTexture() { return myTexture; }

	const Matrix4x4f& GetTransform() const { return myTransform; }
	void Render(ID3D11DeviceContext* aContext) const;

private:
	void RebuildTransform();

	Shader* myShader = nullptr;
	Texture* myTexture = nullptr;
	Mesh* myMesh = nullptr;
	Vector3f myPosition = { 0, 0, 0 };
	float myPitch = 0.0f;
	float myYaw = 0.0f;
	float myRoll = 0.0f;
	float myScale = 1.0f;
	Matrix4x4f myTransform;
};