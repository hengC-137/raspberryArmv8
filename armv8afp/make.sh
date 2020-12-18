as  -o test.o test.S -mfloat-abi=softfp -mfpu=neon -march=armv8-a
gcc -c gflops_benchmark.c
gcc -o gflops_benchmark gflops_benchmark.o test.o