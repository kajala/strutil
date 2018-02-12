/*
Example of strutil library usage.
*/
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning( disable : 4996 )
#endif // _MSC_VER

using namespace str;

/** Simple unit test "framework" */
#define check(A) if (A) {} else {printf( "ERROR @ %s(%d): (%s) is false\n", __FILE__, __LINE__, #A ); abort();}

void strutil_test()
{
	// load UTF-8 encoded text file
	FILE* fh = fopen( "data.txt", "r" );
	if ( !fh )
	{
		printf( "File not found\n" );
		return;
	}
	char_vector_type file;
	while (true)
	{
		int ch = fgetc(fh);
		if ( ch == EOF )
			break;
		file.push_back( char(ch) );
	}
	file.push_back(0);
	fclose(fh);
	string_type s = &file[0];

	unsigned ch = utf8_at(s,1);
	check( ch == 228 );
	check( ch == utf8_at(s,3) );
	check( utf8_len(s) == 28 );
	char buf[8];
	int bytes = utf8_encode( 228, buf );
	check( bytes == 2 );
	check( utf8_decode(buf) == 228 );
	check( trim("a bc") == "a bc" );
	check( trim("a bc  ") == "a bc" );
	check( trim("  a bc  ") == "a bc" );
	check( trim("  a bc") == "a bc" );
	check( ltrim("a bc") == "a bc" );
	check( ltrim("a bc  ") == "a bc  " );
	check( ltrim("  a bc  ") == "a bc  " );
	check( ltrim("  a bc") == "a bc" );
	check( rtrim("a bc") == "a bc" );
	check( rtrim("a bc  ") == "a bc" );
	check( rtrim("  a bc  ") == "  a bc" );
	check( rtrim("  a bc") == "  a bc" );
	check( ssprintf("123=%d",123) == "123=123" );
	check( uppercase("AbCd") == "ABCD" );
	check( lowercase("AbCd") == "abcd" );
	check( uppercase("AbCdäÖ") == "ABCDäÖ" );
	check( lowercase("AbCdäÖ") == "abcdäÖ" );
	check( to_wcs(to_utf8(to_wcs(trim(s)))) == to_wcs("Tämä on UTF-8 tekstitiedosto") );

	string_vector_type e = explode( ",", "jani,markus,kajala," );
	check( e.size() == 4 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( e[3] == "" );
	check( implode(",",e) == "jani,markus,kajala," );

	e = explode( ",", "jani,markus,kajala,," );
	check( e.size() == 5 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( e[3] == "" );
	check( e[4] == "" );
	check( implode(",",e) == "jani,markus,kajala,," );

	e = explode( ",", "jani,markus,kajala" );
	check( e.size() == 3 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( implode(",",e) == "jani,markus,kajala" );

	e = explode( ",", ",jani,markus,kajala" );
	check( e.size() == 4 );
	check( e[0] == "" );
	check( e[1] == "jani" );
	check( e[2] == "markus" );
	check( e[3] == "kajala" );
	check( implode(",",e) == ",jani,markus,kajala" );

	check( substr("abcd",1,2) == "bc" );
	check( substr("abcd",1,3) == "bcd" );
	check( substr("abcd",0,4) == "abcd" );
	check( substr("abcd",-1) == "d" );
	check( substr("abcd",0,-1) == "abc" );
	check( substr("abcd",0,-2) == "ab" );
	check( substr("myfile.dat",0,-4) == "myfile" );
	check( substr("myfile.dat",-4) == ".dat" );

	check( replace("\\","/","C:\\dos\\path\\") == "C:/dos/path/" );
	check( replace('\\','/',"C:\\dos\\path\\") == "C:/dos/path/" );

	check( str::basename("test.tmp") == "test.tmp" );
	check( str::basename("test.tmp",".tmp") == "test" );
	check( str::basename("a/b/test.tmp") == "test.tmp" );
	check( str::basename("a/b/test.tmp/") == "test.tmp" );
	check( str::basename("a/b/test.tmp/ ") == " " );

	check( dirname("") == "" );
	check( dirname("/") == "/" );
	check( dirname(" ") == "." );
	check( dirname("asdasd") == "." );
	check( dirname("asdasd/") == "." );
	check( dirname("/asdasd") == "/" );
	check( dirname("/asd/adas") == "/asd" );
	check( dirname("/asda/asd/") == "/asda" );

    printf("Tests OK\n");
}

int main()
{
	strutil_test();
	return 0;
}

// strutil library is copyright (C) 2009-2018 Jani Kajala (kajala@gmail.com). Licensed under BSD/MIT license.
