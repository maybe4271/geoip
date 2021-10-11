#include <time.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include "geoip.h"


int main()
{
	geoip_initialize();
	struct IP_LINE_BIN *sip_addr = (struct IP_LINE_BIN *)geoip_locate(ntohl((uint32_t)inet_addr("103.87.10.8")));
	assert(sip_addr != NULL);
	printf("ip_start=%d\n", sip_addr->ip_start);
	printf("ip_end=%d\n", sip_addr->ip_end);
	printf("num_start=%d\n", sip_addr->num_start);
	printf("num_end=%d\n", sip_addr->num_end);
	printf("num=%d\n", sip_addr->num);
	printf("land=%s\n", sip_addr->land);
	printf("region=%s\n", sip_addr->region);
	printf("city=%s\n", sip_addr->city);
	printf("area=%s\n", sip_addr->area);
	printf("country=%s\n", sip_addr->country);
	printf("country_en=%s\n", sip_addr->country_en);
	printf("isp=%s\n", sip_addr->isp);
	printf("country_id=%s\n", sip_addr->country_id);
	printf("i18n_code=%s\n", sip_addr->i18n_code);
	printf("region_id=%s\n", sip_addr->region_id);
	printf("city_id=%s\n", sip_addr->city_id);
	printf("area_id=%s\n", sip_addr->area_id);
	printf("lat=%s\n", sip_addr->lat);
	printf("lng=%s\n", sip_addr->lng);
	geoip_clean();
	return 0;
}
