#include "FileMan.h"

FileMan::FileMan(std::string working_dir)
{
	this->working_dir = working_dir;
}

int FileMan::move(std::string filename)
{
	this->working_file = filename;
	return 0;
}

void FileMan::write(std::string text_to_write)
{
	this->out_file.open(this->working_dir + "/" + this->working_file);
	this->out_file << text_to_write << "\n";
	this->out_file.close();
}

int FileMan::create_directory(std::string dir_name)
{
	std::string dir_path = this->working_dir + "/" + dir_name;
	if (!_mkdir(dir_path.c_str()))
	{
		return -1;
	}
	return 0;
}

std::string FileMan::read()
{
	this->in_file.open(this->working_dir + "\\" + this->working_file);
	std::string data;
	this->in_file >> data;
	return data;
}
