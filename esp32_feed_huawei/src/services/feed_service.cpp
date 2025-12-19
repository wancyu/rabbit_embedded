#include "feed_service.h"
#include "sensors.h"
#include "config.h"

// 全局状态变量定义
feed_state_t feed_state = feed_done;
dump_phase_t dump_phase = dump_start;
float expected_weight = 0;
unsigned long action_start_time = 0;

// 日志输出

void print_log(float weight)
{
    static unsigned long last_log = 0;
    if (millis() - last_log < 1000) return;

    Serial.printf("状态=%d | 重量=%.2fg | 目标=%.2fg\n",feed_state, weight, expected_weight);

    last_log = millis();
}

// 倾倒动作控制

bool dump_control()
{
    unsigned long elapsed = millis() - action_start_time;

    switch (dump_phase)
    {
    case dump_start:
        if (elapsed > SETTLE_TIME)
        {
            servo180_write(DUMP_ANGLE);
            action_start_time = millis();
            dump_phase = dump_shake;
        }
        break;

    case dump_shake:
        if (elapsed > DUMP_SHAKE_TIME)
        {
            servo180_write(SHAKE_ANGLE);
            servo180_write(DUMP_ANGLE);
            servo180_write(SHAKE_ANGLE);
            servo180_write(DUMP_ANGLE2);
            action_start_time = millis();
            dump_phase = dump_hold;
        }
        break;

    case dump_hold:
        if (elapsed > DUMP_HOLD_TIME)
        {
            servo180_write(RETURN_ANGLE);
            dump_phase = dump_start;
            action_start_time = millis();
            return true;
        }
        break;
    }
    return false;
}

// ================== 状态处理函数 ==================

void handle_feed(float weight)
{
    if (weight < expected_weight)
    {
        servo360_write(FEED_SPEED);
    }
    else
    {
        servo360_write(STOP_ANGLE);
        feed_state = feed_dump;
        action_start_time = millis();
    }
}

void handle_dump()
{
    if (dump_control())
    {
        feed_state = feed_done;
    }
}

void handle_done()
{
    expected_weight = 0;
}

// ================== 主控逻辑接口 ==================

void feed_control()
{
    float weight = get_weight();

    switch (feed_state)
    {
    case feed_feed:
        handle_feed(weight);
        break;

    case feed_dump:
        handle_dump();
        break;

    case feed_done:
        handle_done();
        break;
    }

    print_log(weight);
}