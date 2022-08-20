/*
** EPITECH PROJECT, 2022
** DLLoader.hpp
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include "IGameModule.hpp"
#include <dlfcn.h>
#include <exception>
#include <cstdlib>

typedef std::unique_ptr<IDisplayModule> (*ent_point_gr_ptr)(const std::string &name);
typedef std::unique_ptr<IGameModule> (*ent_point_gm_ptr)(const std::string &name);

template <typename T1, typename T2>
class DLLoader {
public:
    DLLoader(const std::string &path) {
        _name = path.substr(path.find_last_of("/") + 1, path.find_last_of('.') - (path.find_last_of('/') + 1));
        _handle = dlopen(path.c_str(), RTLD_LAZY);
        if (_handle == NULL)
            throw std::runtime_error("dlopen error");
        dlerror();
        _entry_point = reinterpret_cast<T2>(dlsym(_handle, "entryPoint"));
        if (_entry_point == NULL) {
            dlclose(_handle);
            throw std::runtime_error(dlerror());
        }
    };
    ~DLLoader() {
        std::cerr << "Module name : " << _name << std::endl;
        dlclose(_handle);
        std::cerr << "Success" << std::endl;
    };
    std::unique_ptr<T1> getInstance() {
        return _entry_point(_name);
    };

private:
    std::string _name;
    void *_handle;
    T2 _entry_point;
};

#endif /* !DLLOADER_HPP_ */
