#ifndef _ROS_human_awareness_msgs_TrackedPersonsList_h
#define _ROS_human_awareness_msgs_TrackedPersonsList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "human_awareness_msgs/PersonTracker.h"

namespace human_awareness_msgs
{

  class TrackedPersonsList : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t personList_length;
      typedef human_awareness_msgs::PersonTracker _personList_type;
      _personList_type st_personList;
      _personList_type * personList;

    TrackedPersonsList():
      header(),
      personList_length(0), personList(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->personList_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->personList_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->personList_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->personList_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->personList_length);
      for( uint32_t i = 0; i < personList_length; i++){
      offset += this->personList[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t personList_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      personList_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      personList_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      personList_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->personList_length);
      if(personList_lengthT > personList_length)
        this->personList = (human_awareness_msgs::PersonTracker*)realloc(this->personList, personList_lengthT * sizeof(human_awareness_msgs::PersonTracker));
      personList_length = personList_lengthT;
      for( uint32_t i = 0; i < personList_length; i++){
      offset += this->st_personList.deserialize(inbuffer + offset);
        memcpy( &(this->personList[i]), &(this->st_personList), sizeof(human_awareness_msgs::PersonTracker));
      }
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/TrackedPersonsList"; };
    const char * getMD5(){ return "11428167666e71670fb1b9b9e2044f50"; };

  };

}
#endif