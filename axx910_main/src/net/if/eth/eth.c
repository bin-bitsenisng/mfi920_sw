/************************************************************************
 | Project Name: KRS24
 |    File Name: eth.c
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2015.01.14   0.0   SKJ   Creation;
 |***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "os.h"
#include "sys_config.h"
#include <ctype.h>

/* include system driver header */
#include "network_cfg.h"
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

/* include system bsp header */
/* include system application header */
/* final include module header */
#include "eth.h"
#include "eth_cfg.h"
#include "eth_datatype.h"
//#include "gpio_drv.h"
//#include "net_task.h"
#include "network.h"

/* declare global variables */

typedef struct
{
    int32_t err;
    char *errdef;
    char *message;
} eth_error_text_t;


#if (SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP) || (SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX)
const eth_error_text_t eth_error_text_table[] = {
    {0, "ERR_OK", "Ok."},                            /* ERR_OK          0  */
    {-1, "ERR_MEM", "Out of memory error."},          /* ERR_MEM        -1  */
    {-2, "ERR_BUF", "Buffer error."},                 /* ERR_BUF        -2  */
    {-3, "ERR_TIMEOUT", "Timeout."},                  /* ERR_TIMEOUT    -3  */
    {-4, "ERR_RTE", "Routing problem."},              /* ERR_RTE        -4  */
    {-5, "ERR_INPROGRESS", "Operation in progress."}, /* ERR_INPROGRESS -5  */
    {-6, "ERR_VAL", "Illegal value."},                /* ERR_VAL        -6  */
    {-7, "ERR_WOULDBLOCK", "Operation would block."}, /* ERR_WOULDBLOCK -7  */
    {-8, "ERR_USE", "Address in use."},               /* ERR_USE        -8  */
    {-9, "ERR_ISCONN", "Already connected."},        /* ERR_ISCONN     -9  */
    {-10, "ERR_ABRT", "Connection aborted."},         /* ERR_ABRT       -10 */
    {-11, "ERR_RST", "Connection reset."},            /* ERR_RST        -11 */
    {-12, "ERR_CLSD", "Connection closed."},          /* ERR_CLSD       -12 */
    {-13, "ERR_CONN", "Not connected."},              /* ERR_CONN       -13 */
    {-14, "ERR_ARG", "Illegal argument."},            /* ERR_ARG        -14 */
    {-15, "ERR_IF", "Low-level netif error."},        /* ERR_IF         -15 */
};

extern int errno;

#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
const eth_error_text_t eth_error_text_table[] =
    {
        {-0, "pdFREERTOS_ERRNO_NONE", "No errors"},
        {-2, "pdFREERTOS_ERRNO_ENOENT", "No such file or directory"},
        {-4, "pdFREERTOS_ERRNO_EINTR", "Interrupted system call"},
        {-5, "pdFREERTOS_ERRNO_EIO", "I/O error"},
        {-6, "pdFREERTOS_ERRNO_ENXIO", "No such device or address"},
        {-9, "pdFREERTOS_ERRNO_EBADF", "Bad file number"},
        {-11, "pdFREERTOS_ERRNO_EAGAIN", "No more processes"},
        {-11, "pdFREERTOS_ERRNO_EWOULDBLOCK", "Operation would block"},
        {-12, "pdFREERTOS_ERRNO_ENOMEM", "Not enough memory"},
        {-13, "pdFREERTOS_ERRNO_EACCES", "Permission denied"},
        {-14, "pdFREERTOS_ERRNO_EFAULT", "Bad address"},
        {-16, "pdFREERTOS_ERRNO_EBUSY", "Mount device busy"},
        {-17, "pdFREERTOS_ERRNO_EEXIST", "File exists"},
        {-18, "pdFREERTOS_ERRNO_EXDEV", "Cross-device link"},
        {-19, "pdFREERTOS_ERRNO_ENODEV", "No such device"},
        {-20, "pdFREERTOS_ERRNO_ENOTDIR", "Not a directory"},
        {-21, "pdFREERTOS_ERRNO_EISDIR", "Is a directory"},
        {-22, "pdFREERTOS_ERRNO_EINVAL", "Invalid argument"},
        {-28, "pdFREERTOS_ERRNO_ENOSPC", "No space left on device"},
        {-29, "pdFREERTOS_ERRNO_ESPIPE", "Illegal seek"},
        {-30, "pdFREERTOS_ERRNO_EROFS", "Read only file system"},
        {-42, "pdFREERTOS_ERRNO_EUNATCH", "Protocol driver not attached"},
        {-50, "pdFREERTOS_ERRNO_EBADE", "Invalid exchange"},
        {-79, "pdFREERTOS_ERRNO_EFTYPE", "Inappropriate file type or format"},
        {-89, "pdFREERTOS_ERRNO_ENMFILE", "No more files"},
        {-90, "pdFREERTOS_ERRNO_ENOTEMPTY", "Directory not empty"},
        {-91, "pdFREERTOS_ERRNO_ENAMETOOLONG", "File or path name too long"},
        {-95, "pdFREERTOS_ERRNO_EOPNOTSUPP", "Operation not supported on transport endpoint"},
        {-105, "pdFREERTOS_ERRNO_ENOBUFS", "No buffer space available"},
        {-109, "pdFREERTOS_ERRNO_ENOPROTOOPT", "Protocol not available"},
        {-112, "pdFREERTOS_ERRNO_EADDRINUSE", "Address already in use"},
        {-116, "pdFREERTOS_ERRNO_ETIMEDOUT", "Connection timed out"},
        {-119, "pdFREERTOS_ERRNO_EINPROGRESS", "Connection already in progress"},
        {-120, "pdFREERTOS_ERRNO_EALREADY", "Socket already connected"},
        {-125, "pdFREERTOS_ERRNO_EADDRNOTAVAIL", "Address not available"},
        {-127, "pdFREERTOS_ERRNO_EISCONN", "Socket is already connected"},
        {-128, "pdFREERTOS_ERRNO_ENOTCONN", "Socket is not connected"},
        {-135, "pdFREERTOS_ERRNO_ENOMEDIUM", "No medium inserted"},
        {-138, "pdFREERTOS_ERRNO_EILSEQ", "An invalid UTF-16 sequence was encountered."},
        {-140, "pdFREERTOS_ERRNO_ECANCELED", "Operation canceled."}};
