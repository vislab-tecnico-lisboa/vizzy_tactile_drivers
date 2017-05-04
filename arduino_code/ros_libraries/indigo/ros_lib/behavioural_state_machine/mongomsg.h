#ifndef _ROS_behavioural_state_machine_mongomsg_h
#define _ROS_behavioural_state_machine_mongomsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace behavioural_state_machine
{

  class mongomsg : public ros::Msg
  {
    public:
      const char* gesture;
      float confidence;

    mongomsg():
      gesture(""),
      confidence(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_gesture = strlen(this->gesture);
      memcpy(outbuffer + offset, &length_gesture, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->gesture, length_gesture);
      offset += length_gesture;
      union {
        float real;
        uint32_t base;
      } u_confidence;
      u_confidence.real = this->confidence;
      *(outbuffer + offset + 0) = (u_confidence.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_confidence.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_confidence.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_confidence.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->confidence);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_gesture;
      memcpy(&length_gesture, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gesture; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gesture-1]=0;
      this->gesture = (char *)(inbuffer + offset-1);
      offset += length_gesture;
      union {
        float real;
        uint32_t base;
      } u_confidence;
      u_confidence.base = 0;
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->confidence = u_confidence.real;
      offset += sizeof(this->confidence);
     return offset;
    }

    const char * getType(){ return "behavioural_state_machine/mongomsg"; };
    const char * getMD5(){ return "e342f025373809f4c9dbaf16fd69383c"; };

  };

}
#endif