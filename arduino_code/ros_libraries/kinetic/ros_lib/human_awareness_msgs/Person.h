#ifndef _ROS_human_awareness_msgs_Person_h
#define _ROS_human_awareness_msgs_Person_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "human_awareness_msgs/Embedding.h"
#include "human_awareness_msgs/BodyPart.h"
#include "geometry_msgs/Pose.h"
#include "human_awareness_msgs/FaceCrop.h"

namespace human_awareness_msgs
{

  class Person : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef float _id_confidence_type;
      _id_confidence_type id_confidence;
      typedef human_awareness_msgs::Embedding _face_descriptor_type;
      _face_descriptor_type face_descriptor;
      typedef human_awareness_msgs::Embedding _body_descriptor_type;
      _body_descriptor_type body_descriptor;
      uint32_t body_parts_length;
      typedef human_awareness_msgs::BodyPart _body_parts_type;
      _body_parts_type st_body_parts;
      _body_parts_type * body_parts;
      typedef geometry_msgs::Pose _head_pose_type;
      _head_pose_type head_pose;
      typedef float _head_pos_sigma_type;
      _head_pos_sigma_type head_pos_sigma;
      typedef geometry_msgs::Pose _body_pose_type;
      _body_pose_type body_pose;
      float body_pos_sigma[4];
      uint32_t face_crop_length;
      typedef human_awareness_msgs::FaceCrop _face_crop_type;
      _face_crop_type st_face_crop;
      _face_crop_type * face_crop;

    Person():
      id(""),
      id_confidence(0),
      face_descriptor(),
      body_descriptor(),
      body_parts_length(0), body_parts(NULL),
      head_pose(),
      head_pos_sigma(0),
      body_pose(),
      body_pos_sigma(),
      face_crop_length(0), face_crop(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_id_confidence;
      u_id_confidence.real = this->id_confidence;
      *(outbuffer + offset + 0) = (u_id_confidence.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id_confidence.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id_confidence.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id_confidence.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id_confidence);
      offset += this->face_descriptor.serialize(outbuffer + offset);
      offset += this->body_descriptor.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->body_parts_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->body_parts_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->body_parts_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->body_parts_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->body_parts_length);
      for( uint32_t i = 0; i < body_parts_length; i++){
      offset += this->body_parts[i].serialize(outbuffer + offset);
      }
      offset += this->head_pose.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->head_pos_sigma);
      offset += this->body_pose.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->body_pos_sigma[i]);
      }
      *(outbuffer + offset + 0) = (this->face_crop_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->face_crop_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->face_crop_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->face_crop_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->face_crop_length);
      for( uint32_t i = 0; i < face_crop_length; i++){
      offset += this->face_crop[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_id_confidence;
      u_id_confidence.base = 0;
      u_id_confidence.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id_confidence.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id_confidence.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id_confidence.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id_confidence = u_id_confidence.real;
      offset += sizeof(this->id_confidence);
      offset += this->face_descriptor.deserialize(inbuffer + offset);
      offset += this->body_descriptor.deserialize(inbuffer + offset);
      uint32_t body_parts_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      body_parts_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      body_parts_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      body_parts_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->body_parts_length);
      if(body_parts_lengthT > body_parts_length)
        this->body_parts = (human_awareness_msgs::BodyPart*)realloc(this->body_parts, body_parts_lengthT * sizeof(human_awareness_msgs::BodyPart));
      body_parts_length = body_parts_lengthT;
      for( uint32_t i = 0; i < body_parts_length; i++){
      offset += this->st_body_parts.deserialize(inbuffer + offset);
        memcpy( &(this->body_parts[i]), &(this->st_body_parts), sizeof(human_awareness_msgs::BodyPart));
      }
      offset += this->head_pose.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->head_pos_sigma));
      offset += this->body_pose.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->body_pos_sigma[i]));
      }
      uint32_t face_crop_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      face_crop_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      face_crop_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      face_crop_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->face_crop_length);
      if(face_crop_lengthT > face_crop_length)
        this->face_crop = (human_awareness_msgs::FaceCrop*)realloc(this->face_crop, face_crop_lengthT * sizeof(human_awareness_msgs::FaceCrop));
      face_crop_length = face_crop_lengthT;
      for( uint32_t i = 0; i < face_crop_length; i++){
      offset += this->st_face_crop.deserialize(inbuffer + offset);
        memcpy( &(this->face_crop[i]), &(this->st_face_crop), sizeof(human_awareness_msgs::FaceCrop));
      }
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/Person"; };
    const char * getMD5(){ return "b1c68be32b9d1160bfc67cd366772e54"; };

  };

}
#endif