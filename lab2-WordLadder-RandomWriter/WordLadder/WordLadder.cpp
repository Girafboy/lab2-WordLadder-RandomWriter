/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:¿º»¢È¨
 * Student ID:517021910839
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

void show_ans(vector<string> &ans)
{
    cout << "Found ladder:";
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
    {
        cout << "->" << ans[i];
    }
    cout << endl
         << endl;
}

void input_words(string &start, string &dest)
{
    cout << "Enter start word (enter ':q' to quit):";
    cin >> start;
    if (start == ":q")
    {
        exit(0);
    }
    cout << "Enter destination word:";
    cin >> dest;
}

void read_english(set<string> &english)
{
    while (true)
    {
        cout << "Please enter filename containing source text:";
        string file_name;
        cin >> file_name;
        ifstream file_input(file_name.c_str());
        if (file_input.is_open())
        {
            string temp_word;
            while (getline(file_input, temp_word))
            {
                english.insert(temp_word);
            }
            break;
        }
    }
}

int main()
{
	while (true) {
		set<string> englishfull;//all english words
		string start, dest;
		vector<string> ans;
		read_english(englishfull);
		input_words(start, dest);

		set<string> english;//english words of same length
		for (auto it = englishfull.begin(); it != englishfull.end(); it++)
			if (it->length() == start.length())
				english.insert(*it);

		queue<vector<string>> ladderqueue;
		vector<string> ladder;
		ladder.push_back(start);
		ladderqueue.push(ladder);//start ladder

		while (!ladderqueue.empty()) {
			ladder = ladderqueue.front();
			ladderqueue.pop();//get shortest ladder

			if (ladder.back() == dest) {
				ans = ladder;
				break;
			}//whether get answer

			for (auto it = english.begin(); it != english.end(); it++) {
				int count = 0;
				for (int i = 0; i < it->size(); i++)
					if ((*it)[i] != ladder.back()[i])
						count++;
				if (count != 1) continue;//only differ on one letter

				vector<string> temp(ladder);
				temp.push_back(*it);
				ladderqueue.push(temp);//new longer ladder

				english.erase(it);//erase redundant word
			}
		}

		if (ans.empty())
			cout << "no ladder exists";
		else
			show_ans(ans);//result
	}
	system("pause");
    return 0;
}
