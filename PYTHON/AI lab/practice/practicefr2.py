nums = [1,2,3]
# nums.append(4)

# nums.insert(0,10)

#nums.sort(reverse=True)

# slicing ([start:stop:step])

# list[::-1] is the classic idiom for reversing a list.


users = [ (1, 'Alice', 'admin'), (2, 'Bob', 'user'), (3, 'Charlie', 'guest') ]
for user_id, name, role in users: # Tuple unpacking
    if role == 'admin':
        print(f"ADMIN: {name} (ID: {user_id})")