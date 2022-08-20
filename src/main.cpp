/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2 || ac > 2) {
        std::cout << "Usage: ./arcade [path to a graphical library]" << std::endl;
    } else {
        try {
            Core core(av[1]);
            core.loop();
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
