#ifndef _ROS_SERVICE_BatteryChargingState_h
#define _ROS_SERVICE_BatteryChargingState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_msgs
{

static const char BATTERYCHARGINGSTATE[] = "vizzy_msgs/BatteryChargingState";

  class BatteryChargingStateRequest : public ros::Msg
  {
    public:

    BatteryChargingStateRequest()
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

    const char * getType(){ return BATTERYCHARGINGSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class BatteryChargingStateResponse : public ros::Msg
  {
    public:
      typedef uint8_t _battery_charging_state_type;
      _battery_charging_state_type battery_charging_state;
      enum { NOT_CHARGING = 0 };
      enum { CHARGING = 1 };
      enum { UNKNOWN = 2 };

    BatteryChargingStateResponse():
      battery_charging_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->battery_charging_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->battery_charging_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->battery_charging_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->battery_charging_state);
     return offset;
    }

    const char * getType(){ return BATTERYCHARGINGSTATE; };
    const char * getMD5(){ return "25c827b20bf959c4b4d12b8483cb7b43"; };

  };

  class BatteryChargingState {
    public:
    typedef BatteryChargingStateRequest Request;
    typedef BatteryChargingStateResponse Response;
  };

}
#endif
