#ifndef _ROS_human_awareness_msgs_PersonsList_h
#define _ROS_human_awareness_msgs_PersonsList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "human_awareness_msgs/Person.h"

namespace human_awareness_msgs
{

  class PersonsList : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t persons_length;
      typedef human_awareness_msgs::Person _persons_type;
      _persons_type st_persons;
      _persons_type * persons;

    PersonsList():
      header(),
      persons_length(0), persons(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->persons_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->persons_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->persons_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->persons_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->persons_length);
      for( uint32_t i = 0; i < persons_length; i++){
      offset += this->persons[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t persons_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      persons_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      persons_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      persons_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->persons_length);
      if(persons_lengthT > persons_length)
        this->persons = (human_awareness_msgs::Person*)realloc(this->persons, persons_lengthT * sizeof(human_awareness_msgs::Person));
      persons_length = persons_lengthT;
      for( uint32_t i = 0; i < persons_length; i++){
      offset += this->st_persons.deserialize(inbuffer + offset);
        memcpy( &(this->persons[i]), &(this->st_persons), sizeof(human_awareness_msgs::Person));
      }
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/PersonsList"; };
    const char * getMD5(){ return "0e91f306efa36024f18a00eed23eaafe"; };

  };

}
#endif