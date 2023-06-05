all: output knapsack.o

output: knapsack.o
      g++ knapsack.o -o output
      
knapsack.o: knapsack.cpp
      g++ -c knapsack.cpp
      
clean:
      rm *.o output
