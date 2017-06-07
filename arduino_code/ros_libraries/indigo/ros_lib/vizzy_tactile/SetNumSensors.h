#ifndef _ROS_SERVICE_SetNumSensors_h
#define _ROS_SERVICE_SetNumSensors_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vizzy_tactile
{

static const char SETNUMSENSORS[] = "vizzy_tactile/SetNumSensors";

  class SetNumSensorsRequest : public ros::Msg
  {
    public:
      int8_t numSensors;

    SetNumSensorsRequest():
      numSensors(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_numSensors;
      u_numSensors.real = this->numSensors;
      *(outbuffer + offset + 0) = (u_numSensors.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->numSensors);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_numSensors;
      u_numSensors.base = 0;
      u_numSensors.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->numSensors = u_numSensors.real;
      offset += sizeof(this->numSensors);
     return offset;
    }

    const char * getType(){ return SETNUMSENSORS; };
    const char * getMD5(){ return "8676cf2607964821abb6e1d6151308c6"; };

  };

  class SetNumSensorsResponse : public ros::Msg
  {
    public:
      bool setSensors;

    SetNumSensorsResponse():
      setSensors(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_setSensors;
      u_setSensors.real = this->setSensors;
      *(outbuffer + offset + 0) = (u_setSensors.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->setSensors);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_setSensors;
      u_setSensors.base = 0;
      u_setSensors.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->setSensors = u_setSensors.real;
      offset += sizeof(this->setSensors);
     return offset;
    }

    const char * getType(){ return SETNUMSENSORS; };
    const char * getMD5(){ return "c91784adcd876b981931c3652d97962e"; };

  };

  class SetNumSensors {
    public:
    typedef SetNumSensorsRequest Request;
    typedef SetNumSensorsResponse Response;
  };

}
#endif
