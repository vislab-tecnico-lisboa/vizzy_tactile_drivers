#ifndef _ROS_vizzy_tactile_TactSensorArray_h
#define _ROS_vizzy_tactile_TactSensorArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "vizzy_tactile/TactSensor.h"

namespace vizzy_tactile
{

  class TactSensorArray : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t sensorArray_length;
      vizzy_tactile::TactSensor st_sensorArray;
      vizzy_tactile::TactSensor * sensorArray;

    TactSensorArray():
      header(),
      sensorArray_length(0), sensorArray(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = sensorArray_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < sensorArray_length; i++){
      offset += this->sensorArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t sensorArray_lengthT = *(inbuffer + offset++);
      if(sensorArray_lengthT > sensorArray_length)
        this->sensorArray = (vizzy_tactile::TactSensor*)realloc(this->sensorArray, sensorArray_lengthT * sizeof(vizzy_tactile::TactSensor));
      offset += 3;
      sensorArray_length = sensorArray_lengthT;
      for( uint8_t i = 0; i < sensorArray_length; i++){
      offset += this->st_sensorArray.deserialize(inbuffer + offset);
        memcpy( &(this->sensorArray[i]), &(this->st_sensorArray), sizeof(vizzy_tactile::TactSensor));
      }
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/TactSensorArray"; };
    const char * getMD5(){ return "914d3e231c7957d39bdc163732054737"; };

  };

}
#endif