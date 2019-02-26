
#ifndef SHADOWANTHEMS_SERVER_HPP
#define SHADOWANTHEMS_SERVER_HPP

#include "conn.hpp"

namespace shadow {
class tcp_server :public asio::io_service{
    using super=asio::io_service;
    public:
    explicit tcp_server(const std::string &port, asio::ip::tcp ver = tcpv4);

    tcp_conn accept();

    asio::ip::tcp::acceptor&get();
private:
    asio::ip::tcp::acceptor m_acceptor;
};

}

#endif //SHADOWANTHEMS_SERVER_HPP
