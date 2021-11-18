--[[
--  When a user selects a script to start playing, the script is called from a fresh Lua environment.
--  The top-level function that is called when a script is first run must return another function.
--  The returned function is remembered by the firmware and called periodically to update the toy outputs.
--
--  In this example, the 'waves' function is called when the user selects the script to play.
--  'waves' will return the function 'periodic' after setting up some local variables and helper functions
--  which can be referenced by the 'periodic' function. As its name suggest, 'periodic' is the function
--  that gets called periodically by the firmware.
--
--  Every time the 'periodic' function is called, it is passed two arguments: a timestamp of the current time,
--  and the current value of the 'Adjust' slider for the channel(s) it's playing on. The 'periodic' function then
--  must return configuration settings appropriate for the types of channels it's playing on.
--]]
local function waves (setup)
    local CONST = {
        max_period = 40, min_period = 4,            -- The period of the 'intensity wave', in seconds
        min_TENS_freq = 60, max_TENS_freq = 360,    -- Frequency of TENS pulses, in Hz
        min_TENS_width = 50, max_TENS_width = 200,  -- Duration of each half of the TENS pulse, in microseconds
        min_motor = 0.1, max_motor = 1,             -- Motor power, as a percentile
        min_LED = {r = 0.1, g = 0.1, b =0.1},       -- LED values broken into red, green, and blue percentile components
        max_LED = {r = 1, g = 1, b = 1}             -- with each component representing the strength of that color
    }

    -- Set the initial period of the overall pattern to max, i.e. slowest change.
    local period = CONST.max_period

    -- A helper function to vary the period linearly between min_period and max_period, with max_period at 0 adjust
    local function update_period(adjust)
        period = CONST.min_period +
                 (CONST.max_period - CONST.min_period) *
                 ((setup.adjust_max - adjust) / setup.adjust_max)
        return period
    end

    -- Helper function that determines whether pattern is ramping up or down
    -- and the percentage of completion of the current phase of the overall pattern
    local RAMP = {UP=1, DOWN=2}
    local function progress(delta_t)
        local completion = (delta_t % period) / period  -- completion % of the whole pattern
        local ramp
        if completion < 1/2 then
            ramp = RAMP.UP
            completion = completion * 2  -- 50% overall completion is 100% of ramp up completion
        else
            ramp = RAMP.DOWN
            completion = (completion - 1/2) * 2     -- Ramping down starts at 50%, so subtract that before multiplying
        end
        return ramp, completion
    end

    -- Vary linearly between min and max and min, creating a triangle wave output
    local function linear_ramp_up_ramp_down(dt, min, max)
        local ramp, progress = progress(dt)
        -- If we're ramping down, pretend we're ramping up but backwards
        if ramp == RAMP.DOWN then progress = 1 - progress end
        return (max - min) * progress + min
    end

    local function update_TENS_freq(delta_t)
        return linear_ramp_up_ramp_down(delta_t, CONST.min_TENS_freq, CONST.max_TENS_freq)
    end

    local function update_TENS_width(delta_t)
        return linear_ramp_up_ramp_down(delta_t, CONST.min_TENS_width, CONST.max_TENS_width)
    end

    local function update_motor_power(delta_t)
        return linear_ramp_up_ramp_down(delta_t, CONST.min_motor, CONST.max_motor)
    end

    local function update_LED(delta_t)
        local r = linear_ramp_up_ramp_down(delta_t, CONST.min_LED.r, CONST.max_LED.r)
        local g = linear_ramp_up_ramp_down(delta_t, CONST.min_LED.g, CONST.max_LED.g)
        local b = linear_ramp_up_ramp_down(delta_t, CONST.min_LED.b, CONST.max_LED.b)
        return {r = r, g = g, b = b}
    end

    -- This function is called periodically by the firmware
    -- 'timestamp' is the current time, 'adjust' is the value of the 'Adjust' slider
    local function periodic(timestamp, adjust)
        update_period(adjust)

        -- Calculate how long it's been since the pattern first started (stored in setup.timestamp)
        local dt = timestamp - setup.timestamp

        -- A lookup table to match the correct output values to the type of output for a given channel
        local outputs_table = {
            toyOS.OUTPUT_TYPE_TENS = toyOS.TENS{frequency = update_TENS_freq(dt), width = update_TENS_width(dt)},
            toyOS.OUTPUT_TYPE_ERM = toyOS.ERM{power = update_motor_power(dt)},
            toyOS.OUTPUT_TYPE_LED = toyOS.LED(update_LED(dt))
        }

        -- We only want to return settings for channels that we have control over.
        local channel_settings = {}

        -- Iterate through the channels we control and set their outputs according to the output type.
        for index, type in pairs(setup.active_channels) do
            channel_settings[index] = outputs_table[type]
        end

        -- Return settings for the channels we control.
        return channel_settings
    end

    return periodic
end

local metadata{
    title = "Waves",
    description = "Pattern intensity ramps up and back down."
}

return metadata, waves
