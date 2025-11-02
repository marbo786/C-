import sys
REG = "2024307"

def get_limits(reg_num_str):
                                    # m is last digit + 1
    m = int(reg_num_str[-1]) + 1
    
                                    # n is (sum of digits % 3) + 1
    total = 0
    for digit in reg_num_str:
        total += int(digit)
    n = (total % 3) + 1
    
                                    # k is (second to last digit % 4) + 2
    temp_digit = 0
    if len(reg_num_str) > 1:
        temp_digit = int(reg_num_str[-2])
    
    k = (temp_digit % 4) + 2
    
    return m, n, k

def check_line(text, m, n, k):
                                    #  weird characters first
    for char in text:
        if char != '#' and char != '_' and char != '!':
            return "REJECT"
            
                                    # we check for too many ! in a row
    bang_count = 0
    for char in text:
        if char == '!':
            bang_count += 1
        else:
            bang_count = 0 
        
        if bang_count > k:
            return "REJECT"

    blocks = []
    i = 0
    while i < len(text):
        if text[i] == '#':
            j = i
            while j < len(text) and text[j] == '#':
                j += 1
            blocks.append((i, j))               # save start and end
            i = j
        else:
            i += 1
    
    if len(blocks) > m:
        return "REJECT"

                                                # if 0 or 1 blocks, its fine if other checks passed
    if len(blocks) <= 1:
        return "ACCEPT"

                                                # check the space between blocks
    for i in range(len(blocks) - 1):
        start = blocks[i][1]
        end = blocks[i+1][0]
        
        gap = text[start:end]
        
        us_count = 0
        gap_ok = False
        for char in gap:
            if char == '_':
                us_count += 1
            elif char == '!':
                us_count=0 
            
            if us_count >= n:
                gap_ok = True
                break
        
        if not gap_ok:
            return "REJECT"
            
    return "ACCEPT"

def main():
    m, n, k = get_limits(REG)

    for line in sys.stdin:
        input_line = line.strip()
        if input_line:
            res = check_line(input_line, m, n, k)
            print(res)

if __name__ == "__main__":
    main()