#ifndef UTIL_FILE_OPERATIONS_H
#define UTIL_FILE_OPERATIONS_H

#include <string>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

// Symbolic link status
typedef enum
{
    LNK_OK = 0,     /* Symbolic link created */
    LNK_NO_FILE,    /* File to be linked doesn't exist */
    LNK_EXISTS,     /* Symbolic link was already there */
    LNK_ERROR,      /* Symbolic link couldn't be created */
    LNK_FATAL_ERROR /* Fatal error occurred */
} SymlinkStatus;

namespace Utility_Functions
{
    /* reads a file and stores content on 'filecontents'

        returns true on successful read and false otherwise
    */
    bool read_file(const std::string &filename,std::string &filecontents);

    /* copies the file 'from' to 'to'

        returns true on successful copy and false otherwise
    */
    bool copy_file(const std::string &from,const std::string &to);

    /* returns the size of file 'filename' */
    std::size_t get_file_size(const std::string & filename);

    /* returns the size of file 'filename'
        File pointer is moved back to begining on successful execution
    */
    std::size_t get_file_size(std::ifstream &file);

    /* reads a file and stores content on 'filecontents'

        returns true on successful write and false otherwise
    */
    bool write_file(const std::string &filename,const std::string &contents);

    /*    replaces all occurences of a string in a file

        returns true on successful replace and false otherwise
    */
    bool replace_str_on_file(const std::string &filename,const std::string &replace_from,const std::string &replace_to);

    /*    creates symbolic link for a file
    */
    SymlinkStatus create_symbolic_link(bfs::path &from,bfs::path &to);

    /*  removes files with given extension from dir
    */
    bool remove_files_with_extension_from_dir(bfs::path &dir,const std::string &extension);
}

#endif
