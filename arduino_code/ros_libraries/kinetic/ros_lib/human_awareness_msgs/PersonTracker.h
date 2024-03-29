#ifndef _ROS_human_awareness_msgs_PersonTracker_h
#define _ROS_human_awareness_msgs_PersonTracker_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "human_awareness_msgs/BodyPart.h"
#include "human_awareness_msgs/FaceCrop.h"
#include "human_awareness_msgs/BoundingBox.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"

namespace human_awareness_msgs
{

  class PersonTracker : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _id_type;
      _id_type id;
      typedef const char* _face_id_type;
      _face_id_type face_id;
      uint32_t body_parts_length;
      typedef human_awareness_msgs::BodyPart _body_parts_type;
      _body_parts_type st_body_parts;
      _body_parts_type * body_parts;
      uint32_t face_crop_length;
      typedef human_awareness_msgs::FaceCrop _face_crop_type;
      _face_crop_type st_face_crop;
      _face_crop_type * face_crop;
      typedef human_awareness_msgs::BoundingBox _body_type;
      _body_type body;
      typedef geometry_msgs::Pose _body_pose_type;
      _body_pose_type body_pose;
      typedef geometry_msgs::Pose _head_pose_type;
      _head_pose_type head_pose;
      typedef geometry_msgs::Twist _velocity_type;
      _velocity_type velocity;

    PersonTracker():
      header(),
      id(""),
      face_id(""),
      body_parts_length(0), body_parts(NULL),
      face_crop_length(0), face_crop(NULL),
      body(),
      body_pose(),
      head_pose(),
      velocity()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      uint32_t length_face_id = strlen(this->face_id);
      varToArr(outbuffer + offset, length_face_id);
      offset += 4;
      memcpy(outbuffer + offset, this->face_id, length_face_id);
      offset += length_face_id;
      *(outbuffer + offset + 0) = (this->body_parts_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->body_parts_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->body_parts_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->body_parts_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->body_parts_length);
      for( uint32_t i = 0; i < body_parts_length; i++){
      offset += this->body_parts[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->face_crop_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->face_crop_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->face_crop_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->face_crop_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->face_crop_length);
      for( uint32_t i = 0; i < face_crop_length; i++){
      offset += this->face_crop[i].serialize(outbuffer + offset);
      }
      offset += this->body.serialize(outbuffer + offset);
      offset += this->body_pose.serialize(outbuffer + offset);
      offset += this->head_pose.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      uint32_t length_face_id;
      arrToVar(length_face_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_face_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_face_id-1]=0;
      this->face_id = (char *)(inbuffer + offset-1);
      offset += length_face_id;
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
      offset += this->body.deserialize(inbuffer + offset);
      offset += this->body_pose.deserialize(inbuffer + offset);
      offset += this->head_pose.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/PersonTracker"; };
    const char * getMD5(){ return "e88498f4f2f571511eb99c5c2c73c583"; };

  };

}
#endif