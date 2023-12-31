# Testing C++ Polymorphic Function Techniques

## Benchmarking Output

```
===============================================================================
CppBenchmark report. Version 1.0.4.0
===============================================================================
CPU architecture: AMD Ryzen 5 5600H with Radeon Graphics
CPU logical cores: 12
CPU physical cores: 6
CPU clock speed: 3.294 GHz
CPU Hyper-Threading: enabled
RAM total: 15.356 GiB
RAM free: 7.370 GiB
===============================================================================
OS version: Microsoft Windows 10 Professional (build 19045), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuration: release
Local timestamp: Mon Jan  1 01:52:50 2024
UTC timestamp: Sun Dec 31 18:52:50 2023
===============================================================================
Benchmark: SortAlgorithm
Attempts: 1
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: SortAlgorithm
Total time: 1:05.244 m
-------------------------------------------------------------------------------
Phase: 1. ManuallyInlined_SortAlgorithm. 1000
Total time: 344.600 mcs
-------------------------------------------------------------------------------
Phase: 1. ManuallyInlined_SortAlgorithm. 10000
Total time: 32.367 ms
-------------------------------------------------------------------------------
Phase: 1. ManuallyInlined_SortAlgorithm. 100000
Total time: 8.834 s
-------------------------------------------------------------------------------
Phase: 2. PassedAsAPointer_SortAlgorithm. 1000
Total time: 1.008 ms
-------------------------------------------------------------------------------
Phase: 2. PassedAsAPointer_SortAlgorithm. 10000
Total time: 106.096 ms
-------------------------------------------------------------------------------
Phase: 2. PassedAsAPointer_SortAlgorithm. 100000
Total time: 11.188 s
-------------------------------------------------------------------------------
Phase: 3. PassedAsATemplateParameter_SortAlgorithm. 1000
Total time: 405.800 mcs
-------------------------------------------------------------------------------
Phase: 3. PassedAsATemplateParameter_SortAlgorithm. 10000
Total time: 36.943 ms
-------------------------------------------------------------------------------
Phase: 3. PassedAsATemplateParameter_SortAlgorithm. 100000
Total time: 9.194 s
-------------------------------------------------------------------------------
Phase: 4. CompileTimeBuiltTemplate_SortAlgorithm. 1000
Total time: 403.900 mcs
-------------------------------------------------------------------------------
Phase: 4. CompileTimeBuiltTemplate_SortAlgorithm. 10000
Total time: 37.182 ms
-------------------------------------------------------------------------------
Phase: 4. CompileTimeBuiltTemplate_SortAlgorithm. 100000
Total time: 9.178 s
-------------------------------------------------------------------------------
Phase: 5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 1000
Total time: 347.900 mcs
-------------------------------------------------------------------------------
Phase: 5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 10000
Total time: 32.671 ms
-------------------------------------------------------------------------------
Phase: 5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 100000
Total time: 8.836 s
-------------------------------------------------------------------------------
Phase: 6. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 1000
Total time: 341.000 mcs
-------------------------------------------------------------------------------
Phase: 6. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 10000
Total time: 32.489 ms
-------------------------------------------------------------------------------
Phase: 6. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 100000
Total time: 8.871 s
-------------------------------------------------------------------------------
Phase: 7. CompileTimeBuiltInvocable_SortAlgorithm. 1000
Total time: 341.900 mcs
-------------------------------------------------------------------------------
Phase: 7. CompileTimeBuiltInvocable_SortAlgorithm. 10000
Total time: 32.331 ms
-------------------------------------------------------------------------------
Phase: 7. CompileTimeBuiltInvocable_SortAlgorithm. 100000
Total time: 8.825 s
===============================================================================
```
