all : kmeans
kmeans : kmeans.o
	g++ kmeans.o -g -o kmeans
kmeans.o:kmeans.cpp
	g++ -c -g kmeans.cpp
clean:
	rm -rf *.o kmeans
