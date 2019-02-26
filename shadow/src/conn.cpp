#include "conn.hpp"

#include "logger.hpp"
namespace shadow {
tcp_conn::tcp_conn(asio::io_service &io)
        : super(asio_tcp_conn(new asio::ip::tcp::socket(io), [](asio::ip::tcp::socket *ptr) {
    try {
        ptr->shutdown(ptr->shutdown_both);
    } catch (const std::exception &e) {
        logger::debug(POS, FUN, e.what());
    }
    try {
        ptr->close();
    } catch (const std::exception &e) {
        logger::debug(POS, FUN, e.what());
    }
    delete ptr;
})) {


}


}