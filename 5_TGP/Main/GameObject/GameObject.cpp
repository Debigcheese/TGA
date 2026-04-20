#include "GameObject.h"

void GameObject::SetMesh(Mesh* aMesh)
{
	myMesh = aMesh;
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
		Matrix4x4f::CreateRotationAroundX(myPitch * FMath::RadToDeg) *
		Matrix4x4f::CreateRotationAroundY(myYaw * FMath::RadToDeg) *
		Matrix4x4f::CreateRotationAroundZ(myRoll * FMath::RadToDeg);

	// Apply scale
	myTransform(1, 1) *= myScale;
	myTransform(2, 2) *= myScale;
	myTransform(3, 3) *= myScale;

	// Apply position
	myTransform(4, 1) = myPosition.x;
	myTransform(4, 2) = myPosition.y;
	myTransform(4, 3) = myPosition.z;
}

void GameObject::Render(ID3D11DeviceContext* aContext) const
{
	if (!myMesh) return;

	if (myShader)
		myMesh->Render(aContext, myShader);
	else
		myMesh->Render(aContext);
}