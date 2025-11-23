#include <stdint.h>
#include "point.h"


#pragma pack(push, 1)   // IMPORTANT: prevent padding
struct LASFile
{
    FILE* adress;

    char file_signature[4];               // 4 bytes
    uint16_t file_source_ID;              // 2 bytes
    uint16_t global_encoding;             // 2 bytes

    uint32_t project_ID_GUID_data_1;      // 4 bytes
    uint16_t project_ID_GUID_data_2;      // 2 bytes
    uint16_t project_ID_GUID_data_3;      // 2 bytes
    uint8_t  project_ID_GUID_data_4[8];   // 8 bytes

    uint8_t  version_major;               // 1 byte
    uint8_t  version_minor;               // 1 byte

    char system_identifier[32];           // 32 bytes
    char generating_software[32];         // 32 bytes

    uint16_t file_creation_day;           // 2 bytes
    uint16_t file_creation_year;          // 2 bytes
    uint16_t header_size;                 // 2 bytes

    uint32_t offset_2_pts_data;           // 4 bytes
    uint32_t number_of_var_length_records;// 4 bytes
    uint8_t  pt_data_record_format;       // 1 byte
    uint16_t pt_data_record_length;       // 2 bytes

    uint32_t number_of_pts_records;       // 4 bytes
    uint32_t number_of_pts_by_return[5];  // 5×4 = 20 bytes

    double x_scale_factor;                // 8 bytes
    double y_scale_factor;                // 8 bytes
    double z_scale_factor;                // 8 bytes

    double x_offset;                      // 8 bytes
    double y_offset;                      // 8 bytes
    double z_offset;                      // 8 bytes

    double x_max;                        // 8 bytes
    double x_min;
    double y_max;
    double y_min;
    double z_max;
    double z_min;

    Point* pts;
};
#pragma pack(pop)

int initLASFile(struct LASFile* file, char* path2file, long int num_pts);
// If num_pts = -1 it loads all the points in the las file


int delLASFile(struct LASFile* file);

