// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

#include <fmt/core.h>

#include "GenevaTest.h"
#include "OtlpTest.h"

void run_all_tests()
{
  // MsaLab::Details::TestLogWithGeneva();
 
  // MsaLab::Details::TestTraceWithGeneva();

  //MsaLab::Details::TestLogWithOtlp();
  
  MsaLab::Details::TestTraceWithOtlp();

}

int main()
{
  fmt::print("\n\n Start of Main() \n\n");

  // Run periodically instead of looping forever.
  for (std::uint64_t i = 0; i < 1'000'000ULL; ++i)
  {
    run_all_tests();
    break;
    std::this_thread::sleep_for(std::chrono::seconds(56));
  }
  
  std::cout << "\n\n End of Main() \n\n";

  return 0;
}

