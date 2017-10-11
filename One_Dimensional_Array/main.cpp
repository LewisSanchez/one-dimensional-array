#include <crtdbg.h>
#include <Windows.h>
#include <cassert>
#include <iostream>
#include "Array.h"
#include "Exception.h"
#include <string>
using std::string;

#define _CRTDBG_MAP_ALLOC

const size_t GREEN = 10;
const size_t RED = 12;
const size_t WHITE = 23;
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RunTests();
void PrintTestHeader(const char * testName);
void PrintTestPass(const char * test);
void PrintTestFail(const char * test, const char * message);
void TestConstructor();
void TestCopyConstructor();
void TestAssignmentOperator();
void TestingIndexer();
void TestingConst();

int main()
{
	RunTests();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;	
}

void RunTests()
{
	TestConstructor();
	TestCopyConstructor();
	TestAssignmentOperator();
	TestingIndexer();
	TestingConst();

}

void PrintTestHeader(const char * testName)
{
	std::cout << "\n********** " << testName << " **********" << std::endl;
}

void PrintTestPass(const char * test)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << '\t' << test << ": TEST PASS" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void PrintTestFail(const char * test, const char * message)
{
	SetConsoleTextAttribute(hConsole, RED);
	std::cerr << message << std::endl;
	std::cerr << '\t' << test << ": TEST FAIL" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void TestConstructor()
{
	const char * test = "Constructor";
	PrintTestHeader(test);

	try
	{
		Array<int> array1;

		assert(array1.getLength() == 0);
		assert(array1.getStartIndex() == 0);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestCopyConstructor()
{
	const char * test = "Copy Constructor";
	PrintTestHeader(test);

	try
	{
		Array<int> array1;
		array1.setLength(1);
		array1[0] = 5;

		Array<int> array2(array1);

		assert(array2.getLength() == 1);
		assert(array2[0] == 5);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestAssignmentOperator()
{
	const char * test = "Assignment Operator";
	PrintTestHeader(test);

	try
	{
		int length = 5;
		int start_index = 0;
		Array<int> array1(length, start_index);
		Array<int> array2;

		size_t values[] = { 5, 15, 25, 35, 45 };

		for (size_t i = 0; i < 5; ++i)
			array1[i] = values[i];

		array2 = array1;

		for (size_t i = 0; i < 5; ++i)
		{
			assert(array2[i] == values[i]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingIndexer()
{
	const char * test = "Indexer";
	PrintTestHeader(test);

	try
	{
		int length = 5;
		int start_index = 0;
		Array<int> array1(length, start_index);

		size_t values[] = { 5, 15, 25, 35, 45 };

		for (size_t i = 0; i < 5; ++i)
			array1[i] = values[i];

		for (size_t i = 0; i < 5; ++i)
		{
			assert(array1[i] == values[i]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingConst()
{
	const char * test = "Testing const: Expecting an exception";
	PrintTestHeader(test);

	try
	{
		const Array<int> array1;
		const int value = array1[0];
	}
	catch (Exception msg)
	{
		std::cerr << msg.getMessage();
		PrintTestPass(test);
	}
}