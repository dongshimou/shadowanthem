


#include <iostream>
#include <server.hpp>
#include <bytes.hpp>
#include <functional>
#include "logger.hpp"

void listen(const std::string&port,const std::string&method,const std::string&pass) {


    auto data = shadow::bytes{"hello\n"};
    auto sendBuffer = shadow::bytes(2048);
    auto recvBuffer = shadow::bytes(2048);
    //send buffer
    //recv buffer
    auto buf = asio::buffer(sendBuffer.data(), sendBuffer.size());

    auto sbuf=asio::buffer(sendBuffer.data(), sendBuffer.size());
    auto rbuf=asio::buffer(recvBuffer.data(),recvBuffer.size());

    shadow::tcp_server ser(port);


    auto accept=std::function<void(void)>();

    accept=[&](){
        logger::debug("accept!");
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

int main(int argc,char*argv[]) {
    auto parse = [&](const char *arg) -> std::string {
        for (auto i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], arg) == 0) {
                if (i + 1 < argc) {
                    return std::string(argv[i + 1]);
                }
            }
        }
        return std::string{};
    };
    auto parse_port = [&]() {
        auto port = parse("-p");
        if (port.empty()) {
            port = std::string{"9090"};
        }
        return port;
    };
    auto parse_method = [&]() {
        auto method = parse("-m");
        if (method.empty()) {
            method = std::string{"aes-256-cfb"};
        }
        return method;
    };

    auto parse_password = [&]() {
        auto pass = parse("-k");
        if (pass.empty()) {
            pass = std::string("test");
        }
        return pass;
    };

    auto port = parse_port();
    auto method = parse_method();
    auto pass = parse_password();

    listen(port,method,pass);
    return 0;
}