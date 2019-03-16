# Smart Neural Fuzzer

## Research Proposal
Fuzzing is one of the main techniques for automated software testing. 
A fuzzer generates semi-random inputs to the program that is being tested, 
trying to generate test cases that cause crashes, memory leaks, 
or other detectable problems with the program. 
By finding the inputs that crash the program, 
bugs that are otherwise extremely hard to find in the source code can be detected. 
However, the problem with current state-of-the-art fuzzers 
is that they generate mostly random input data. 
Some of them also try to guide their test cases 
using optimization algorithms such as genetic algorithms. 
But all of them are far from being smart and targeted, 
and so they still find bugs mostly by chance. 
It would be much more efficient if a fuzzer could take advantage of 
the semantic structure of the program to ensure all parts of the code base 
are thoroughly tested with many different values. 
That's what this research intends to accomplish: 
train a neural net to specifically target untested corner cases 
and thereby discover bugs much more systematically and rapidly.

The first step of this is to instrument a program, 
inject bits of code into the program that will trace its structure 
so that the neural net can understand and mimic its structure. 
This will be done through an LLVM optimization pass. 
LLVM is the major compiler infrastructure for low-level languages such as C and C++. 
It handles parsing programs into an intermediate representation (IR), 
applying a series of optimization passes to this IR, 
and then generating machine code for many different backend operating systems and processors. 
I will write an LLVM optimization pass that injects instrumentation code into the program 
that will trace every branch—every if-else statement, 
every decision the program makes---so that one can see the entire path of the program execution. 
LLVM already has its own Sanitizer Coverage tool that does similar tracing, 
but it can't trace the exact execution path of a program, 
and that is what our new Branch Coverage tool will do.

By using a normal fuzzer to test a Branch Coverage instrumented program, 
we can generate complete traces of the program's different execution paths for each input. 
We can then train a neural net to match the execution path to its input, 
allowing us to use the neural net to predict the input that will generate a particular execution path. 
Since the execution path is expressed as a series of binary decisions, 
we will know exactly how to change the execution path to expose untested parts of the program. 
The neural net can then predict the input that will generate that execution path, 
meaning we can generate targeted test cases that will systematically test every part of the program.

This two-stage smart fuzzer is our final goal. 
It will use the Branch Coverage tool to trace a program using a normal fuzzer, 
use that data to train the neural net, which will then systematically hunt for bugs. 
If we can get this all to work smoothly and discover bugs in major, widely-used programs, 
that will be an enormous success, allowing us to discover critical bugs 
in programs we use every day at an unprecedented rate. 
First, though, we will want to get our smart fuzzer to expose contrived bugs in sample programs.

