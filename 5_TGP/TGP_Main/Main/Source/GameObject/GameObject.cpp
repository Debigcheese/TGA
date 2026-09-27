#include "GameObject.h"
#include "Model/Texture.h"
#include <cassert>

void GameObject::SetModel(Model* aModel)
{
	myModel = aModel;
	myTextures.clear();
	if (!myModel) return;

	myTextures.resize(myModel->GetSubMeshCount());
	for (int i = 0; i < myModel->GetSubMeshCount(); ++i)
	{
		for (int slot = 0; slot < TextureSlot::Count; ++slot)
		{
			myTextures[i][slot] = myModel->GetSubMesh(i).defaultTextures[slot];
		}
	}
}

void GameObject::SetTexture(int aSlot, Texture* aTexture)
{
	for (int i = 0; i < static_cast<int>(myTextures.size()); ++i)
	{
		SetTexture(i, aSlot, aTexture);
	}
}

void GameObject::SetTexture(int aSubMesh, int aSlot, Texture* aTexture)
{
	assert(myModel && "GameObject: SetTexture called before SetModel");
	assert(aSubMesh < static_cast<int>(myTextures.size()) && aSlot < TextureSlot::Count);

	myTextures[aSubMesh][aSlot] = aTexture ? aTexture : myModel->GetSubMesh(aSubMesh).defaultTextures[aSlot];
}

void GameObject::SetPosition(Vector3f aPosition)
{
	myPosition = aPosition;
	RebuildTransform();
}

void GameObject::SetRotation(float aPitch, float aYaw, float aRoll)
{
	myPitch = aPitch;
	myYaw = aYaw;
	myRoll = aRoll;
	RebuildTransform();
}

void GameObject::SetScale(float aScale)
{
	myScale = aScale;
	RebuildTransform();
}

void GameObject::RebuildTransform()
{
	myTransform =
		Matrix4x4f::CreateRotationAroundX(myPitch) *
		Matrix4x4f::CreateRotationAroundY(myYaw) *
		Matrix4x4f::CreateRotationAroundZ(myRoll);

	for (int row = 1; row <= 3; ++row)
	{
		for (int col = 1; col <= 3; ++col)
		{
			myTransform(row, col) *= myScale;
		}
	}

	myTransform(4, 1) = myPosition.x;
	myTransform(4, 2) = myPosition.y;
	myTransform(4, 3) = myPosition.z;
}

void GameObject::Render(ID3D11DeviceContext* aContext) const
{
	if (!myModel || !myShader) return;

	for (int i = 0; i < myModel->GetSubMeshCount(); ++i)
	{
		for (int slot = 0; slot < TextureSlot::Count; ++slot)
		{
			if (const Texture* texture = myTextures[i][slot])
			{
				texture->Bind(aContext, TextureSlot::Registers[slot]);
			}
		}
		myModel->GetSubMesh(i).mesh.Render(aContext, myShader);
	}
}