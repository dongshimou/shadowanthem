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


void socks5::handshake(tcp_conn conn) {

    auto rbuf = asio::buffer(m_recv.data(), m_recv.size());
    auto sbuf = asio::buffer(m_send.data(), m_send.size());
    auto first = [&]() -> bool {
        if (m_recv[0] != 0x05) {
            logger::debug(POS, "NOT socksv5!");
            return false;
        }
        switch (m_recv[2]) {
            case 0x00: {
                m_send = bytes({0x05, 0x00});
                break;
            }
            default: {
                m_send = bytes({0x05, 0x00});
                break;
            }
        }
        return true;
    };
    auto second=[&]()->bool{
        if(m_recv[0]!=0x05){
            return false;
        }
        if(m_recv[1]!=0x01){
            return false;
        }
        static const constexpr auto typeIPv4 = 0x01; // type is ipv4 address
        static const constexpr auto typeDM   = 0x03; // type is domain address
        static const constexpr auto typeIPv6 = 0x04; // type is ipv6 address
        auto typeAddr=m_recv.split(3);
        const constexpr auto  IPv4len = 4;
        auto DMlen=0;//dynamic
        const constexpr auto  IPv6len = 16;
        const constexpr auto PortLen=2;
        size_t len=1;
        switch(typeAddr[0]){
            case typeIPv4:{
                len+=IPv4len;
                break;
            }
            case typeIPv6:{
                len+=IPv6len;
                break;
            }
            case typeDM:{
                len+=typeAddr[1];
                break;
            }
        }
        len+=PortLen;

        m_head=typeAddr.split(0,len);

        return true;
    };

    auto two=[&](){
        conn->async_receive(rbuf, [&](const asio::error_code &error, std::size_t len){
            if(error){
                return;
            }
            if(!second()){
                return;
            }

            auto rsp=bytes(10);
            //socket version
            rsp[0]=0x05;
            //response status
            //	0x00	成功
            //	0x01	普通的失败
            //	0x02	规则不允许的连接
            //	0x03	网络不可达
            //	0x04	主机不可达
            //	0x05	连接被拒绝
            //	0x06	TTL超时
            //	0x07	不支持的命令
            //	0x08	不支持的地址类型
            //	0x09 ~ 0xFF		未定义
            rsp[1]=0x00;
            //RSV must 0x00
            rsp[2]=0x00;
            //address type
            //	0x01	IPV4
            //	0x03	域名
            //	0x04	IPV6
            rsp[3]=0x01;
            // IPV4为4字节 域名为字符串 IPV6为16字节
            rsp[4]= rsp[5]= rsp[6]=rsp[7] = 0x00;
            //bind port
            rsp[8]=0x00,rsp[9]=0x00;

            auto tmpbuf=asio::buffer(rsp.data(),rsp.size());
            conn->async_send(tmpbuf,[&](const asio::error_code &error, std::size_t len){
                if(error){
                    return;
                }
                pipe(conn,);
            });
        });
    };
    auto one=[&](){
        conn->async_receive(rbuf, [&](const asio::error_code &error, std::size_t len) {
            if (error) {
                logger::debug(POS, error.message());
                return;
            }
            if (!first()) {
                return;
            }
            conn->async_send(sbuf, [&](const asio::error_code &error, std::size_t len) {
                if(error){
                    logger::debug(POS,error.message());
                    return;
                }
                two();
            });
        });
    };


    one();
}

void socks5::pipe(tcp_conn,tcp_conn) {

}

void socks5::listen() {
    auto conn=tcp_conn((*this));
    this->get().async_accept(*conn,[](const asio::error_code &err){
        if(err){
            logger::debug(POS,err.message());
            return;
        }
        handshake(conn);
        listen();
    });
    this->run();
}

}