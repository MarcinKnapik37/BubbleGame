default: kod

%: %.cpp
	g++ kod.cpp -o Gra -lepoxy -lGL -lglfw -Wfatal-errors
clean:
	rm a.out *.o *~ Gra
