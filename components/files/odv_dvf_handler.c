#include "odv_dvf_handler.h"

struct ODVDvf *odv_dvf_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVDvf *dvf = NULL;
    struct ODVImage *sprite = NULL;
    struct ODVDvfProfile *profile = NULL;
    unsigned int i;
    size_t numberofbytesread = 0;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_dvf_open - odv_file_open failed\n");
        return NULL;
    }
    dvf = calloc(1, sizeof (struct ODVDvf));
    if (dvf == NULL) {
        fprintf(stderr, "[-] odv_dvf_open #1 - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    dvf->file = file;
    if (odv_dvf_parse_header(dvf) == 0) {
        odv_dvf_close(dvf);
        return NULL;
    }
    dvf->sprites = calloc(dvf->header.nb_sprites, sizeof (struct ODVImage*));
    if (dvf->sprites == NULL) {
        fprintf(stderr, "[-] odv_dvf_open #2 - calloc failed\n");
        odv_dvf_close(dvf);
        return NULL;
    }
    for (i = 0; i < dvf->header.nb_sprites; i++) {
        sprite = odv_dvf_parse_sprite(dvf);
        if (sprite == NULL) {
            odv_dvf_close(dvf);
            return NULL;
        }
        dvf->sprites[i] = sprite;
    }
    numberofbytesread = odv_file_read(dvf->file, &dvf->nb_profiles, sizeof (unsigned short));
    if (numberofbytesread != sizeof (unsigned short)) {
        fprintf(stderr, "[-] odv_dvf_open - file read %zu failed\n", sizeof (unsigned short));
        odv_dvf_close(dvf);
        return NULL;
    }
    if (dvf->nb_profiles) {
        dvf->profiles = calloc(dvf->nb_profiles, sizeof (struct ODVDvfProfile*));
        if (dvf->profiles == NULL) {
            fprintf(stderr, "[-] odv_dvf_open #3 - calloc failed\n");
            odv_dvf_close(dvf);
            return NULL;
        }
        for (i = 0; i < dvf->nb_profiles; i++) {
            profile = odv_dvf_parse_profile(dvf);
            if (profile == NULL) {
                odv_dvf_close(dvf);
                return NULL;
            }
            dvf->profiles[i] = profile;
        }
    }
    return dvf;
}

struct ODVDvfFrame* odv_dvf_parse_frame(struct ODVDvf *dvf)
{
    struct ODVDvfFrame *frame = NULL;
    size_t numberofbytesread = 0;

    frame = calloc(0x01, sizeof (struct ODVDvfFrame));
    if (frame == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_frame #1 - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dvf->file, frame, sizeof (struct ODVDvfFrame));
    if (numberofbytesread != sizeof (struct ODVDvfFrame)) {
        fprintf(stderr, "[-] odv_dvf_parse_frame #1 - file read %zu failed\n", sizeof (struct ODVDvfFrame));
        free(frame);
        return NULL;
    }
    return frame;
}

struct ODVDvfAnimation* odv_dvf_parse_animation(struct ODVDvf *dvf)
{
    struct ODVDvfAnimationHeader header;
    struct ODVDvfAnimation *animation = NULL;
    struct ODVDvfFrame *frame = NULL;
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(dvf->file, &header, sizeof (struct ODVDvfAnimationHeader));
    if (numberofbytesread != sizeof (struct ODVDvfAnimationHeader)) {
        fprintf(stderr, "[-] odv_dvf_parse_animation #1 - file read %zu failed\n", sizeof (struct ODVDvfAnimationHeader));
        return NULL;
    }
    animation = calloc(0x01, sizeof (struct ODVDvfAnimation));
    if (animation == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_animation #1 - calloc failed\n");
        return NULL;
    }
    animation->nb_frames = header.nb_frames;
    animation->unk_word_00 = header.unk_word_00;
    animation->unk_word_01 = header.unk_word_01;
    animation->coordinate_x = header.coordinate_x;
    animation->coordinate_y = header.coordinate_y;
    animation->perspective_id = header.perspective_id;
    animation->animation_id = header.animation_id;
    strncpy(animation->animation_name, header.animation_name, 32);
    if (animation->nb_frames) {
        animation->frames = calloc(animation->nb_frames, sizeof (struct ODVDvfFrame*));
        if (animation->frames == NULL) {
            fprintf(stderr, "[-] odv_dvf_parse_animation #2 - calloc failed\n");
            free(animation);
            return NULL;
        }
        for (unsigned int i = 0; i < animation->nb_frames; i++) {
            frame = odv_dvf_parse_frame(dvf);
            if (frame == NULL) {
                odv_dvf_clean_animation(animation);
                return NULL;
            }
            animation->frames[i] = frame;
        }
    }
    return animation;
}

struct ODVDvfProfile* odv_dvf_parse_profile(struct ODVDvf *dvf)
{
    struct ODVDvfProfileHeader header;
    struct ODVDvfProfile *profile = NULL;
    struct ODVDvfAnimation *animation = NULL;
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(dvf->file, &header, sizeof (struct ODVDvfProfileHeader));
    if (numberofbytesread != sizeof (struct ODVDvfProfileHeader)) {
        fprintf(stderr, "[-] odv_dvf_parse_profile #1 - file read %zu failed\n", sizeof (struct ODVDvfProfileHeader));
        return NULL;
    }
    profile = calloc(0x01, sizeof (struct ODVDvfProfile));
    if (profile == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_profile #1 - calloc failed\n");
        return NULL;
    }
    strncpy(profile->name, header.name, 32);
    profile->nb_perspectives = header.nb_perspectives;
    profile->nb_animations = header.nb_animations;
    profile->max_width = header.max_width;
    profile->max_height = header.max_height;
    profile->coordinate_x = header.coordinate_x;
    profile->coordinate_y = header.coordinate_y;
    if ((profile->nb_perspectives * profile->nb_animations) != 0x00) {
        profile->animations = calloc(profile->nb_perspectives * profile->nb_animations, sizeof (struct ODVDvfAnimation*));
        if (profile->animations == NULL) {
            fprintf(stderr, "[-] odv_dvf_parse_profile #2 - calloc failed\n");
            free(profile);
            return NULL;
        }
        for (unsigned short i = 0; i < (unsigned short)(profile->nb_perspectives * profile->nb_animations); i++) {
            animation = odv_dvf_parse_animation(dvf);
            if (animation == NULL) {
                odv_dvf_clean_profile(profile);
                return NULL;
            }
            profile->animations[i] = animation;
        }
    }
    return profile;
}

struct ODVImage* odv_dvf_parse_sprite(struct ODVDvf *dvf)
{
    struct ODVImage *sprite = NULL;
    struct ODVDvfSpriteHeader sprite_header;
    struct ODVDvfRowSpriteHeader *row_sprite_header = NULL;
    size_t numberofbytesread = 0;
    unsigned char *data = NULL;
    unsigned char *cur_data = NULL;
    unsigned int row = 0x00;

    numberofbytesread = odv_file_read(dvf->file, &sprite_header, sizeof (struct ODVDvfSpriteHeader));
    if (numberofbytesread != sizeof (struct ODVDvfSpriteHeader)) {
        fprintf(stderr, "[-] odv_dvf_parse_sprite #1 - file read %zu failed\n", sizeof (struct ODVDvfSpriteHeader));
        return NULL;
    }
    data = calloc(0x01, sprite_header.size);
    if (data == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_sprite #1 - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dvf->file, data, sprite_header.size);
    if (numberofbytesread != sprite_header.size) {
        fprintf(stderr, "[-] odv_dvf_parse_sprite #2 - file read %u failed\n", sprite_header.size);
        free(data);
        return NULL;
    }
    sprite = calloc(0x01, sizeof (struct ODVImage));
    if (sprite == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_sprite #2 - calloc failed\n");
        free(data);
        return NULL;
    }
    cur_data = data;
    sprite_header.width = align4(sprite_header.width);
    sprite->width = sprite_header.width;
    sprite->height = sprite_header.height;
    sprite->type_compression = 0x00;
    sprite->data_size = sprite->width * sprite->height * 2;  /* R5G6B5 */
    sprite->buf =  calloc(sprite->data_size, sizeof (char));
    if (sprite->buf == NULL) {
        fprintf(stderr, "[-] odv_dvf_parse_sprite #3 - calloc failed\n");
        free(sprite);
        free(data);
        return NULL;
    }

    for (unsigned int i = 0; i < sprite->height; i++) {
        for (unsigned int j = 0; j < sprite->width; j++) {
            *(unsigned short*)((unsigned char*)sprite->buf + ((((i * sprite->width)) + j) * 2)) = 0x7C0;
        }
    }

    for (row = 0; row < sprite_header.height; row++) {
        if ((cur_data + sizeof (struct ODVDvfRowSpriteHeader)) > (data + sprite_header.size)) {
            odv_image_clean(sprite);
            free(data);
            return NULL;
        }
        row_sprite_header = (struct ODVDvfRowSpriteHeader *)(cur_data);
        cur_data = cur_data + sizeof (struct ODVDvfRowSpriteHeader);
        if (row_sprite_header->num_transparent_pixels == 0x00 && row_sprite_header->num_total_pixels == 0xFFFF) {
            continue;
        }
        else if (row_sprite_header->num_transparent_pixels > sprite->width || 
            row_sprite_header->num_transparent_pixels > row_sprite_header->num_total_pixels || 
            (row_sprite_header->num_total_pixels + 1) > sprite->width) {
            continue;
        }
        else {
                row_sprite_header->num_total_pixels = row_sprite_header->num_total_pixels + 1;
                for (unsigned short i = 0; i < (row_sprite_header->num_total_pixels - row_sprite_header->num_transparent_pixels); i++) {
                    if ((cur_data + sizeof (unsigned short)) > (data + sprite_header.size)) {
                        odv_image_clean(sprite);
                        free(data);
                        return NULL;
                    }
                    unsigned short cur_pix = *(unsigned short*)(cur_data);
                    if (cur_pix != 0x1F && cur_pix != 0x7C0) {
                        *(unsigned short*)((unsigned char*)sprite->buf + ((unsigned short)(row * sprite_header.width) + ((i + row_sprite_header->num_transparent_pixels))) * 2) = cur_pix;
                    }
                    cur_data += 0x02;
                }
        }
    }
    free(data);
    return sprite;
}

unsigned short odv_dvf_get_frame_max_x(const struct ODVDvfAnimation *animation)
{
    unsigned short max_x = 0;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (animation->frames[i]->coordinate_x > max_x) {
            max_x = animation->frames[i]->coordinate_x;
        }
    }
    return max_x;
}

unsigned short odv_dvf_get_frame_max_y(const struct ODVDvfAnimation *animation)
{
    unsigned short max_y = 0;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (animation->frames[i]->coordinate_y > max_y) {
            max_y = animation->frames[i]->coordinate_y;
        }
    }
    return max_y;
}

void odv_dvf_get_frame_max_width_height(const struct ODVDvf *dvf, const struct ODVDvfAnimation *animation, unsigned short *max_width, unsigned short *max_height)
{
    *max_width = 0;
    *max_height = 0;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (dvf->sprites[animation->frames[i]->sprite_id]->width > *max_width) {
            *max_width = dvf->sprites[animation->frames[i]->sprite_id]->width;
        }
        if (dvf->sprites[animation->frames[i]->sprite_id]->height > *max_height) {
            *max_height = dvf->sprites[animation->frames[i]->sprite_id]->height;
        }
    }
}

