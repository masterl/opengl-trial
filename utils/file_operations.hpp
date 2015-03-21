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
    /* returns the size of file 'filename' */
    std::size_t get_file_size(const std::string & filename);

    /* returns the size of file 'filename'
        File pointer is moved back to begining on successful execution
    */
    std::size_t get_file_size(std::ifstream &file);

    template <typename T>
    bool read_file_to_vector(const std::string &filename,std::vector<T> &filecontents)
    {
        std::ifstream file(filename.c_str(), std::ios::binary);
        //const unsigned int bufferSize = 256;
        //const unsigned int bufferStr = 256;
        //char aux[bufferStr+2];
        //unsigned char tam;

        filecontents.clear();

        if( !file.is_open() )
        {
            return false;
        }

        std::size_t file_size = Utility_Functions::get_file_size(file);

        //std::cout << "\nread_file::file_size = " << file_size << std::endl;

        if(file_size > 0)
        {
            filecontents.resize(file_size);
            file.read(&filecontents[0], file_size);
            file.close();
            //std::string strAux(&bytes[0], file_size);
            //boost::algorithm::erase_all(strAux, "\r");
            //filecontents = strAux;
            // filecontents[file_size] = '\0';
        }

        return true;
    }

    /* reads a file and stores content on 'filecontents'

        returns true on successful read and false otherwise
    */
    bool read_file(const std::string &filename,std::string &filecontents);

    /* copies the file 'from' to 'to'

        returns true on successful copy and false otherwise
    */
    bool copy_file(const std::string &from,const std::string &to);

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
