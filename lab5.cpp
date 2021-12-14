#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdlib.h>

int const BLOCK_SIZE = 2;
int const BLOCK_NUM = 500;
int const MAXNUM_FILES = 5000;

using namespace std;

struct block {
	int no;
	int size;
	int next;
};

class fat_entry {
public:
	string file_name;
	int no;
	vector<int> block_allocated;

	fat_entry(const string& file_name, int no, vector<int> blocks)
	{
		this->file_name.assign(file_name);
		this->no = no;
		this->block_allocated = blocks;
	}

	fat_entry& operator=(const fat_entry& fat)
	{
		this->file_name = fat.file_name;
		no = fat.no;
		this->block_allocated = fat.block_allocated;
		return *this;
	}
};
struct disk_controller {
	int free_ptr = 0;
	block blocks[BLOCK_NUM + 1];
	vector<fat_entry> fat_table;
	int fat_ptr;
	int remain;
}controller;

void init()
{
	controller.free_ptr = 1;
	for (int i = 0; i <= BLOCK_NUM; i++)
	{
		controller.blocks[i].next = i + 1;
		controller.blocks[i].no = i;
		controller.blocks[i].size = BLOCK_SIZE;
	}
	controller.blocks[BLOCK_NUM].next = 0;
	controller.remain = BLOCK_NUM;
	controller.fat_ptr = 0;
}

vector<int> create_blocks(int allocated_block_num)
{
	vector<int> allocated_blocks;
	int allocated_ptr = controller.free_ptr;
	int free_ptr = controller.free_ptr;
	for (int i = 0; i < allocated_block_num; i++)
	{
		free_ptr = controller.blocks[free_ptr].next;
		controller.blocks[allocated_ptr].next = 0;
		allocated_blocks.push_back(controller.blocks[allocated_ptr].no);
		allocated_ptr = free_ptr;
	}
	controller.free_ptr = free_ptr;
	controller.remain -= allocated_block_num;
	return allocated_blocks;
}

bool create_file(string file_name, double size)
{
	if (size > controller.remain)
		return false;

	int allocated_block_num = size / BLOCK_SIZE;
	allocated_block_num += (size - allocated_block_num * BLOCK_SIZE);
	vector<int> allocated_blocks = create_blocks(allocated_block_num + 1);
	int index_block = allocated_blocks[0];
	allocated_blocks.erase(allocated_blocks.begin());
	fat_entry fat = fat_entry(file_name, index_block, allocated_blocks);
	controller.fat_table.push_back(fat);
	controller.fat_ptr++;
	return true;
}

int free_blocks(vector<int> blocks)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		controller.blocks[blocks[i]].next = controller.free_ptr;
		controller.free_ptr = blocks[i];
	}
	return 0;
}
bool delete_files(string file_name)
{
	fat_entry fat("", 0, vector<int>());
	for (int ptr = 0; ptr < controller.fat_ptr; ptr++)
	{
		if (file_name == controller.fat_table[ptr].file_name)
		{
			fat = controller.fat_table[ptr];
			controller.fat_table.erase(controller.fat_table.begin() + ptr);
			controller.fat_ptr--;
			break;
		}
	}
	if (fat.no == 0)
		return false;
	fat.block_allocated.push_back(fat.no);
	free_blocks(fat.block_allocated);
	return true;
}

void display_fat()
{
	for (int i = 0; i < controller.fat_ptr; i++)
	{
		cout << "file_name:" << controller.fat_table[i].file_name << "\t" << "index_block:" << controller.fat_table[i].no << "\t";
		cout << "blocks:";
		for (int j = 0; j < controller.fat_table[i].block_allocated.size(); j++)
		{
			cout << controller.fat_table[i].block_allocated[j] << " ";
		}
		cout << endl;
	}
}

void display_free()
{
	for (int i = controller.free_ptr; i; i = controller.blocks[i].next)
	{
		cout << controller.blocks[i].no << " ";
	}
	cout << endl;
}
int main()
{
	init();
	for (int i = 0; i <= 50; i++)
	{
		int r = rand() % 9 + 2;
		char name[10];
		sprintf_s(name, "%d.txt", i);
		create_file(name, r);
	}
	cout << "FILE ALLOCATION TABLE:" << endl;
	display_fat();

	create_file("A.txt", 1);
	create_file("B.txt", 2);
	create_file("C.txt", 3);
	create_file("D.txt", 4);
	create_file("E.txt", 5);
	
	cout << "FILE ALLOCATION TABLE:" << endl;
	display_fat();

	cout << "FREE BLOCKS:" << endl;
	display_free();

	system("pause");
	return 0;
}

