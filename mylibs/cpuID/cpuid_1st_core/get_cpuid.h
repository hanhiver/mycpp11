/** 
 * @brief 调用ASM获取当前运行CPU的唯一编号(LINUX only)
 * @param cpu_id 输出CPU唯一编号的字符串，原有字符串内容会被清空。
 *
 * @return 是否获取成功
 *    -<em>true</em> 获取CPUID成功。
 *    -<em>false</em> 获取CPUID失败。
 * @note 函数会在堆上分配空间返回结果，如果是长期运行的调用，请确保使用free对返回结果显示
 */
//int get_cpu_id_c(char* cpu_id);
#ifdef __cplusplus
extern "C"
{
#endif
char* get_cpu_id_c();
#ifdef __cplusplus
}
#endif