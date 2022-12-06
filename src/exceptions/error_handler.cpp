#include "error_handler.h"

Error::Error(std::string& info, TextPos& pos) {
    this->info = info;
    this->pos = pos;
}

void ErrorHandler::add_error(std::string& info, TextPos& pos) {
	errors.push_back(std::make_unique<Error>(info, pos));
}

std::vector<std::unique_ptr<Error>> ErrorHandler::get_errors() {
	std::sort(errors.begin(), errors.end(), [](std::unique_ptr<Error> a, std::unique_ptr<Error> b) -> bool
    {return (a->pos.line_number < b->pos.line_number || a->pos.line_number == b->pos.line_number && a->pos.char_number < b->pos.char_number);});
	return errors;
}

int ErrorHandler::get_errors_count() {
	return errors.size();
}
