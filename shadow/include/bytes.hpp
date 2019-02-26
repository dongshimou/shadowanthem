
#ifndef SHADOWANTHEMS_BYTES_HPP
#define SHADOWANTHEMS_BYTES_HPP


#include <string>
#include <utility>
#include <vector>
#include <ostream>
#include <array>

namespace shadow{

using byte=unsigned char;
class bytes : public std::vector<byte> {
    using super = std::vector<byte>;
public:
    static const constexpr std::size_t Block_Size = 4096;

    bytes(const std::string &str);

    bytes(const char *str);

    bytes(std::size_t t);

    bytes()= default;

    bytes& cover(const bytes&data,std::size_t begin=0);

    bytes &operator+=(const bytes &data);

    bytes &operator+=(const char *str);

    bytes &operator+=(const std::string &str);

    friend bytes operator+(const bytes &src, const bytes &data);

    friend bytes operator+(const bytes &src, const char *str);

    friend bytes operator+(const bytes &src, const std::string &str);

    bytes split(std::size_t begin, std::size_t end = std::size_t(-1));

    std::string to_string();

    template <int n>
    std::array<byte,n> to_array(){
        std::array<byte,n>res;
        std::size_t count=0;
        for(auto &i:*this){
            res[count++]=i;
        }
        return res;
    };

    friend std::ostream &operator<<(std::ostream &out,const bytes &data);
};

}

#endif //SHADOWANTHEMS_BYTES_HPP
