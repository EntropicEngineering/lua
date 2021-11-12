function waves (setup)
    setup += {
        max_period = 40, min_period = 4,           -- seconds
        min_TENS_freq = 60, max_TENS_freq = 360,   -- Hz
        min_TENS_pulse = 50, max_TENS_pulse = 200, -- microseconds
        min_motor = 0.1, max_motor = 1,            -- percentile
        min_LED = {r = 0.1, g = 0.1, b =0.1},
        max_LED = {r = 1, g = 1, b = 1}
    }

    local period = setup.max_period

    -- Vary period linearly between min_period and max_period, with max_period at 0 adjust
    local function update_period(adjust)
        period = setup.min_period +
                 (setup.max_period - setup.min_period) *
                 ((setup.ARG_MAX - adjust) / setup.ARG_MAX)
        return period
    end

    -- Return whether pattern is ramping up or down and percentage of completion of that phase
    local RAMP = {UP=1, DOWN=2}
    local function progress(delta_t)
        local completion = (delta_t % period) / period
        local ramp
        if completion < 1/2 then
            ramp = RAMP.UP
            completion = completion * 2  -- 50% overall completion is 100% of ramp up completion
        else
            ramp = RAMP.DOWN
            completion = (completion - 1/2) * 2
        end
        return ramp, completion
    end

    -- Vary linearly between min and max and min
    local function linear_ramp_up_ramp_down(dt, min, max)
        local ramp, progress = progress(dt)
        -- If we're ramping down, pretend we're ramping up but backwards
        if ramp == RAMP.DOWN then progress = 1 - progress
        return (max - min) * progress + min
    end

    local function update_TENS_freq(delta_t)
        return linear_ramp_up_ramp_down(delta_t, setup.min_TENS_freq, setup.max_TENS_freq)
    end

    local function udpate_TENS_pulse(delta_t)
        return linear_ramp_up_ramp_down(delta_t, setup.min_TENS_pulse, setup.max_TENS_pulse)
    end

    local function udpate_motor_power(delta_t)
        return linear_ramp_up_ramp_down(delta_t, setup.min_motor, setup.max_motor)
    end

    local function update_LED(delta_t)
        local r = linear_ramp_up_ramp_down(delta_t, setup.min_LED.r, setup.max_LED.r)
        local g = linear_ramp_up_ramp_down(delta_t, setup.max_LED.g, setup.max_LED.g)
        local b = linear_ramp_up_ramp_down(delta_t, setup.max_LED.b, setup.max_LED.b)
        return {r = r, g = g, b = b}
    end

    return function (timestamp, adjust)
        update_period(adjust)

        dt = timestamp - setup.timestamp

        outputs_table = {
            OUTPUT_TYPE_TENS = TENS{frequency = update_TENS_freq(dt), pulse = update_TENS_pulse(dt)},
            OUTPUT_TYPE_ERM = ERM{power = update_motor_power(dt)},
            OUTPUT_TYPE_LED = LED(update_LED(dt))
        }

        channel_settings = {}

        for idx, type in pairs(get_active_channels(setup)) do
            channel_settings[idx] = outputs_table[type]
        end

        return channel_settings
    end
end