#endif


uint8_t ucMACAddress[6] = {configMAC_ADDR0, configMAC_ADDR1, configMAC_ADDR2,
                           configMAC_ADDR3, configMAC_ADDR4, configMAC_ADDR5};

/* declare static variables */
//os_sem_t sem_ipaddr_cfg_complete = NULL;
os_sem_t sem_ipaddr_cfg_complete;
static uint8_t eth_link_newup=0;
/* static function prototypes */
void eth_tcpip_init_done(void *p);

/* functions */

/******************************************************************************
 * function name : eth_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return eth_ret_t description
 * modification date : 2017.05.29
 *****************************************************************************/
eth_ret_t eth_init(void)
{
	eth_link_newup = 1;
    //gpio_drv_write(gpio_id_GETH_nRESET, 0);
    //os_sleep(1);
    //gpio_drv_write(gpio_id_GETH_nRESET, 1);
    //krs_log("eth gpio reset assert complete\n\r");
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP

#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
    eth_link_newup = 0;
#endif

    // Broadcast IP:
    return retOK;
}


/******************************************************************************
 * function name : eth_osinit
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return eth_ret_t description
 * modification date : 2019.08.27
 *****************************************************************************/
eth_ret_t eth_osinit(void)
{
    os_sem_init(sem_ipaddr_cfg_complete);

#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
    eth_freertostcp_init();
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
    eth_lwip_init();
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
    eth_linux_init();
#endif
    os_sem_give(sem_ipaddr_cfg_complete);
    return retOK;
}




/******************************************************************************
 * function name : eth_is_setup_complete
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return uint32_t description
 * modification date : 2017.05.29
 *****************************************************************************/
uint32_t eth_is_setup_complete(void)
{
    //BaseType_t ret = pdFALSE;
    int ret = os_False;
    struct timespec temp_timespec;  \
    temp_timespec.tv_sec = 0;   \
    temp_timespec.tv_nsec = 100000000;  \
    ret = os_sem_take(sem_ipaddr_cfg_complete, temp_timespec);
    //if(ret == pdTRUE)
    if(ret == os_retOK)
    {
        os_sem_give(sem_ipaddr_cfg_complete);
        return (retOK);
    }
    return (retFail);
}


/******************************************************************************
 * function name : eth_tcpip_init_done
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *p description
 * \return void description
 * modification date : 2017.05.29
 *****************************************************************************/
void eth_tcpip_init_done(void *p) { (void)p; }




/******************************************************************************
 * function name : eth_print_ip_settings
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 ip description
 * \param1 mask description
 * \param2 gw description
 * \return void description
 * modification date : 2017.05.29
 *****************************************************************************/
void eth_print_ip_settings(uint32_t ip, uint32_t mask, uint32_t gw)
{

    eth_print_ip("Board IP: ", ip, 0);
    eth_print_ip("Netmask : ", mask, 0);
    eth_print_ip("Gateway : ", gw, 0);
}


