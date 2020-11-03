f = open('states-data', 'r')
for line in f:
    tdata = line.split('|')
    count = tdata[0]
    states = tdata[1].split(',')
    for s in states:
        print(count, s.strip())

