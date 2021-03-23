all: nvml.out

nvml.out: nvml.cpp
	g++ -c nvml.cpp -I /usr/local/cuda/include
	g++ nvml.o -I /usr/local/cuda/include -lnvidia-ml -L /usr/lib64/ -o nvml.out

clean:
	rm *.o nvml.out