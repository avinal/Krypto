/**
 * /mnt/z/my_git/RCRS-CSD-327/src/Main.cpp
 * @file Main.cpp
 * @author Avinal Kumar
 * @since February 18, 2021
 *
 * The driver code
 */

#include "Encryptor.h"
#include "Utils.h"

int main(int argc, char const *argv[]) {
  krypto::fileop test;
  std::vector<char> buffer;
  std::string filename, password;
  std::cin >> filename >> password;

  krypto::filestat stat(filename);
  test.read_file(filename, buffer, stat);
  test.pad_input(buffer, stat.filesize);

  krypto::Encryptor encryptor;
  // encryptor.blowfish_encrypt(buffer, password, stat.filesize);
  encryptor.blowfish_decrypt(buffer,password,stat.filesize);
  test.write_file(filename.substr(8) , buffer, stat.filesize);
   
  return 0;
}
