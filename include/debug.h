#ifndef __INCLUDE_DEBUG_H_
#define __INCLUDE_DEBUG_H_

// 打印错误位置信息
void panic_spin(char *filename, int line, const char *func, const char *condition);

// 采用编译器自带宏
#define PANIC(...) panic_spin(__FILE__, __LINE__, __func__, __VA_ARGS__)

#ifdef NODEBUG
// 如果定义了NODEBUG宏，将ASSERT设为空宏
#define ASSERT(CONDITION)
#else
// 否则，正常设置ASSERT宏
#define ASSERT(CONDITION) if(!(CONDITION))PANIC(#CONDITION)
#endif

#endif