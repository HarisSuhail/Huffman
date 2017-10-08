#ifndef HUFMAN_NODE_H
#define HUFMAN_NODE_H
#include <iostream>
using namespace std;

class HNode
{
private:
	int occurrence, codeLength;
	bool hasChar, eof, hasCodeChar;
	char character, codechar;



public:
	void showData()  //Shows all the data
	{
		cout << "["<<character<<","<<occurrence<<","<<eof<<"]";
	}
	void setCodeLength(int x)  //Sets code length
	{ 
		codeLength = x; 
	}
	int getCodeLength()  //Gives code length
	{ 
		return codeLength; 
	}
	void setCodeChar(char w)  //Sets code character
	{
		codechar = w;
	}
	char getCodeChar()  //Gives code character
	{
		return codechar;
	}
	void changeCodeCharFlag()  //Changes code character flag
	{
		hasCodeChar = true;
	}

	HNode()
	{
		hasCodeChar = false;
		occurrence = 0;
		hasChar = false;
		eof = false;

	}
	void setEOF(bool val = true)
	{
		eof = val; 
		
	}
	bool isEOF()
	{
		return eof;
	}
	void setChar(char t)  //Sets the value of character
	{
		hasChar = true;
		character = t;

	}
	void setOccurrence(int y)  //Sets the value of occurrence
	{
		occurrence = y;
	}
	int getOccurrence()  //Gives the value of occurrence
	{
		return occurrence;
	}
	void getCombinedOccurrence(HNode &a, HNode &b)  //Gives combined occurrence of both the arguments
	{
		occurrence = a.occurrence + b.occurrence;
	}
	bool getChar(char & t)  //Gives the value of the character
	{
		if (!hasChar) return false;
		t = character;
		return true;
	}


	HNode& operator = (HNode& x)  //Equates the variables of the argument to the object whose function is called
	{
		this->hasChar = x.hasChar;
		this->occurrence = x.occurrence;
		this->eof = x.eof;
	
		if (x.hasChar)
		{
			this->character = x.character;
		}
		return *this;
	}

	bool operator == (char x)
	{
		if (hasChar == false) return false;
		else return (x == character);
	}
	bool operator == (int q)
	{
		return eof;
	}

	HNode& operator = (char x)  //Sets the character value equal to the argument passed
	{

		this->character = x;
		return *this;
	}

	HNode& operator= (int y)  //Sets the occurrence value equal to the argument passed
	{
		this->occurrence = y;
	}


	friend ostream& operator << (ostream&, HNode&);



	bool operator < (HNode & hn)  //Overloads opertor <
	{
		return this->occurrence < hn.occurrence;
	}

	bool operator >(HNode & hn)  //Overloads opertor >
	{
		return this->occurrence > hn.occurrence;
	}



};


ostream& operator << (ostream& out, HNode& c)  //Overloads operator <<
{
	out << "(";
	if (c.hasChar)
	{
		out << c.character;
	}
	else
	{
		
		out << "No Char";
	}
	
	if (c.isEOF())cout << ", Has EOF";
	out << "," << c.occurrence << ")";
	return out;

}





#endif