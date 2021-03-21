/**
 * /mnt/z/my_git/RCRS-CSD-327/src/Encryptor.cpp
 * @file Encryptor.cpp
 * @author Avinal Kumar
 * @since March 06, 2021
 *
 * Encryptor class implementation
 */

#include "Encryptor.h"

namespace krypto {
uint64_t Encryptor::blowfish_encrypt(std::vector<char> &input_buf,
                                     std::string const &key, uint64_t in_size) {
  uint32_t L = 0, R = 0;
  int block_size = sizeof(uint32_t);
  Blowfish blowfish(key);

  for (size_t i = 0; i < in_size; i += (block_size * 2)) {
    L = str_to_uint32(
        std::string(input_buf.data() + i, input_buf.data() + i + block_size),
        block_size);
    R = str_to_uint32(std::string(input_buf.data() + i + block_size,
                                  input_buf.data() + i + 2 * block_size),
                      block_size);
    blowfish.encrypt(L, R);
    std::string block = uint32_to_str(L, block_size);
    block += uint32_to_str(R, block_size);
    int j = i;
    std::for_each(block.begin(), block.end(), [&](char b) {
      input_buf[j] = b;
      j++;
    });
  }

  return input_buf.size();
}

uint64_t Encryptor::blowfish_decrypt(std::vector<char> &input_buf,
                                     std::string const &key, uint64_t in_size) {
  uint32_t L = 0, R = 0;
  int block_size = sizeof(uint32_t);
  Blowfish blowfish(key);

  for (size_t i = 0; i < in_size; i += (block_size * 2)) {
    L = str_to_uint32(
        std::string(input_buf.data() + i, input_buf.data() + i + block_size),
        block_size);
    R = str_to_uint32(std::string(input_buf.data() + i + block_size,
                                  input_buf.data() + i + 2 * block_size),
                      block_size);
    blowfish.decrypt(L, R);
    std::string block = uint32_to_str(L, block_size);
    block += uint32_to_str(R, block_size);
    int j = i;
    std::for_each(block.begin(), block.end(), [&](char b) {
      input_buf[j] = b;
      j++;
    });
  }
  return input_buf.size();
}
} // namespace krypto
