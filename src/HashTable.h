#include <string>
using namespace std;
#include "util.h"
#include "List.h"

/*
	Hash Table Class, uses a DJB2 Hash function
*/

const unsigned int DEFAULT_HASH_SIZE = 65536;

template <typename Element>
class HashTable
{
public:
    HashTable(int s = DEFAULT_HASH_SIZE)
    : size(s) { table = new List<Element>[size]; }


	/*
		Using DJB2 Hash Function
	*/
    unsigned int hash(const string & k) const
    {
/*        unsigned int     sum = 0;

        for (int i = 0; i < k.size(); i++)
            sum = ((sum << 5) + sum) + (k[i]);
*/
		unsigned int sum = DJBHash(k);
        return sum % size;
    }

    void install(const Element & x, const string & k)
    {
        table[hash(k)].insertBeforeFirst(x);
    }
	
	bool update(const Element & x, const string & k)
	{
		int i = hash(k);
		table[i].restart();
		if (table[i].pastLast()) {
			return false;
		}
		for (table[i].restart(); !table[i].pastLast(); table[i].goNext()) {
            if (table[i].getCurrent() == k) {
				table[i].changeCurrentVal(x);
				return true;
			}
		}
		return false;
	}

    bool lookup(Element & x, const string & k)
    {
        int     i = hash(k);
		table[i].restart();
		if (table[i].pastLast()) {
		  return false;
		}
        for (table[i].restart(); !table[i].pastLast(); table[i].goNext())
            if ((x = table[i].getCurrent()) == k)
                return true;
        table[i].restart();
        x = table[i].getCurrent();  // just put something in x
        return false;
    }
	
	~HashTable() {
		delete[] table;
	}

private:
    List<Element>   *table;
    int             size;
};

