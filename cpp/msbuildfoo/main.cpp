// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fmt/core.h>

#include "IOTelPipeline.h"
#include "test/GenevaTest.h"
#include "test/OtlpTest.h"

int main()
{
  fmt::print("Hello World!\n");

  MsaLab::Details::TestTraceWithGeneva();

  MsaLab::Details::TestTraceWithOtlp();
  
  // TestWithOtlpExporter();
  // TestWithEtwExporter();

  std::cout << "Hello, from MSBuild!\n";

  return 0;
}






