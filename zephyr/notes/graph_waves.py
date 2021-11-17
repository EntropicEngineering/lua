import matplotlib.pyplot as plt
import csv
import sys

# Can pass a comma-seperated list of fields to graph, e.g. python3 graph_waves.py led.r,led.g,led.b

if len(sys.argv)==2:
	toshow = sys.argv[1].split(',')
else:
	toshow = ['erm.power']

with open('output.csv', 'r') as fd:
	r = csv.reader(fd)
	header, *rows = list(r)

timestamps = [x[header.index("timestamp")] for x in rows]
seriesdata = {}
for item in header:
	if item != "timestamp":
		seriesdata[item] = [float(x[header.index(item)]) for x in rows]

# print(seriesdata['erm.power'])

fig, ax = plt.subplots()
for series, values in seriesdata.items():
	if series in toshow:
		ax.plot(timestamps, values, label=series)
ax.legend()

ax.set(xlabel='Time (s)', ylabel='Values')
ax.grid()

plt.show()