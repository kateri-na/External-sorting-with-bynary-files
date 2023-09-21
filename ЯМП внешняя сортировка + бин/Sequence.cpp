#include "Sequence.h"

void BubbleSort(std::vector<Elem>& vec)
{
	int n = vec.size();
	for (int i = 0; i < n; ++i)
		for (int j = n - 1; j > i; --j)
			if (vec[j - 1].key > vec[j].key)
				std::swap(vec[j - 1], vec[j]);
}

void Sequence::ReadNext()
{
	if (!file.eof())
	{
		file.read((char*)&elem, sizeof(Elem));
		eof = file.eof();
	}
}

void Sequence::StartRead(std::string filename)
{
	file.open(filename, std::ios::in | std::ios::binary);
	ReadNext();
}

void Sequence::StartWrite(std::string filename)
{
	file.open(filename, std::ios::out | std::ios::binary);
}

void Sequence::Close()
{
	file.close();
}

void Sequence::Copy(Sequence& x)
{
	elem = x.elem;
	file.write((char*)&elem, sizeof(Elem));
	x.ReadNext();
}

void Sequence::CopyRun(Sequence& x, int number)
{
	int count = 0;
	while (count != number && !x.eof)
	{
		Copy(x);
		++count;
	}
}

void Sequence::CopyBubble(Sequence& x)
{
	auto is_ordered = [](std::vector<Elem> arr)
	{
		bool check = true;
		int i = 0, size = arr.size();
		while (i < size - 1 && check)
		{
			if (arr[i].key > arr[i + 1].key)
				check = false;
			++i;
		}
		return check;
	};
	std::vector<Elem> arr;
	int count = 0;
	do
	{
		arr.push_back(x.elem);
		x.ReadNext();
		++count;
	} while (count < count_r && !x.eof);
	if(!is_ordered(arr))
		BubbleSort(arr);
	for (int i = 0; i < arr.size(); ++i)
		file.write((char*)&arr[i], sizeof(Elem));
}
