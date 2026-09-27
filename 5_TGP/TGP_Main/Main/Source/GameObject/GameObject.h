#pragma once
#include <array>
#include <vector>
#include "Model/Model.h"
#include "Shader/Shader.h"

#include "CommonUtilities/math/Matrix4x4.h"
#include "CommonUtilities/math/Vector3.h"

using namespace Tga;

class Texture;

class GameObject
{
public:
	void SetModel(Model* aModel);
	Model* GetModel() const { return myModel; }

	void SetPosition(Vector3f aPosition);
	void SetRotation(float aPitch, float aYaw, float aRoll);
	void SetScale(float aScale);
	float GetRadius() const { return myModel ? myModel->GetRadius() * myScale : 0.0f; }

	void SetShader(Shader* aShader) { myShader = aShader; }
	Shader* GetShader() { return myShader; }

	void SetTexture(int aSlot, Texture* aTexture);
	void SetTexture(int aSubMesh, int aSlot, Texture* aTexture);
	Texture* GetTexture(int aSubMesh, int aSlot) const { return myTextures[aSubMesh][aSlot]; }

	const Matrix4x4f& GetTransform() const { return myTransform; }
	void Render(ID3D11DeviceContext* aContext) const;

private:
	void RebuildTransform();

	Shader* myShader = nullptr;
	Model* myModel = nullptr;
	std::vector<std::array<Texture*, TextureSlot::Count>> myTextures; 
	Vector3f myPosition = { 0, 0, 0 };
	float myPitch = 0.0f;
	float myYaw = 0.0f;
	float myRoll = 0.0f;
	float myScale = 1.0f;
	Matrix4x4f myTransform;
};