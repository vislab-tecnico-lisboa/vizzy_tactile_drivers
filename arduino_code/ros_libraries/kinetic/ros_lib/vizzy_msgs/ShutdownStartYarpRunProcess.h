#ifndef _ROS_SERVICE_ShutdownStartYarpRunProcess_h
#define _ROS_SERVICE_ShutdownStartYarpRunProcess_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_msgs
{

static const char SHUTDOWNSTARTYARPRUNPROCESS[] = "vizzy_msgs/ShutdownStartYarpRunProcess";

  class ShutdownStartYarpRunProcessRequest : public ros::Msg
  {
    public:
      typedef uint8_t _shutdown_request_type;
      _shutdown_request_type shutdown_request;
      typedef const char* _server_port_type;
      _server_port_type server_port;
      typedef const char* _command_str_type;
      _command_str_type command_str;
      typedef const char* _tag_str_type;
      _tag_str_type tag_str;
      enum { SHUTDOWN = 0 };
      enum { TURNON = 1 };

    ShutdownStartYarpRunProcessRequest():
      shutdown_request(0),
      server_port(""),
      command_str(""),
      tag_str("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->shutdown_request >> (8 * 0)) & 0xFF;
      offset += sizeof(this->shutdown_request);
      uint32_t length_server_port = strlen(this->server_port);
      varToArr(outbuffer + offset, length_server_port);
      offset += 4;
      memcpy(outbuffer + offset, this->server_port, length_server_port);
      offset += length_server_port;
      uint32_t length_command_str = strlen(this->command_str);
      varToArr(outbuffer + offset, length_command_str);
      offset += 4;
      memcpy(outbuffer + offset, this->command_str, length_command_str);
      offset += length_command_str;
      uint32_t length_tag_str = strlen(this->tag_str);
      varToArr(outbuffer + offset, length_tag_str);
      offset += 4;
      memcpy(outbuffer + offset, this->tag_str, length_tag_str);
      offset += length_tag_str;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->shutdown_request =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->shutdown_request);
      uint32_t length_server_port;
      arrToVar(length_server_port, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_server_port; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_server_port-1]=0;
      this->server_port = (char *)(inbuffer + offset-1);
      offset += length_server_port;
      uint32_t length_command_str;
      arrToVar(length_command_str, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_command_str; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_command_str-1]=0;
      this->command_str = (char *)(inbuffer + offset-1);
      offset += length_command_str;
      uint32_t length_tag_str;
      arrToVar(length_tag_str, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_tag_str; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_tag_str-1]=0;
      this->tag_str = (char *)(inbuffer + offset-1);
      offset += length_tag_str;
     return offset;
    }

    const char * getType(){ return SHUTDOWNSTARTYARPRUNPROCESS; };
    const char * getMD5(){ return "c5ce80df75712562795113fa171ae9df"; };

  };

  class ShutdownStartYarpRunProcessResponse : public ros::Msg
  {
    public:
      typedef uint8_t _shutdown_reply_type;
      _shutdown_reply_type shutdown_reply;
      enum { FAILURE = 0 };
      enum { SUCCESS = 1 };

    ShutdownStartYarpRunProcessResponse():
      shutdown_reply(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->shutdown_reply >> (8 * 0)) & 0xFF;
      offset += sizeof(this->shutdown_reply);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->shutdown_reply =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->shutdown_reply);
     return offset;
    }

    const char * getType(){ return SHUTDOWNSTARTYARPRUNPROCESS; };
    const char * getMD5(){ return "00e34715d837d8983c542cd2a76295c8"; };

  };

  class ShutdownStartYarpRunProcess {
    public:
    typedef ShutdownStartYarpRunProcessRequest Request;
    typedef ShutdownStartYarpRunProcessResponse Response;
  };

}
#endif
