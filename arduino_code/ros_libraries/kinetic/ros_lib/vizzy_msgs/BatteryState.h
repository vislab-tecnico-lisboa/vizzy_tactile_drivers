#ifndef _ROS_SERVICE_BatteryState_h
#define _ROS_SERVICE_BatteryState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_msgs
{

static const char BATTERYSTATE[] = "vizzy_msgs/BatteryState";

  class BatteryStateRequest : public ros::Msg
  {
    public:

    BatteryStateRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return BATTERYSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class BatteryStateResponse : public ros::Msg
  {
    public:
      typedef uint8_t _battery_state_type;
      _battery_state_type battery_state;
      typedef uint8_t _percentage_type;
      _percentage_type percentage;
      enum { CHARGED = 0 };
      enum { GOOD = 1 };
      enum { MEDIUM = 2 };
      enum { LOW_BATTERY = 3 };
      enum { UNKNOWN = 4 };

    BatteryStateResponse():
      battery_state(0),
      percentage(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->battery_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->battery_state);
      *(outbuffer + offset + 0) = (this->percentage >> (8 * 0)) & 0xFF;
      offset += sizeof(this->percentage);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->battery_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->battery_state);
      this->percentage =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->percentage);
     return offset;
    }

    const char * getType(){ return BATTERYSTATE; };
    const char * getMD5(){ return "4c3f18c6e165940e41a82f62df7f5b78"; };

  };

  class BatteryState {
    public:
    typedef BatteryStateRequest Request;
    typedef BatteryStateResponse Response;
  };

}
#endif
