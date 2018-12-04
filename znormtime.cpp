#include <iostream>
#include <fstream>
#include <sstream> 
#include<stdio.h>
#include <string>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include<bits/stdc++.h> 
#include <math.h>
#include <stdlib.h>
#include "tree_m.h"
// Utility headers
//#include "libmorton_test.h"
//#include "libmorton_test_2D.h"


using namespace std;
using namespace tree_m;
//using namespace std::chrono;
//using namespace libmorton;

// 2D functions collections
//vector<encode_2D_64_wrapper> f2D_64_encode; // 2D 64-bit encode functions
//vector<encode_2D_32_wrapper> f2D_32_encode; // 2D 32_bit encode functions
//vector<decode_2D_64_wrapper> f2D_64_decode; // 2D 64-bit decode functions
//vector<decode_2D_32_wrapper> f2D_32_decode; // 2D 32_bit decode functions

uint_fast32_t string_to_unsigned_int(string str)
{
	uint_fast32_t result(0);
	for (int i = str.size() - 1; i >= 0; i--)
	{
		uint_fast32_t temp(0), k = str.size() - i - 1;
		if (isdigit(str[i]))
		{
			temp = str[i] - '0';
			while (k--)
				temp *= 10;
			result += temp;
		}
		else
		{
			break;
			//result = (int)x - 87;
		}
	}
	return result;
}

void menu()
{
	cout << "\n\n";
	cout << "l - preprocessing dataset" << endl;
	cout << "a - build the tree and query" << endl;
	//cout << "r - Remove Word" << endl;
	cout << "\nEnter choice : ";
}

uint64_t invertsax(string & list)
{
	//std::string mystring;
	/*for (int i = 0; i < list.size(); i++)
	{
		mystring.push_back(list[i]);
	}*/
	uint64_t answer = 0;
	for (int i = 3; i > 0; i--)
	{
		for (int j = 0; j < sizeof(list); j++)
		{
			answer += ((list[j] >> (i - 1)) & 0x1)*pow(2, (i * sizeof(list) - j - 1)); //converting every binary bit to base 10 and adding up
			/*const char *ch;
			ch = list[j].c_str();*/
			//uint_fast32_t x = std::stoul(list[i]);
			//uint_fast32_t x = string_to_unsigned_int(list[i]);
			/*uint_fast32_t x = std::stoul(list[i],nullptr,32);
			char u;
			strcpy(u, list[i].c_str());*/
			//uint_fast32_t y = std::stoul(list[i + 1], nullptr, 32);
			//bitset<8> x = std::bitset<8>(*ch);
			//x >> (i - 1) &= 1;
			//answer[list.size() - j] = x[i];
			//answer = answer | (x << (list.size()-j));
			//result.push_back(morton2D_32_encode(x, y));
		}
	}
	//result = answer.to_ullong();
	cout << answer << endl;
	return answer;
}

std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

vector<float> zvaluecal(vector<float> && list)
{
	float sum = 0, ssum = 0, ave = 0, newvalue;
	vector<float> result;
	for (int i = 0; i < list.size(); i++)
	{
		sum = sum + list[i];
	}
	ave = sum / list.size();
	for (int i = 0; i < list.size(); i++)
	{
		ssum = ssum + pow((abs(list[i] - ave)), 2);
	}
	ssum = sqrt(ssum);
	for (int i = 0; i < list.size(); i++)
	{
		newvalue = (list[i] - ave) / ssum;
		result.push_back(newvalue);
	}
	return result;
}

vector<float> paacal(vector<float> && list)
{
	int M = list.size() / 4, n = list.size();
	int newsize = M;
	vector<float> result;
	for (int i = 1; i <= newsize; i++)
	{
		float sum = 0;
		for (int k = (n / M * (i - 1) + 1); k <= ((n / M)*i); k++)
		{
			sum = list[k - 1] + sum;
		}
		float x = sum * M / n;
		result.push_back(x);
	}
	return result;
}

std::string saxcal(vector<float> && list)
{
	int size = list.size();
	string result;
	for (int i = 0; i < size; i++)
	{
		int a = ceil(list[i] * 10) + 107;

		//std::string x(1,char(a));
		result.push_back(char(a));
	}
	return result;
}


