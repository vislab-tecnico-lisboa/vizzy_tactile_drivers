#ifndef _ROS_SERVICE_MotorsShutdown_h
#define _ROS_SERVICE_MotorsShutdown_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_msgs
{

static const char MOTORSSHUTDOWN[] = "vizzy_msgs/MotorsShutdown";

  class MotorsShutdownRequest : public ros::Msg
  {
    public:
      typedef uint8_t _shutdown_request_type;
      _shutdown_request_type shutdown_request;
      enum { SHUTDOWN = 0 };
      enum { TURNON = 1 };

    MotorsShutdownRequest():
      shutdown_request(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->shutdown_request >> (8 * 0)) & 0xFF;
      offset += sizeof(this->shutdown_request);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->shutdown_request =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->shutdown_request);
     return offset;
    }

    const char * getType(){ return MOTORSSHUTDOWN; };
    const char * getMD5(){ return "b98eea324a50dd370648dbfb5974abca"; };

  };

  class MotorsShutdownResponse : public ros::Msg
  {
    public:
      typedef uint8_t _shutdown_reply_type;
      _shutdown_reply_type shutdown_reply;
      enum { FAILURE = 0 };
      enum { SUCCESS = 1 };

    MotorsShutdownResponse():
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

    const char * getType(){ return MOTORSSHUTDOWN; };
    const char * getMD5(){ return "00e34715d837d8983c542cd2a76295c8"; };

  };

  class MotorsShutdown {
    public:
    typedef MotorsShutdownRequest Request;
    typedef MotorsShutdownResponse Response;
  };

}
#endif
