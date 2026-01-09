#pragma once
#include "tge/math/Vector2.h"
#include "tge/sprite/sprite.h"
#include "tge/drawers/SpriteDrawer.h"

#include "Component.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <utility>

struct Transform
{
	Tga::Vector2f position;
	float rotation;
	Tga::Vector2f scale;
	Tga::Vector2f pivot;
};

class Entity
{
public:
	Entity();
	~Entity();

	void Update(float aTimeDelta);

	//ECS (Entity component system)
	template <typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	template <typename T>
	std::shared_ptr<T> GetComponent();

	template <typename T>
	bool RemoveComponent();

	//TRANSFORM COMP
	void SetTransform(const Transform& aTransform);
	Transform GetTransform();

	void SetPosition(Tga::Vector2f aPosition) { mySpriteInstance.myPosition = aPosition; }
	void SetRotation(float aRotation);
	void SetScale(Tga::Vector2f aScale);
	void SetPivot(Tga::Vector2f aPivot);

	Tga::Vector2f GetPosition() const { return mySpriteInstance.myPosition; }
	float GetRotation() const { return mySpriteInstance.myRotation; }
	Tga::Vector2f GetSize() const { return mySpriteInstance.mySize * mySpriteInstance.mySizeMultiplier; }
	Tga::Vector2f GetResolution() const { return myResolution; }

	//SPRITE RENDERER COMP
	void SetTexture(const std::string& aTexturePath);
	void SetTexture(const Tga::TextureResource* aTextureResource) { mySpriteData.myTexture = aTextureResource; }
	Tga::Sprite2DInstanceData& GetSpriteInstance() { return mySpriteInstance; }
	Tga::SpriteSharedData& GetSpriteData() { return mySpriteData; }

	void SetOnCollided(std::function<void(Entity*)> aCallback) { myOnCollidedCallback = aCallback; }
	void OnCollided();

private:
	std::vector<std::shared_ptr<Component>> myComponents;

	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySpriteData;
	Tga::Vector2f myResolution;

	std::function<void(Entity*)> myOnCollidedCallback;
};


template <typename T, typename... Args>
std::shared_ptr<T> Entity::AddComponent(Args&&... args)
{
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);
	comp->SetOwner(this);
	comp->OnAdded();

	myComponents.push_back(comp);
	return comp;
}

template <typename T>
std::shared_ptr<T> Entity::GetComponent()
{
	for (auto& comp : myComponents)
	{
		if (auto casted = std::dynamic_pointer_cast<T>(comp))
		{
			return casted;
		}
	}
	return nullptr;
}

template <typename T>
bool Entity::RemoveComponent()
{
	auto it = std::find_if(
		myComponents.begin(), myComponents.end(),
		[](const std::shared_ptr<Component>& comp)
		{
			return dynamic_cast<T*>(comp.get()) != nullptr;
		});

	if (it == myComponents.end())
	{
		return false;
	}

	myComponents.erase(it);
	return true;
}
