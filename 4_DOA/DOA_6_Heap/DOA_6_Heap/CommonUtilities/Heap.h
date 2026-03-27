#pragma once

namespace CommonUtilities
{
	template <class T>
	class Heap
	{
	public:
		Heap()
		{
			
		}
		~Heap()
		{
			myHeap.clear();
		}

		//Returnerar antal element i heapen
		int GetSize() const;

		//Lägger till elementet i heapen
		void Enqueue(const T& aElement); //lägger till elementet i heapen

		//Returnerar det största elementet i heapen
		const T& GetTop() const;

		//Tar bort det största elementet ur heapen och returnerar det
		T Dequeue();

	private:
		std::vector<T> myHeap;
	};

	template <class T>
	int Heap<T>::GetSize() const
	{
		return myHeap.size();
	}

	template <class T>
	void Heap<T>::Enqueue(const T& aElement)
	{
		myHeap.push_back(aElement);

		int index = myHeap.size() - 1;
		while (0 < index)
		{
			int parent = (index - 1) / 2;
			if ( myHeap[parent]<  myHeap[index])
			{
				T temp = myHeap[index];
				myHeap[index] = myHeap[parent];
				myHeap[parent] = temp;
				index = parent;
			}
			else
			{
				break;
			}
		}
	}

	template <class T>
	const T& Heap<T>::GetTop() const
	{
		//assert(!myHeap.empty() && "Heap is empty!");
		return myHeap.front();
	}

	template <class T>
	T Heap<T>::Dequeue()
	{
		T top = GetTop();

		myHeap[0] = myHeap[myHeap.size() - 1];
		myHeap.pop_back();

		int index = 0;
		while (true)
		{
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int largest = index;

			if (left < myHeap.size() &&  myHeap[largest]<  myHeap[left])
			{
				largest = left;
			}
			if (right < myHeap.size() &&myHeap[largest] <   myHeap[right])
			{
				largest = right;
			}
			if (largest == index)
			{
				break;
			}

			T temp = myHeap[index];
			myHeap[index] = myHeap[largest];
			myHeap[largest] = temp;
			index = largest;
		}

		return top;
	}
}
