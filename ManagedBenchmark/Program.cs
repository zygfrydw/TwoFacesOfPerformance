using System.Collections.Generic;
using System.Linq;
using System.Text;
using BenchmarkDotNet.Running;

namespace ManagedBenchmark
{
    class Program
    {
        static void Main(string[] args)
        {
            BenchmarkRunner.Run<AdditionBenchmark>();
        }
    }
}
