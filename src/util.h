/*
	Collection of utility functions as needed
*/

/*
	DJB2 Hash Function Implementation from https://www.programmingalgorithms.com/algorithm/djb-hash?lang=C%2B%2B
*/
static unsigned int DJBHash(string str) {
	unsigned int len = str.length();
	unsigned int hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < len; i++)
	{
		hash = ((hash << 5) + hash) + (str[i]);
	}

	return hash;
}
