CC = g++

method1:
	$(CC) a1_part3_method1.cpp -o a1_part3_method1 -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

method2:
	$(CC) a1_part3_method2.cpp -o a1_part3_method2 -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

method3:
	$(CC) a1_part3_method3.cpp -o a1_part3_method3 -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

method4:
	$(CC) a1_part3_method4.cpp -o a1_part3_method4 -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

run_method1:
	./a1_part3_method1

run_method2:
	./a1_part3_method2

run_method3:
	./a1_part3_method3

run_method4:
	./a1_part3_method4

clean:
	$(RM) a1_part3_method1 a1_part3_method2 a1_part3_method3 a1_part3_method4 utility
.PHONY: clean
