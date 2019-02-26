

#ifndef SHADOWANTHEMS_CIPHER_HPP
#define SHADOWANTHEMS_CIPHER_HPP

#include "cipher_stream.hpp"

namespace shadow {

class cipher {
private:

public:
    explicit cipher(const std::string &method, const std::string &password);

    virtual ~cipher();

    cipher(const cipher &other);

    cipher(cipher &&other);

    cipher &operator=(const cipher &other);

    cipher &operator=(cipher &&other);

    cipher copy();

    //md5 hash --> general enough length password
    static bytes evpBytesToKey(std::string password, int kenLen);

    static bytes md5Sum(const bytes &ori);

    static bytes md5Sum(bytes &&ori);

    static bytes md5Sum(const std::string &str);

    static bytes md5Sum(std::string &&str);

public:
    cipher_stream *method = nullptr;

private:
    cipher() {};
};

}

#endif //SHADOWANTHEMS_CIPHER_HPP
