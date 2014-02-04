build:
	g++ tema3.cpp -o tema3 -Wall

.PHONY : clean
clean:
	rm -f tema3 *~
