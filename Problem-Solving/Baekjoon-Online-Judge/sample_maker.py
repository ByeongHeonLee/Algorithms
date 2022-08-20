
INPUT_SIZE = 30000
QUERY_SIZE = 30000
STEP = 1

with open("input", 'w') as file:
    file.write(str(INPUT_SIZE) + '\n')
    for i in range(1, INPUT_SIZE+1):
        file.write(str(i))
        file.write(' ')
    file.write('\n')

    file.write(str(QUERY_SIZE) + '\n')
    query_cnt = 0
    for i in range(1, INPUT_SIZE+1, STEP):
        file.write(str(i) + '\n')
        query_cnt += 1
        if query_cnt >= QUERY_SIZE:
            break