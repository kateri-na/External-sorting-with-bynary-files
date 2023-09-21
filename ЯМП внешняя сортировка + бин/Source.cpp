//простое двухпутевое двухфазное слияние с внутренней сортировкой
#include "Sequence.h"

int count_r = 2;

void Distribute(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2);
int Merge(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2);
void Sorting(std::string filename);
void Create_File(std::string filename, int cnt);
bool CheckFile(std::string filename);
void PrintFile(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in | std::ios::binary);
	Elem elem;
	while (file.read((char*)&elem, sizeof(Elem)))
		std::cout << elem.key << ' ' << elem.value << '\n';
}

int main()
{
	Create_File("data.txt", 30);
	std::cout << "Original file:\n---------------------------------\n";
	PrintFile("data.txt");
	Sorting("data.txt");
	if (CheckFile("data.txt"))
	{
		std::cout << "\nFile is ordered!\n";
		std::cout << "\nOrdered file:\n---------------------------------\n";
		PrintFile("data.txt");
	}
	else
		std::cout << "File is not ordered\n";
	
	std::cin.get();
	return 0;
}


void Distribute(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2)
{
	f0.StartRead(filename);
	f1.StartWrite("f1.txt");
	f2.StartWrite("f2.txt");
	while (!f0.eof)
	{
		f1.CopyBubble(f0);
		if (!f0.eof)
			f2.CopyBubble(f0);
	}
	f0.Close();
	f1.Close();
	f2.Close();
}

int Merge(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2)
{
	f1.StartRead("f1.txt");
	f2.StartRead("f2.txt");
	f0.StartWrite(filename);
	int count = 0;
	int i = 0;
	int j = 0;
	while (!f1.eof && !f2.eof&&i != count_r && j != count_r)
	{
		while (i != count_r && j != count_r&&!f2.eof)
		{
			if (f1.elem.key <= f2.elem.key)
			{
				f0.Copy(f1);
				++i;
			}
			else
			{
				f0.Copy(f2);
				++j;
			}
		}
		if (i != count_r)
			f0.CopyRun(f1, count_r - i);
		if (j != count_r)
			f0.CopyRun(f2, count_r - j);
		i = 0;
		j = 0;
		++count;
	}
	while (!f1.eof)
	{
		f0.CopyRun(f1,count_r);
		++count;
	}
	while (!f2.eof)
	{
		f0.CopyRun(f2, count_r);
		++count;
	}
	f0.Close();
	f1.Close();
	f2.Close();
	return count;
}

void Sorting(std::string filename)
{
	Sequence f0, f1, f2;
	int count = 0;
	do
	{
		Distribute(f0, filename, f1, f2);
		count = Merge(f0, filename, f1, f2);
		count_r *= 2;
	} while (count > 1);
	remove("f1.txt");
	remove("f2.txt");
}

void Create_File(std::string filename, int cnt)
{
	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::binary);
	srand(GetTickCount64());
	Elem elem;
	for (int i = 0; i < cnt; ++i)
	{
		elem.key = rand() % 100;
		elem.value = 'a' + rand() % 26;
		file.write((char*)&elem, sizeof(Elem));
	}
}

bool CheckFile(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in | std::ios::binary);
	Elem x, y;
	bool check = true;
	file.read((char*)&y, sizeof(Elem));
	while (!file.eof() && check)
	{
		x = y;
		file.read((char*)&y, sizeof(Elem));
		check = x.key <= y.key;
	}
	file.close();
	return check;
}