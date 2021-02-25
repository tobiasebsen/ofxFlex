#pragma once

#include "flex\Library.h"

struct NvFlexBuffer;

namespace flex {

	class Buffer {
	public:
		~Buffer() {
			free();
		}

		void allocate(Library * flex, int elementCount, int elementByteStride, unsigned int bufferGL = 0);
		void free();

		void * map() const;
		void * mapDoNotWait() const;

		template<typename T>
		T * map() const { return (T*)map(); }
		template<typename T>
		T * mapDoNotWait() const { return (T*)mapDoNotWait(); }

		void unmap() const;

		void loadData(void * data, int elementCount, int elementByteStride);
		template<typename T>
		void loadData(T * data, int elementCount) {
			loadData(data, elementCount, sizeof(T));
		}

		int getElementCount() const { return elementCount; }
		int getElementByteStride() const { return elementByteStride; }

		NvFlexBuffer * getBuffer() const { return buffer; }
		unsigned int getBufferGL() const { return bufferGL; }

		operator NvFlexBuffer*() const { return buffer; }

	private:
		int elementCount = 0;
		int elementByteStride = 0;
		unsigned int bufferGL = 0;
		NvFlexBuffer * buffer = nullptr;
	};

	template<typename T>
	class BufferT : public Buffer {
	public:
		void allocate(Library * flex, int elementCount, unsigned int glBuffer = 0) {
			Buffer::allocate(flex, elementCount, sizeof(T), glBuffer);
		}

		T* map() {
			return (T*)Buffer::map();
		}

		void set(int index, const T & t) {
			T * d = map();
			d[index] = t;
			unmap();
		}

		const T get(int index) {
			T * d = map();
			T h = d[index];
			unmap();
			return h;
		}

		const T operator[](int index) {
			return get(index);
		}
	};

}