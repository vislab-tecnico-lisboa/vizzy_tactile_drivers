
/*This is a ROS node to read from the serial port a publish to a topic
*
* The ROS Serial Arduino solution seems to be faster, so this is not being used at the moment
*
*
*/



#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <boost/asio/signal_set.hpp>
#include <csignal>
#include <string>
#include <iostream>
#include <sstream>


using namespace boost::asio;
using namespace boost::system;
using std::signal;
using boost::asio::io_service;

io_service io;
boost::system::error_code ec;
serial_port sp(io);
ros::Publisher chatter_pub;
boost::asio::streambuf read_buf;

boost::system::error_code flushIncomingBuffer()
{
  boost::system::error_code ec;
#if !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)
  const bool isFlushed =! ::tcflush(sp.native(), TCIOFLUSH);
  if (!isFlushed)
    ec = boost::system::error_code(errno,
                                   boost::asio::error::get_system_category());
#else
  const bool isFlushed = ::PurgeComm(_serialPort.native(),
                                 #include <boost/asio/signal_set.hpp>    PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
  if (!isFlushed)
    ec = boost::system::error_code(::GetLastError(),
                                   boost::asio::error::get_system_category());
#endif
  return ec;
}


bool simpleSend(std::string msg)
{
  int tries = 0;
  while(tries < 10)
  {
    int sentSize = write(sp, boost::asio::buffer(msg));

    if(sentSize == (int) msg.size())
    {
      return true;
    }
    else
      tries++;
  }

  return false;
}

void handler( const boost::system::error_code& error , int signal_number )
{
  ROS_ERROR_STREAM("Exiting driver");
  sp.close();
  exit(1);
}

void read_handler(const error_code &ec, size_t nbytes)
{

  std_msgs::String msg;

  std::istream is(&read_buf);

  std::string line;

  std::getline(is, line);


  msg.data = line;

  chatter_pub.publish(msg);

//  chatter_pub.publish(msg);


  async_read_until(sp,read_buf,"\n",read_handler);

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "vizzy_tactile");
  ros::NodeHandle nh;

  chatter_pub = nh.advertise<std_msgs::String>("tactile", 1000);

  sp.open("/dev/ttyUSB1", ec);

  if(ec)
  {
    //Failure to connect
    ROS_ERROR_STREAM("Error connecting to sensors board: " << ec.message());
    sp.close();
    throw std::exception();
  }


  //Set the baudrate
  sp.set_option(serial_port_base::baud_rate(115200));

  flushIncomingBuffer();
  async_read_until(sp,read_buf,"\n",read_handler);

  // Construct a signal set registered for process termination.
  boost::asio::signal_set signal(io, SIGINT, SIGTERM);


  // Start an asynchronous wait for one of the signals to occur.
  signal.async_wait( handler );

  io.run();


  return 0;
}