unsigned short odv_dvf_get_frame_max_width(const struct ODVDvf *dvf, const struct ODVDvfAnimation *animation)
{
    unsigned short max_height = 0;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (dvf->sprites[animation->frames[i]->sprite_id]->height > max_height) {
            max_height = dvf->sprites[animation->frames[i]->sprite_id]->height;
        }
    }
    return max_height;
}

unsigned short odv_dvf_get_frame_min_x(const struct ODVDvfAnimation *animation)
{
    unsigned short min_x = 0xFFFF;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (animation->frames[i]->coordinate_x < min_x) {
            min_x = animation->frames[i]->coordinate_x;
        }
    }
    return min_x;
}

unsigned short odv_dvf_get_frame_min_y(const struct ODVDvfAnimation *animation)
{
    unsigned short min_y = 0xFFFF;

    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        if (animation->frames[i]->coordinate_y < min_y) {
            min_y = animation->frames[i]->coordinate_y;
        }
    }
    return min_y;
}


int odv_dvf_parse_header(struct ODVDvf *dvf)
{
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(dvf->file, &dvf->header, sizeof (struct ODVDvfHeader));
    if (numberofbytesread != sizeof (struct ODVDvfHeader)) {
        fprintf(stderr, "[-] odv_dvf_parse_header - file read %zu failed\n", sizeof (struct ODVDvfHeader));
        return 0;
    }
    if (dvf->header.version != 0x200) {
        fprintf(stderr, "[-] odv_dvf_parse_header - Wrong version 0x%04X (expected 0x200)\n", dvf->header.version);
        return 0;
    }
    return 1;
}

