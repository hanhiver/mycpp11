#include <iostream> 
#include <string> 
#include <sstream> 
#include <fstream>

std::string readKeyFile(std::string filename)
{
	std::string keyFromFile;
	std::ifstream inputFile;
	inputFile.open(filename, std::ios_base::out);
	std::ostringstream buf; 
	char ch;
	while(buf && inputFile.get(ch))
	{
		buf.put(ch);
	}
	inputFile.close();
	return buf.str();
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " filename" << std::endl;
		return -1; 
	}
	else
	{
		std::cout << readKeyFile(argv[1]) << std::endl;
	}

	return 0;
}

