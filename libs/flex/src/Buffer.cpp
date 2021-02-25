#include "flex\Buffer.h"

#include <string>

#include "NvFlex.h"
#include "gl/glew.h"

using namespace flex;

void Buffer::allocate(Library * flex, int elementCount, int elementByteStride, unsigned int bufferGL) {
	
	free();

	this->elementCount = elementCount;
	this->elementByteStride = elementByteStride;
	this->bufferGL = bufferGL;

	if (bufferGL)
		buffer = NvFlexRegisterOGLBuffer(flex->getLibrary(), bufferGL, elementCount, elementByteStride);
	else
		buffer = NvFlexAllocBuffer(flex->getLibrary(), elementCount, elementByteStride, eNvFlexBufferHost);
}

void Buffer::free() {
	if (buffer) {
		if (bufferGL)
			NvFlexUnregisterOGLBuffer(buffer);
		else
			NvFlexFreeBuffer(buffer);
		buffer = nullptr;
	}
}

void * Buffer::map() const {
	return NvFlexMap(buffer, eNvFlexMapWait);
}

void * Buffer::mapDoNotWait() const {
	return NvFlexMap(buffer, eNvFlexMapDoNotWait);
}

void Buffer::unmap() const {
	NvFlexUnmap(buffer);
}

void Buffer::loadData(void * src, int elementCount, int elementByteStride) {
	if (elementCount <= this->elementCount && elementByteStride == this->elementByteStride) {
		void * dst = map();
		memcpy(dst, src, elementCount * elementByteStride);
		unmap();
	}
}
