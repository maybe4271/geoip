#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include "geoip.h"


struct IP_LINE_BIN *global_bin_ip = NULL;
struct IP_C_GROUP *global_ip_c = NULL;
struct node_info *node_info_list = NULL;
struct hash_node *hash_node_list = NULL;

uint8_t *bin_str = NULL;

////The retrieved IP_LINE_BIN is written to the binary file
/**
 * retrieved IP_LINE_BIN
 * write binnary file
 */
void geoip_write_bin_file(FILE *fp_bin, const struct IP_LINE *p_ip_line)
{
	//read line data to custom struct
	struct IP_LINE_BIN ip_line_bin;

	ip_line_bin.ip_start = p_ip_line->ip_start;
	ip_line_bin.ip_end = p_ip_line->ip_end;
	ip_line_bin.num_start = p_ip_line->num_start;
	ip_line_bin.num_end = p_ip_line->num_end;
	ip_line_bin.num = p_ip_line->num;
	ip_line_bin.land_len = p_ip_line->land_len;
	ip_line_bin.region_len = p_ip_line->region_len;
	ip_line_bin.city_len = p_ip_line->city_len;
	ip_line_bin.area_len = p_ip_line->area_len;
	ip_line_bin.country_len = p_ip_line->country_len;
	ip_line_bin.country_en_len = p_ip_line->country_en_len;
	ip_line_bin.isp_len = p_ip_line->isp_len;
	ip_line_bin.country_id_len = p_ip_line->country_id_len;
	ip_line_bin.i18n_code_len = p_ip_line->i18n_code_len;
	ip_line_bin.region_id_len = p_ip_line->region_id_len;
	ip_line_bin.city_id_len = p_ip_line->city_id_len;
	ip_line_bin.area_id_len = p_ip_line->area_id_len;
	ip_line_bin.lat_len = p_ip_line->lat_len;
	ip_line_bin.lng_len = p_ip_line->lng_len;
	ip_line_bin.line_data_len = 0;
	ip_line_bin.land = NULL;
	ip_line_bin.region = NULL;
	ip_line_bin.city = NULL;
	ip_line_bin.area = NULL;
	ip_line_bin.country = NULL;
	ip_line_bin.country_en = NULL;
	ip_line_bin.isp = NULL;
	ip_line_bin.country_id = NULL;
	ip_line_bin.i18n_code = NULL;
	ip_line_bin.region_id = NULL;
	ip_line_bin.city_id = NULL;
	ip_line_bin.area_id = NULL;
	ip_line_bin.lat = NULL;
	ip_line_bin.lng = NULL;

	uint8_t tmp_len = 0;

	// writing every line
	char ip_line_bin_str[STR_BUFFER_SIZE];

	memset(ip_line_bin_str, 0, STR_BUFFER_SIZE);

	if (p_ip_line->land == NULL)
	{
		ip_line_bin.land_offset = 0;
		ip_line_bin_str[0] = '\0';
		ip_line_bin.line_data_len = 1;
	}
	else
	{
		ip_line_bin.land_offset = 0;
		tmp_len = p_ip_line->land_len + 1;
		memcpy(ip_line_bin_str, p_ip_line->land, tmp_len);
		//memcpy is copy num byte from src to dest, never mind '\0'
		ip_line_bin.line_data_len = tmp_len;
	}

	if (p_ip_line->region == NULL)
	{
		ip_line_bin.region_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.region_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->region_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->region, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->city == NULL)
	{
		ip_line_bin.city_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.city_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->city_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->city, tmp_len);
		ip_line_bin.line_data_len += tmp_len;		
	}

	if (p_ip_line->area == NULL)
	{
		ip_line_bin.area_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.area_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->area_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->area, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->country == NULL)
	{
		ip_line_bin.country_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.country_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->country_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->country, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->country_en == NULL)
	{
		ip_line_bin.country_en_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.country_en_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->country_en_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->country_en, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->isp == NULL)
	{
		ip_line_bin.isp_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.isp_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->isp_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->isp, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->country_id == NULL)
	{
		ip_line_bin.country_id_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.country_id_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->country_id_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->country_id, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->i18n_code == NULL)
	{
		ip_line_bin.i18n_code_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.i18n_code_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->i18n_code_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->i18n_code, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->region_id == NULL)
	{
		ip_line_bin.region_id_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.region_id_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->region_id_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->region_id, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->city_id == NULL)
	{
		ip_line_bin.city_id_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.city_id_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->city_id_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->city_id, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->area_id == NULL)
	{
		ip_line_bin.area_id_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.area_id_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->area_id_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->area_id, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->lat == NULL)
	{
		ip_line_bin.lat_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.lat_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->lat_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->lat, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	if (p_ip_line->lng == NULL)
	{
		ip_line_bin.lng_offset = ip_line_bin.line_data_len;
		ip_line_bin_str[ip_line_bin.line_data_len] = '\0';
		ip_line_bin.line_data_len += 1;
	}
	else
	{
		ip_line_bin.lng_offset = ip_line_bin.line_data_len;
		tmp_len = p_ip_line->lng_len + 1;
		memcpy((ip_line_bin_str + ip_line_bin.line_data_len), p_ip_line->lng, tmp_len);
		ip_line_bin.line_data_len += tmp_len;
	}

	//printf("geoip_read_file str_bin_line %s\n", ip_line_bin_str);

	//ip_line_bin write to bin file
	fwrite(&ip_line_bin, sizeof(struct IP_LINE_BIN), 1, fp_bin);
	//struct IP_LINE_BIN write to bin_file 

	fwrite(ip_line_bin_str, ip_line_bin.line_data_len, 1, fp_bin);
}


