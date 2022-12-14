#include "pch.h"
#include "compilier.h"
using namespace System;

int main(array<System::String ^> ^args)
{
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "eng");

    
    auto compilier = gcnew CCompilier("input.txt", "output.txt");
    compilier->Run();
    
}
