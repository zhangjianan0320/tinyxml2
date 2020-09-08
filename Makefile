CC=g++
OBJECT=edit
SOURCE=$(wildcard *.cpp)
$(OBJECT):$(SOURCE)
	$(CC) $(SOURCE) -o $@

clean:
	rm edit
