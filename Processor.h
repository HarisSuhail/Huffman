#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "BinaryTree.h"
#include "HuffmanNode.h"
#include "FileProcessor.h"
#include "LinkedList.h"
#include "Display.h"
#include <string>

struct code{
	char codeChar;
	int codeInt;
	int codeLength;
	bool isFull;
	code()
	{
		isFull = false;
	}
};



class Processor{

private:
	Tree<HNode> *thetree, temp1, temp2;
	HNode *thenode;
	List<Tree<HNode>> priorityQueue, frequencyTable;
	bool initialized;
	bool formed;


public:

	//This function clears all varible values stored in the current processor object. This is useful if the same processor is used 
	//for compression and decompression
	void clear()
	{
		initialized = formed = false;
		List<Tree<HNode>> x;
		priorityQueue = x;
		frequencyTable = x;
	}

	//The two functions below are for bitwise manipulation of data and to assign code characters to the characters to be compressed. For example 
	//if 'a' is coded with 1011 then the function below will return a char such that it will be 1011000 (8 bits). Similarly, the function below 
	//the char one will return 10110000 00000000 00000000 00000000 (32 bits of an int). As such these two functions "Package" code values in 
	//variables.
	char getCodeChar(string t)
	{
		char code = 0;
		for (int i = 0; i < t.length(); i++)
		{
			if (i == 8)
			{
				cout << "Error: Exceed Packet Size";
				break;
			}
			if (t[i] == '1')
				code = code | getOnePosition(i);
		}
		return code;


	}
	int getCodeInt(string t)
	{
		int code = 0;

		int i;
		for (i = 0; i < t.length(); i++)
		{
			if (i == 32)
			{

				cout << "Error: Packet Size Exceeded!";
				break;
			}
			if (t[i] == '1')
				code = code | getOnePositionInt(i);
		}

		return code;


	}



