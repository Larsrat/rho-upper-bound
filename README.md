# rho-upper-limit
Programs for running tests in evaluating the upper limit for the constant rho.
These programs are part of my project in the course DD2467 Individual Project in Theoretical Computer Science.

## Description
main.cpp contains the main deterministic tests. If this program is run, it will tests all graphs between the sizes 3x3 and 6x6 for their rho constants and give four files of output. 

bigger_tests.cpp is for running the random tests on the graphs of sizes 7x7 to 9x9. These are run for 24 hours per size of a graph. 
That is 24 hours for tests with random graphs of the size 7x7, 24 hours for tests with random graphs of the size 8x8 and 24 hours for the tests with random graphs of the size 9x9.

check_single_graph.cpp can be used for testing a single graph, given that you have the dimensions of the graph as well as its proper integer representation. 

get_graph.cpp can be used to print the matrix representation for a graph, given that you have the dimensions of the graph as well as its proper integer representation. 
