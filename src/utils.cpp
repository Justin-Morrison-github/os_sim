#include <string>
#include <fstream>
#include <iostream>

std::string fill_n(char c, int n)
{
    return std::string(n, c);
}

void write_output(std::string string, const char *filename)
{
    std::ofstream output_file(filename);

    if (output_file.is_open())
    {
        output_file << string;
        output_file.close(); // Close the file when done
        std::cout << "File content overwritten successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::cout << "Output generated in " << filename << std::endl;
}