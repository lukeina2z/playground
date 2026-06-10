// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

#include "GenevaTest.h"
#include "OtlpTest.h"

void run_all_tests()
{
  // MsaLab::Details::TestLogWithGeneva();
 
  MsaLab::Details::TestTraceWithGeneva();
}

int main()
{

    run_all_tests();

  
  std::cout << "\n\n End of Main() \n\n";

  return 0;
}

