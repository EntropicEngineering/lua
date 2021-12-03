
io = require('io')

dofile('util.lua')

toyOS = {
	TENS = function (x) return x end,
	ERM = function (x) return x end,
	LED = function (x) return x end,
	OUTPUT_TYPE_TENS = 1,
	OUTPUT_TYPE_ERM = 2,
	OUTPUT_TYPE_LED = 3,
}

metadata, waves = dofile('waves_functional_prototype.lua')

setup = {
	timestamp = 0,
	adjust_max = 0xffff,
	active_channels = {
		toyOS.OUTPUT_TYPE_TENS,
		toyOS.OUTPUT_TYPE_ERM,
		toyOS.OUTPUT_TYPE_LED
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
	print('\t TENS = ' .. table_to_string(v[toyOS.OUTPUT_TYPE_TENS]))
	print('\t ERM  = ' .. table_to_string(v[toyOS.OUTPUT_TYPE_ERM]))
	print('\t LED  = ' .. table_to_string(v[toyOS.OUTPUT_TYPE_LED]))

	file:write(table.concat({
		timestamp,
		v[1].width, v[1].frequency,
		v[2].power,
		v[3].r, v[3].g, v[3].b
	}, ",").."\n")

	timestamp = timestamp + 0.1
end

file:close()