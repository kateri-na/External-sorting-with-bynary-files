#pragma once
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

extern int count_r;

struct Elem
{
	int key;
	char value;
};

struct Sequence
{
	std::fstream file;
	Elem elem;
	bool eof;
	void ReadNext();
	void StartRead(std::string filename);
	void StartWrite(std::string filename);
	void Close();
	void Copy(Sequence& x);
	void CopyRun(Sequence& x, int number);
	void CopyBubble(Sequence& x);
};