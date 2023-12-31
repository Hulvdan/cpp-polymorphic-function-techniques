#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

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
// EXAMPLE 1. Inlined manually
//
void ManuallyInlined_SortAlgorithm(int* numbers, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            auto cmp_result = numbers[i] > numbers[k] ? 1 : -1;
            if (cmp_result == -1) {
                std::swap(numbers[i], numbers[k]);
            }
        }
    }
}

//
// EXAMPLE 2. Passing function as an argument
//
inline int Compare_Variant1(int a, int b) {
    return a > b ? 1 : -1;
}

inline int Compare_Variant2(int a, int b) {
    return a > b ? -1 : 1;
}

void PassedAsAPointer_SortAlgorithm(int* numbers, int n, int (*cmp)(int, int)) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            auto cmp_result = cmp(numbers[i], numbers[k]);
            if (cmp_result == -1) {
                std::swap(numbers[i], numbers[k]);
            }
        }
    }
}

//
// EXAMPLE 3. Using templates and inlining the function inside
//
template <int (*cmp_func)(int, int)>
constexpr auto sort_alg_factory() {
    return [](int* numbers, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (cmp_func(numbers[i], numbers[k]) == -1) {
                    std::swap(numbers[i], numbers[k]);
                }
            }
        }
    };
}

static auto CompileTimeParametrized_SortAlgorithm =
    sort_alg_factory<Compare_Variant1>();

//
// EXAMPLE 4. Using std::invocable with a factory while passing a lambda as a rvalue
//
constexpr auto sort_alg_factory_invocable(
    std::invocable<int, int> auto&& cmp_func
) {
    return [&cmp_func](int* numbers, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (cmp_func(numbers[i], numbers[k]) == -1) {
                    std::swap(numbers[i], numbers[k]);
                }
            }
        }
    };
}

static constexpr auto CompileTimeInvocable_SortAlgorithm =
    sort_alg_factory_invocable([](int a, int b) {
        return a > b ? 1 : -1;
    });

//
// EXAMPLE 5. Using std::invocable without a factory
//
void PassingRValueInvocableAsAnArgument_SortAlgorithm(
    int* numbers, int n, std::invocable<int, int> auto&& cmp_func
) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if (cmp_func(numbers[i], numbers[k]) == -1) {
                std::swap(numbers[i], numbers[k]);
            }
        }
    }
}

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

            auto phase = benchmark->StartPhase(std::format("3. CompileTimeParametrized_SortAlgorithm. {}", numbers.size()));
            CompileTimeParametrized_SortAlgorithm(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("4. CompileTimeInvocable_SortAlgorithm. {}", numbers.size()));
            CompileTimeInvocable_SortAlgorithm(numbers.data(), numbers.size());
            phase->StopPhase();
        }
    }

    {
        for (int i = 0; i < vectors.size(); i++) {
            std::vector<int> numbers(vectors[i]);

            auto phase = benchmark->StartPhase(std::format("5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a lambda that is known at compile time. {}", numbers.size()));
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

            auto phase = benchmark->StartPhase(std::format("5. PassingRValueInvocableAsAnArgument_SortAlgorithm. Passing a function pointer that is known at compile time. {}", numbers.size()));
            PassingRValueInvocableAsAnArgument_SortAlgorithm(
                numbers.data(),
                numbers.size(),
                Compare_Variant1
            );
            phase->StopPhase();
        }
    }
}

int main(int argc, char** argv)
{
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
