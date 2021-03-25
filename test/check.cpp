/**
 * /mnt/z/my_git/RCRS-CSD-327/test/check.cpp
 * @file check.cpp
 * @author Avinal Kumar
 * @since March 25, 2021
 *
 * Check filesystem
 */


#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
namespace fs = std::filesystem;

template <typename TP> std::time_t to_time_t(TP tp) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() +
                                                      system_clock::now());
  return system_clock::to_time_t(sctp);
}

struct fileprop {

  std::string filename;
  unsigned long file_size;
  fs::file_type type;
  std::time_t modify;
  fileprop(std::string filename) : filename(filename) {}
  void file_stat() {
    fs::path p = fs::current_path() / filename;

    auto ftime = fs::last_write_time(p);
    modify = to_time_t(ftime);
    type = fs::status(p).type();
    file_size = fs::file_size(p);
  }

  void print() {
    std::cout << "Name: " << filename << std::endl
              << "Modify time" << std::asctime(std::localtime(&modify))
              << std::endl
              << "File Size: " << file_size << std::endl;
  }
};

int main(int argc, char const *argv[]) {

  fs::path p = fs::current_path();
  std::cout << p;

  return 0;
}
