#include <iostream>
#include "ustring.h"

int main() {
    using namespace nustr;
    ustring s = "abcdef";

    std::cout << "s.size() = "    << s.size();
    std::cout << " s.capacity = " << s.capacity() << std::endl;

    s.insert(4, 'H');

    s.print(std::cout);
    std::cout << std::endl;

    ustring s1 = {'a', 'K', 'J', 'D', 'k', 'i'};
    s1.print(std::cout);
    std::cout << std::endl;
    s1[2] = '0';
    s1.print(std::cout);
    std::cout << std::endl;

    ustring s15(s1);
    s15.print(std::cout);
    std::cout << std::endl;

    ustring s2(5, 'f');
    s2.print(std::cout);
    std::cout << std::endl << s2[5] << std::endl;
    std::cout << std::endl;

    ustring s3(7);
    s2.print(std::cout);
    std::cout << std::endl;

    ustring s4(s1, 3, 2);
    s4.print(std::cout);
    std::cout << std::endl;
    ustring s45 = "Take a seat, let me tell you";

    std::cout << "find_res: " << s45.find("seat") << std::endl;
    ustring ss = "seat";
    std::cout << "find_res: " << s45.find(ss) << std::endl;

    ustring nf("Yeah, when i grow up, ");
    nf += "you know what I wanna be?\n";
    nf += s45;
    std::cout << "find_res: " << nf.find(s45) << std::endl;
    nf += " my ridiculous dreams\n";
    nf.push_back('I');
    nf.insert(nf.size(), ' ');
    nf += "wanna rap, I know it's hard to belive";
    nf.push_back('\n');
    nf += "But I'm okey with it, I admit the lyrics are weak\n";
    nf += "I've been workin' on 'em, I'll be good eventually\n";
    std::cout << "find_res: " << nf.find(ss) << std::endl;
    nf += "I understand you gotta crawl before you get to your feet\n";
    nf += "But I been running for a while, they ain't ready for me, ah!\n";
    std::cout << std::endl;

    std::cout << nf << std::endl;
}
