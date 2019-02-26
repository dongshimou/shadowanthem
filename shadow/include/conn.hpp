

#ifndef SHADOWANTHEMS_CONN_HPP
#define SHADOWANTHEMS_CONN_HPP

#include <memory>
#include <asio.hpp>

#include "bytes.hpp"

namespace shadow{

using asio_tcp_conn=std::shared_ptr<asio::ip::tcp::socket>;
#if __cplusplus>201703L
inline static auto tcpv4 = asio::ip::tcp::v4();
#else
const auto tcpv4=asio::ip::tcp::v4();
#endif


class tcp_conn:public asio_tcp_conn {
    using super=asio_tcp_conn ;

public:

    explicit tcp_conn(asio::io_service&io);

};


}

#endif //SHADOWANTHEMS_CONN_HPP
