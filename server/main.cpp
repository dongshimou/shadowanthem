


#include <iostream>
#include <server.hpp>
#include <bytes.hpp>
#include <functional>
#include "logger.hpp"

void listen(const std::string&lport) {



    auto data = shadow::bytes{"hello\n"};
    auto buffer = shadow::bytes(2048);
    //send buffer
    //recv buffer
    auto buf = asio::buffer(buffer.data(), buffer.size());

    auto handshake = [&](const asio::error_code &error, std::size_t len) {

    };

    shadow::tcp_server ser(lport);

    auto accept=std::function<void(void)>();
    accept=[&](){
        auto close=[&](shadow::tcp_conn conn){
            asio::error_code err;
            conn->close(err);
        };

        auto send=[&](shadow::tcp_conn conn){
//            auto sbuf=asio::buffer(data.data(),data.size());
            conn->async_send(buf,[&](const asio::error_code &error,std::size_t len){
                if (error) {
                    logger::debug(POS,error.message());
                }
                close(conn);
            });
        };
        auto recv=[&](shadow::tcp_conn conn){
            conn->async_receive(buf,[&](const asio::error_code &error,std::size_t len){
                if (error) {
                    logger::debug(POS,error.message());
                }
                send(conn);
            });
        };


        auto conn=shadow::tcp_conn(ser);
        ser.get().async_accept(*conn, [&](const asio::error_code &error) {
            if (error) {
                logger::debug(POS,error.message());
            }
            recv(conn);
            accept();
        });
        ser.run();

    };

    accept();


}

int main(){

    listen("9090");
    return 0;
}