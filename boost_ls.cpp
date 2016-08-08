/* 
 * C++ program to list all non-directory files in provided path
 * Usage: ./boost_ls path
 *  e.g. ./boost_ls A/
*/
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

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

    directory_iterator end_iter;

    // Stack to maintain a list of directories to be traversed
    stack<directory_iterator> directoriesStack;

    // directory_iterator object initialized for current directory
    directory_iterator dir_iter(p);

    // Push present directory onto stack
    directoriesStack.push(dir_iter);

    cout << "All files in this path are " << endl;

    // Traverse directories in stack until stack is empty
    while ( ! directoriesStack.empty() ){

        // Get and remove the directory on top of the stack
        directory_iterator curr_dir_iter = directoriesStack.top();
        directoriesStack.pop();

        // Traverse all files and directories in present directory
        for ( curr_dir_iter; curr_dir_iter != end_iter; ++curr_dir_iter )
        {
            // If present directory contains a directory push it on the stack to be traveresed later
            if ( is_directory(curr_dir_iter->status()) ) 
            {
                //cout << "Directory " << curr_dir_iter->path().filename() << endl;
                directory_iterator dir_iter( curr_dir_iter->path() ); 
                directoriesStack.push( dir_iter );

            }
            // If present directory contains a file print it out
            else if ( is_regular_file( curr_dir_iter->status() ) )
            {
                cout << curr_dir_iter->path().relative_path().string() << endl;
            }

        }
    }

}
