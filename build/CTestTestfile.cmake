# CMake generated Testfile for 
# Source directory: /home/hamme/ece309_p3/working-P3
# Build directory: /home/hamme/ece309_p3/working-P3/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(p2_regression "/home/hamme/ece309_p3/working-P3/build/test_p2")
set_tests_properties(p2_regression PROPERTIES  WORKING_DIRECTORY "/home/hamme/ece309_p3/working-P3/build" _BACKTRACE_TRIPLES "/home/hamme/ece309_p3/working-P3/CMakeLists.txt;82;add_test;/home/hamme/ece309_p3/working-P3/CMakeLists.txt;0;")
add_test(p3 "/home/hamme/ece309_p3/working-P3/build/test_p3")
set_tests_properties(p3 PROPERTIES  WORKING_DIRECTORY "/home/hamme/ece309_p3/working-P3/build" _BACKTRACE_TRIPLES "/home/hamme/ece309_p3/working-P3/CMakeLists.txt;86;add_test;/home/hamme/ece309_p3/working-P3/CMakeLists.txt;0;")
add_test(tool_loop "/home/hamme/ece309_p3/working-P3/build/test_loop")
set_tests_properties(tool_loop PROPERTIES  WORKING_DIRECTORY "/home/hamme/ece309_p3/working-P3/build" _BACKTRACE_TRIPLES "/home/hamme/ece309_p3/working-P3/CMakeLists.txt;90;add_test;/home/hamme/ece309_p3/working-P3/CMakeLists.txt;0;")
add_test(e2e "bash" "/home/hamme/ece309_p3/working-P3/tests/e2e/run_e2e.sh" "/home/hamme/ece309_p3/working-P3/build/miniharness")
set_tests_properties(e2e PROPERTIES  WORKING_DIRECTORY "/home/hamme/ece309_p3/working-P3" _BACKTRACE_TRIPLES "/home/hamme/ece309_p3/working-P3/CMakeLists.txt;99;add_test;/home/hamme/ece309_p3/working-P3/CMakeLists.txt;0;")
