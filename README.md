# Testing C++ Polymorphic Function Techniques

## Objective

I wanted to test various techniques of making polymorphic functions at compile time that would allow following the DRY principle without performance penalty of `call` assembly instruction

## Conclusion

As benchmarking output shows, using pointers to functions removes the ability from the compiler to optimize the code

## References. Benchmarking Output

```
ManuallyInlined_SortAlgorithm. 1000. Total time: 344.600 mcs
ManuallyInlined_SortAlgorithm. 10000. Total time: 32.367 ms
ManuallyInlined_SortAlgorithm. 100000 Total time: 8.834 s
PassedAsAPointer_SortAlgorithm. 1000. Total time: 1.008 ms
PassedAsAPointer_SortAlgorithm. 10000. Total time: 106.096 ms
❗ PassedAsAPointer_SortAlgorithm. 100000 Total time: 11.188 s ❗
PassedAsATemplateParameter_SortAlgorithm. 1000. Total time: 405.800 mcs
PassedAsATemplateParameter_SortAlgorithm. 10000. Total time: 36.943 ms
PassedAsATemplateParameter_SortAlgorithm. 100000 Total time: 9.194 s
CompileTimeBuiltTemplate_SortAlgorithm. 1000. Total time: 403.900 mcs
CompileTimeBuiltTemplate_SortAlgorithm. 10000. Total time: 37.182 ms
CompileTimeBuiltTemplate_SortAlgorithm. 100000. Total time: 9.178 s
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 1000. Total time: 347.900 mcs
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 10000. Total time: 32.671 ms
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. 100000 Total time: 8.836 s
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 1000. Total time: 341.000 mcs
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 10000. Total time: 32.489 ms
PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. 100000 Total time: 8.871 s
CompileTimeBuiltInvocable_SortAlgorithm. 1000. Total time: 341.900 mcs
CompileTimeBuiltInvocable_SortAlgorithm. 10000. Total time: 32.331 ms
CompileTimeBuiltInvocable_SortAlgorithm. 100000 Total time: 8.825 s
```
