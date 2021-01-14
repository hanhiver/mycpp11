#include <string>
#include "estring.h"
DEFINE_ESTRING(pub0, 0x1e, ('-')('-')('-')('-')('-')('B')('E')('G')('I')('N')(' ')('P')('U')('B')('L')('I')('C')(' ')('K')('E')('Y')('-')('-')('-')('-')('-')('\n'))
DEFINE_ESTRING(pub1, 0x1e, ('M')('I')('G')('f')('M')('A')('0')('G')('C')('S')('q')('G')('S')('I')('b')('3')('D')('Q')('E')('B')('A')('Q')('U')('A')('A')('4')('G')('N')('A')('D')('C')('B')('i')('Q')('K')('B')('g')('Q')('D')('b')('d')('9')('k')('J')('l')('W')('Y')('H')('8')('y')('c')('h')('u')('S')('Q')('5')('x')('t')('y')('q')('u')('z')('M')('W')('\n'))
DEFINE_ESTRING(pub2, 0x1e, ('X')('z')('H')('6')('D')('W')('4')('V')('k')('j')('p')('j')('+')('W')('b')('O')('9')('2')('O')('e')('I')('b')('6')('A')('0')('f')('n')('T')('u')('w')('T')('8')('N')('2')('/')('Q')('M')('j')('Y')('z')('v')('0')('W')('V')('V')('U')('q')('6')('x')('N')('o')('l')('8')('V')('q')('6')('C')('x')('i')('4')('6')('f')('c')('V')('\n'))
DEFINE_ESTRING(pub3, 0x1e, ('Y')('2')('T')('g')('K')('P')('z')('l')('W')('9')('Z')('i')('q')('P')('c')('o')('C')('R')('g')('E')('N')('/')('n')('F')('r')('C')('7')('W')('X')('j')('X')('Z')('q')('O')('W')('3')('I')('g')('8')('Q')('f')('5')('E')('X')('H')('Q')('s')('T')('K')('3')('7')('X')('w')('D')('R')('D')('N')('O')('K')('X')('g')('X')('O')('8')('\n'))
DEFINE_ESTRING(pub4, 0x1e, ('x')('G')('C')('O')('B')('U')('9')('G')('O')('c')('B')('d')('D')('L')('G')('E')('8')('w')('I')('D')('A')('Q')('A')('B')('\n'))
DEFINE_ESTRING(pub5, 0x1e, ('-')('-')('-')('-')('-')('E')('N')('D')(' ')('P')('U')('B')('L')('I')('C')(' ')('K')('E')('Y')('-')('-')('-')('-')('-')('\n'))
DEFINE_ESTRING(pub6, 0x1e, ('n')('a')('j')('i')('u')('z')('h')('e')('y')('a')('n')('g')('b')('a')('\n'))
DEFINE_ESTRING(pub7, 0x1e, ('b')('u')('g')('u')('a')('n')(' ')(' ')('\\')('t')('\n'))
DEFINE_ESTRING(pub8, 0x1e, ('h')('a')('n')('d')('o')('n')('g')('\n'))
#define pub_length 9
std::string GetEstring_pub()
{
	std::string pub_str = "";
	pub_str += std::string(GetEstring_pub0());
	pub_str += std::string(GetEstring_pub1());
	pub_str += std::string(GetEstring_pub2());
	pub_str += std::string(GetEstring_pub3());
	pub_str += std::string(GetEstring_pub4());
	pub_str += std::string(GetEstring_pub5());
	pub_str += std::string(GetEstring_pub6());
	pub_str += std::string(GetEstring_pub7());
	pub_str += std::string(GetEstring_pub8());
	return pub_str;
}
