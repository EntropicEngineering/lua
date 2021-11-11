function waves (setup)
    setup += {
        base_period: 40,                         -- seconds
        min_TENS_freq: 60, max_TENS_freq: 360,   -- Hz
        min_TENS_pulse: 50, max_TENS_pulse: 200, -- microseconds
        min_motor: 0.1, max_motor: 1,            -- percentile
        min_LED: {r: 0.1, g: 0.1, b:0.1},
        max_LED: {r: 1, g: 1, b: 1}
    }

    period = setup.base_period;

    function update_period(adjust) <...> period = new_period end

    function update_TENS_freq(delta_t) <...> return freq end

    function udpate_TENS_pulse(delta_t) <...> return width end

    function udpate_motor_power(delta_t) <...> return power end

    function update_LED(delta_t) <...> return {r: r, g: g, b: b} end

    function pseudo_iterator(timestamp, my_arg1, my_arg2, ... )
        update_period(my_arg1)

        dt = timestamp - state.timestamp

        outputs_table = {
            OUTPUT_TYPE_TENS = TENS{frequency: update_TENS_freq(dt), pulse: update_TENS_pulse(dt)},
            OUTPUT_TYPE_ERM = ERM{power: update_motor_power(dt)},
            OUTPUT_TYPE_LED = LED(update_LED(dt))
        }

        return outputs_table
    end

    return pseudo_iterator
end