/******************************************************************************
 * function name : eth_print_ip
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *msg description
 * \param1 ip description
 * \param2 port description
 * \return void description
 * modification date : 2017.05.29
 *****************************************************************************/
void eth_print_ip(char *msg, uint32_t ip, uint16_t port)
{
    struct in_addr addr;
	char buff[16];
    //eth_inet_ntoa(ip, buff, sizeof(buff));

    addr.s_addr = htonl(ip);
    memcpy(buff, eth_inet_ntoa(addr), sizeof(buff));

    if(port != 0)
    {
    	krs_log("%s %s:%d\n\r",msg, buff,port);
    }
    else
    {
    	krs_log("%s %s\n\r",msg, buff);
    }
}


/******************************************************************************
 * function name : eth_errcheck_timeout
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 errcode description
 * \return int32_t description
 * modification date : 2019.08.27
 *****************************************************************************/
int32_t eth_errcheck_timeout(int32_t errcode)
{
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
    if((errcode == ERR_TIMEOUT) || (errcode == ERR_OK))
    {
        return retOK;
    }
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
    if((errno == EWOULDBLOCK) || (errno == 0))
    {
        return retOK;
    }    
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
    if((errcode == pdFREERTOS_ERRNO_ETIMEDOUT) || (errcode == pdFREERTOS_ERRNO_NONE))
    {
        return retOK;
    }
#endif
    return retFail;
}

/******************************************************************************
 * function name : eth_print_errmsg
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 errcode description
 * \return void description
 * modification date : 2019.08.27
 *****************************************************************************/
void eth_print_errmsg(int32_t errcode)
{
    int32_t i;
    int32_t tablesize;
    int32_t errornumber=0;

#if (SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP) || (SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX)
    errornumber = errno;
#else
    errornumber = errcode;
#endif

    if(errornumber > 0)
    	errornumber = -errornumber;

    tablesize = sizeof(eth_error_text_table) / sizeof(eth_error_text_t);

    for(i = 0; i < tablesize; i++)
    {
        if(errornumber == eth_error_text_table[i].err)
        {
            krs_log("Eth Err : %s %s\n\r", eth_error_text_table[i].errdef, eth_error_text_table[i].message);
            break;
        }
    }
}

const char *eth_strerr(err_t errcode)
{
    int32_t i;
    int32_t tablesize;
    if(errcode > 0)
        errcode = -errcode;

    tablesize = sizeof(eth_error_text_table) / sizeof(eth_error_text_t);

    for(i = 0; i < tablesize; i++)
    {
        if(errcode == eth_error_text_table[i].err)
        {
        	return eth_error_text_table[i].errdef;
        }
    }
    return NULL;
}


/******************************************************************************
 * function name : eth_get_ipaddr_ntoa
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 ip description
 * \param1 *dest description
 * \return void description
 * modification date : 2019.08.27
 *****************************************************************************/
void eth_get_ipaddr_ntoa(uint32_t ip, char *dest, uint32_t buflen)
{
	//eth_inet_ntoa(ip, dest, buflen);
    struct in_addr addr;
    
    addr.s_addr = ip;//htonl(ip);
    memcpy(dest, eth_inet_ntoa(addr), buflen);
}


/******************************************************************************
 * function name : eth_get_ipaddr_fromstring
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *cp description
 * \return uint32_t description
 * modification date : 2019.08.27
 *****************************************************************************/
uint32_t eth_get_ipaddr_fromstring(const char *cp)
{
    uint32_t val;

    if(eth_get_ipaddr_aton(cp, &val))
    {
        return eth_htonl(val);
    }
    return (ETH_IPADDR_NONE);
}



/******************************************************************************
 * function name : eth_get_macaddr_fromstring
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *cp description
 * \return uint32_t description
 * modification date : 2019.08.27
 *****************************************************************************/
int32_t eth_get_macaddr_fromstring(uint8_t *mac_addr, const char *macstr)
{
	unsigned int addrbuff[6]={0};
	int32_t i;

	if (sscanf(macstr, "%x:%x:%x:%x:%x:%x",
	           &addrbuff[0],
	           &addrbuff[1],
	           &addrbuff[2],
	           &addrbuff[3],
	           &addrbuff[4],
	           &addrbuff[5]) < 6)
	{
		krs_log("could not parse mac %s\n\r", macstr);
		return retFail;
	}
	for(i=0;i<6;i++)
	{
		mac_addr[i] = (uint8_t)addrbuff[i];
	}
	return retOK;
}

/******************************************************************************
 * function name : eth_get_macaddr_fromhw
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *cp description
 * \return uint32_t description
 * modification date : 2021.02.04
 *****************************************************************************/
