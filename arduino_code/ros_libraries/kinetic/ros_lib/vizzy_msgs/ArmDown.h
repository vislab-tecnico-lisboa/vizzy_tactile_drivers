#ifndef _ROS_SERVICE_ArmDown_h
#define _ROS_SERVICE_ArmDown_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_msgs
{

static const char ARMDOWN[] = "vizzy_msgs/ArmDown";

  class ArmDownRequest : public ros::Msg
  {
    public:
      typedef uint8_t _arm_down_request_type;
      _arm_down_request_type arm_down_request;
      typedef uint8_t _robot_type_type;
      _robot_type_type robot_type;
      enum { LEFT = 0 };
      enum { RIGHT = 1 };
      enum { REAL = 0 };
      enum { SIM = 1 };

    ArmDownRequest():
      arm_down_request(0),
      robot_type(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->arm_down_request >> (8 * 0)) & 0xFF;
      offset += sizeof(this->arm_down_request);
      *(outbuffer + offset + 0) = (this->robot_type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->robot_type);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->arm_down_request =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->arm_down_request);
      this->robot_type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->robot_type);
     return offset;
    }

    const char * getType(){ return ARMDOWN; };
    const char * getMD5(){ return "f42f7d342f46565a74ab6d89e7a9e2aa"; };

  };

  class ArmDownResponse : public ros::Msg
  {
    public:
      typedef uint8_t _arm_down_reply_type;
      _arm_down_reply_type arm_down_reply;
      enum { FAILURE = 0 };
      enum { SUCCESS = 1 };

    ArmDownResponse():
      arm_down_reply(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->arm_down_reply >> (8 * 0)) & 0xFF;
      offset += sizeof(this->arm_down_reply);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->arm_down_reply =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->arm_down_reply);
     return offset;
    }

    const char * getType(){ return ARMDOWN; };
    const char * getMD5(){ return "a09d290a533b61392b9f90286175fee5"; };

  };

  class ArmDown {
    public:
    typedef ArmDownRequest Request;
    typedef ArmDownResponse Response;
  };

}
#endif
