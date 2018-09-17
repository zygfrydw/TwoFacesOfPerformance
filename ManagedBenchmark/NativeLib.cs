using System.Runtime.InteropServices;

namespace ManagedBenchmark
{
    public static class NativeLib
    {
        [DllImport("NativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void NativeAdd(byte[] arg1, byte[] arg2, byte[] arg3, int length);

        [DllImport("NativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void NativeParallelAdd(byte[] arg1, byte[] arg2, byte[] arg3, int length);

        [DllImport("NativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SimdAdd(byte[] arg1, byte[] arg2, byte[] arg3, int length);

        [DllImport("NativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IntelIppAdd(byte[] arg1, byte[] arg2, byte[] arg3, int length);

        [DllImport("NativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IntelIppParallelAdd(byte[] arg1, byte[] arg2, byte[] arg3, int length);
    }
}
