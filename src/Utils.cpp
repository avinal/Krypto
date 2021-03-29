/**
 * /mnt/z/my_git/RCRS-CSD-327/src/Utils.cpp
 * @file Utils.cpp
 * @author Avinal Kumar
 * @since March 04, 2021
 *
 * File utilities
 */

#include "Utils.h"

namespace krypto {

/**
 * Generates file stats for a given file name.
 *
 * @param file_name     name of the file
 */
filestat::filestat(std::string const &file_name) : filename(file_name) {
  filepath = fs::absolute(fs::current_path() / file_name);
  m_time = to_time_t(fs::last_write_time(filepath));
  filetype = fs::status(filepath).type();
  filesize = fs::file_size(filepath);
  is_regular = fs::is_regular_file(filepath);
}

/**
 * Copy constructor of the filestat struct.
 *
 * @param stat      Another filestat to copy
 */
filestat::filestat(filestat const &stat) {
  filename = stat.filename;
  filepath = stat.filepath;
  filesize = stat.filesize;
  filetype = stat.filetype;
  m_time = stat.m_time;
  is_regular = stat.is_regular;
}

/**
 * Prints the file properties gathered by filestat.
 * File Name
 * File Path
 * File Size
 * Last Modification Time
 *
 */
void filestat::print() {
  std::cout << "File name: " << filename << std::endl
            << "File path: " << filepath << std::endl
            << "File Size: " << filesize << " bytes." << std::endl
            << "Last modification time: "
            << std::asctime(std::localtime(&m_time)) << std::endl;
}

/**
 * The encrypt function encrypts/decrypts 8 bytes in a go. And thus the buffer
 * size must be a multiple of 8. If not then rest of the space is padded null.
 *
 * @param input_buf     Input char buffer
 * @param in_size       Size of the buffer
 *
 * @return              total size after padding
 */
uint64_t fileop::pad_input(std::vector<char> &input_buf, uint64_t in_size) {
  unsigned int dv = sizeof(uint32_t) * 2, rem;
  rem = ((in_size >= dv) ? (((in_size / dv) + 1) * dv - in_size)
                         : (dv - in_size));
  if (rem < dv) {
    input_buf.resize(rem + in_size + 1);
    in_size += rem;
  }
  return in_size;
}

/**
 * Attaches the encrypted password to the buffer.
 *
 * @param input_buf      Input char buffer
 * @param key            Encrypted Password
 * @param in_size        size of input buffer
 *
 * @return               total size of buffer after attaching key
 */
uint64_t fileop::attach_key(std::vector<char> &input_buf,
                            std::string const &key, uint64_t in_size) {
  input_buf.resize(in_size + MAXKEYBYTES + 3);
  std::for_each(key.begin(), key.end(), [&](char k) {
    input_buf[in_size] = k;
    in_size++;
  });
  return in_size;
}

/**
 * Reads input file into char buffer
 *
 * @param infile         Input file name
 * @param input_buf      Input char buffer
 * @param stat           File stats
 *
 * @return               total buffer size after reading file
 */
uint64_t fileop::read_file(std::string const &infile,
                           std::vector<char> &input_buf, filestat const &stat) {
  uint32_t in_size = 0, readsize = stat.filesize + 1;
  std::ifstream ifile(infile, std::ios::in | std::ios::binary);
  if (!ifile) {
    std::cerr << "Unable to open file: " << infile << std::endl;
    return -1;
  }

  input_buf.clear();
  input_buf.reserve(readsize + in_size + 1);
  if (ifile.is_open()) {
    input_buf.insert(input_buf.begin(), std::istreambuf_iterator<char>(ifile),
                     std::istreambuf_iterator<char>());
  }
  in_size = input_buf.size();
  ifile.close();
  return in_size;
}

/**
 * Write file from a buffer
 *
 * @param outfile       Output file name
 * @param output_buf    Output char buffer
 * @param out_size      Total write size
 *
 * @return              Number of bytes written
 */
uint64_t fileop::write_file(std::string const &outfile,
                            std::vector<char> &output_buf, uint64_t out_size) {
  std::ofstream ofile(outfile,
                      std::ios::out | std::ios::binary | std::ios::trunc);
  if (!ofile) {
    std::cerr << "Unable to create file: " << outfile << std::endl;
  }
  if (ofile.is_open()) {
    ofile.write(reinterpret_cast<char *>(&output_buf[0]),
                out_size * sizeof(char));
  }
  ofile.close();
  return fs::file_size(outfile);
}

/**
 * Scans the current directory and stores their information into an unordered
 * map.
 *
 * @return        Unordered Map: "key": string, "value": filestat
 */
std::unordered_map<std::string, filestat> fileop::scan_current_directory() {
  std::string ext(".cpp");
  fs::path current = fs::current_path();
  for (const auto &file : fs::directory_iterator(current)) {
    if (fs::is_regular_file(file)) {
      std::string _filename(file.path().filename().string());
      filestat fstat(_filename);
      _files.insert({_filename, fstat});
    }
  }
  return _files;
}
} // namespace krypto
