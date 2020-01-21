#include <cstdlib>
#include <stdlib.h>
#include <boost/regex.hpp>
#include <string>
#include <iostream> 

using namespace std; 
using namespace boost; 

bool validate_card_format(const std::string& s)
{
   static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
   return regex_match(s, e);
}

int main()
{
	std::string in; 
	cmatch what; 
	cout << "Enter testing string: " << endl;
	getline(cin, in);
	
	if (regex_match(in.c_str(), what, expression))
	{
		for (int i=0; i<what.size(); i++)
		{
			cout << "str: " << what[i].str() << endl;
		} 
	}
	else
	{
		cout << "ERROR input." << endl; 
	}
	
	return 0;
}
