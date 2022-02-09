#ifndef KARAMAY_ENGINE_FILESYSTEM_H
#define KARAMAY_ENEGIN_FILESYSTEM_H

#include "public/stl.h"

namespace ke_filesystem
{



    /*
    * 
    * 
    */
    static bool load(const std::filesystem::path& ke_path, std::string& content)
    {
        using namespace std::filesystem;

        if (!exists(ke_path))
        {
            return false;
        }

        directory_entry _entry(ke_path);
        if (_entry.status().type() != file_type::directory)
        {
            return false;
        }

        std::string_view _path;
        std::ifstream _file(ke_path);
        std::string _content;

        _file.exceptions(std::fstream::failbit | std::fstream::badbit);
        directory_iterator _dit(ke_path);
        for (auto& _it : _dit)
        {
            _it.path().filename();
        }

        try {
            _file.open(_path);
            std::stringstream sstream;
            sstream << _file.rdbuf();
            _file.close();
            _content = sstream.str();
        }
        catch (const std::exception& e) {
            std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
        }

        return true;
    }

    /*
    * 
    * 
    */
    static bool load_x(const std::filesystem::path& ke_path, std::string& content) { return false; }

    /*
    * 
    * 
    */
    static bool save(const std::filesystem::path& path) { return false; }

    /*
    * 
    * 
    */
    static bool save(const std::filesystem::path& path, const std::string& content) { return false; }


};

#endif