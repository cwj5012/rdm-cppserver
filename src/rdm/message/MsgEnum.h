/**
 * 消息枚举
 */

#pragma once

enum class MsgEnum {

    REGISTER_REQUEST = 0,       // 注册
    REGISTER_RETURN = 1,
    LOGIN_REQUEST = 2,          // 登录
    LOGIN_RETURN = 3,
    LOGIN_HALL_REQUEST = 4,
    LOGIN_HALL_RETURN = 5,
    PLAYER_TOKEN_NOTIFY = 6,    // S -> S

    MATCH_PVE_REQUEST = 11,     // PVE 匹配
    MATCH_PVE_RETURN = 12,
    MATCH_PVP_REQUEST = 13,     // PVP 匹配
    MATCH_PVP_RETURN = 14,

    HALL_INFO = 21,             // 大厅信息

    GAME_START = 31,            // 游戏开始
    GAME_END = 32,              // 游戏结束
    GAME_ACTION_REQUEST = 33,   // 操作
    GAME_ACTION_RETURN = 34,
    GAME_PAUSE_REQUEST = 35,    // 暂停
    GAME_PAUSE_RETURN = 36

};