int main(int argc, char *argv[])
{
	string choice;
	menu();
	while (cin >> choice && choice[0] != 'x') 
	{
		switch (choice[0])
		{
		case 'l':
		{
			string line, str;
			for (int i = 1; i < argc; i++)
			{
				cout << "argument" << i << " is " << argv[i] << endl;
			}
			std::ifstream myfile;
			if (argc != 2)
			{
				cerr << argv[0] << " error" << endl;
				exit(EXIT_FAILURE);
			}
			myfile.open(argv[1]);
			if (myfile.fail())
			{
				cerr << "cannot open input file: " << argv[1]
					<< " ... terminating." << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << "open successed" << endl;
			}

			clock_t startTime1, endTime1;
			startTime1 = clock();

			while (std::getline(myfile, line))
			{
				//cout << line << "\n";
				vector<float> numlist;
				std::vector<std::string> list = split(line, " ");
				//std::cout << result.size() << std::endl;
				for (int i = 0; i < list.size(); i++)
				{
					if (list[i].compare("") != 0)
					{
						numlist.push_back(std::stof(list[i]));
						//std::cout << result[i] << std::endl;
					}
				}
				vector<float> output1 = zvaluecal(std::move(numlist));
				vector<float> output2 = paacal(std::move(output1));
				string output3 = saxcal(std::move(output2));
				uint64_t f2D_32_encode = invertsax(output3); // 2D 32_bit encode functions

				endTime1 = clock();
				cout << "Totle Time : " << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << endl;
				std::ofstream timerecord;
				timerecord.open("timerecord.txt", ios::app);
				timerecord << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "\n";


				//save to file then destructure
				std::ofstream outfile;
				outfile.open("saxoutput.txt", ios::app);
				/*for(int i=0; i< f2D_32_encode.size();i++)
				{
					if (i == f2D_32_encode.size() - 1)
					{
						outfile << f2D_32_encode[i]<<"\n";
					}
					else
					{
						outfile << f2D_32_encode[i]<<" ";
					}

				}
				f2D_32_encode.clear();*/
				outfile << f2D_32_encode << "\n";
			}
			myfile.close();
			break;
		}
		case 'a':
		{
			std::ifstream myfile1;
			std::ifstream myfile2;
			myfile1.open("output.txt");
			myfile2.open("saxoutput.txt");
			if (myfile1.fail())
			{
				cerr << "cannot open input file: output.txt ... terminating." << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << "open successed" << endl;
			}
			if (myfile2.fail())
			{
				cerr << "cannot open input file: insaxoutput.txt ... terminating." << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << "open successed" << endl;
			}
			string line1, line2;
			int numline = 0;

			clock_t startTime3, endTime3;
			startTime3 = clock();

			BTree bt(3);
			while (std::getline(myfile2, line2) && std::getline(myfile1, line1))
			{

				numline++;
				bt.insert(std::stoull(line2),line1);
			}

			endTime3 = clock();
			cout << "Totle Time : " << (double)(endTime3 - startTime3) / CLOCKS_PER_SEC << "s" << endl;
			system("pause");

			//bt.traverse();
			cout << "tree is built, if you want to query please enter 3:" << endl;
			cout << numline << endl;
			int queryflag = 0;
			string queryline;
			cin >> queryflag;

			while (queryflag == 3)
			{
				cout << "please enter a group of sequence end with # simbol" << endl;
				getline(cin,queryline,'#');

				clock_t startTime2, endTime2;
				startTime2 = clock();

				vector<float> numlst;
				std::vector<std::string> lst = split(queryline, " ");
				//std::cout << result.size() << std::endl;
				for (int i = 0; i < lst.size(); i++)
				{
					if (lst[i].compare("") != 0)
					{
						numlst.push_back(std::stof(lst[i]));
						//std::cout << result[i] << std::endl;
					}
				}
				vector<float> output4 = zvaluecal(std::move(numlst));
				vector<float> output5 = paacal(std::move(output4));
				string output6 = saxcal(std::move(output5));
				uint64_t encode = invertsax(output6); // 2D 32_bit encode functions
				cout << encode << endl;
				cout << "the result is (key and sequence ) " << endl;
				BTreeNode *node = bt.search(encode);
				cout << node << endl;
				//cout << bt.getkey(node) << endl;
				//cout << bt.getsequence(node) << endl;

				endTime2 = clock();
				cout << "Totle Time : " << (double)(endTime2 - startTime2) / CLOCKS_PER_SEC << "s" << endl;
				system("pause");
			}
			break;
		}
		case 'r':
		{
			//string queryline;
			//cout << "please enter a group of sequence" << endl;
			//cin >> queryline;

			//vector<float> numlst;
			//std::vector<std::string> lst = split(queryline, " ");
			////std::cout << result.size() << std::endl;
			//for (int i = 0; i < lst.size(); i++)
			//{
			//	if (lst[i].compare("") != 0)
			//	{
			//		numlst.push_back(std::stof(lst[i]));
			//		//std::cout << result[i] << std::endl;
			//	}
			//}
			//vector<float> output4 = zvaluecal(std::move(numlst));
			//vector<float> output5 = paacal(std::move(output4));
			//string output6 = saxcal(std::move(output5));
			//uint64_t encode = invertsax(output6); // 2D 32_bit encode functions

			//cout << "the result is (key and sequence ) " << endl;
			//BTreeNode *node = bt.search(encode);
			//cout << node << endl;
			break;
		}
		default:
		{
			cout << "*****Error: Invalid entry.  Try again." << endl;
			break;
		}
		}
		menu();
	}
	
    return (EXIT_SUCCESS);
}



