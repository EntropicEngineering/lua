
io = require('io')

-- Adapted from https://gist.github.com/justnom/9816256
function table_to_string(tbl)
    local result = "{"
    for k, v in pairs(tbl) do
        -- Check the key type (ignore any numerical keys - assume its an array)
        if type(k) == "string" then
            result = result..k.."="
        else
        	result = result.."<"..k..">="
        end

        -- Check the value type
        if type(v) == "table" then
            result = result..table_to_string(v)
        elseif type(v) == "boolean" or type(v) == "number" then
            result = result..tostring(v)
        elseif type(v) == "table" then
            result = result.."\""..v.."\""
        else
            result = result.."<"..v..">"
        end
        result = result..","
    end
    return result.."}"
end

function TENS(x)
	return x
end

function ERM(x)
	return x
end

function LED(x)
	return x
end

dofile('waves_prototype.lua')

setup = {
	timestamp = 0,
	adjust_max = 0xffff,
	active_channels = {
		'OUTPUT_TYPE_TENS',
		'OUTPUT_TYPE_ERM',
		'OUTPUT_TYPE_LED'
	}
}

iterator = waves(setup)

file = io.open("output.csv", "w")

file:write("timestamp,tens.pulse,tens.frequency,erm.power,led.r,led.g,led.b\n")

adjust = 0xffff
timestamp = 0
while (timestamp < 20) do
	v = iterator(timestamp, adjust)

	print('ts=' .. timestamp)
	print('\t TENS = ' .. table_to_string(v[1]))
	print('\t ERM  = ' .. table_to_string(v[2]))
	print('\t LED  = ' .. table_to_string(v[3]))

	file:write(table.concat({
		timestamp,
		v[1].pulse, v[1].frequency,
		v[2].power,
		v[3].values.r, v[3].values.g, v[3].values.b
	}, ",").."\n")

	timestamp = timestamp + 0.1
end

file:close()