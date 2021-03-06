#include <iostream>
#include <iomanip>
#include <boost/bind.hpp>
#include "tcp_connection.hpp"
#include "query.h"
#include "client.h"
using std::cout;
using std::endl;

Client::Client (Query query,
                boost::asio::io_service& io_service, 
                tcp::resolver::iterator endpoint_iterator)
  : query_(query) {
    
  connection_ = TcpConnection::create(io_service);
  boost::asio::async_connect(connection_->socket(), endpoint_iterator,
      boost::bind(&Client::handle_connect, this,
        boost::asio::placeholders::error));
}

// upon connection, send the query to server
void Client::handle_connect(const boost::system::error_code& error)
{
  if (!error) {
    tcp::endpoint endpoint = connection_->socket().remote_endpoint();
    boost::asio::ip::address addr = endpoint.address();
    unsigned short port = endpoint.port();
    cout << "Connected: " << addr << ":" << port << endl;

    connection_->async_write(query_, 
        boost::bind(&Client::handle_write, this,
          boost::asio::placeholders::error));
  } else {
    cout << "[handle_connect] " << error.message() << endl;
    connection_->do_close();
  }
}

// upon sending the query, read the content sent back by server
void Client::handle_write(const boost::system::error_code& error) {
  if (!error) {
    connection_->async_read(result_,
        boost::bind(&Client::handle_read, this,
          boost::asio::placeholders::error));
  } else {
    cout << "[handle_write] " << error.message() << endl;
    connection_->do_close();
  }
}

void Client::handle_read(const boost::system::error_code& error) {
  if (!error) {
    // print out the result and close connection
    cout << query_.filename_ << ":\n";
    cout << result_ << "\n";

    connection_->do_close();
  } else {
    cout << "[handle_read] " << error.message() << endl;
    connection_->do_close();
  }
}

