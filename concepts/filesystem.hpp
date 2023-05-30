#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <filesystem>
#include <iostream>
#include <regex>
#include <string_view>

// Implement functions
/**
 * Prints content of directory given by path
 * Format
 * [X] file_name file_size
 * where X equals D for directories, F for regular files, L for symlinks and space otherwise.
 * @param path directory path
 */
void printDirectory(std::string_view path)
{
    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        std::cout << "["
                  << (file.is_directory()      ? "D"
                      : file.is_regular_file() ? "F"
                      : file.is_symlink()      ? "L"
                                               : " ")
                  << "] " << file.path().filename() << " " << file.file_size() << std::endl;
    }
}

/**
 * Makes copies of all files matching fileNames regular expression in directory given by path
 * to files in the same directory but with changes extension to newExtension
 * @param path directory path
 * @param fileNames regular expression
 * @param newExtension new extension
 */
void changeExtension(std::filesystem::path path, std::string fileNames, std::string_view newExtension)
{
    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        if (std::regex_match(file.path().filename().string(), std::regex(fileNames)))
        {
            std::filesystem::path newPath = file.path();
            newPath.replace_extension(newExtension);
            std::filesystem::copy(file.path(), newPath);
        }
    }
}

#endif // FILESYSTEM_HPP