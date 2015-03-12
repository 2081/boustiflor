#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Server {
	int size, capacity;
	double score()
	{
		return capacity/(double)size;
	}

	Server( int s = 1, int c = 1):size(s),capacity(c)
	{}
};

int main(int argc, char** argv)
{
	int R,S,U,P,M;
	cin >> R >> S >> U >> P >> M;
	cout << R << endl;
	/*for( int i = 0; i < U; ++i){

	}*/
	return 0;
}