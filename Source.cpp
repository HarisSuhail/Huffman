#include "LinkedList.h"
#include "LinkedList.cpp"
#include "BinaryTree.h"
#include "HuffmanNode.h"
#include "Processor.h"
#include "FileProcessor.h"
#include <chrono>
#include <windows.h>
#include <stdio.h>
using namespace std::chrono;

struct filenames
{
	string toCompress;
	string compressed;
	string decompressed;
};
int menu()
{



	int choice;
	cout << "                   ___  ___ _________  " << endl;
	cout << "                  / _ \\/ _ /_  __/ _ | " << endl;
	cout << "                 / // / __ |/ / / __ | " << endl;
	cout << "                /____/_/ |_/_/ /_/ |_| " << endl;

	cout << endl;

	cout << "   _________  __  ______  ___  ____________________  _  __ " << endl;
	cout << "  / ___/ __ \\/  |/  / _ \\/ _ \\/ __/ __/ __/  _/ __ \\/ |/ /" << endl;
	cout << " / /__/ /_/ / /|_/ / ___/ , _/ _/_\\ \\_\\ \\_/ // /_/ /    /" << endl;
	cout << " \\___/\\____/_/  /_/_/  /_/|_/___/___/___/___/\\____/_/|_/" << endl;


	filenames f;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "1.Compress File\n2.Decompress File\n3.Exit\nChoice:";
	cin >> choice;
	return choice;
}










int main()
{	
	FileIO s;
	string y;
	Processor q, p, r;
	string sd;
	high_resolution_clock::time_point t1, t2;
	string name, temp;
	while (1)
	{

		switch (menu())
		{
		case 1:
			cout << "Enter name of text file to compress:";
			cin >> name;
			system("cls");

			q.compressFile(name+".txt", name+".hf");
			temp = name + ".txt";
			remove(temp.c_str());
			q.clear();
			break;
		case 2:
			cout << "Enter name of file to decompress:";
			cin >> name;
			system("cls");
			q.decompressFile(name + ".hf", name + ".txt");
			temp = name + ".hf";
			remove(temp.c_str());
			q.clear();
			break;
		default:
			cout << "Exiting Program";
			fflush(stdin);
			getchar();
			return 0;



		}
		system("cls");
	}
	
	
}


