add_test([=[ExampleTest.AlwaysTrue]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=ExampleTest.AlwaysTrue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExampleTest.AlwaysTrue]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[sample_test_case.sample_test]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=sample_test_case.sample_test]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[sample_test_case.sample_test]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestCaseInvertedIndex.TestBasic]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=TestCaseInvertedIndex.TestBasic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestCaseInvertedIndex.TestBasic]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestCaseInvertedIndex.TestBasic2]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=TestCaseInvertedIndex.TestBasic2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestCaseInvertedIndex.TestBasic2]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestCaseInvertedIndex.TestInvertedIndexMissingWord]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=TestCaseInvertedIndex.TestInvertedIndexMissingWord]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestCaseInvertedIndex.TestInvertedIndexMissingWord]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestCaseSearchServer.TestSimple]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=TestCaseSearchServer.TestSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestCaseSearchServer.TestSimple]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestCaseSearchServer.TestTop5]=]  E:/search_engine/cmake-build-debug/search_engine_test.exe [==[--gtest_filter=TestCaseSearchServer.TestTop5]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestCaseSearchServer.TestTop5]=]  PROPERTIES WORKING_DIRECTORY E:/search_engine/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  search_engine_test_TESTS ExampleTest.AlwaysTrue sample_test_case.sample_test TestCaseInvertedIndex.TestBasic TestCaseInvertedIndex.TestBasic2 TestCaseInvertedIndex.TestInvertedIndexMissingWord TestCaseSearchServer.TestSimple TestCaseSearchServer.TestTop5)
