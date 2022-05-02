#ifndef _ROS_human_awareness_msgs_OpenFaceFeatures_h
#define _ROS_human_awareness_msgs_OpenFaceFeatures_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace human_awareness_msgs
{

  class OpenFaceFeatures : public ros::Msg
  {
    public:
      uint32_t left_gaze_vector_length;
      typedef float _left_gaze_vector_type;
      _left_gaze_vector_type st_left_gaze_vector;
      _left_gaze_vector_type * left_gaze_vector;
      uint32_t right_gaze_vector_length;
      typedef float _right_gaze_vector_type;
      _right_gaze_vector_type st_right_gaze_vector;
      _right_gaze_vector_type * right_gaze_vector;
      uint32_t poses_T_length;
      typedef float _poses_T_type;
      _poses_T_type st_poses_T;
      _poses_T_type * poses_T;
      uint32_t poses_R_length;
      typedef float _poses_R_type;
      _poses_R_type st_poses_R;
      _poses_R_type * poses_R;
      uint32_t left_landmarks_length;
      typedef float _left_landmarks_type;
      _left_landmarks_type st_left_landmarks;
      _left_landmarks_type * left_landmarks;
      uint32_t right_landmarks_length;
      typedef float _right_landmarks_type;
      _right_landmarks_type st_right_landmarks;
      _right_landmarks_type * right_landmarks;
      uint32_t action_units_length;
      typedef float _action_units_type;
      _action_units_type st_action_units;
      _action_units_type * action_units;

    OpenFaceFeatures():
      left_gaze_vector_length(0), left_gaze_vector(NULL),
      right_gaze_vector_length(0), right_gaze_vector(NULL),
      poses_T_length(0), poses_T(NULL),
      poses_R_length(0), poses_R(NULL),
      left_landmarks_length(0), left_landmarks(NULL),
      right_landmarks_length(0), right_landmarks(NULL),
      action_units_length(0), action_units(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->left_gaze_vector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->left_gaze_vector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->left_gaze_vector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->left_gaze_vector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_gaze_vector_length);
      for( uint32_t i = 0; i < left_gaze_vector_length; i++){
      union {
        float real;
        uint32_t base;
      } u_left_gaze_vectori;
      u_left_gaze_vectori.real = this->left_gaze_vector[i];
      *(outbuffer + offset + 0) = (u_left_gaze_vectori.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_gaze_vectori.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_gaze_vectori.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_gaze_vectori.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_gaze_vector[i]);
      }
      *(outbuffer + offset + 0) = (this->right_gaze_vector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->right_gaze_vector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->right_gaze_vector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->right_gaze_vector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_gaze_vector_length);
      for( uint32_t i = 0; i < right_gaze_vector_length; i++){
      union {
        float real;
        uint32_t base;
      } u_right_gaze_vectori;
      u_right_gaze_vectori.real = this->right_gaze_vector[i];
      *(outbuffer + offset + 0) = (u_right_gaze_vectori.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_gaze_vectori.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_gaze_vectori.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_gaze_vectori.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_gaze_vector[i]);
      }
      *(outbuffer + offset + 0) = (this->poses_T_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->poses_T_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->poses_T_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->poses_T_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_T_length);
      for( uint32_t i = 0; i < poses_T_length; i++){
      union {
        float real;
        uint32_t base;
      } u_poses_Ti;
      u_poses_Ti.real = this->poses_T[i];
      *(outbuffer + offset + 0) = (u_poses_Ti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_poses_Ti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_poses_Ti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_poses_Ti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_T[i]);
      }
      *(outbuffer + offset + 0) = (this->poses_R_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->poses_R_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->poses_R_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->poses_R_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_R_length);
      for( uint32_t i = 0; i < poses_R_length; i++){
      union {
        float real;
        uint32_t base;
      } u_poses_Ri;
      u_poses_Ri.real = this->poses_R[i];
      *(outbuffer + offset + 0) = (u_poses_Ri.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_poses_Ri.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_poses_Ri.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_poses_Ri.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_R[i]);
      }
      *(outbuffer + offset + 0) = (this->left_landmarks_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->left_landmarks_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->left_landmarks_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->left_landmarks_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_landmarks_length);
      for( uint32_t i = 0; i < left_landmarks_length; i++){
      union {
        float real;
        uint32_t base;
      } u_left_landmarksi;
      u_left_landmarksi.real = this->left_landmarks[i];
      *(outbuffer + offset + 0) = (u_left_landmarksi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_landmarksi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_landmarksi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_landmarksi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_landmarks[i]);
      }
      *(outbuffer + offset + 0) = (this->right_landmarks_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->right_landmarks_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->right_landmarks_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->right_landmarks_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_landmarks_length);
      for( uint32_t i = 0; i < right_landmarks_length; i++){
      union {
        float real;
        uint32_t base;
      } u_right_landmarksi;
      u_right_landmarksi.real = this->right_landmarks[i];
      *(outbuffer + offset + 0) = (u_right_landmarksi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_landmarksi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_landmarksi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_landmarksi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_landmarks[i]);
      }
      *(outbuffer + offset + 0) = (this->action_units_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->action_units_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->action_units_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->action_units_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->action_units_length);
      for( uint32_t i = 0; i < action_units_length; i++){
      union {
        float real;
        uint32_t base;
      } u_action_unitsi;
      u_action_unitsi.real = this->action_units[i];
      *(outbuffer + offset + 0) = (u_action_unitsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_action_unitsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_action_unitsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_action_unitsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->action_units[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t left_gaze_vector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      left_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      left_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      left_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->left_gaze_vector_length);
      if(left_gaze_vector_lengthT > left_gaze_vector_length)
        this->left_gaze_vector = (float*)realloc(this->left_gaze_vector, left_gaze_vector_lengthT * sizeof(float));
      left_gaze_vector_length = left_gaze_vector_lengthT;
      for( uint32_t i = 0; i < left_gaze_vector_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_left_gaze_vector;
      u_st_left_gaze_vector.base = 0;
      u_st_left_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_left_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_left_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_left_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_left_gaze_vector = u_st_left_gaze_vector.real;
      offset += sizeof(this->st_left_gaze_vector);
        memcpy( &(this->left_gaze_vector[i]), &(this->st_left_gaze_vector), sizeof(float));
      }
      uint32_t right_gaze_vector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      right_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      right_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      right_gaze_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->right_gaze_vector_length);
      if(right_gaze_vector_lengthT > right_gaze_vector_length)
        this->right_gaze_vector = (float*)realloc(this->right_gaze_vector, right_gaze_vector_lengthT * sizeof(float));
      right_gaze_vector_length = right_gaze_vector_lengthT;
      for( uint32_t i = 0; i < right_gaze_vector_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_right_gaze_vector;
      u_st_right_gaze_vector.base = 0;
      u_st_right_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_right_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_right_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_right_gaze_vector.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_right_gaze_vector = u_st_right_gaze_vector.real;
      offset += sizeof(this->st_right_gaze_vector);
        memcpy( &(this->right_gaze_vector[i]), &(this->st_right_gaze_vector), sizeof(float));
      }
      uint32_t poses_T_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      poses_T_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      poses_T_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      poses_T_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->poses_T_length);
      if(poses_T_lengthT > poses_T_length)
        this->poses_T = (float*)realloc(this->poses_T, poses_T_lengthT * sizeof(float));
      poses_T_length = poses_T_lengthT;
      for( uint32_t i = 0; i < poses_T_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_poses_T;
      u_st_poses_T.base = 0;
      u_st_poses_T.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_poses_T.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_poses_T.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_poses_T.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_poses_T = u_st_poses_T.real;
      offset += sizeof(this->st_poses_T);
        memcpy( &(this->poses_T[i]), &(this->st_poses_T), sizeof(float));
      }
      uint32_t poses_R_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      poses_R_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      poses_R_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      poses_R_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->poses_R_length);
      if(poses_R_lengthT > poses_R_length)
        this->poses_R = (float*)realloc(this->poses_R, poses_R_lengthT * sizeof(float));
      poses_R_length = poses_R_lengthT;
      for( uint32_t i = 0; i < poses_R_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_poses_R;
      u_st_poses_R.base = 0;
      u_st_poses_R.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_poses_R.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_poses_R.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_poses_R.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_poses_R = u_st_poses_R.real;
      offset += sizeof(this->st_poses_R);
        memcpy( &(this->poses_R[i]), &(this->st_poses_R), sizeof(float));
      }
      uint32_t left_landmarks_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      left_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      left_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      left_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->left_landmarks_length);
      if(left_landmarks_lengthT > left_landmarks_length)
        this->left_landmarks = (float*)realloc(this->left_landmarks, left_landmarks_lengthT * sizeof(float));
      left_landmarks_length = left_landmarks_lengthT;
      for( uint32_t i = 0; i < left_landmarks_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_left_landmarks;
      u_st_left_landmarks.base = 0;
      u_st_left_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_left_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_left_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_left_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_left_landmarks = u_st_left_landmarks.real;
      offset += sizeof(this->st_left_landmarks);
        memcpy( &(this->left_landmarks[i]), &(this->st_left_landmarks), sizeof(float));
      }
      uint32_t right_landmarks_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      right_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      right_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      right_landmarks_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->right_landmarks_length);
      if(right_landmarks_lengthT > right_landmarks_length)
        this->right_landmarks = (float*)realloc(this->right_landmarks, right_landmarks_lengthT * sizeof(float));
      right_landmarks_length = right_landmarks_lengthT;
      for( uint32_t i = 0; i < right_landmarks_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_right_landmarks;
      u_st_right_landmarks.base = 0;
      u_st_right_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_right_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_right_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_right_landmarks.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_right_landmarks = u_st_right_landmarks.real;
      offset += sizeof(this->st_right_landmarks);
        memcpy( &(this->right_landmarks[i]), &(this->st_right_landmarks), sizeof(float));
      }
      uint32_t action_units_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      action_units_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      action_units_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      action_units_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->action_units_length);
      if(action_units_lengthT > action_units_length)
        this->action_units = (float*)realloc(this->action_units, action_units_lengthT * sizeof(float));
      action_units_length = action_units_lengthT;
      for( uint32_t i = 0; i < action_units_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_action_units;
      u_st_action_units.base = 0;
      u_st_action_units.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_action_units.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_action_units.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_action_units.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_action_units = u_st_action_units.real;
      offset += sizeof(this->st_action_units);
        memcpy( &(this->action_units[i]), &(this->st_action_units), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/OpenFaceFeatures"; };
    const char * getMD5(){ return "541efd4d96f926241f6315bbc2615621"; };

  };

}
#endif