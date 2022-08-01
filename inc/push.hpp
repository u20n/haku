#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <functional>
#include "base.hpp"

/**
 * this provides filesystem information 
 * needed to generate a COBS block
 * we leave the creation of this block to an
 * agent implementation to avoid
 * unneeded complexity here
 * */
void push(
    std::function<
      std::array<std::string, 2>
      (std::vector<std::string>)
    > bgen, 
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
    }
    // prune
    // v see above comment
    unsigned int COUNT = 3;
    if (top.size() > COUNT) {
      top.erase(top.end()-COUNT, top.begin());
    }

    /** fill out parents */
    std::vector<std::string> parents;
    for (const auto& entry: top) {
      parents.push_back(entry.path().stem());
    }
    
    // TODO: write to new block
    auto cont = bgen(parents);
    std::ofstream nblock(bdir+cont[0]+".block");
    nblock << cont[1].c_str();
    nblock.close();
  } catch (std::exception& e) {
    // TODO: log
    base::log("./logfile.log", e.what());
  }
 }
