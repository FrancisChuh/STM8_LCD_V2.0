#include "include.h"

void GPRS_TEST(void);
void GPRS_ReStart(void);
u8* GPRS_check_cmd(u8 *str);
u8 GPRS_send_cmd(u8 *cmd,u8 *ack,u16 waittime);