	//The two functions below take an open file and compress it. The lower one of the two has an additional functionality of writing the
	//compressed string directly to the open output file.
	string encode(ifstream& fin)
	{
		string coded = "", tempstr;
		char packet = 0, temp = 0, shiftedRight = 0, shiftedLeft = 0;
		int counter = 0;
		temp1 = priorityQueue.pop();
		priorityQueue.push(temp1);
		code arr[256];
		//ADD PSEUDO EOF
		string eofCode = temp1.getCode(1);
		int eofInt = getCodeInt(eofCode);
		int eofLength = eofCode.length();
		//DONE ADDING PSEUDO EOF
		char t;
		int co;
		int len;
		int sl;
		int effectiveLength;
		string buffstr;
		while (1)
		{

			fin.get(temp);
			if (fin.eof())break;
			if (arr[temp].isFull == false)
			{
				tempstr = temp1.getCode(temp);
				arr[temp].codeLength = tempstr.length();
				arr[temp].codeInt = getCodeInt(tempstr);
				arr[temp].isFull = true;

			}

			co = arr[temp].codeInt;
			len = arr[temp].codeLength;




			for (int j = 0; j < (len / 8) + 1; j++)
			{
				t = 0;
				t = (unsigned char)t | (unsigned int)((unsigned int)co >> ((3 - (unsigned int)j) * 8));
				if (j == (len / 8))
					effectiveLength = len % 8;
				else
				{
					effectiveLength = 8;

				}
				shiftedRight = shiftedLeft = 0;
				shiftedRight = (unsigned char)t >> (unsigned int)counter;
				shiftedLeft = t << (8 - counter);
				packet = packet | shiftedRight;

				if (counter + effectiveLength > 7)
				{
					coded += packet;
					packet = 0;


					packet = packet | shiftedLeft;
				}

				counter = (counter + effectiveLength) % 8;
			}
		}

		co = eofInt;
		len = eofLength;
		for (int j = 0; j < (len / 8) + 1; j++)
		{
			t = 0;
			t = (unsigned char)t | (unsigned int)((unsigned int)co >> ((3 - (unsigned int)j) * 8));
			if (j == (len / 8))
				effectiveLength = len % 8;
			else
			{
				effectiveLength = 8;

			}
			shiftedRight = shiftedLeft = 0;
			shiftedRight = (unsigned char)t >> (unsigned int)counter;
			shiftedLeft = t << (8 - counter);
			packet = packet | shiftedRight;

			if (counter + effectiveLength > 7)
			{
				coded += packet;
				packet = 0;


				packet = packet | shiftedLeft;
			}

			counter = (counter + effectiveLength) % 8;
		}



		if (counter != 0)
		{
			coded += packet;
			packet = 0;
		}
		return coded;

	}
	void encode(ifstream& fin, ofstream& fout)
	{
		if (!fout.is_open())
		{
			cout << "\nError while encoding: output file not open.\n";
		}
		string  tempstr;
		char packet = 0, temp = 0, shiftedRight = 0, shiftedLeft = 0;
		int counter = 0;
		temp1 = priorityQueue.pop();
		priorityQueue.push(temp1);
		code arr[256];
		//ADD PSEUDO EOF
		string eofCode = temp1.getCode(1);
		int eofInt = getCodeInt(eofCode);
		int eofLength = eofCode.length();
		//DONE ADDING PSEUDO EOF
		char t;
		int co;
		int len;
		int sl;
		int effectiveLength;
		unsigned char usc;
		//display
		int total, current = 0;
		fin.seekg(0, ios::end);
		total = fin.tellg();
		fin.seekg(0, ios::beg);
		progressBar pbar(60, 2, 5, 5);
		pbar.setTitle("Compressing");
		pbar.drawOutline();
		int times = (total) / 10 + 1;
		//display



		while (1)
		{

			//display
			current++;
			if (!(current%times))
			{
				pbar.setProgress(current, total);
				pbar.update();
			}

			//display

			fin.get(temp);


			usc = temp;
			if (fin.eof())break;
			if (arr[usc].isFull == false)
			{
				tempstr = temp1.getCode(temp);
				arr[usc].codeLength = tempstr.length();
				arr[usc].codeInt = getCodeInt(tempstr);
				arr[usc].isFull = true;

			}

			co = arr[usc].codeInt;
			len = arr[usc].codeLength;





			for (int j = 0; j < (len / 8) + 1; j++)
			{
				t = 0;
				t = (unsigned char)t | (unsigned int)((unsigned int)co >> ((3 - (unsigned int)j) * 8));
				if (j == (len / 8))
					effectiveLength = len % 8;
				else
				{
					effectiveLength = 8;

				}
				shiftedRight = shiftedLeft = 0;
				shiftedRight = (unsigned char)t >> (unsigned int)counter;
				shiftedLeft = t << (8 - counter);
				packet = packet | shiftedRight;

				if (counter + effectiveLength > 7)
				{
					fout << packet;
					packet = 0;


					packet = packet | shiftedLeft;
				}

				counter = (counter + effectiveLength) % 8;
			}
		}

		co = eofInt;
		len = eofLength;
		for (int j = 0; j < (len / 8) + 1; j++)
		{
			t = 0;
			t = (unsigned char)t | (unsigned int)((unsigned int)co >> ((3 - (unsigned int)j) * 8));
			if (j == (len / 8))
				effectiveLength = len % 8;
			else
			{
				effectiveLength = 8;

			}
			shiftedRight = shiftedLeft = 0;
			shiftedRight = (unsigned char)t >> (unsigned int)counter;
			shiftedLeft = t << (8 - counter);
			packet = packet | shiftedRight;

			if (counter + effectiveLength > 7)
			{
				fout << packet;
				packet = 0;


				packet = packet | shiftedLeft;
			}

			counter = (counter + effectiveLength) % 8;
		}

		cout << "\n\n\n\t\t\tDONE";
		//getchar();

		pbar.clearAll();

		if (counter != 0)
		{
			fout << packet;
			packet = 0;
		}
		fin.close();
		fout.close();

	}



