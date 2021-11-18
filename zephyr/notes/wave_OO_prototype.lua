Program = {
    title = "Waves",
    description = "Pattern intensity ramps up and back down.",
    max_period = 40, min_period = 4,            -- The period of the 'intensity wave', in seconds
    min_TENS_freq = 60, max_TENS_freq = 360,    -- Frequency of TENS pulses, in Hz
    min_TENS_width = 50, max_TENS_width = 200,  -- Duration of each half of the TENS pulse, in microseconds
    min_motor = 0.1, max_motor = 1,             -- Motor power, as a percentile
    min_LED = {r = 0.1, g = 0.1, b =0.1},       -- LED values broken into red, green, and blue percentile components
    max_LED = {r = 1, g = 1, b = 1}             -- with each component representing the strength of that color
}

-- "Program:start(setup)" is shorthand for "Program.start(self, setup)"
function Program:start(setup)
    self.timestamp = setup.timestamp        -- Start time
    self.adjust_max = setup.adjust_max      -- Max value of adjust
    -- Set the initial period of the overall pattern to max, i.e. slowest rate of change.
    self.period = self.max_period
end

-- A helper function to vary the period linearly between min_period and max_period, with max_period at 0 adjust
function Program:update_period(adjust)
    self.period = self.min_period +
                  (self.max_period - self.min_period) *
                  ((self.adjust_max - adjust) / self.adjust_max)
end

-- Vary linearly between min and max and min, creating a triangle wave output
function Program:triangle_wave(delta_t, min, max)
    local completion = (delta_t % self.period) / self.period  -- completion % of the whole pattern
    if completion < 1/2 then    -- Ramping up
        completion = completion * 2             -- 50% overall completion is 100% of ramp up completion
    else                        -- Ramping down
        completion = (completion - 1/2) * 2     -- Ramping down starts at 50%, so subtract that before multiplying
        completion = 1 - completion             -- Pretend we're ramping up, but backwards
    end
    return (max - min) * completion + min
end

function Program:run(timestamp, adjust)
    -- "self:update_period(adjust)" is shorthand for "self.update_period(self, adjust)"
    self:update_period(adjust)

    local delta_t = timestamp - self.timestamp

    -- toyOS is a helper library documented elsewhere.
    return {
        toyOS.OUTPUT_TYPE_TENS = toyOS.TENS{
            frequency = self:triangle_wave(delta_t, self.min_TENS_freq, self.max_TENS_freq),
            width = self:triangle_wave(delta_t, self.min_TENS_width, self.max_TENS_width)
        },
        toyOS.OUTPUT_TYPE_ERM = toyOS.ERM{
            power = self:triangle_wave(delta_t, self.min_motor, self.max_motor)
        },
        toyOS.OUTPUT_TYPE_LED = toyOS.LED{
            r = self:triangle_wave(delta_t, self.min_LED.r, self.max_LED.r),
            g = self:triangle_wave(delta_t, self.min_LED.g, self.max_LED.g),
            b = self:triangle_wave(delta_t, self.min_LED.b, self.max_LED.b),
        }
    }
end

--[[
--  The table passed to toyOS must have, at minimum, the following four fields: "title", "description", "start", "run".
--   * The "title" field is a short string containing the title of the program, which is displayed in the UI.
--   * The "description" field is a string containing the description of what the program does. This field may
--     contain multiple lines and will also be displayed in the UI, usually behind an info button.
--   * The "start" field must be a function. "start" will be called exactly once when the user starts running this
--     program. "start" will be passed a table filled with initialization values.
--   * The "run" field must also be a function and will be called repeatedly in order to update the toy outputs.
--     "run" will be passed a timestamp and a the value of the 'Adjust' slider for its associated channel.
--]]
return toyOS(Program)
