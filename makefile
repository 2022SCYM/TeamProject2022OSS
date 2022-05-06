CC = gcc
TARG = review.o util.o

testwrite: review.c util.o
	$(CC) -o review $^ -DTESTWRITE

testedit: review.c util.o
	$(CC) -o review $^ -DTESTEDIT

testdel: review.c util.o
	$(CC) -o review $^ -DTESTDEL

clean:
	del $(TARG)
	del *.exe
	rm -rf $(TARG)
	rm -rf *.exe