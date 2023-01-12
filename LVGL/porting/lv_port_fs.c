/**
 * @file lv_port_fs_templ.c
 *
 */

/*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 0

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "lvgl.h"
#include "ff.h"
#include "diskio.h"
#include "usart.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef FIL file_t;
typedef DIR dir_t;
FATFS *flash_fs;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size(lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
//static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

//static void * fs_dir_open(lv_fs_drv_t * drv, const char * path);
//static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn);
//static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();
	  

    /*---------------------------------------------------
     * Register the file system interface in LVGL
     *--------------------------------------------------*/

    /*Add a simple drive to open images*/
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);
		
    /*Set up fields...*/
    fs_drv.letter = 'A';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
//    fs_drv.tell_cb = fs_tell;

//    fs_drv.dir_close_cb = fs_dir_close;
//    fs_drv.dir_open_cb = fs_dir_open;
//    fs_drv.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /*E.g. for FatFS initialize the SD card and FatFS itself*/
		flash_fs = (FATFS*)lv_mem_alloc(sizeof(FATFS));//为文件系统的对象分配内存
		if(!f_mount(flash_fs,"0:", 1))//挂载外部flash，flash驱动号为0
		{
			printf("FLASH mount success!\r\n");
			
		}
		else printf("FLASH mount failed!\r\n");
    /*You code here*/
		 
}

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
		
    void * f = NULL;

    if(mode == LV_FS_MODE_WR) {//只写权限
        /*Open a file for write*/
				f = (void*) f_open((FIL*)drv,path,FA_CREATE_ALWAYS | FA_WRITE);
    }
    else if(mode == LV_FS_MODE_RD) {//只读权限
        /*Open a file for read*/
				f = (void*) f_open((FIL*)drv, path, FA_READ);
        
    }
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {//可读写
        /*Open a file for read and write*/
				f = (void*) f_open((FIL*)drv, path, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
        
    }
		
//		fatfs_path = (TCHAR*)lv_mem_alloc(sizeof(TCHAR)*strlen(path)+4);//分配内存
//		if(drv->letter == '0')
//		{
//			snprintf(fatfs_path, sizeof(TCHAR)*strlen(path)+4,"0:/%s",path);//FATFS打开文件的路径
//		}
//		else
//		{
//			lv_mem_free(fatfs_path);//释放内存
//			return (unsigned char*)LV_FS_RES_NOT_EX;//未找到驱动器
//			printf("Driver No Found,please try again.\r\n");
//		}
//		if(!f_open((FIL*)file_p,fatfs_path,fatfs_mode)
//		{
//			
//		}

    return f;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    if(!f_close((FIL*)file_p))
		{
				return LV_FS_RES_OK;
				printf("File Closed.\r\n");
		}
		else
		{
			return LV_FS_RES_NOT_IMP;
			printf("File Closed failure.\r\n");
		}
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
		f_read((FIL*)file_p, buf, (uint32_t)btr, (uint32_t*)br);

    /*Add your code here*/

    return res;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btw       Bytes To Write
 * @param bw        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
		f_write((FIL*)file_p, buf, (uint32_t)btw, (uint32_t*)bw);
    /*Add your code here*/

    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
		f_lseek((FIL*)file_p, (FSIZE_t)pos);
    /*Add your code here*/

    return res;
}
/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
//static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

//    /*Add your code here*/

//    return res;
//}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
//static void * fs_dir_open(lv_fs_drv_t * drv, const char * path)
//{
//    void * dir = NULL;
//    /*Add your code here*/
//    dir = ...           /*Add your code here*/
//          return dir;
//}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
//static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

//    /*Add your code here*/

//    return res;
//}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
//static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

//    /*Add your code here*/

//    return res;
//}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
