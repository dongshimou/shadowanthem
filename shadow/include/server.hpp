
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


class anthems{
public:
    virtual void listen()=0;
    virtual void handshake(tcp_conn)=0;
    virtual void pipe(tcp_conn,tcp_conn)=0;
};

class socks5:public tcp_server,public anthems{
    using super =tcp_server;

public:
    explicit socks5(const std::string &port,asio::ip::tcp ver=tcpv4)
    :super(port,ver){
        m_recv=bytes(2048);
        m_send=bytes(2048);
    }

public:

    void listen()override ;
    void handshake(tcp_conn)override;
    void pipe(tcp_conn,tcp_conn)override ;
private:

    bytes m_recv;
    bytes m_send;
    bytes m_head;
};

}

#endif //SHADOWANTHEMS_SERVER_HPP