	//The two functions below are for file compression and decompression. They take strings, which are file names of files to be
	//compressed/decompressed. The second argument is the name of the output file.
	void compressFile(string toBeCompressed, string saveHere)
	{
		ifstream fin(toBeCompressed, ios::binary);
		if (!fin.is_open())
		{
			cout << "\nFile to be compressed was not found.\n";
			fflush(stdin);
			getchar();
			return;

		}
		ofstream fout(saveHere, ios::binary);

		initializeQueue(fin);
		writeFrequencyTable(fout);
		formTree();
		fin.close();
		fin.open(toBeCompressed, ios::binary);
		encode(fin, fout);



	}
	void decompressFile(string toBeDecomp, string saveHere)
	{
		ifstream fin(toBeDecomp, ios::binary);
		if (!fin.is_open())
		{
			cout << "\nDecompression failed: Could not find file to be decompressed\n";
			fflush(stdin);
			getchar();
			return;
		}
		ofstream fout(saveHere, ios::binary);
		clear();
		readFrequencyTable(fin);

		initializeQueue();

		formTree();

		decode(fin, fout);

	}

	//The constructor. Sets things up initially.
	Processor()
	{
		thenode = NULL;
		thetree = NULL;
		initialized = formed = false;
	}

	//The two functions below are for 1. reading frequency table from a compressed file 2. Write frequency table at the start of 
	//compressed file
	void writeFrequencyTable(ofstream& file)
	{

		HNode temp;
		char tch;
		frequencyTable.reset();
		if (frequencyTable.isEmpty())return;
		do{



			temp1 = frequencyTable.getData();
			temp1.reset();
			temp = temp1.getData();
			temp.getChar(tch);
			file << (int)tch;
			file << ".";
			file << temp.getOccurrence();
			if (!frequencyTable.currentAtEnd())
				file << ",";
		} while (frequencyTable++);
		file << ">";
	}
	void readFrequencyTable(ifstream& fin)
	{
		HNode *temp;
		Tree<HNode> *xz;

		int x;
		char t;
		while (1)
		{
			temp = new HNode();
			xz = new Tree<HNode>();

			fin >> x;
			fin >> t;
			t = (char)x;
			fin >> x;
			temp->setChar(t);
			temp->setOccurrence(x);
			xz->setRootData(*temp);
			frequencyTable.append(*xz);
			fin >> t;
			if (t != ','){ break; }


		}

	}



	//The three functions below are for bitwise manipulation. the 'getOnePosition' initializes a character, initially equal to 1, and then 
	//shifts it (7 - num) places to the left. eg getOnePosition(3) will return a char whose bits will be 00001000. getZeroPosition simply returns 
	//the NOT of getOnePosition (i.e. it will return 11110111 instead of 00001000). The middle function does the same thing with ints and shifts by
	//(31 - num)
	char getOnePosition(int num)
	{

		return 1 << (7 - num);
	}
	int getOnePositionInt(int num)
	{

		return 1 << (31 - num);
	}
	char getZeroPosition(int num)
	{
		return ~getOnePosition(num);

	}


