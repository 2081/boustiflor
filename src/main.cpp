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
	int x;
	Row* row;
	vector<Server*> servers;

	SubRow(int fsize, int fx = 0):size(fsize),x(fx){}
};

struct Row
{
	vector<SubRow> subRows;

	Row(int size)
	{
		subRows.push_back(SubRow(size));
	}
	void disableSlot(int x)
	{
		vector<SubRow>::iterator it = subRows.begin();
	}
};

int main(int argc, char** argv)
{
	int R,S,U,P,M;
	cin >> R >> S >> U >> P >> M;
	cerr << R << ";" << S << ";"<< U << ";"<< P << ";" <<  endl;
	/*for( int i = 0; i < U; ++i){

	}*/
	Row r(2);

	return 0;
}