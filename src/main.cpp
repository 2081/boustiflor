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

	bool compare (Server s1, Server s2) { return (s1.score() < s2.score()); }
};

struct SubRow
{
	int size;
	int available;
	int x;
	Row* row;
	vector<Server*> servers;

	SubRow(int fsize, int fx = 0):size(fsize),x(fx){}

	bool compare (SubRow sb1, SubRow sb2) { return (sb1.available < sb2.available); }
};

struct Row
{
	vector<SubRow*> subRows;

	Row(int size)
	{
		subRows.push_back(new SubRow(size));
	}
	void disableSlot(int x)
	{
		for(int i = 0; i < subRows.size(); ++i)
		{
			int size = subRows[i]->size;
			int xx = subRows[i]->x;
			if( xx <= x  &&  x < xx+size)
			{
				int s2 = size - (x+1-xx);

				delete subRows[i];
				subRows.erase(subRows.begin()+i);

				subRows.insert(subRows.begin()+i, new SubRow( s2 ,x+1));
				subRows.insert(subRows.begin()+i, new SubRow( size - s2 -1, xx));
			}
		}
	}
};

int serv_alloc(Server* server, SubRow* subrow)
{
	if (server->size > subrow->available)
		cerr << "<ERR: Can't allocate a server in a smaller subrow." << endl; return -1;

	subrow->servers.insert(server);
	subrow-> available -= server->size;

	// Returns 0 if the subrow is full
	return subrow->available;
}

int main(int argc, char** argv)
{
	int R,S,U,P,M;
	cin >> R >> S >> U >> P >> M;
	cerr << R << ";" << S << ";"<< U << ";"<< P << ";" <<  endl;
	/*for( int i = 0; i < U; ++i){

	}*/
	Row r(2);

	const int ROW_SIZE = S, ROW_NUMBER = R, SERVER_NUMBER = M;

	vector<Server> servers = vector<Server>();

	vector<Server>[ROW_SIZE] available_servers;
	// vector<Row> rows;
	vector<SubRow> subrows = vector<SubRow>();

	sort(subrows.begin(), subrows.end(), SubRows::compare);

	sort(servers.begin(), servers.end(), Server::compare);

	for (vector<Server>::iterator it_serv = servers.begin(); it_serv != servers.end(); it_serv++)
	{
		for (vector<SubRow>::iterator it_subr = subrows.begin(); it_subr != subrows.end(); it_subr++)
		{
			if (it_serv->size == it_subr->size)
			{
				if (serv_alloc(it_serv, it_subr) == 0)
					subrows.erase(it_subr);
			}
		}
	}

	return 0;
}

/*************************************/
