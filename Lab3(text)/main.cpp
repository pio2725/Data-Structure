#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <time.h>
#include <list>

using std::string;
using std::cout;
using std::endl;

void FileUsingVector(string filename)
{
	//Part 2
	std::ifstream inFile;
	std::ofstream newFile;
	inFile.open(filename + ".txt");
	newFile.open(filename + "_vector.txt");

	std::vector<string> vectorWords;

	string nextLine;
	string token;

	while (getline(inFile, nextLine))
	{
		std::istringstream iss(nextLine);
		while (iss >> token)
		{
			string nopunct = "";
			for (auto &c : token)
			{
				if (isalpha(c))
				{
					nopunct += c;
				}
			}
			vectorWords.push_back(nopunct);
		}
	}

	for (std::vector<string>::iterator itr = vectorWords.begin(); itr != vectorWords.end(); itr++)
	{
		newFile << *itr << endl;
	}

	newFile.close();
	inFile.close();

	//Part 3
	std::map<string, string> wordMap;
	string last = "";
	for (std::vector<string>::iterator itr = vectorWords.begin(); itr != vectorWords.end(); itr++)
	{
		wordMap[last] = *itr;
		last = *itr;
	}

	newFile.open(filename + "_1_1.txt");

	//output "key, value"
	for (std::map<string, string>::iterator itr = wordMap.begin(); itr != wordMap.end(); itr++)
	{
		newFile << itr->first << ", " << itr->second << endl;
	}

	newFile.close();

	//Part 4
	string state = "";
	for (int i = 0; i < 100; i++)
	{
		cout << wordMap[state] << " ";
		state = wordMap[state];
	}
	cout << endl << endl;

	//Part 5
	std::map<string, std::vector<string>> wordMap2;
	state = "";
	for (std::vector<string>::iterator itr = vectorWords.begin(); itr != vectorWords.end(); itr++)
	{
		wordMap2[state].push_back(*itr);
		state = *itr;
	}

	//print out the vector of words: 6th entry
	int toFindSixth = 0;
	for (std::map<string, std::vector<string>>::iterator itr = wordMap2.begin(); itr != wordMap2.end(); itr++)
	{
		if (toFindSixth == 6)
		{			
			std::vector<string>::iterator it = itr->second.begin();
			cout << *it;
			++it;
			while (it != itr->second.end())
			{
				cout << ", " << *it;
				++it;
			}
			cout << endl;
		}
		++toFindSixth;
	}

	cout << endl << endl;

	srand(time(NULL));
	state = "";
	for (int i = 0; i < 100; i++)
	{
		int ind = rand() % wordMap2[state].size();
		cout << wordMap2[state][ind] << " ";
		state = wordMap2[state][ind];
	}
	cout << endl << endl;

	//Part 6
	int M = 2;
	std::map<std::list<string>, std::vector<string>> wordMap3;
	std::list<string> listState;

	for (int i = 0; i < M; i++)
	{
		listState.push_back("");
	}

	for (std::vector<string>::iterator itr = vectorWords.begin(); itr != vectorWords.end(); itr++)
	{
		wordMap3[listState].push_back(*itr);
		listState.push_back(*itr);
		listState.pop_front();
	}

	listState.clear();
	for (int i = 0; i < M; i++)
	{
		listState.push_back("");
	}

	if (wordMap3[listState].size() == 0)
	{
		for (int i = 0; i < M; i++)
		{
			listState.push_back("");
		}
	}

	for (int i = 0; i < 100; i++)
	{
		int ind = rand() % wordMap3[listState].size();
		cout << wordMap3[listState][ind] << " ";
		listState.push_back(wordMap3[listState][ind]);
		listState.pop_front();
	}
	cout << endl << endl;

	// Part 7

	
}

int main()
{
	//Part 1
	std::set<string> setWords;

	string userInput;
	cout << "Enter a title of a text file : ";
	getline(std::cin, userInput);
	
	std::ifstream inFile;
	std::ofstream newFile;
	inFile.open(userInput + ".txt");
	newFile.open(userInput + "_set.txt");

	if (inFile.is_open())
	{
		cout << "It's open!" << endl;
	}
	
	string nextLine;
	string token;

	while (getline(inFile, nextLine))
	{
		std::istringstream iss(nextLine);
		
		while (iss >> token)
		{
			string nopunct = "";
			
			for (auto& c : token)
			{
				if (isalpha(c))
				{
					nopunct += c;
				}
			}
			setWords.insert(nopunct);
		}
	}

	for (std::set<string>::iterator itr = setWords.begin(); itr != setWords.end(); itr++)
	{
		newFile << *itr << endl;
	}



	newFile.close();
	inFile.close();

	FileUsingVector(userInput);

	system("pause");
	return 0;
}