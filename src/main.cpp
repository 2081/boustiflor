#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

	static bool compare (Server* s1, Server* s2) { return (s1->score() < s2->score()); }
};

struct SubRow
{
	int size;
	int available;
	int x;
	Row* row;
	vector<Server*> servers;

	SubRow(int fsize, int fx = 0):size(fsize),x(fx){}

	static bool compare (SubRow* sb1, SubRow* sb2) { return (sb1->available < sb2->available); }

	void print()
	{
		cerr << "(" << x << " [" << size << 
			"] " << x+size-1 << ")";
	}
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

	void print()
	{
		for(int i = 0; i < subRows.size(); ++i)
		{
			cerr <<  " | ";
			subRows[i]->print();
		}
		cerr << endl;
	}
};

int serv_alloc(Server* server, SubRow* subrow)
{
	if (server->size > subrow->available)
		cerr << "<ERR: Can't allocate a server in a smaller subrow." << endl; return -1;

	subrow->servers.push_back(server);
	subrow->available -= server->size;

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
	const int ROW_SIZE = S, ROW_NUMBER = R, SERVER_NUMBER = M,
				UNAVAILABLE_NUMBER = U, POOL_NUMBER = P;

	Row * rows[ROW_NUMBER];
	for( int i = 0; i < ROW_NUMBER; ++i)
	{
		rows[i] = new Row(S);
	}

	// Disabling unavailable slots
	for( int i = 0; i < UNAVAILABLE_NUMBER; ++i)
	{
		int ri,si;
		cin >> ri >> si;
		rows[ri]->disableSlot(si);
		//rows[ri]->print();
	}

	vector<Server*> servers = vector<Server*>();

	//getting servers
	for( int i = 0; i < SERVER_NUMBER; ++i)
	{
		int zi,ci;
		cin >> zi >> ci;
		servers.push_back(Server(zi,ci));
	}


	vector<Server*> available_servers[ROW_SIZE];
	// vector<Row> rows;
	vector<SubRow*> subrows = vector<SubRow*>();

	sort(subrows.begin(), subrows.end(), SubRow::compare);

	sort(servers.begin(), servers.end(), Server::compare);

	for (vector<Server>::iterator it_serv = servers.begin(); it_serv != servers.end(); it_serv++)
	{
		for (vector<SubRow>::iterator it_subr = subrows.begin(); it_subr != subrows.end(); it_subr++)
		{
			if (it_serv->size == it_subr->size)
			{
				if (serv_alloc(it_serv, it_subr) == 0)
					subrows.erase(it_subr);
				break;
			}
		}
	}

	for (int i = 0; i < servers.size(); i++)
	{
		for (int j = 0; j < subrows.size(); j++)
		{
			if (servers[i].size <= subrows[j].size)
			{
				if (serv_alloc(servers.[i], subrows.[j]) == 0)
					subrows.erase(subrows.[j]);
				break;
			}
		}
	}

	

	return 0;
}

/*************************************/
