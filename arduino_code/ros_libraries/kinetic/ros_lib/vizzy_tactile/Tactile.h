#ifndef _ROS_vizzy_tactile_Tactile_h
#define _ROS_vizzy_tactile_Tactile_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "vizzy_tactile/TacVector.h"

namespace vizzy_tactile
{

  class Tactile : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t sensorsArray_length;
      typedef vizzy_tactile::TacVector _sensorsArray_type;
      _sensorsArray_type st_sensorsArray;
      _sensorsArray_type * sensorsArray;

    Tactile():
      header(),
      sensorsArray_length(0), sensorsArray(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->sensorsArray_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sensorsArray_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sensorsArray_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sensorsArray_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sensorsArray_length);
      for( uint32_t i = 0; i < sensorsArray_length; i++){
      offset += this->sensorsArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t sensorsArray_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sensorsArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sensorsArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sensorsArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sensorsArray_length);
      if(sensorsArray_lengthT > sensorsArray_length)
        this->sensorsArray = (vizzy_tactile::TacVector*)realloc(this->sensorsArray, sensorsArray_lengthT * sizeof(vizzy_tactile::TacVector));
      sensorsArray_length = sensorsArray_lengthT;
      for( uint32_t i = 0; i < sensorsArray_length; i++){
      offset += this->st_sensorsArray.deserialize(inbuffer + offset);
        memcpy( &(this->sensorsArray[i]), &(this->st_sensorsArray), sizeof(vizzy_tactile::TacVector));
      }
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/Tactile"; };
    const char * getMD5(){ return "b81d60810ce1bbf537e144de54fe1c67"; };

  };

}
#endif