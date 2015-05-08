/*
The MIT License (MIT)

Copyright (c) 2015 Leonardo de Oliveira Lourenço

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "file_operations.hpp"

/*   --------------
    |   read_file   |
     --------------

     Reads file 'filename' and store it's contents on string 'filecontents'
*/
bool Utility_Functions::read_file(const std::string &filename,std::string &filecontents)
{
    std::vector<char> content_vector;

    if(Utility_Functions::read_file_to_vector(filename,content_vector))
    {
        filecontents.assign(content_vector.data(),content_vector.size());

        return true;
    }

    return false;
}

/*   ---------------
    |   copy_file   |
     ---------------

     Copies the file 'from', saving on 'to'
*/
bool Utility_Functions::copy_file(const std::string &from,const std::string &to)
{
    std::string content;

    if(Utility_Functions::read_file(from,content))
    {
        if(Utility_Functions::write_file(to,content))
        {
            return true;
        }
    }

    return false;
}

/*   -------------------
    |   get_file_size   |
     -------------------

     Opens the file 'filename' and returns it's size
*/
std::size_t Utility_Functions::get_file_size(const std::string &filename)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    std::size_t file_size = 0;

    if(file.is_open())
    {
        file_size = Utility_Functions::get_file_size(file);

        file.close();
    }

    return file_size;
}

/*   -------------------
    |   get_file_size   |
     -------------------

     Returns the size of an open file
*/
std::size_t Utility_Functions::get_file_size(std::ifstream &file)
{
    std::size_t file_size = 0;

    if(file.is_open())
    {
        // Determine the file length
        file.seekg(0, std::ios_base::end);

        file_size = file.tellg();

        file.seekg(0, std::ios_base::beg);
    }

    return file_size;
}

/*   ----------------
    |   write_file   |
     ----------------

     Creates a file and stores 'contents' in it
*/
bool Utility_Functions::write_file(const std::string &filename,const std::string &contents)
{
    std::ofstream file(filename.c_str());

    if( !file.is_open() )
    {
        /* If file couldn't be opened, returns false */
        return false;
    }
    
    file << contents;

    file.close();

    return true;
}

bool Utility_Functions::replace_str_on_file(const std::string &filename,const std::string &replace_from,const std::string &replace_to)
{
    std::string file_content;

    if(Utility_Functions::read_file(filename,file_content))
    {
        //std::cout << "\nConteudo:\n" << file_content << std::endl;
        boost::replace_all(file_content,replace_from,replace_to);
        
        return Utility_Functions::write_file(filename,file_content);
    }

    return false;
}

SymlinkStatus Utility_Functions::create_symbolic_link(bfs::path &from,bfs::path &to)
{
    
    //std::cout << "\nLinking: > " << from.string() <<
    //             "\n     To: > " << to.string() << std::endl;
    

    if( bfs::exists(to) )
    {
        return LNK_EXISTS;
    }
    else if (!bfs::exists(from))
    {
        return LNK_NO_FILE;
    }
    else
    {
        boost::system::error_code ec;

        bfs::create_symlink(from,to,ec);

        if(!ec)
        {
            return LNK_OK;
        }
        else
        {
            return LNK_ERROR;
        }
    }

    return LNK_FATAL_ERROR;
}

bool Utility_Functions::remove_files_with_extension_from_dir(bfs::path &dir,const std::string &extension)
{
    //  Cria um iterator para indicar fim do diretorio
    bfs::directory_iterator end_itr;

    //  Cria um iterator para percorrer o diretorio
    bfs::directory_iterator dir_itr(dir);

    boost::system::error_code ec;

    //  Le os nomes dos "fpack" primeiros arquivos
    for( ; dir_itr != end_itr; ++dir_itr)
    {
        if(bfs::is_regular_file(dir_itr->status()) )
        {
            if( !extension.compare(dir_itr->path().extension().string()) )
            {
                //std::cout << "\nRemoving file: " << dir_itr->path().string();
                bfs::remove(dir_itr->path(),ec);

                if(ec)
                {
                    return false;
                }
            }
        }
    }

    return true;
}
