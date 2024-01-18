.SUFFIXES : .cpp

CC = g++

CXXFLAGS = -g -std=c++11

OBJS = BSTDriver.o

TARGET = fin

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

clean:
	rm -f $(OBJS) $(TARGET) core

zipIt:
	zip -r Galindo_J_FINAL.zip BSTDriver.cpp actormovie.h BSTree.h Node.h *.h README makefile