int32_t eth_get_macaddr_fromhw(uint8_t *mac)
{
	int sock;
    struct ifreq ifr;
	char mac_adr[18] = {0,};	

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) 
	{
		//dp(4, "socket");
		return 0;
	}

	strcpy(ifr.ifr_name, "eth0");

	if (ioctl(sock, SIOCGIFHWADDR, &ifr)< 0)    
	{
		//dp(4, "ioctl() - get mac");
		close(sock);
		return 0;
	}

    //strcpy(mac, mac_adr);
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);
	close(sock);

	return retOK;
}


/******************************************************************************
 * function name : eth_get_ipaddr_aton
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *cp description
 * \param1 *addr description
 * \return int32_t description
 * modification date : 2019.08.27
 *****************************************************************************/
int32_t eth_get_ipaddr_aton(const char *cp, uint32_t *addr)
{
    uint32_t val;
    uint8_t base;
    char c;
    uint32_t parts[4];
    uint32_t *pp = parts;

    c = *cp;
    for(;;)
    {
        /*
         * Collect number up to ``.''.
         * Values are specified as for C:
         * 0x=hex, 0=octal, 1-9=decimal.
         */
        if(!isdigit(c))
            return (0);
        val = 0;
        base = 10;
        if(c == '0')
        {
            c = *++cp;
            if(c == 'x' || c == 'X')
            {
                base = 16;
                c = *++cp;
            }
            else
                base = 8;
        }
        for(;;)
        {
            if(isdigit(c))
            {
                val = (val * base) + (int)(c - '0');
                c = *++cp;
            }
            else if(base == 16 && isxdigit(c))
            {
                val = (val << 4) | (int)(c + 10 - (islower(c) ? 'a' : 'A'));
                c = *++cp;
            }
            else
                break;
        }
        if(c == '.')
        {
            /*
             * Internet format:
             *  a.b.c.d
             *  a.b.c   (with c treated as 16 bits)
             *  a.b (with b treated as 24 bits)
             */
            if(pp >= parts + 3)
            {
                return (0);
            }
            *pp++ = val;
            c = *++cp;
        }
        else
            break;
    }
    /*
     * Check for trailing characters.
     */
    if(c != '\0' && !isspace(c))
    {
        return (0);
    }
    /*
     * Concoct the address according to
     * the number of parts specified.
     */
    switch(pp - parts + 1)
    {

        case 0:
            return (0); /* initial nondigit */

        case 1: /* a -- 32 bits */
            break;

        case 2: /* a.b -- 8.24 bits */
            if(val > 0xffffffUL)
            {
                return (0);
            }
            val |= parts[0] << 24;
            break;

        case 3: /* a.b.c -- 8.8.16 bits */
            if(val > 0xffff)
            {
                return (0);
            }
            val |= (parts[0] << 24) | (parts[1] << 16);
            break;

        case 4: /* a.b.c.d -- 8.8.8.8 bits */
            if(val > 0xff)
            {
                return (0);
            }
            val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
            break;
        default:
            krs_log("unhandled\n\r");
            krs_assert(0);
            break;
    }
    if(addr)
    {
        *addr = eth_htonl(val);
    }
    return (1);
}



int32_t eth_link_isvalid(void)
{
	if(eth_link_newup == 0 && network_up_flag == 1)
	{
		return retOK;
	}
	return retFail;
}

void eth_link_undefined_callback(void *param)
{
	krs_log("eth link undefined\n\r");
	//led_drv_setcolormask(LED_DRV_NETSTATE_ID, LedMaskBlue, 0);
	eth_link_newup = 1;
	network_up_flag = 0;
}



void eth_link_up_callback(void *param)
{
	uint32_t *link_speed;
	link_speed = (uint32_t *)param;

	if(eth_link_newup == 1)
	{
		eth_link_newup = 0;

		krs_log("eth link up %d\n\r",*link_speed);
		//led_drv_setcolormask(LED_DRV_NETSTATE_ID, LedMaskBlue, 1);
		network_up_flag = 1;

		/* Network Task notify     */
	/*	if(net_task_handle != NULL)
		{
			xTaskNotifyGive(net_task_handle);
		}*/

	}
}



void eth_link_down_callback(void *param)
{
	krs_log("eth link down\n\r");
	//led_drv_setcolormask(LED_DRV_NETSTATE_ID, LedMaskBlue, 0);
	eth_link_newup = 1;
	network_up_flag = 0;
}

void eth_link_negotiating_callback(void *param)
{
	static uint8_t ledtoggle=0;

	krs_log("eth link negotiating\n\r");
	ledtoggle ^= 1;
	//led_drv_setcolormask(LED_DRV_NETSTATE_ID, LedMaskBlue, ledtoggle);
	eth_link_newup = 1;
	network_up_flag = 0;
}
/* end of file */
