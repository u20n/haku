#pragma once
#include <cryptopp/secblock.h>
#include <cryptopp/hex.h>

#include <string>
#include <vector>
#include <utility>

#include "base.hpp"
/**
 * key manager for haku
 * we map a keypair to a set of trips
 * and use it to read/send
 * */
using namespace CryptoPP;
struct keys {
  std::vector<
    std::array<SecByteBlock*, 2>
  > kpledger;
  std::map<
    std::string, // trip 
    std::tuple<
      int, // index in kpledger
      SecByteBlock* // AES (for server)
    >
  > ledger; // use this one 
  
  void set(
      std::string trip, 
      std::array<std::string, 3> kp
    ) {
    std::array<SecByteBlock*, 3> tmp;
    for (unsigned int i=0; i<kp.size(); i++) {
      std::string ks;
      std::string k = kp[i];
      HexDecoder hex(new StringSink(ks));
      hex.Put((const byte*)k.data(), k.size(), true);
      hex.MessageEnd();
      tmp[i] = new SecByteBlock{reinterpret_cast<const byte*>(&ks[0]), ks.size()};
    }

    // push to ledger
    this->kpledger.push_back({tmp[0], tmp[1]});
    this->ledger[trip] = 
    {
      this->kpledger.size()-1,
      tmp[2]
    };
  }
  // encrypt
  std::string enc(std::string trip, std::string m) {
    try {
      auto id = this->kpledger.at(std::get<0>(this->ledger[trip]));
      auto k = std::get<1>(this->ledger[trip]);
      
    } catch(std::exception& e) {
      base::log("./log.log", e.what());
    }
  }
  // decrypt
  std::string dec(std::string trip) {

  }
};
