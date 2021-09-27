Project5: main.o linkedListOperations.o 
	g++ -o Project5 main.o linkedListOperations.o 

main.o: main.cpp linkedList.h
	g++ -c main.cpp

linkedListOperations.o: linkedListOperations.cpp linkedList.h
	g++ -c linkedListOperations.cpp

run:
	./Project5

clean:
	rm main.o linkedListOperations.o Project5

