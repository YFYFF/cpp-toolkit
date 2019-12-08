// Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>  
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <errno.h>
#include <sstream> // stringstream
#include <typeinfo> // get the data type
#include <regex> // cpp11
#include <map>
#pragma warning(disable:4996)
using namespace std;

class StockInfo {
private:
	string name;
	string ticker;
	string date;
	double actual;
	double estimate;
	double surprise;
public:
	map<string, StockInfo> getBloomberg(string myFile);
	string getDate();
	double getSurprise();
};

map<string, StockInfo> StockInfo::getBloomberg(string myFile) 
{
	string line;
	map<string, StockInfo> stock;
	ifstream in(myFile); // read myFile into fstream "in"

	if (in)
	{
		string firstLine;
		getline(in, firstLine); //skip first line
		while (getline(in, line))
		{
			StockInfo info;
			regex comma(",");
			vector<string> v(sregex_token_iterator(line.begin(), line.end(),
				comma, -1), sregex_token_iterator());  //split using comma
			info.name = v[0];
			info.ticker = v[1];
			info.date = v[2];
			info.actual = stod(v[3]);
			info.estimate = stod(v[4]);
			info.surprise = (info.actual - info.estimate) / info.estimate;
			stock.insert({ v[0], info });
		}
		in.close();
		return stock;
		/*
		// code to check the accuracy of the code, you can delete it
		auto map_it = stock.cbegin();
		while (map_it != stock.cend())
		{
			StockInfo c = map_it->second;
			cout << map_it->first << c.getSurprise() << endl;
			++map_it;
		}
		*/
	}
	else
	{
		cout << "The file" << myFile << "could not open" << endl;
	}
}

string StockInfo::getDate()
{
	return date;
}

double StockInfo::getSurprise()
{
	return surprise;
}

int main()
{
	string myFile;
	StockInfo a;
	map<string, StockInfo> stock;
	myFile = "C:\\Users\\WilliamNG\\Desktop\\2019Q1.csv"; //Bloomberg file
	stock = a.getBloomberg(myFile);
	system("pause");
	return 0;
}





