
#include <cinttypes>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

#define LIMIT 10000

int primesList[1250];
int numprimes;

uint64_t iscompound[1+((LIMIT + 1)>>6)];

void fillprimes(int upperBound);

inline int digitsignature(int v){
	int digits[10] = { 0 };
	int d;
	while (v > 9) {
		d = v % 10;
		digits[d]++;
		v /= 10;
	}
	digits[v]++;

	int sig = 0;
	for (int i = 9; i >= 0; i--) {
		d = digits[i];
		while (d-- > 0) {
			sig = 10 * sig + i;
		}
	}

	return sig;
}

int main()
{
	int solution[3];

    fillprimes(LIMIT);

	map<int, vector<int>> primedigits;

	for(int i = 0; i < numprimes; i++){
		int p = primesList[i];
		int sig = digitsignature(p);
		primedigits[sig].push_back(p);
	}

	map<int, set<int>> diffsset;
	for(auto &it: primedigits){
		vector<int> &v = it.second;
		if(v.size()>=3){
			diffsset.clear();
			for(int i = 0; i < v.size(); i++){
				for(int j = i+1; j < v.size(); j++){
					diffsset[v[j]-v[i]].emplace(v[i]);
					diffsset[v[j]-v[i]].emplace(v[j]);
				}
			}

			for(auto &ot: diffsset){
				if(ot.second.size()%2 == 1){
					for(int vvv:ot.second){
						cout << vvv;
					}
					cout << endl;
				}
			}
		}
	}
}


void fillprimes(int upperBound) {
	int i, j;

	baset(iscompound, 0);
	baset(iscompound, 1);
	for (i = 2; i*i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}
}