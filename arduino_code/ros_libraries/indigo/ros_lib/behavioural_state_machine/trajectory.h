#ifndef _ROS_behavioural_state_machine_trajectory_h
#define _ROS_behavioural_state_machine_trajectory_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace behavioural_state_machine
{

  class trajectory : public ros::Msg
  {
    public:
      const char* mov;
      float neck;
      float eyes;

    trajectory():
      mov(""),
      neck(0),
      eyes(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_mov = strlen(this->mov);
      memcpy(outbuffer + offset, &length_mov, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->mov, length_mov);
      offset += length_mov;
      union {
        float real;
        uint32_t base;
      } u_neck;
      u_neck.real = this->neck;
      *(outbuffer + offset + 0) = (u_neck.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_neck.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_neck.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_neck.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->neck);
      union {
        float real;
        uint32_t base;
      } u_eyes;
      u_eyes.real = this->eyes;
      *(outbuffer + offset + 0) = (u_eyes.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_eyes.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_eyes.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_eyes.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->eyes);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_mov;
      memcpy(&length_mov, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mov; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mov-1]=0;
      this->mov = (char *)(inbuffer + offset-1);
      offset += length_mov;
      union {
        float real;
        uint32_t base;
      } u_neck;
      u_neck.base = 0;
      u_neck.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_neck.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_neck.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_neck.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->neck = u_neck.real;
      offset += sizeof(this->neck);
      union {
        float real;
        uint32_t base;
      } u_eyes;
      u_eyes.base = 0;
      u_eyes.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_eyes.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_eyes.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_eyes.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->eyes = u_eyes.real;
      offset += sizeof(this->eyes);
     return offset;
    }

    const char * getType(){ return "behavioural_state_machine/trajectory"; };
    const char * getMD5(){ return "d3281b3be2a22adc4dc0061684309936"; };

  };

}
#endif