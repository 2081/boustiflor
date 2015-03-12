#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Row;

struct Server
{
	int size, capacity;
	double score()
	{
		return capacity/(double)size;
	}

	Server( int s = 1, int c = 1):size(s),capacity(c)
	{}
};

struct SubRow
{
	int size;
	int available;
	Row* row;
	vector<Server*> servers;
};

struct Row
{
	vector<SubRow> subRows;
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