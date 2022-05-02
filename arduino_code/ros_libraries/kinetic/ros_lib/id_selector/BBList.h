#ifndef _ROS_id_selector_BBList_h
#define _ROS_id_selector_BBList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "id_selector/BoundingBox.h"

namespace id_selector
{

  class BBList : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t bbVector_length;
      typedef id_selector::BoundingBox _bbVector_type;
      _bbVector_type st_bbVector;
      _bbVector_type * bbVector;

    BBList():
      header(),
      bbVector_length(0), bbVector(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->bbVector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bbVector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bbVector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bbVector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bbVector_length);
      for( uint32_t i = 0; i < bbVector_length; i++){
      offset += this->bbVector[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t bbVector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bbVector_length);
      if(bbVector_lengthT > bbVector_length)
        this->bbVector = (id_selector::BoundingBox*)realloc(this->bbVector, bbVector_lengthT * sizeof(id_selector::BoundingBox));
      bbVector_length = bbVector_lengthT;
      for( uint32_t i = 0; i < bbVector_length; i++){
      offset += this->st_bbVector.deserialize(inbuffer + offset);
        memcpy( &(this->bbVector[i]), &(this->st_bbVector), sizeof(id_selector::BoundingBox));
      }
     return offset;
    }

    const char * getType(){ return "id_selector/BBList"; };
    const char * getMD5(){ return "451051af5703a61c3d4949dd71734381"; };

  };

}
#endif