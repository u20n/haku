#pragma once

#include <crypt.hpp>

#include <string>
#include <vector>
#include <utility>
#include <cassert>

#include "base.hpp"
/**
 * key manager for haku
 * we map a keypair to a set of trips
 * and use it to pack/unpack messages
 * for distribution
 *
 * keys doesn't keep track of anything beyond
 * the very basic pack/unpack functionality
 * keys is built to be as 'stupid' as possible
 * if a client needs more, use the core library
 * */
using namespace CryptoPP;
struct keys {
  std::vector<
    std::array<SecByteBlock*, 2> // [0] is pub, [1] is pri
  > idledger; // id ledger, outside parties have a nullptr for priv key
  std::map<
    std::string, // server trip 
    std::tuple<
      int, // index in idledger
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
    this->idledger.push_back({tmp[0], tmp[1]});
    this->ledger[trip] = 
    {
      this->kpledger.size()-1,
      tmp[2]
    };
  }

  std::string get(SecByteBlock* b) {
    std::string rk, ek;
    SecByteBlock bk = *b;
    rk = std::string(reinterpret_cast<const char*>(&bk[0]), bk.size());
    /** written so it's blocking */
    HexEncoder dx(new StringSink(ek));
    dx.Put((const byte*)rk.data(), rk.size(), true /** blocking */);
    dx.MessageEnd();
    return ek;
  }
  
  // TODO:
  // unclear how we pack/unpack messages,
  // await clarification

  /**
   * we sign the message w/ DSA
   * and tag it with 
   * this is left to the message encoding/decoding protocol
   * */
  
  // pack a message for distribution 
  std::string pack(std::string trip, std::string m) {
    auto id = this->idledger.at(std::get<0>(this->ledger[trip]));
    auto k = std::get<1>(this->ledger[trip]);
      
    // sign the message with our id
    auto sig = cDSA::sign(id[1], m);       
    std::string receipt = {m, '$', sig}; 
    
    // encrypt it
    std::array<std::array, 2> epair = cAES::encrypt(this->get(k), receipt);

    // pack it
    return std::string{epair[0], '$', epair[1]); 
  }
  
  // (attempt to) unpack a message
  std::string unpack(std::string trip, std::string m) {
    auto id = this->idledger.at(std::get<0>(this->ledger[trip]));
    auto k = std::get<1>(this->ledger[trip]);

    // extract the nonce, cipher
    auto d = m.split('$');
    auto nonce = d[1];
    auto cipher = d[0];

    // decrypt
    auto raw = cAES::decrypt(this->get(k), nonce, cipher).split('$');
    
    // attempt to verify
//    assert(raw[ 
  }
};
