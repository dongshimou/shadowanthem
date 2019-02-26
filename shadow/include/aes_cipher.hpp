
#ifndef SHADOWANTHEMS_AES_STREAM_HPP
#define SHADOWANTHEMS_AES_STREAM_HPP

#include "cipher_stream.hpp"

#include <openssl/aes.h>

namespace shadow{

//AES_cfb128_encrypt
class aes_cipher : public cipher_stream {
    using super = cipher_stream;
public:
    aes_cipher(const bytes&keys,int ivl) ;

    virtual ~aes_cipher() = default;

    bytes init_encrypt() override;

    cipher_stream* copy()override;


    void init_decrypt(const bytes &iv) override;

    bytes encrypt(const bytes &src) override;

    bytes decrypt(const bytes &src) override;

private:
    bytes xor_stream(const bytes &src, DecOrEnc doe);

private:
    AES_KEY enc;
//    AES_KEY dec;
};

}

#endif //SHADOWANTHEMS_AES_STREAM_HPP
