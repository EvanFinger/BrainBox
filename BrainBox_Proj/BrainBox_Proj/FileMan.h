#ifndef FILE_MAN_H
#define FILE_MAN_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <map> 
#include <stack>
#include <stdlib.h>

#include <fstream>
#include <direct.h>
#include <filesystem>


class FileMan
{
public:

	FileMan(std::string working_dir);

	int move(std::string filename);
	
	void write(std::string text_to_write);
	std::string read();

	std::vector<std::string> read_directory();
	int create_directory(std::string dir_name);
	int delete_directory(std::string dir_name);

	const std::string get_wdir() const
	{
		return this->working_dir;
	}
	const std::string get_wfile() const
	{
		return this->working_file;
	}
protected:

private:
	std::string working_dir;
	std::string working_file;
	std::fstream out_file;
	std::ifstream in_file;
};


#endif