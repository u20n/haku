#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>


#include "../base.hpp"

struct splash {
  std::vector<std::vector<std::string>> frames;
  
  void show(int time = -1) { // >0 -> until animation finishes
    
  }
  void show(bool* ready) {

  }
  
  splash(std::string path){
    /** load animation from folder */
    try {
      //fopen(path
    } catch (std::exception& e) {
      time_t t = std::time(0);
    base::log(
          "./splash.log",
          std::ctime(&t), e.what());
    }
  }
};
