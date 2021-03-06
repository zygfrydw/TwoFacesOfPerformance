// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the NATIVELIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// NATIVELIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef NATIVELIB_EXPORTS
#define NATIVELIB_API __declspec(dllexport)
#else
#define NATIVELIB_API __declspec(dllimport)
#endif
#include <cstdint>

extern "C" {
	void NATIVELIB_API NativeAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length);
	void NATIVELIB_API NativeParallelAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length);
	void NATIVELIB_API SimdAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length);
	void NATIVELIB_API IntelIppAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length);
	void NATIVELIB_API IntelIppParallelAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length);
}
