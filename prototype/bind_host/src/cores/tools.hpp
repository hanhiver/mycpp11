#ifdef WIN32
#include <io.h>
#include <direct.h> 
#else // LINUX or others
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#endif

#include <stdint.h>
#include <string>
#include <sstream>

#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

/** 
 * @brief 按照给定路径创建整个目录结构
 * @param dir_path 指定目录全路径
 *
 * @return 无
 *    -<em>0</em> 创建目录成功
 *    -<em>not 0</em> 创建目录失败，返回值为失败error code.
 * 
 * @note 从左到右依次判断文件夹是否存在，不存在就创建
 *       example： /tmp/a/b/c
 *       注意：最后一个如果是文件夹的话,需要加上 '\' 或者 '/'。比如上述例子中的c不会被创建
 */
int32_t createDirs(const std::string& dir_path);

#ifndef WIN32
/** 
 * @brief 调用ASM获取当前运行CPU的唯一编号(LINUX only)
 * @param cpu_id 输出CPU唯一编号的字符串，原有字符串内容会被清空。
 *
 * @return 是否获取成功
 *    -<em>true</em> 获取CPUID成功。
 *    -<em>false</em> 获取CPUID失败。
 */
bool get_cpu_id(std::string& cpu_id);
#endif