void odv_dvf_info(const struct ODVDvf *dvf)
{
    if (dvf == NULL) {
        return;
    }
    printf("[- ODV DVF information -]\n");
    printf("version         = 0x%08X\n", dvf->header.version);
    printf("nb_sprites      = 0x%04X\n", dvf->header.nb_sprites);
    printf("padding_00      = 0x%04X\n", dvf->header.padding_00);
    printf("max_width       = 0x%04X (%d)\n", dvf->header.max_width, dvf->header.max_width);
    printf("max_height      = 0x%04X (%d)\n", dvf->header.max_height, dvf->header.max_height);
    printf("nb_profiles     = 0x%04X\n", dvf->nb_profiles);
    for (unsigned short i = 0; i < dvf->header.nb_sprites; i++) {
        printf("[Sprite #%d (0x%04X)]\n", i, i);
        odv_image_info(dvf->sprites[i]);
    }
    for (unsigned short i = 0; i < dvf->nb_profiles; i++) {
        printf("    [Profile #%d information]\n", i);
        odv_dvf_profile_info(dvf->profiles[i]);
    }
    printf("[---------------------------------]\n");
}

void odv_dvf_profile_info(const struct ODVDvfProfile *profile)
{
    if (profile == NULL) {
        return;
    }
    printf("    + name            : %s\n", profile->name);
    printf("    + nb_perspectives : 0x%04X\n", profile->nb_perspectives);
    printf("    + nb_animations   : 0x%04X\n", profile->nb_animations);
    printf("    + max_width       : 0x%04X (%d)\n", profile->max_width, profile->max_width);
    printf("    + max_height      : 0x%04X (%d)\n", profile->max_height, profile->max_height);
    printf("    + coordinate_x    : %f\n", profile->coordinate_x);
    printf("    + coordinate_y    : %f\n", profile->coordinate_y);
    for (unsigned short i = 0; i < (unsigned short)(profile->nb_perspectives * profile->nb_animations); i++) {
        printf("        [Animation #%d information]\n", i);
        odv_dvf_animation_info(profile->animations[i]);
    }
}

