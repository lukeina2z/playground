// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fmt/core.h>

#include "GenevaTest.h"
#include "OtlpTest.h"

int main()
{
  fmt::print("Hello World!\n");

  MsaLab::Details::TestTraceWithGeneva();

  MsaLab::Details::TestLogWithOtlp();
  MsaLab::Details::TestTraceWithOtlp();
  
  std::cout << "Hello, from MSBuild!\n";

  return 0;
}

