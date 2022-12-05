#ifndef OPENDV_DVF_HANDLER_H
#define OPENDV_DVF_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

#include "odv_file.h"
#include "odv_image.h"
#include "odv_utils.h"


#pragma pack(push, 1)
struct ODVDvfSpriteHeader
{
    unsigned int size;
    unsigned short width;
    unsigned short height;
    unsigned short unused_00;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ODVDvfFrame
{
    unsigned short sprite_id;
    unsigned short duration;
    unsigned short distance;
    unsigned short coordinate_x;
    unsigned short coordinate_y;
    unsigned short sound_id;
    unsigned short unused_00;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ODVDvfAnimationHeader
{
    char padding_00[4];
    unsigned short nb_frames;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    float coordinate_x;
    float coordinate_y;
    unsigned short perspective_id;
    unsigned short animation_id;
    char animation_name[32];
};
#pragma pack(pop)

struct ODVDvfAnimation
{
    unsigned short nb_frames;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    float coordinate_x;
    float coordinate_y;
    unsigned short perspective_id;
    unsigned short animation_id;
    char animation_name[32];
    struct ODVDvfFrame **frames;
};

#pragma pack(push, 1)
struct ODVDvfProfileHeader
{
    char name[32];
    unsigned short nb_perspectives;
    char padding_00[32];
    unsigned short nb_animations;
    char padding_01[16];
    unsigned short max_width;
    unsigned short max_height;
    float coordinate_x;
    float coordinate_y;
    char padding_02[20];
};
#pragma pack(pop)

struct ODVDvfProfile
{
    char name[32];
    unsigned short nb_perspectives;
    unsigned short nb_animations;
    unsigned short max_width;
    unsigned short max_height;
    float coordinate_x;
    float coordinate_y;
    struct ODVDvfAnimation **animations;
};

#pragma pack(push, 1)
struct ODVDvfRowSpriteHeader
{
    unsigned short num_transparent_pixels;
    unsigned short num_total_pixels;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ODVDvfHeader
{
    unsigned short version;
    unsigned short nb_sprites;
    unsigned short padding_00;
    unsigned short max_width;
    unsigned short max_height;
    unsigned char padding_01[20];
};
#pragma pack(pop)

struct ODVDvf
{
    struct ODVFile *file;
    struct ODVDvfHeader header;
    struct ODVImage **sprites;
    unsigned short nb_profiles;
    struct ODVDvfProfile **profiles;
};

struct ODVDvf *odv_dvf_open(const char *filename);
int odv_dvf_parse_header(struct ODVDvf *fnt);
struct ODVDvfProfile* odv_dvf_parse_profile(struct ODVDvf *dvf);
struct ODVImage* odv_dvf_parse_sprite(struct ODVDvf *dvf);
void odv_dvf_info(const struct ODVDvf *fnt);
void odv_dvf_profile_info(const struct ODVDvfProfile *profile);
void odv_dvf_animation_info(const struct ODVDvfAnimation *animation);
void odv_dvf_frame_info(const struct ODVDvfFrame *frame);
void odv_dvf_close(struct ODVDvf *fnt);
void odv_dvf_clean_animation(struct ODVDvfAnimation *animation);
void odv_dvf_clean_profile(struct ODVDvfProfile *profile);
void odv_dvf_get_frame_max_x_y(const struct ODVDvfAnimation *animation, unsigned short *max_x, unsigned short *max_y);
void odv_dvf_get_frame_min_x_y(const struct ODVDvfAnimation *animation, unsigned short *min_x, unsigned short *min_y);
void odv_dvf_get_frame_max_width_height(const struct ODVDvf *dvf, const struct ODVDvfAnimation *animation, unsigned short *max_width, unsigned short *max_height);
void odv_dvf_get_frame_max_wx_hy(const struct ODVDvf *dvf, const struct ODVDvfAnimation *animation, unsigned short *max_wx, unsigned short *max_hy);

#endif /* OPENDV_DVF_HANDLER_H */
