#ifndef FEED_SERVICE_H
#define FEED_SERVICE_H

#include <Arduino.h>
#include "config.h"
#include "sensor.h"

// ================== 投喂状态机定义 ==================

/**
 * @brief 投喂主状态机
 * 
 * feed_feed：加料中（使用螺旋输料舵机）
 * feed_dump：倾倒中（翻斗倾倒，有子流程）
 * feed_done：一次循环完成
 */
typedef enum {
    feed_feed,  // 加料中
    feed_dump,  // 倾倒中（有子流程）
    feed_done   // 一次循环完成
} feed_state_t;

/**
 * @brief 倾倒子状态机
 * 
 * dump_start：准备倾倒（等待稳定时间）
 * dump_shake：倾倒抖动（使料粒均匀落下）
 * dump_hold：保持倾倒（等待料粒完全落下）
 */
typedef enum {
    dump_start,
    dump_shake,
    dump_hold
} dump_phase_t;

// ================== 全局状态变量声明 ==================

extern feed_state_t feed_state;
extern dump_phase_t dump_phase;
extern unsigned long action_start_time;
extern float expected_weight;
// ================== 函数声明 ==================

/**
 * @brief 投喂控制主函数（在 loop() 中调用）
 * 
 * 实现完整的投喂流程：
 * 1. 加料：输料舵机转动直到达到目标重量
 * 2. 倾倒：翻斗倾倒、抖动、复位
 * 3. 完成：清零称重，回到初始状态
 */
void feed_control();

/**
 * @brief 倾倒控制（包含抖动、保持、复位）
 * 
 * @return true 倾倒完成，false 倾倒进行中
 */
bool dump_control();

/**
 * @brief 处理加料状态
 * @param weight 当前重量（g）
 */
void handle_feed(float weight);

/**
 * @brief 处理倾倒状态
 */
void handle_dump();

/**
 * @brief 处理完成状态（清零称重、准备下一循环）
 */
void handle_done();

/**
 * @brief 打印投喂系统日志（每秒输出一次）
 * @param weight 当前重量（g）
 */
void print_log(float weight);

#endif // FEED_SERVICE_H