#ifndef FILE_MAN_H
#define FILE_MAN_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <map> 

#include <fstream>
#include <direct.h>


class FileMan
{
public:

	FileMan(std::string working_dir);

	int move(std::string filename);
	
	void write(std::string text_to_write);
	int create_directory(std::string dir_name);

	std::string read();

protected:

private:
	std::string working_dir;
	std::string working_file;
	std::fstream out_file;
	std::ifstream in_file;
};


#endif