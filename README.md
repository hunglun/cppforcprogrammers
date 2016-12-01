# cppforcprogrammers
Homework : C++ For C Programmers (Coursera Course)

Os-MacBook-Pro:cppforcprogrammers hl$ make

Os-MacBook-Pro:cppforcprogrammers hl$ ./build/dikjstra

[==========] Running 5 tests from 1 test case.  
[----------] Global test environment set-up.  
[----------] 5 tests from DikjstraTest  
[ RUN      ] DikjstraTest.SingleNodeGraph  
[       OK ] DikjstraTest.SingleNodeGraph (0 ms)  
[ RUN      ] DikjstraTest.DoubleNodeGraph  
0[0]  
1<--0  
[       OK ] DikjstraTest.DoubleNodeGraph (0 ms)  
[ RUN      ] DikjstraTest.MultiNodeGraph1  
0[0]  
2[2]  
1[3]  
4[4]  
3<--2  
2<--0  
[       OK ] DikjstraTest.MultiNodeGraph1 (0 ms)  
[ RUN      ] DikjstraTest.MultiNodeGraph2  
0[0]  
2[1]  
4[2]  
3[4]  
5[5]  
6[6]  
7[13]  
8[14]  
9<--7  
7<--5  
5<--3  
3<--2  
2<--0  
[       OK ] DikjstraTest.MultiNodeGraph2 (0 ms)  
[ RUN      ] DikjstraTest.NodeTest  
[       OK ] DikjstraTest.NodeTest (0 ms)  
[----------] 5 tests from DikjstraTest (0 ms total)  
  
[----------] Global test environment tear-down  
[==========] 5 tests from 1 test case ran. (1 ms total)  
[  PASSED  ] 5 tests.  
