#ifndef _ROS_human_awareness_msgs_Embedding_h
#define _ROS_human_awareness_msgs_Embedding_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace human_awareness_msgs
{

  class Embedding : public ros::Msg
  {
    public:
      uint32_t embedding_length;
      typedef float _embedding_type;
      _embedding_type st_embedding;
      _embedding_type * embedding;

    Embedding():
      embedding_length(0), embedding(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->embedding_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->embedding_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->embedding_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->embedding_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->embedding_length);
      for( uint32_t i = 0; i < embedding_length; i++){
      union {
        float real;
        uint32_t base;
      } u_embeddingi;
      u_embeddingi.real = this->embedding[i];
      *(outbuffer + offset + 0) = (u_embeddingi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_embeddingi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_embeddingi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_embeddingi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->embedding[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t embedding_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      embedding_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      embedding_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      embedding_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->embedding_length);
      if(embedding_lengthT > embedding_length)
        this->embedding = (float*)realloc(this->embedding, embedding_lengthT * sizeof(float));
      embedding_length = embedding_lengthT;
      for( uint32_t i = 0; i < embedding_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_embedding;
      u_st_embedding.base = 0;
      u_st_embedding.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_embedding.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_embedding.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_embedding.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_embedding = u_st_embedding.real;
      offset += sizeof(this->st_embedding);
        memcpy( &(this->embedding[i]), &(this->st_embedding), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/Embedding"; };
    const char * getMD5(){ return "b2fe64d0918b001fee3435866a0d2530"; };

  };

}
#endif