	//The two functions below take an open file and decompress it. The lower one of the two has an additional functionality of writing the
	//decompressed string directly to the open output file.
	string decode(ifstream & fin)
	{
		temp1 = priorityQueue.pop();
		priorityQueue.push(temp1);
		temp1.reset();
		string decoded = "";
		char temp;
		int counter = 0;
		char t = 0;
		char ch;
		while (fin)
		{

			fin.get(ch);

			for (int c = 0; c < 8; c++)
			{
				if (temp1.isLeaf())
				{
					if (temp1.getData().isEOF())
					{
						return decoded;
					}
					temp1.getData().getChar(temp);
					if (temp == '\n')
						decoded += "\r";
					decoded += temp;
					temp1.reset();
				}
				if (!(ch & getOnePosition(c)))
				{
					temp1.moveLeft();
				}
				else
				{
					temp1.moveRight();
				}
			}

		}

		return decoded;



	}
	void decode(ifstream & fin, ofstream & fout)
	{
		if (!fin.is_open())
		{
			cout << "Error in decode: File to be decoded not open.\n";
		}
		if (!fout.is_open())
		{
			cout << "Error in decode: File output file not open.\n";
		}
		filebuf* buff = fin.rdbuf();
		temp1 = priorityQueue.pop();
		priorityQueue.push(temp1);
		temp1.reset();

		char temp;
		int counter = 0;
		char t = 0;
		char ch;


		//DISPLAY
		int dat = fin.tellg();
		fin.seekg(0, ios::end);
		int total = fin.tellg();
		fin.seekg(dat, ios::beg);
		total -= dat;
		int prog = 0;
		progressBar p(60, 2, 5, 5);
		p.setTitle("decrypting");
		p.drawOutline();
		int times = total / 10 +1; 
		//DISPLAY
		while (fin)
		{
			//DISPLAY
			prog++;
			if (!(prog % times))
			{
				p.setProgress(prog, total);
				p.update();


			}
			//DISPLAY
			fin.get(ch);
			for (int c = 0; c < 8; c++)
			{
				if (temp1.isLeaf())
				{
					if (temp1.getData().isEOF())
					{
						cout << "\n\n\t\t DONE";
						//getchar();
						p.clearAll();
						return;
					}
					temp1.getData().getChar(temp);

					fout << temp;
					temp1.reset();
				}
				if (!(ch & getOnePosition(c)))
				{
					temp1.moveLeft();
				}
				else
				{
					temp1.moveRight();
				}
			}

		}





	}



	//These two functions initialize the priority queue. The first one takes no arguments and is used while decompressing and 
	//it simply equates the priority queue to the frequency table. The lower one is used for compressing. It takes an open file, makes 
	//a frequency table form it's data using an array, and the initializes the priority Queue.
	void initializeQueue(){


		priorityQueue = frequencyTable;
		initialized = true;
	}
	void initializeQueue(ifstream & fin)
	{

		int arra[256] = { 0 };
		char ch;
		unsigned char dss;



		while (fin)
		{
			fin.get(ch);
			dss = ch;
			arra[dss]++;
		}

		int value;
		for (int i = 0; i < 256; i++)
		{


			value = arra[i];
			if (value == 0) continue;
			thenode = new HNode();
			thenode->setChar((char)i);
			thenode->setOccurrence(value);
			thetree = new Tree<HNode>;
			thetree->addSingleItem(*thenode);
			priorityQueue.push(*thetree);
			thetree = NULL;
			thenode = NULL;
		}



		frequencyTable = priorityQueue;
		priorityQueue.reset();

		initialized = true;




	}



	//One the queue has been initialized, the function below uses it to form a tree.
	void formTree()
	{
		if (!initialized)
		{
			cout << "\nQueue not Initialized. Failed to form Tree.\n";
			return;
		}
		//THIS IS NEW

		thenode = new HNode();
		//thenode->setChar('@');
		thenode->setEOF();
		thenode->setOccurrence(1);




		thetree = new Tree<HNode>;
		thetree->addSingleItem(*thenode);
		priorityQueue.push(*thetree);


		//

		thetree = NULL;
		thenode = NULL;
		while (!priorityQueue.oneLeft())
		{
			temp1 = priorityQueue.pop();
			temp2 = priorityQueue.pop();

			thetree = new Tree<HNode>();

			thenode = new HNode();
			thenode->getCombinedOccurrence(temp1.getRootData(), temp2.getRootData());
			thetree->setRootData(*thenode);
			thetree->mergeTrees(temp1, temp2);
			priorityQueue.push(*thetree);


		}


		formed = true;
	}



};

#endif