# GPS 

CXXFLAGS = -g -I . -I c:/boost_1_38_0/

objects = main.o gps.o stlutil.o 

gps.exe : $(objects)
	g++ -g -o gps.exe -g $(objects)

gps.o : gps.h stlutil.h
main.o: main.cpp stlutil.h
stlutil.o: stlutil.cpp stlutil.h

.PHONY : clean

TAGS : gps.h stlutil.h main.cpp stlutil.cpp gps.cpp
	maketags.bat

clean:
	rm $(objects)






