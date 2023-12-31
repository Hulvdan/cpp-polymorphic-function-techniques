#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <assert.h>

#include "benchmark/cppbenchmark.h"

//
// Helper functions
//
std::vector<int> GetVectorOfNumbers(const char* filename) {
    using defer = std::shared_ptr<void>;

    std::ifstream file;
    file.open(filename);
    defer _(nullptr, [&file](...){ file.close(); });

    std::vector<int> numbers = {};

    int number;
    while (file >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

//
// EXAMPLE 1. Our baseline. Compare function is inlined manually
//
void ManuallyInlined_SortAlgorithm(int* numbers, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            // It's bad because we will need to change these places everywhere in the codebase.
            // It's a matter of when we will forget to change it in some place
            auto cmp_result = numbers[i] < numbers[k] ? 1 : -1;
            if (cmp_result == -1) {
                auto t = numbers[i];
                numbers[i] = numbers[k];
                numbers[k] = t;
            }
        }
    }
}

//
// EXAMPLE 2. Compare function passed as a pointer-argument
//
inline int Compare_Variant1(int a, int b) {
    return a < b ? 1 : -1;
}

inline int Compare_Variant2(int a, int b) {
    return a < b ? -1 : 1;
}

void PassedAsAPointer_SortAlgorithm(int* numbers, int n, int (*cmp)(int, int)) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            // Now it's better. We can parametrize the behaviour.
            // But benchmarks show ~26% worse performance
            auto cmp_result = cmp(numbers[i], numbers[k]);
            if (cmp_result == -1) {
                auto t = numbers[i];
                numbers[i] = numbers[k];
                numbers[k] = t;
            }
        }
    }
}

//
// EXAMPLE 3. Compare function passed as a template-argument
// NOTE(hulvdan): Sometimes it shows a bit higher execution duration. I believe this is an error margin
//
template <int (*cmp)(int, int)>
constexpr void PassedAsATemplateParameter_SortAlgorithm(int* numbers, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if (cmp(numbers[i], numbers[k]) == -1) {
                auto t = numbers[i];
                numbers[i] = numbers[k];
                numbers[k] = t;
            }
        }
    }
}

//
// EXAMPLE 4. Using a factory for generating a sorting algorithm using templates
// NOTE(hulvdan): Sometimes it shows a bit higher execution duration. I believe this is an error margin
//
template <int (*cmp)(int, int)>
constexpr auto sort_alg_factory() {
    return [](int* numbers, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (cmp(numbers[i], numbers[k]) == -1) {
                    auto t = numbers[i];
                    numbers[i] = numbers[k];
                    numbers[k] = t;
                }
            }
        }
    };
}

static auto CompileTimeBuiltTemplate_SortAlgorithm =
    sort_alg_factory<Compare_Variant1>();

//
// EXAMPLE 5-6. Compare function passed as an rvalue std::invocable argument that is known at compile-time
//
void PassingRValueInvocableAsAnArgument_SortAlgorithm(
    int* numbers, int n, std::invocable<int, int> auto&& cmp_func
) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if (cmp_func(numbers[i], numbers[k]) == -1) {
                auto t = numbers[i];
                numbers[i] = numbers[k];
                numbers[k] = t;
            }
        }
    }
}

//
// EXAMPLE 7. Using a factory for generating a sorting algorithm using rvalue std::invocable lambda
//
constexpr auto sort_alg_factory_invocable(
    std::invocable<int, int> auto&& cmp_func
) {
    return [&cmp_func](int* numbers, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (cmp_func(numbers[i], numbers[k]) == -1) {
                    auto t = numbers[i];
                    numbers[i] = numbers[k];
                    numbers[k] = t;
                }
            }
        }
    };
}

static constexpr auto CompileTimeBuiltInvocable_SortAlgorithm =
    sort_alg_factory_invocable([](int a, int b) {
        return a < b ? 1 : -1;
    });

void Calculate()
{
    const char* filenames[] = {
        // "numbers_10.txt",
        // "numbers_100.txt",
        "numbers_1000.txt",
        "numbers_10000.txt",
        "numbers_100000.txt",
        // "numbers_1000000.txt",
        // "numbers_10000000.txt",
    };

    std::vector<std::vector<int>> vectors = {};
    for (auto filename : filenames) {
        auto numbers = GetVectorOfNumbers(filename);
        vectors.push_back(numbers);
    }

    auto benchmark = BENCHCODE_SCOPE("SortAlgorithm");

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("1. ManuallyInlined_SortAlgorithm. {}", numbers.size()));
            ManuallyInlined_SortAlgorithm(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("2. PassedAsAPointer_SortAlgorithm. {}", numbers.size()));
            PassedAsAPointer_SortAlgorithm(numbers.data(), numbers.size(), Compare_Variant2);
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("3. PassedAsATemplateParameter_SortAlgorithm. {}", numbers.size()));
            PassedAsATemplateParameter_SortAlgorithm<Compare_Variant1>(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("4. CompileTimeBuiltTemplate_SortAlgorithm. {}", numbers.size()));
            CompileTimeBuiltTemplate_SortAlgorithm(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known lambda. {}", numbers.size()));
            PassingRValueInvocableAsAnArgument_SortAlgorithm(
                numbers.data(),
                numbers.size(),
                [](int a, int b) { return a > b ? 1 : -1; }
            );
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("6. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a compile-time known function. {}", numbers.size()));
            PassingRValueInvocableAsAnArgument_SortAlgorithm(
                numbers.data(),
                numbers.size(),
                Compare_Variant1
            );
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("7. CompileTimeBuiltInvocable_SortAlgorithm. {}", numbers.size()));
            CompileTimeBuiltInvocable_SortAlgorithm(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }
}

int main(int argc, char** argv)
{
    int numbers[] = { 5,4,3,2,1 };
    ManuallyInlined_SortAlgorithm(numbers, 5);
    assert(numbers[0] == 1);
    assert(numbers[1] == 2);
    assert(numbers[2] == 3);
    assert(numbers[3] == 4);
    assert(numbers[4] == 5);

    Calculate();

    // const int THREADS = 8;
    //
    // // Start parallel calculations
    // std::vector<std::thread> threads;
    // for (int i = 0; i < THREADS; ++i)
    //     threads.push_back(std::thread(calculate));
    //
    // // Wait for all threads
    // for (auto& thread : threads)
    //     thread.join();

    // Report benchmark results
    BENCHCODE_REPORT();

    return 0;
}
