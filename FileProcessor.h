#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class FileIO
{
private:
	ofstream out;
	ifstream in;
public:
	FileIO()
	{}



	void writeToFile(string name, string data)  //Writes the provided data to the given file i.e name(format: C://project/new.txt)
	{
		try{
			out.open(name, ios::binary);
		}
		catch (...)
		{
			cout << "Output File Error.";
		}

		out << data;



		out.close();
	}



	string readFromFile(string name)  //Reads data from the provided file i.e name(format: C://project/new.txt)
	{

		string buffer = "", line;
		try{
			in.open(name, ios::binary);
		}
		catch (...)
		{
			cout << "Input File Error.";
		}
		while (!in.eof())
		{
			getline(in, line);
			buffer = buffer + line + "\n";
		}
		in.close();
		return buffer;
	}



	void writeToFile(ofstream &kout, string data)  //Writes the provided data to the file passed in argument
	{
		if (!kout.is_open())
		{
			cout << "Error: File not open. Write failed!.";
		}
		kout << data;




	}



	string readFromFile(ifstream &kfin)  //Reads data from the file passed in argument
	{
		if (!kfin.is_open())
		{
			cout << "Error: File not Open. Read Failed!";
		}

		string buffer = "", line;



		while (!kfin.eof())
		{
			getline(kfin, line);
			buffer = buffer + line + "\n";
		}

		return buffer;
	}













};


#endif