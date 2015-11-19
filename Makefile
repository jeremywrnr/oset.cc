bin=oset
run: compile
	./$(bin)
compile:
	g++ *.cc -o $(bin)
clean:
	rm -v $(bin)
