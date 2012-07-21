CXX		=	g++
CXXFLAGS	=	-g -O3 -Wall

SRCFILES	=	$(wildcard *.cpp)
OBJFILES	=	$(patsubst %.cpp, %.o, $(SRCFILES))


all:		predict

predict:	$(OBJFILES)
		$(CXX) $(CXXFLAGS) $^ -o $@

%.o:		%.cpp %.h
		$(CXX) $(CXXFLAGS) $< -c
clean:
		rm -f predict $(OBJFILES)
