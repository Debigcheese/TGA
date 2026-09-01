#pragma once
#pragma once
#include <cstdint>
#include <vector>
#include <optional>
#include <utility>

#include "Hash.hpp"

namespace CommonUtilities
{
	template <class Key, class Value>
	class HashMap
	{
	public:
		//Skapar en HashMap med plats för aCapacity element. Den behöver inte 
	//kunna växa. Blir den full så blir den full.
		HashMap(int aCapacity);

		//Stoppar in aValue under nyckeln aKey. Om det fanns ett värde innan med
		//aKey som nyckel så skrivs det värdet över. Om det lyckas returneras
		//true. Om map:en är full så görs ingenting, och false returneras.
		bool Insert(const Key& aKey, const Value& aValue);

		//Plockar bort elementet med nyckeln aKey, om det finns. Om det finns
		//returneras true. Om det inte finns görs ingenting, och false
		//returneras.
		bool Remove(const Key& aKey);

		//Ger en pekare till värdet med nyckeln aKey, om det finns. Om det inte
		//finns returneras nullptr.
		const Value* Get(const Key& aKey) const;

		//Som ovan, men returnerar en icke-const-pekare.
		Value* Get(const Key& aKey);

	private:
		struct Slot
		{
			std::optional<std::pair<Key, Value>> myEntry;
			bool myTombstone = false;
		};

		static bool KeysEqual(const Key& aLhs, const Key& aRhs)
		{
			return !(aLhs < aRhs) && !(aRhs < aLhs);
		}

		int myCapacity;
		std::vector<Slot> mySlots;
	};

	template <class Key, class Value>
	HashMap<Key, Value>::HashMap(int aCapacity)
		: myCapacity(aCapacity)
		, mySlots(aCapacity < 0 ? 0 : aCapacity)
	{
	}

	template <class Key, class Value>
	bool HashMap<Key, Value>::Insert(const Key& aKey, const Value& aValue)
	{
		if (mySlots.empty())
		{
			return false;
		}

		const uint32_t hash = Hash(aKey);
		const int start = static_cast<int>(hash % static_cast<uint32_t>(myCapacity));

		int firstTombstone = -1;
		for (int i = 0; i < myCapacity; ++i)
		{
			const int idx = (start + i) % myCapacity;
			Slot& slot = mySlots[idx];

			if (slot.myEntry.has_value())
			{
				if (KeysEqual(slot.myEntry->first, aKey))
				{
					slot.myEntry.emplace(aKey, aValue);
					return true;
				}
			}
			else if (slot.myTombstone)
			{
				if (firstTombstone < 0)
				{
					firstTombstone = idx;
				}
			}
			else
			{
				const int target = (firstTombstone >= 0) ? firstTombstone : idx;
				mySlots[target].myEntry.emplace(aKey, aValue);
				mySlots[target].myTombstone = false;
				return true;
			}
		}

		if (firstTombstone >= 0)
		{
			mySlots[firstTombstone].myEntry.emplace(aKey, aValue);
			mySlots[firstTombstone].myTombstone = false;
			return true;
		}

		return false;
	}

	template <class Key, class Value>
	bool HashMap<Key, Value>::Remove(const Key& aKey)
	{
		if (mySlots.empty())
		{
			return false;
		}

		const uint32_t hash = Hash(aKey);
		const int start = static_cast<int>(hash % static_cast<uint32_t>(myCapacity));

		for (int i = 0; i < myCapacity; ++i)
		{
			const int idx = (start + i) % myCapacity;
			Slot& slot = mySlots[idx];

			if (slot.myEntry.has_value())
			{
				if (KeysEqual(slot.myEntry->first, aKey))
				{
					slot.myEntry.reset();
					slot.myTombstone = true;
					return true;
				}
			}
			else if (!slot.myTombstone)
			{
				return false;
			}

		}

		return false;
	}

	template <class Key, class Value>
	const Value* HashMap<Key, Value>::Get(const Key& aKey) const
	{
		if (mySlots.empty())
		{
			return nullptr;
		}

		const uint32_t hash = Hash(aKey);
		const int start = static_cast<int>(hash % static_cast<uint32_t>(myCapacity));

		for (int i = 0; i < myCapacity; ++i)
		{
			const int idx = (start + i) % myCapacity;
			const Slot& slot = mySlots[idx];

			if (slot.myEntry.has_value())
			{
				if (KeysEqual(slot.myEntry->first, aKey))
				{
					return &slot.myEntry->second;
				}
			}
			else if (!slot.myTombstone)
			{
				return nullptr;
			}
		}

		return nullptr;
	}

	template <class Key, class Value>
	Value* HashMap<Key, Value>::Get(const Key& aKey)
	{
		const HashMap* constThis = this;
		return const_cast<Value*>(constThis->Get(aKey));
	}
}