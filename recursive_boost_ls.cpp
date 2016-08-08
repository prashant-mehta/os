/* 
 * C++ program to list all non-directory files in provided path (Recursive implementation)
 * Usage: ./recursive_boost_ls path
 *  e.g. ./recursive_boost_ls A/
 */
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <vector>


using namespace std;
using namespace boost::filesystem;

void listFilesInDirectory ( directory_iterator );

int main (int argc, char* argv[])
{
    // Exit the program in case of missing argument
    if ( argc < 2 )
    {
        cout << "Usage: boost_ls path\n" ;
        return 1;
    }

    path p ( argv[1] );

    // Exit the program if argument is not a valid directory path
    if ( ! exists(p) )
    {
        cout << p.string() << " directory does not exist" << endl;
        return 1;
    }

    // Exit the program if argument is not a directory
    if ( ! is_directory(p) )
    {
        cout << p.string() << " is not a directory" << endl;
        return 1;
    }

    cout << "Entered path is " << p.string() << endl;

    // directory_iterator object initialized for current directory
    directory_iterator dir_iter(p);

    cout << "All files in this path are " << endl;
    
    // Recursively list all the files in directory and traverse the sub-directories
    listFilesInDirectory ( dir_iter );
}

void listFilesInDirectory ( directory_iterator dir_iter )
{

    vector<path> sortedList;
    
    // Copy all files in present directory from dir_iter to sortedList vector
    copy ( dir_iter, directory_iterator(), back_inserter(sortedList) );

    // Sort the vector to order files and directories
    sort ( sortedList.begin(), sortedList.end() );

    // Reverse the vector to bring all files before directories since we want to print
    // files in current directory first and then traverse to sub-directories
    reverse( sortedList.begin(), sortedList.end() );

    // Traverse through all files and directories in present directory
    for (vector<path>::const_iterator it (sortedList.begin()), it_end(sortedList.end()); it != it_end; ++it)
    {
        // If present directory contains a directory, recurse
        if ( is_directory( *it ) ) 
        {
            //cout << "Directory " << curr_dir_iter->path().filename() << endl;
            directory_iterator next_dir_iter( *it ); 
            listFilesInDirectory ( next_dir_iter );

        }
        // If present directory contains a file print it out
        else if ( is_regular_file( *it ) )
        {
            path temp_path(*it);
            cout << temp_path.relative_path().string() << endl;
        }

    }
}
