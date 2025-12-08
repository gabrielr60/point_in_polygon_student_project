#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "las_reader.h"




int initLASFile(struct LASFile* file, char* path_2_file, long int number_of_points){

    FILE* ptr = fopen(path_2_file, "rb");
    if (ptr == NULL) {
        perror("Couldn't open the file");
        return 1;
    }

    /* -----------------------
       Read + PRINT fields
       ----------------------- */

    fread(file->file_signature, sizeof(file->file_signature), 1, ptr);
    //printf("File Signature: %.4s\n", file->file_signature);

    fread(&file->file_source_ID, sizeof(file->file_source_ID), 1, ptr);
    // printf("File Source ID: %u\n", file->file_source_ID);

    fread(&file->global_encoding, sizeof(file->global_encoding), 1, ptr);
    // printf("Global Encoding: %u\n", file->global_encoding);

    fread(&file->project_ID_GUID_data_1, sizeof(file->project_ID_GUID_data_1), 1, ptr);
    fread(&file->project_ID_GUID_data_2, sizeof(file->project_ID_GUID_data_2), 1, ptr);
    fread(&file->project_ID_GUID_data_3, sizeof(file->project_ID_GUID_data_3), 1, ptr);
    fread(file->project_ID_GUID_data_4, sizeof(file->project_ID_GUID_data_4), 1, ptr);

    // printf("Project ID GUID: %08X-%04X-%04X-",  file->project_ID_GUID_data_1, file->project_ID_GUID_data_2, file->project_ID_GUID_data_3);

    //for (int i = 0; i < 8; i++)
    //    printf("%02X", file->project_ID_GUID_data_4[i]);
    //printf("\n");

    fread(&file->version_major, sizeof(file->version_major), 1, ptr);
    fread(&file->version_minor, sizeof(file->version_minor), 1, ptr);
    //printf("Version: %u.%u\n", file->version_major, file->version_minor);

    fread(file->system_identifier, sizeof(file->system_identifier), 1, ptr);
    //printf("System Identifier: %s\n", file->system_identifier);

    fread(file->generating_software, sizeof(file->generating_software), 1, ptr);
    //printf("Generating Software: %s\n", file->generating_software);

    fread(&file->file_creation_day, sizeof(file->file_creation_day), 1, ptr);
    fread(&file->file_creation_year, sizeof(file->file_creation_year), 1, ptr);
    //printf("Creation Day/Year: %u / %u\n",file->file_creation_day, file->file_creation_year);

    fread(&file->header_size, sizeof(file->header_size), 1, ptr);
    //printf("Header Size: %u\n", file->header_size);

    fread(&file->offset_2_pts_data, sizeof(file->offset_2_pts_data), 1, ptr);
    //printf("Offset to Point Data: %u\n", file->offset_2_pts_data);

    fread(&file->number_of_var_length_records, sizeof(file->number_of_var_length_records), 1, ptr);
    //printf("Num Variable Length Records: %u\n", file->number_of_var_length_records);

    fread(&file->pt_data_record_format, sizeof(file->pt_data_record_format), 1, ptr);
    //printf("Point Data Record Format: %u\n", file->pt_data_record_format);

    fread(&file->pt_data_record_length, sizeof(file->pt_data_record_length), 1, ptr);
    //printf("Point Data Record Length: %u\n", file->pt_data_record_length);

    fread(&file->number_of_pts_records, sizeof(file->number_of_pts_records), 1, ptr);
    //printf("Number of Point Records: %u\n", file->number_of_pts_records);

    fread(file->number_of_pts_by_return, sizeof(file->number_of_pts_by_return), 1, ptr);
    //printf("Points by Return: ");
    //for (int i = 0; i < 5; i++)
    //    printf("%u ", file->number_of_pts_by_return[i]);
    //printf("\n");

    fread(&file->x_scale_factor, sizeof(file->x_scale_factor), 1, ptr);
    fread(&file->y_scale_factor, sizeof(file->y_scale_factor), 1, ptr);
    fread(&file->z_scale_factor, sizeof(file->z_scale_factor), 1, ptr);
    printf("Scale Factors: X=%f  Y=%f  Z=%f\n",file->x_scale_factor, file->y_scale_factor, file->z_scale_factor);

    fread(&file->x_offset, sizeof(file->x_offset), 1, ptr);
    fread(&file->y_offset, sizeof(file->y_offset), 1, ptr);
    fread(&file->z_offset, sizeof(file->z_offset), 1, ptr);
    printf("Offsets: X=%f  Y=%f  Z=%f\n",file->x_offset, file->y_offset, file->z_offset);

    fread(&file->x_max, sizeof(double), 1, ptr);
    fread(&file->x_min, sizeof(double), 1, ptr);
    fread(&file->y_max, sizeof(double), 1, ptr);
    fread(&file->y_min, sizeof(double), 1, ptr);
    fread(&file->z_max, sizeof(double), 1, ptr);
    fread(&file->z_min, sizeof(double), 1, ptr);

    //printf("X Min/Max: %f / %f\n", file->x_min, file->x_max);
    //printf("Y Min/Max: %f / %f\n", file->y_min, file->y_max);
    //printf("Z Min/Max: %f / %f\n", file->z_min, file->z_max);

    /* -----------------------
       Read Point Records
       ----------------------- */

    fseek(ptr, file->offset_2_pts_data, SEEK_SET);

    if (number_of_points == -1 || number_of_points > file->number_of_pts_records){
	number_of_points = file->number_of_pts_records;
    }

    Point* points = malloc(sizeof(Point) * number_of_points);
    if (!points) {
        printf("Error allocating memory for points\n");
        fclose(ptr);
        return 1;
    }

    int32_t x_l, y_l, z_l;
    unsigned char class;

    for (unsigned long long i = 0; i < number_of_points; i++){
        Point* point = points + i;

        fread(&x_l, sizeof(x_l), 1, ptr);
        fread(&y_l, sizeof(y_l), 1, ptr);
        fread(&z_l, sizeof(z_l), 1, ptr);

        point->x = (double)x_l * (double) file->x_scale_factor + (double) file->x_offset;
        point->y = (double)y_l * (double) file->y_scale_factor + (double) file->y_offset;
        point->z = (double)z_l * (double) file->z_scale_factor + (double) file->z_offset;
	
	fseek(ptr, 3, SEEK_CUR);
	fread(&class, sizeof(class), 1, ptr);

	point->class = class; 
	
       //printf("Point %llu: X=%f Y=%f Z=%f\n",i, point->x, point->y, point->z);


        fseek(ptr, file->pt_data_record_length - 16, SEEK_CUR);
    }

    file->pts = points;

    fclose(ptr);
    return 0;
}

