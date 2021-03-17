/**
 * /mnt/z/my_git/RCRS-CSD-327/include/Utils.hpp
 * @file Utils.hpp
 * @author Avinal Kumar
 * @since March 04, 2021
 *
 * Utilities
 */
// include blowfish library
#include <blowfish/blowfish.h>

// include standard headers
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>

// defines
namespace fs = std::filesystem;

#if !defined(UTILS_HPP)
#define UTILS_HPP

namespace MCPS {

struct filestat {
  std::string filename;
  fs::path filepath;
  uint64_t filesize;
  fs::file_type filetype;
  std::time_t m_time;
  bool is_regular;
  filestat() {} // default constructor
  filestat(std::string const &file_name); 
  filestat(filestat const &stat); // copy constructor
  void print();

private:
  template <typename TP> std::time_t to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() +
                                                        system_clock::now());
    return system_clock::to_time_t(sctp);
  }
};

class fileop {
private:
  std::unordered_map<std::string, filestat> _files;

public:
  uint64_t read_file(std::string const &infile, std::vector<char> &input_buf,
                  filestat const &stat);

  uint64_t write_file(std::string const &outfile, std::vector<char> &output_buf,
                   uint64_t out_size);
  std::unordered_map<std::string, filestat> scan_current_directory();
  uint64_t pad_input(std::vector<char> &input_buf, uint64_t in_size);
  uint64_t attach_key(std::vector<char> &input_buf, std::string const &key,
                  uint64_t in_size);
};

} // namespace MCPS

#endif // UTILS_HPP
