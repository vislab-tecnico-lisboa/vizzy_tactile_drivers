#ifndef _ROS_SERVICE_StringSrv_h
#define _ROS_SERVICE_StringSrv_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_behavior_trees
{

static const char STRINGSRV[] = "vizzy_behavior_trees/StringSrv";

  class StringSrvRequest : public ros::Msg
  {
    public:
      typedef const char* _command_type;
      _command_type command;
      typedef const char* _arg1_type;
      _arg1_type arg1;
      typedef const char* _arg2_type;
      _arg2_type arg2;

    StringSrvRequest():
      command(""),
      arg1(""),
      arg2("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_command = strlen(this->command);
      varToArr(outbuffer + offset, length_command);
      offset += 4;
      memcpy(outbuffer + offset, this->command, length_command);
      offset += length_command;
      uint32_t length_arg1 = strlen(this->arg1);
      varToArr(outbuffer + offset, length_arg1);
      offset += 4;
      memcpy(outbuffer + offset, this->arg1, length_arg1);
      offset += length_arg1;
      uint32_t length_arg2 = strlen(this->arg2);
      varToArr(outbuffer + offset, length_arg2);
      offset += 4;
      memcpy(outbuffer + offset, this->arg2, length_arg2);
      offset += length_arg2;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_command;
      arrToVar(length_command, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_command; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_command-1]=0;
      this->command = (char *)(inbuffer + offset-1);
      offset += length_command;
      uint32_t length_arg1;
      arrToVar(length_arg1, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_arg1; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_arg1-1]=0;
      this->arg1 = (char *)(inbuffer + offset-1);
      offset += length_arg1;
      uint32_t length_arg2;
      arrToVar(length_arg2, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_arg2; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_arg2-1]=0;
      this->arg2 = (char *)(inbuffer + offset-1);
      offset += length_arg2;
     return offset;
    }

    const char * getType(){ return STRINGSRV; };
    const char * getMD5(){ return "7addab281efdf18482237e77c6129c86"; };

  };

  class StringSrvResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    StringSrvResponse():
      success(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return STRINGSRV; };
    const char * getMD5(){ return "937c9679a518e3a18d831e57125ea522"; };

  };

  class StringSrv {
    public:
    typedef StringSrvRequest Request;
    typedef StringSrvResponse Response;
  };

}
#endif
