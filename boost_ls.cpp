#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main (int argc, char* argv[])
{
    if ( argc < 2 )
    {
        cout << "Usage: boost_ls path\n" ;
        return 1;
    }

    path p (argv[1]);

    if ( ! exists(p) )
    {
        cout << "Invalid path" << endl;
        return 1;
    }

    if ( ! is_directory(p) )
    {
        cout << "Not a directory" << endl;
        return 1;
    }

    cout << "Entered path is " << p << endl;

    directory_iterator end_iter;

    stack<directory_iterator> directoriesStack;

    directory_iterator dir_iter(p);

    directoriesStack.push(dir_iter);

    while ( ! directoriesStack.empty() ){

        directory_iterator curr_dir_iter = directoriesStack.top();
        directoriesStack.pop();



        for ( curr_dir_iter; curr_dir_iter != end_iter; ++curr_dir_iter )
        {
            if ( is_directory(curr_dir_iter->status()) ) 
            {
                cout << "Directory " << curr_dir_iter->path().filename() << endl;
                directory_iterator dir_iter(curr_dir_iter->path()); 
                directoriesStack.push(dir_iter);

            }
            else if ( is_regular_file(curr_dir_iter->status()) )
            {
                cout << "File " << curr_dir_iter->path().relative_path().string() << endl;
            }

        }
    }



}
