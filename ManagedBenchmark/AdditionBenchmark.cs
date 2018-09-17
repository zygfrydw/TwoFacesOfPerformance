using System;
using System.Collections.Concurrent;
using System.Threading.Tasks;
using BenchmarkDotNet.Attributes;

namespace ManagedBenchmark
{
    public class AdditionBenchmark
    {
        private const int N = 1024 * 1024 * 1024;
        private readonly byte[] argument1;
        private readonly byte[] argument2;
        private readonly byte[] result;

        public AdditionBenchmark()
        {
            argument1 = new byte[N];
            argument2 = new byte[N];
            result = new byte[N];

            var random = new Random(43);
            random.NextBytes(argument1);
            random.NextBytes(argument2);
        }

        [Benchmark]
        public void ManagedAdd()
        {
            for (var i = 0; i < N; i++)
            {
                var value = argument1[i] + argument2[i];
                result[i] = value <= byte.MaxValue ? (byte) value : byte.MaxValue;
            }
        }

        [Benchmark]
        public void ManagedParallelAdd()
        {
            var partitioner = Partitioner.Create(0, N);
            Parallel.ForEach(partitioner, range =>
            {
                for (var i = range.Item1; i < range.Item2; i++)
                {
                    var value = argument1[i] + argument2[i];
                    result[i] = value <= byte.MaxValue ? (byte)value : byte.MaxValue;
                }
            });
        }

        [Benchmark]
        public void NativeAdd()
        {
            NativeLib.NativeAdd(argument1, argument2, result, N);
        }

        [Benchmark]
        public void NativeParallelAdd()
        {
            NativeLib.NativeParallelAdd(argument1, argument2, result, N);
        }

        [Benchmark]
        public void SimdAdd()
        {
            NativeLib.SimdAdd(argument1, argument2, result, N);
        }

        [Benchmark]
        public void IntelIppAdd()
        {
            NativeLib.IntelIppAdd(argument1, argument2, result, N);
        }

        [Benchmark]
        public void IntelIppParallelAdd()
        {
            NativeLib.IntelIppParallelAdd(argument1, argument2, result, N);
        }
    }
}