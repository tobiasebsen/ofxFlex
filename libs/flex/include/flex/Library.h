#pragma once

struct NvFlexLibrary;

namespace flex {

	class Library {
	public:
		static Library * init(int deviceIndex = 0, bool enableExtensions = false);
		void shutdown();

		NvFlexLibrary * getLibrary() const { return library; }

		static int getVersion();

	private:
		Library(NvFlexLibrary * lib) : library(lib) {}
		~Library() {
			shutdown();
		}

		NvFlexLibrary * library = nullptr;

		friend class ofxFlexSolver;
		friend class ofxFlexBuffer;
	};

}