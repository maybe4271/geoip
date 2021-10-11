#ifndef _GEOIP_
#define _GEOIP_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define STR_BUFFER_SIZE			1024

#define MAX_IPLOCA_LINE		 	2805002

#define IPLOCA_FILE				"data_ip_20210405_world.csv"    //location for src file
#define IPLOCA_BIN				"data_20210405.bin"             //location for dst file

//hash size
#define MAX_GROUP_IPC		16777216	/* 256*256*256 =16M */
#define MAX_IP_SIZE				16

// .txt/.csv
struct IP_LINE
{
	// about ip information
	uint32_t ip_start;
	uint32_t ip_end;
	uint32_t num_start;
	uint32_t num_end;
	uint32_t num;

	uint8_t* land;
	uint8_t* region;
	uint8_t* city;
	uint8_t* area;
	uint8_t* country;
	uint8_t* country_en;
	uint8_t* isp;
	uint8_t* country_id;
	uint8_t* i18n_code;
	uint8_t* region_id;
	uint8_t* city_id;
	uint8_t* area_id;
	uint8_t* lat;
	uint8_t* lng;

	uint8_t land_len;
	uint8_t region_len;
	uint8_t city_len;
	uint8_t area_len;
	uint8_t country_len;
	uint8_t country_en_len;
	uint8_t isp_len;
	uint8_t country_id_len;
	uint8_t i18n_code_len;
	uint8_t region_id_len;
	uint8_t city_id_len;
	uint8_t area_id_len;
	uint8_t lat_len;
	uint8_t lng_len;
}; 

// .bin
struct IP_LINE_BIN
{
	uint32_t ip_start;
	uint32_t ip_end;
	uint32_t num_start;
	uint32_t num_end;
	uint32_t num;

	uint8_t* land;
	uint8_t* region;
	uint8_t* city;
	uint8_t* area;
	uint8_t* country;
	uint8_t* country_en;
	uint8_t* isp;
	uint8_t* country_id;
	uint8_t* i18n_code;
	uint8_t* region_id;
	uint8_t* city_id;
	uint8_t* area_id;
	uint8_t* lat;
	uint8_t* lng;

	uint8_t land_offset;
	uint8_t region_offset;
	uint8_t city_offset;
	uint8_t area_offset;
	uint8_t country_offset;
	uint8_t country_en_offset;
	uint8_t isp_offset;
	uint8_t country_id_offset;
	uint8_t i18n_code_offset;
	uint8_t region_id_offset;
	uint8_t city_id_offset;
	uint8_t area_id_offset;
	uint8_t lat_offset;
	uint8_t lng_offset;

	uint8_t land_len;
	uint8_t region_len;
	uint8_t city_len;
	uint8_t area_len;
	uint8_t country_len;
	uint8_t country_en_len;
	uint8_t isp_len;
	uint8_t country_id_len;
	uint8_t i18n_code_len;
	uint8_t region_id_len;
	uint8_t city_id_len;
	uint8_t area_id_len;
	uint8_t lat_len;
	uint8_t lng_len;

	// buffer line
	uint8_t line_data_len;
};

// hash table
struct node_info
{
	uint32_t sip;
	uint32_t eip;
	struct IP_LINE_BIN* addr;
};

struct hash_node
{
	struct node_info* node_info;
	struct hash_node* next;
};

struct IP_C_GROUP
{
	struct hash_node* hash_node;
};

void* geoip_initialize(void);
void* geoip_locate(uint32_t ip);
void geoip_clean();

#ifdef __cplusplus
}
#endif

#endif
