// Chapter 11
#include <iostream>
#include <string>


int main()
{
    // ask for the person's name
    std::cout << "Please enter your first name: ";
    
    // read the name
    std::string name;
    getline( std::cin, name );

    // build the message that we intend to write
    const auto greeting = "Hello, " + name + "!";

    // build the second and fourth lines of the output
    const auto spaces = std::string( greeting.size(), ' ' );
    const auto second = "* " + spaces + " *";

    // build the first and fifith lines of the output
    const auto first = std::string( second.size(), '*' );

    // write it all
    std::cout << std::endl;
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << "* " << greeting << " *" << std::endl;
    std::cout << second << std::endl;
    std::cout << first << std::endl;

    return 0;
}
