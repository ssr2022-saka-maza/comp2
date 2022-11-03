#pragma once

#include "ssr2/Motor.hpp"
#include "ssr2/MovingAverage.hpp"
#include "ssr2/Vector2D.hpp"
#include <Arduino.h>

namespace ssr2 {

/**
 * @brief 足回りを操作
 */
class LowerBody {
private:
    const Vector2D<float> _dir1, _dir2, _dir3;
    Motor _motor1, _motor2, _motor3;
    MovingAverage<float> _moving_average1, _moving_average2, _moving_average3;

public:
    LowerBody() = delete;
    LowerBody(const LowerBody &) = delete;
    LowerBody & operator=(const LowerBody &) = delete;
    LowerBody(LowerBody &&) = delete;
    LowerBody & operator=(LowerBody &&) = delete;
    ~LowerBody() = default;

    explicit LowerBody(
        uint8_t dir1, uint8_t pwm1, uint8_t dir2, uint8_t pwm2, uint8_t dir3, uint8_t pwm3,
        uint16_t movAveCapacity = 32);

    /**
     * @note
     * # 各軸の設定など
     * x軸: 重心から正面の方向
     * y軸: 重心からx軸の正方向を向いて垂直に左方向
     *
     * # モーター配置の詳細
     *           正面
     * +----------^----------+
     * |        --1--        |
     * |                     |
     * |          x          |
     * |         y*          |
     * |  \               /  |
     * |   2             3   |
     * |    \           /    |
     * +---------------------+
     * 配置は上のAsciiArtの通り。真ん中の*が中心、軸はxyって書いてあるやつが各軸の正方向。各タイヤは反時計回りを正転方向で
     *
     * # 各変数名の定義
     * v_x := 並行速度x成分
     * v_y := 並行速度y成分
     * v_theta := 中心からタイヤまでの距離 * 角速度
     */

    void begin(float v_x = 0, float v_y = 0, float v_theta = 0) noexcept;

private:
    void _setPowers_raw(float v1, float v2, float v3) noexcept;
    void _setPowers_normalized(float v1, float v2, float v3) noexcept;

public:
    void setPowers(float v1, float v2, float v3) noexcept;
    void reset() noexcept;
    void twist(float v_x, float v_y, float v_theta) noexcept;
    inline void parallel(float v_x, float v_y) noexcept;
    inline void rotate(float v_theta) noexcept;
};  // class LowerBody

}  // namespace ssr2
