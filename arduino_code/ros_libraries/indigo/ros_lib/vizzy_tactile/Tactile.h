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
      std_msgs::Header header;
      uint8_t sensorsArray_length;
      vizzy_tactile::TacVector st_sensorsArray;
      vizzy_tactile::TacVector * sensorsArray;

    Tactile():
      header(),
      sensorsArray_length(0), sensorsArray(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = sensorsArray_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < sensorsArray_length; i++){
      offset += this->sensorsArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t sensorsArray_lengthT = *(inbuffer + offset++);
      if(sensorsArray_lengthT > sensorsArray_length)
        this->sensorsArray = (vizzy_tactile::TacVector*)realloc(this->sensorsArray, sensorsArray_lengthT * sizeof(vizzy_tactile::TacVector));
      offset += 3;
      sensorsArray_length = sensorsArray_lengthT;
      for( uint8_t i = 0; i < sensorsArray_length; i++){
      offset += this->st_sensorsArray.deserialize(inbuffer + offset);
        memcpy( &(this->sensorsArray[i]), &(this->st_sensorsArray), sizeof(vizzy_tactile::TacVector));
      }
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/Tactile"; };
    const char * getMD5(){ return "109219fb581126f61c3f37301d9310eb"; };

  };

}
#endif