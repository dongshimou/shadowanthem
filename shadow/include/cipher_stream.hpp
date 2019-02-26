

#ifndef SHADOWANTHEMS_CIPHER_STREAM_HPP
#define SHADOWANTHEMS_CIPHER_STREAM_HPP

#include "bytes.hpp"

namespace shadow{

//interface
struct cipher_interface {
    virtual bytes init_encrypt() = 0;

    virtual void init_decrypt(const bytes &iv) = 0;

    virtual bytes encrypt(const bytes &src) = 0;

    virtual bytes decrypt(const bytes &src) = 0;
};

struct cipher_stream : public cipher_interface {
    enum struct DecOrEnc {
        Decrypt = 1,
        Encrypt = 2,
    };
    bytes m_key;
    bytes enc_iv;
    bytes dec_iv;

    cipher_stream(const bytes&keys,int ivl) :m_key(keys),ivLen(ivl){}
    virtual cipher_stream* copy()=0;
    virtual void reset(){
        enc_iv=bytes();
        dec_iv=bytes();
    }
    virtual bool is_init_encrypt(){
        return !enc_iv.empty();
    }
    virtual bool is_init_decrypt(){
        return !dec_iv.empty();
    }

    virtual ~cipher_stream() = default;

    std::size_t ivLen;
};

}
#endif //SHADOWANTHEMS_CIPHER_STREAM_HPP
