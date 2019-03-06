/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:¿º»¢È¨
 * Student ID:517021910839
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 2000

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

void read_file(ifstream &file_input)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		file_input.open(file_name.c_str());
		if (file_input.is_open())//read until open successfully
			break;
	}
}

int read_order()
{
	while (true)
	{
		cout << "Please enter order of Markov model to use (a number from 1 to 10):";
		int order;
		cin >> order;
		if (order >= 1 && order <= 10)//read until get order from 1 to 10
			return order;
	}
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model)
{
	char ch;//get character one by one
	string key;//seed with order-k length

	while (file_input.get(ch)) {
		if (key.length() >= order)//do something until key is long enough
		{
			if (model.find(key) != model.end())
				model[key].push_back(ch);//found, add char to vector
			else {
				vector<char> temp;
				temp.push_back(ch);
				model.insert(pair<string, vector<char>>(key, temp));
			}//not found, add new pair to map

			key.erase(key.begin());//erase char from front
		}

		key.push_back(ch);//add char from behind
	}
}

void random_write(const int &order, map<string, vector<char>> &model)
{
	//initialize seed
	string seed = model.begin()->first;
	for (auto it = model.begin(); it != model.end(); it++) {
		if (it->second.size() > model[seed].size())
			seed = it->first;
	}//most frequecy
	cout << seed;

	srand(time(NULL));
	for (int i = 0; i < MAX_CHAR_NUM-order; i++) {
		int size = model[seed].size();//amount of possibility
		char next = model[seed][rand() % size];//get char randomly
		cout << next;
		seed.push_back(next);
		seed.erase(seed.begin());//update seed
	}
}

int main()
{
	ifstream infile;
	int order;
	map<string, vector<char>> model;

	read_file(infile);//read source
	order = read_order();//read order
	model_read(infile, order, model);//produce model
	random_write(order, model);//write randomly

	system("pause");
    return 0;
}
