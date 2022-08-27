#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <functional>

/**
 * this provides filesystem information 
 * needed to generate a COBS+ block
 * we leave the creation of this block to an
 * overlay implementation to avoid
 * unneeded complexity here
 * ~
 * this is to reduce code repetion across
 * seperate overlay implementation
 * */

namespace bfs {
  std::vector<std::string> recent(unsigned int depth, std::string fspath) {
    try {
      std::vector<std::filesystem::directory_entry> top;
      top.resize(depth);
      for (const auto& block: std::filesystem::directory_iterator{fspath}) {
        for (unsigned int i=top.size()-1; i!=0; i--) {
          if (std::filesystem::last_write_time(top.at(i)) > std::filesystem::last_write_time(block)) {
            top.at(i) = block;
          }
        }
      }
      std::vector<std::string> r;
      for (const auto& entry: top) {
        r.push_back(entry.path().stem());
      }
      return r;
    } catch (std::exception& e) {
      // log
    }
  }
  /** read the file */
  std::string read(std::string fpath) {
    std::string fbuff, l;
    std::ifstream fs(fpath);
    while (getline(fs, l)) {
      fbuff.append(l+'\n');
      l.clear();
    }
    fs.close();
    return fbuff;
  }
};
