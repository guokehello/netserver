
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include "Server.h"

using namespace std;


int main()
{
    boost::asio::io_service service;

    Server svr(service, 11111);
    svr.Start();

    service.run();
    getchar();

    return 0;
}