//read file of iplocation, to IP_LINE
/**
 * read file of iplocation
 */
void* geoip_read_file()
{
	FILE* fp;

	if ((fp = fopen(IPLOCA_FILE, "r")) == NULL)
	{
		fprintf(stderr, "can not open %s : %s\n", IPLOCA_FILE, strerror(errno));
		return NULL;
	}

	FILE* fp_bin;

	if((fp_bin = fopen(IPLOCA_BIN, "wab+")) == NULL)
	{
		fprintf(stderr, "can not open %s : %s\n", IPLOCA_BIN, strerror(errno));
		return NULL;
	}

	int lineN = 0;

	// eg: "1.119.0.0","1.119.191.255","24576000","24625151","49152","亚洲","北京市","北京市","朝阳区","中国","China","中国电信","CN","+86","110000","110100","110105","39.948574","116.601144"
	// read file, and save in array
	while (!feof(fp))
	{
		// reading every line, in variables
		char line[STR_BUFFER_SIZE];
		char *begin = NULL, *end = NULL;

		if ((begin = fgets(line, STR_BUFFER_SIZE - 1, fp)) == NULL)
			continue;

		if (strlen(begin) < 23)
			continue;

		int type = 0;

		struct IP_LINE ip_line;

		uint8_t ip_line_arr[STR_BUFFER_SIZE] = {0};
		uint8_t *ip_line_arr_ptr = ip_line_arr;

		while ((begin != NULL) && ((end = strchr(begin, ',')) != NULL))
		{
			int len = end - begin;

			switch (type)
			{
				case 0:
				{
					uint8_t ip[MAX_IP_SIZE] = {0};
					// delete field "", eg: "0.0.0.0"
					if (len > 2)
						memcpy(ip, begin+1, len-2);

					ip_line.ip_start = ntohl((uint32_t)inet_addr(ip));
					break;
				}
				case 1:
				{
					uint8_t ip[MAX_IP_SIZE] = {0};
					// delete field "", eg: "0.255.255.255"
					if (len > 2)
						memcpy(ip, begin+1, len-2);

					ip_line.ip_end = ntohl((uint32_t)inet_addr(ip));
					break;
				}
				case 2:
				{
					uint8_t num[MAX_IP_SIZE] = {0};
					// delete field "", eg: "0"
					if (len > 2)
						memcpy(num, begin+1, len-2);

					ip_line.num_start = atoi(num);
					break;
				}
				case 3:
				{
					uint8_t num[MAX_IP_SIZE] = {0};
					// delete field "", eg: "16777215"
					if (len > 2)
						memcpy(num, begin+1, len-2);

					ip_line.num_end = atoi(num);
					break;
				}
				case 4:
				{
					uint8_t num[MAX_IP_SIZE] = {0};
					// delete field "", eg: "16777216"
					if (len > 2)
						memcpy(num, begin+1, len-2);

					ip_line.num = atoi(num);
					break;
				}
				case 5:
				{
					if (len <= 2)
					{
						ip_line.land = NULL;
						ip_line.land_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.land = ip_line_arr_ptr;
					ip_line.land_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 6:
				{
					if (len <= 2)
					{
						ip_line.region = NULL;
						ip_line.region_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.region = ip_line_arr_ptr;
					ip_line.region_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 7:
				{
					if (len <= 2)
					{
						ip_line.city = NULL;
						ip_line.city_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.city = ip_line_arr_ptr;
					ip_line.city_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 8:
				{
					if (len <= 2)
					{
						ip_line.area = NULL;
						ip_line.area_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.area = ip_line_arr_ptr;
					ip_line.area_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 9:
				{
					if (len <= 2)
					{
						ip_line.country = NULL;
						ip_line.country_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.country = ip_line_arr_ptr;
					ip_line.country_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 10:
				{
					if (len <= 2)
					{
						ip_line.country_en = NULL;
						ip_line.country_en_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.country_en = ip_line_arr_ptr;
					ip_line.country_en_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 11:
				{
					if (len <= 1)
					{
						ip_line.isp = NULL;
						ip_line.isp_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.isp = ip_line_arr_ptr;
					ip_line.isp_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 12:
				{
					if (len <= 2)
					{
						ip_line.country_id = NULL;
						ip_line.country_id_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.country_id = ip_line_arr_ptr;
					ip_line.country_id_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 13:
				{
					if (len <= 2)
					{
						ip_line.i18n_code = NULL;
						ip_line.i18n_code_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.i18n_code = ip_line_arr_ptr;
					ip_line.i18n_code_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 14:
				{
					if (len <= 2)
					{
						ip_line.region_id = NULL;
						ip_line.region_id_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.region_id = ip_line_arr_ptr;
					ip_line.region_id_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 15:
				{
					if (len <= 2)
					{
						ip_line.city_id = NULL;
						ip_line.city_id_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.city_id = ip_line_arr_ptr;
					ip_line.city_id_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 16:
				{
					if (len <= 2)
					{
						ip_line.area_id = NULL;
						ip_line.area_id_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.area_id = ip_line_arr_ptr;
					ip_line.area_id_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				case 17:
				{
					if (len <= 2)
					{
						ip_line.lat = NULL;
						ip_line.lat_len = 0;
						break;
					}

					memcpy(ip_line_arr_ptr, begin+1, len-2);
					*(ip_line_arr_ptr+len-2) = '\0';

					ip_line.lat = ip_line_arr_ptr;
					ip_line.lat_len = len-2;
					ip_line_arr_ptr += len-1;
					break;
				}
				default:
				{
					break;
				}
			}
			begin = end + 1;	//后移一位
			type++;
		}

		{
			//处理最后一部分，"119.295144"\r\n\0
			int len = strlen(begin);
			if (len <= 4)
			{
				ip_line.lng = NULL;
				ip_line.lng_len = 0;
			}
			else
			{
				memcpy(ip_line_arr_ptr, begin+1, len-4);
				*(ip_line_arr_ptr+len-4) = '\0';
				
				ip_line.lng = ip_line_arr_ptr;
				ip_line.lng_len = len-4;
				ip_line_arr_ptr += len-3;
			}
		}

		struct IP_LINE *p_ip_line = &ip_line;

		geoip_write_bin_file(fp_bin, p_ip_line);

		lineN++;

		if (lineN >= MAX_IPLOCA_LINE)
		{
			break;
		}
	}

	fclose(fp);
	fclose(fp_bin);
}

bool geoip_add_hash(struct IP_C_GROUP *p, struct node_info *node_info, int index)
{
	struct IP_C_GROUP *t = p;
	struct hash_node *node = t->hash_node;
	struct hash_node *node_last = node;

	while (node != NULL)
	{
		if (node->node_info->sip > node_info->eip || node->node_info->eip < node_info->sip)
		{
			node_last = node;
			node = node->next;
		}
		else
		{
			return false;
		}
	}

	node = &hash_node_list[index];
	
	node->node_info = node_info;
	node->next = NULL;

	if (node_last != NULL)
	{
		node_last->next = node;
	}
	else
	{
		t->hash_node = node;
	}

	return true;
}

/**
 *read bin_file to ip_line_bin_str
 *IP_LINE_BIN to IP_LINE
 */
uint32_t geoip_read_bin_file(struct IP_LINE_BIN *global_bin_ip, FILE *fp)
{
	uint32_t i = 0;

	//comput data.bin.file size
	fseek(fp, 0L, SEEK_END);
	int bin_file_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	//printf("geoip_read_bin_file bin_file_size %d\n", bin_file_size);

	bin_str = (uint8_t *)malloc(bin_file_size * sizeof(uint8_t));
	if (bin_str == NULL)
	{
		printf ("bin_str malloc fail.\n");
		exit(1); 
	}

	int count = fread(bin_str, bin_file_size * sizeof(uint8_t), 1, fp);
	if (count != 1)
	{
		printf("geoip_initialize fread data_bin failed\n");
		exit(1);
	}

	uint8_t *begin = bin_str;
	uint8_t *end = bin_str + bin_file_size;
		
	while (begin < end)
	{
		struct IP_LINE_BIN *tmp = (struct IP_LINE_BIN *)begin;
		if (tmp == NULL || tmp->line_data_len == 0)
			break;

		//gain IP_LINE_BIN data
		global_bin_ip[i].ip_start = tmp->ip_start;
		global_bin_ip[i].ip_end = tmp->ip_end;
		global_bin_ip[i].num_start = tmp->num_start;
		global_bin_ip[i].num_end = tmp->num_end;
		global_bin_ip[i].num = tmp->num;
		global_bin_ip[i].land_offset = tmp->land_offset;
		global_bin_ip[i].region_offset = tmp->region_offset;
		global_bin_ip[i].city_offset = tmp->city_offset;
		global_bin_ip[i].area_offset = tmp->area_offset;
		global_bin_ip[i].country_offset = tmp->country_offset;
		global_bin_ip[i].country_en_offset = tmp->country_en_offset;
		global_bin_ip[i].isp_offset = tmp->isp_offset;
		global_bin_ip[i].country_id_offset = tmp->country_id_offset;
		global_bin_ip[i].i18n_code_offset = tmp->i18n_code_offset;
		global_bin_ip[i].region_id_offset = tmp->region_id_offset;
		global_bin_ip[i].city_id_offset = tmp->city_id_offset;
		global_bin_ip[i].area_id_offset = tmp->area_id_offset;
		global_bin_ip[i].lat_offset = tmp->lat_offset;
		global_bin_ip[i].lng_offset = tmp->lng_offset;
		global_bin_ip[i].land_len = tmp->land_len;
		global_bin_ip[i].region_len = tmp->region_len;
		global_bin_ip[i].city_len = tmp->city_len;
		global_bin_ip[i].area_len = tmp->area_len;
		global_bin_ip[i].country_len = tmp->country_len;
		global_bin_ip[i].country_en_len = tmp->country_en_len;
		global_bin_ip[i].isp_len = tmp->isp_len;
		global_bin_ip[i].country_id_len = tmp->country_id_len;
		global_bin_ip[i].i18n_code_len = tmp->i18n_code_len;
		global_bin_ip[i].region_id_len = tmp->region_id_len;
		global_bin_ip[i].city_id_len = tmp->city_id_len;
		global_bin_ip[i].area_id_len = tmp->area_id_len;
		global_bin_ip[i].lat_len = tmp->lat_len;
		global_bin_ip[i].lng_len = tmp->lng_len;
		global_bin_ip[i].line_data_len = tmp->line_data_len;

		begin = begin + sizeof(struct IP_LINE_BIN);

		global_bin_ip[i].land = begin + tmp->land_offset;
		global_bin_ip[i].region = begin + tmp->region_offset;
		global_bin_ip[i].city = begin + tmp->city_offset;
		global_bin_ip[i].area = begin + tmp->area_offset;
		global_bin_ip[i].country = begin + tmp->country_offset;
		global_bin_ip[i].country_en = begin + tmp->country_en_offset;
		global_bin_ip[i].isp = begin + tmp->isp_offset;
		global_bin_ip[i].country_id = begin + tmp->country_id_offset;
		global_bin_ip[i].i18n_code = begin + tmp->i18n_code_offset;
		global_bin_ip[i].region_id = begin + tmp->region_id_offset;
		global_bin_ip[i].city_id = begin + tmp->city_id_offset;
		global_bin_ip[i].area_id = begin + tmp->area_id_offset;
		global_bin_ip[i].lat = begin + tmp->lat_offset;
		global_bin_ip[i].lng = begin + tmp->lng_offset;

		begin = begin + (tmp->line_data_len);

		//read next line
		i++;
	}		

	uint32_t cnt = i;  

	fclose(fp);

	return cnt;
}

/**
 * geoip data initialize function
 *
 * @return 
 *		A pointer of geoip info
 */
void* geoip_initialize(void)
{
	FILE *fp;
	uint32_t i = 0;

	//whether bin file
	//.txt->.bin
	if ((fp=fopen(IPLOCA_BIN, "rb+")) == NULL)
	{
		geoip_read_file();
	}

	//read .bin
	if ((fp = fopen(IPLOCA_BIN, "rb")) == NULL)
	{
		fprintf(stderr, "can not open %s : %s\n", IPLOCA_BIN, strerror(errno));
		return NULL;
	}

	global_bin_ip = (struct IP_LINE_BIN *)malloc(MAX_IPLOCA_LINE * sizeof(struct IP_LINE_BIN));

	if (global_bin_ip == NULL)
	{
		printf("global_bin_ip : error malloc\n");
		return NULL; 
	}

	uint32_t global_bin_ip_cnt;

	global_bin_ip_cnt = geoip_read_bin_file(global_bin_ip, fp);

	// build C address hash table.
	global_ip_c = (struct IP_C_GROUP *)malloc(MAX_GROUP_IPC * sizeof(struct IP_C_GROUP));

	if (global_ip_c == NULL)
	{
		printf("global_ip_c : error malloc\n");
		return NULL; 
	}

	memset(global_ip_c, 0, MAX_GROUP_IPC * sizeof(struct IP_C_GROUP));

	uint32_t total_cnt = 0;

	for (i = 0; i < global_bin_ip_cnt; i++)
	{
		uint32_t arr_sip_c = (global_bin_ip[i].ip_start) >> 8;
		uint32_t arr_eip_c = (global_bin_ip[i].ip_end) >> 8;

		// network C range
		uint32_t line_cnt = arr_eip_c - arr_sip_c + 1;

		total_cnt += line_cnt;
	}
	
	node_info_list = (struct node_info *)malloc(sizeof(struct node_info) * total_cnt);

	if (node_info_list == NULL)
	{
		printf("node_info_list : error malloc\n");
		return NULL; 
	}

	hash_node_list = (struct hash_node *)malloc(sizeof(struct hash_node) * total_cnt);
	
	if (hash_node_list == NULL)
	{
		printf("hash_node_list : error malloc\n");
		return NULL; 
	}

	i = 0;
	int tmp_pre_cnt = 0;
	
	while (1)
	{
		uint32_t arr_sip_c = (global_bin_ip[i].ip_start) >> 8;
		uint32_t arr_eip_c = (global_bin_ip[i].ip_end) >> 8;

		// network C range
		int cnt = arr_eip_c - arr_sip_c + 1;

		if (i > 0)
		{
			tmp_pre_cnt += ((global_bin_ip[i - 1].ip_end) >> 8) - ((global_bin_ip[i - 1].ip_start) >> 8);
		}

		assert(tmp_pre_cnt >= 0);

		if (cnt > 1)
		{
			int j;
			for (j = 0; j < cnt; j++)
			{
				int index = tmp_pre_cnt + i + j;
				struct node_info* node_info = &node_info_list[index];
				if (j == 0)
				{
					//begin
					/********************
					 *s: 1.1.1.2 - 1.1.3.253
					 *
					 *	1.1.1.2 - 1.1.1.255
					 * **********************/
					node_info->sip = global_bin_ip[i].ip_start;
					node_info->eip = (global_bin_ip[i].ip_start & 0xffffff00) + 0xff;
					node_info->addr = &global_bin_ip[i];
				}
				else if (j == cnt - 1)
				{
					//end
					/********************
					 *s: 1.1.1.2 - 1.1.3.253
					 *
					 *	1.1.2.0 - 1.1.2.255
					 *
					 * **********************/
					node_info->sip = global_bin_ip[i].ip_end & 0xffffff00;
					node_info->eip = global_bin_ip[i].ip_end;
					node_info->addr = &global_bin_ip[i];
				}
				else
				{
					/********************
					 *s: 1.1.1.2 - 1.1.3.253
					 *
					 *	1.1.2.0 - 1.1.2.255
					 *
					 * **********************/

					node_info->sip = (global_bin_ip[i].ip_start & 0xffffff00) + 0x100 * j;
					node_info->eip = (global_bin_ip[i].ip_start & 0xffffff00) + 0x100 * j + 0xff;
					node_info->addr = &global_bin_ip[i];
				}

				if (!geoip_add_hash(&global_ip_c[arr_sip_c + j], node_info, index))
				{
					printf("Error, ip addr refrain: line is %d, ip start is %d, ip end is %d\n", i, global_bin_ip[i].ip_start, global_bin_ip[i].ip_end);
					goto err;	
				}

				assert((&global_ip_c[arr_sip_c + j])->hash_node != NULL);
			}
		}
		else if (cnt == 1)
		{
			int index = tmp_pre_cnt + i;
			struct node_info *node_info = &node_info_list[index];
			node_info->sip = global_bin_ip[i].ip_start;
			node_info->eip = global_bin_ip[i].ip_end;
			node_info->addr = &global_bin_ip[i];

			geoip_add_hash(&global_ip_c[arr_sip_c], node_info, index);
			//assert((&global_ip_c[arr_sip_c])->hash_node != NULL);
		}

err:
		//assert(!(arr_sip_c <= 11513096 && arr_eip_c >= 11513096));
		i++;
		if (i >= global_bin_ip_cnt)
		{
			break;
		}
	}

	return global_ip_c;
}

void* geoip_locate(uint32_t ip)
{
	struct IP_C_GROUP *t = global_ip_c;
	if (t == NULL || ip == 0xffffffff)
		return NULL;

	uint32_t key = ip >> 8;
	struct IP_C_GROUP *group = &(t[key]);
	struct hash_node *node = group->hash_node;
	while (node != NULL)
	{
		struct node_info *node_info = node->node_info;
		if (ip >= node_info->sip && ip <= node_info->eip)
		{
			return node_info->addr;
		}

		node = node->next;
	}

	return NULL;
}

void geoip_clean()
{
	free(bin_str);
	free(hash_node_list);
	free(node_info_list);
	free(global_ip_c);
	free(global_bin_ip);
}

