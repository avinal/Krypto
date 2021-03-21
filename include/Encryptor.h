/**
 * /mnt/z/my_git/RCRS-CSD-327/include/Encryptor.hpp
 * @file Encryptor.hpp
 * @author Avinal Kumar
 * @since March 05, 2021
 *
 * Encryptor class
 */

#include <blowfish/blowfish.h>
#include <functional>

#if !defined(ENCRYPTOR_HPP)
#define ENCRYPTOR_HPP

namespace krypto {
class Encryptor {

  uint32_t str_to_uint32(std::string const &block, int block_size) {
    return *reinterpret_cast<uint32_t *>(
        const_cast<char *>(block.substr(0, block_size).c_str()));
  }

  std::string uint32_to_str(uint32_t digest, int const block_size) {
    std::string data("");
    for (int i = 0; i < block_size; i++) {
      data += (uint8_t)(digest >> i * 8);
    }
    return data;
  }

public:
  Encryptor();
  ~Encryptor();
  uint64_t blowfish_encrypt(std::vector<char> &input_buf,
                            std::string const &key, uint64_t in_size);
  uint64_t blowfish_decrypt(std::vector<char> const &input_buf,
                            std::string const &key, uint64_t in_size);
};

} // namespace krypto

#endif // ENCRYPTOR_HPP
