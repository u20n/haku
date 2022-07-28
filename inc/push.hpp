#pragma once
#include <string>
#include <vector>
#include <filesystem>

/**
 * we don't need a 'creator' trip,
 * this hasn't been propagated yet
 * */
void push(
    std::string msg, 
    std::string strip,
    std::string bdir
  ) {
  /** 
   * pull the most recently written files
   * from the block directory 
   * we assume 3 parents here, but this can be updated
   * and read from a config file later
   *
   *
   * we look at relative time between blocks 
   * */
  try {
    std::vector<std::filesystem::directory_entry> top;
    for (auto const& block: std::filesystem::directory_iterator{bdir}) {
      for (unsigned int i=top.size()-1; i!=0; i--) {
        if (std::filesystem::last_write_time(top.at(i)) > std::filesystem::last_write_time(block)) {
          top.insert(top.begin()+i, block);
        }
      }
      // prune
      
    }  
  } catch (std::exception& e) {
    // TODO: log
  }
 }