void odv_dvf_animation_info(const struct ODVDvfAnimation *animation)
{
    if (animation == NULL) {
        return;
    }
    printf("        + nb_frames      : 0x%04X\n", animation->nb_frames);
    printf("        + unk_word_00    : 0x%04X\n", animation->unk_word_00);
    printf("        + unk_word_01    : 0x%04X\n", animation->unk_word_01);
    printf("        + coordinate_x   : %f\n", animation->coordinate_x);
    printf("        + coordinate_y   : %f\n", animation->coordinate_y);
    printf("        + perspective_id : 0x%04X\n", animation->perspective_id);
    printf("        + animation_id   : 0x%04X\n", animation->animation_id);
    printf("        + animation_name : %s\n", animation->animation_name);
    for (unsigned short i = 0; i < animation->nb_frames; i++) {
        printf("            [Frame #%d information]\n", i);
        odv_dvf_frame_info(animation->frames[i]);
    }
}

void odv_dvf_frame_info(const struct ODVDvfFrame *frame)
{
    if (frame == NULL) {
        return;
    }
     printf("            + sprite_id    : 0x%04X\n", frame->sprite_id);
     printf("            + duration     : 0x%04X\n", frame->duration);
     printf("            + distance     : 0x%04X\n", frame->distance);
     printf("            + coordinate_x : %f\n", (float)frame->coordinate_x);
     printf("            + coordinate_y : %f\n", (float)frame->coordinate_y);
     printf("            + sound_id     : 0x%04X\n", frame->sound_id);
     printf("            + unused_00    : 0x%04X\n", frame->unused_00);
}

void odv_dvf_close(struct ODVDvf *dvf)
{
    if (dvf == NULL) {
        return;
    }
    if (dvf->file != NULL) {
        odv_file_close(dvf->file);
        dvf->file = NULL;
    }
    if (dvf->sprites != NULL) {
        for (unsigned int i = 0; i < dvf->header.nb_sprites; i++) {
            if (dvf->sprites[i] != NULL) {
                odv_image_clean(dvf->sprites[i]);
            }
            dvf->sprites[i] = NULL;
        }
        free(dvf->sprites);
        dvf->sprites = NULL;
    }
    if (dvf->profiles != NULL) {
        for (int i = 0; i < dvf->nb_profiles; i++) {
            if (dvf->profiles[i] != NULL) {
                odv_dvf_clean_profile(dvf->profiles[i]);
                dvf->profiles[i] = NULL;
            }
        }
        free(dvf->profiles);
        dvf->profiles = NULL;
    }
    free(dvf);
}

void odv_dvf_clean_animation(struct ODVDvfAnimation *animation)
{
    if (animation == NULL) {
        return;
    }
    if (animation->frames) {
        for (unsigned short i = 0; i < animation->nb_frames; i++) {
            if (animation->frames[i] != NULL) {
                free(animation->frames[i]);
                animation->frames[i] = NULL;
            }
        }
        free(animation->frames);
        animation->frames = NULL;
    }
    free(animation);
}

void odv_dvf_clean_profile(struct ODVDvfProfile *profile)
{
    if (profile == NULL) {
        return;
    }
    if (profile->animations) {
        for (unsigned short i = 0; i < (unsigned short)(profile->nb_perspectives * profile->nb_animations); i++) {
            if (profile->animations[i] != NULL) {
                odv_dvf_clean_animation(profile->animations[i]);
                profile->animations[i] = NULL;
            }
        }
        free(profile->animations);
        profile->animations = NULL;
    }
    free(profile);
}