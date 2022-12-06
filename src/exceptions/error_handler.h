#pragma once
#include <memory>
#include "../inout/classes.h"

class Error
{
public:
	std::string info;
	TextPos pos;
	Error(std::string& info, TextPos& pos);
};

class ErrorHandler
{
private:
	std::vector<std::unique_ptr<Error>> errors;
public:
	ErrorHandler() {};
	void add_error(std::string& info, TextPos& pos);
	std::vector<std::unique_ptr<Error>> get_errors();
	int get_errors_count();
};