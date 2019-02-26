#include "server.hpp"

#include "logger.hpp"
namespace shadow{

tcp_server::tcp_server(const std::string &port, asio::ip::tcp ver)
:m_acceptor(asio::ip::tcp::acceptor(*this, asio::ip::tcp::endpoint(ver, std::stoi(port)))){

}


tcp_conn tcp_server::accept() {
    auto conn = tcp_conn(*this);
    m_acceptor.accept(*conn);
    logger::debug(POS, FUN, "=========accept!=========");
    return conn;
}

asio::ip::tcp::acceptor& tcp_server::get()  {
    return m_acceptor;
}


}