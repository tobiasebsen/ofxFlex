#include "flex\Library.h"
#include "NvFlex.h"

#include <iostream>

using namespace flex;

void flexErrorCallback(NvFlexErrorSeverity type, const char* msg, const char* file, int line) {
	std::cerr <<  msg << std::endl;
}

Library * Library::init(int deviceIndex, bool enableExtensions) {

	NvFlexInitDesc desc;
	desc.deviceIndex = deviceIndex;
	desc.enableExtensions = enableExtensions;
	desc.renderDevice = 0;
	desc.renderContext = 0;
	desc.computeType = eNvFlexCUDA;

	NvFlexLibrary * lib = NvFlexInit(NV_FLEX_VERSION, flexErrorCallback, &desc);
	if (lib)
		return new Library(lib);
	else
		return nullptr;
}

void Library::shutdown() {

	NvFlexShutdown(library);
}

int Library::getVersion() {
	return NvFlexGetVersion();
}
