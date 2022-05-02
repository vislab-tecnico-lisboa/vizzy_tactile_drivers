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
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t sensorArray_length;
      typedef vizzy_tactile::TactSensor _sensorArray_type;
      _sensorArray_type st_sensorArray;
      _sensorArray_type * sensorArray;

    TactSensorArray():
      header(),
      sensorArray_length(0), sensorArray(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->sensorArray_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sensorArray_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sensorArray_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sensorArray_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sensorArray_length);
      for( uint32_t i = 0; i < sensorArray_length; i++){
      offset += this->sensorArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t sensorArray_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sensorArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sensorArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sensorArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sensorArray_length);
      if(sensorArray_lengthT > sensorArray_length)
        this->sensorArray = (vizzy_tactile::TactSensor*)realloc(this->sensorArray, sensorArray_lengthT * sizeof(vizzy_tactile::TactSensor));
      sensorArray_length = sensorArray_lengthT;
      for( uint32_t i = 0; i < sensorArray_length; i++){
      offset += this->st_sensorArray.deserialize(inbuffer + offset);
        memcpy( &(this->sensorArray[i]), &(this->st_sensorArray), sizeof(vizzy_tactile::TactSensor));
      }
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/TactSensorArray"; };
    const char * getMD5(){ return "52f07a98d4d1810ffab54d16cfaf470c"; };

  };

}
#endif