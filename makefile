CC = gcc
TARG = review.o util.o
MAIN = main.c
ifeq ($(OS),Windows_NT) #delete function for different OS
	DELFUNC = del
else
	DELFUNC = rm -rf
endif

review: $(MAIN) $(TARG)
	$(CC) -o $@ $^

testwrite: review.c util.o
	$(CC) -o review $^ -DTESTWRITE

testedit: review.c util.o
	$(CC) -o review $^ -DTESTEDIT

testdel: review.c util.o
	$(CC) -o review $^ -DTESTDEL

testread: review.c util.o
	$(CC) -o review $^ -DTESTREAD

testcond: review.c util.o
	$(CC) -o review $^ -DTESTCONDI

testfile: review.c util.o
	$(CC) -o review $^ -DTESTFILE

clean:
	$(DELFUNC) $(TARG)
	$(DELFUNC) review
	$(DELFUNC) review.exe
