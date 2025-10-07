# # Ex. 1
# for x in range(10, 34, 2):
#     print(x , end="");

# print()
# # Ex. 2
# y :int = -1 

# while(y < 0 or y > 100):
#     y = int(input("Enter a number:"))

#     unidades = y % 10
#     dezenas = (y / 10) % 10
#     print("O número tem" + str(unidades) + "unidades e " + str(dezenas) + " dezenas")

# # Ex. 3
# def read():
#     return input("Enter a string:")

# def save(text_file, string):  
#     with open(text_file, "a") as f:
#         f.write(string)

# def countVowels(string):
#     num_vowels: int = 0

#     for x in string:
#         if x in ['a', 'e', 'i', 'o', 'u']:
#             num_vowels += 1
    
#     return num_vowels

# string1 = read()
# string2 = read()

# save("f1.txt", 
#      string1 if countVowels(string1) > countVowels(string2) 
#      else string2
# )

# ########## Ex. 4

# def read_list():
#     input = 0
#     arr = []
#     while (True):
#         print("Input number to list: ")
#         input: int = int(read())

#         if(input < 0): break

#         arr.append(input)
    
#     return arr 

# def compare_list(arr1, arr2):
#     for x in arr1:
#         if x in arr2:
#             print(x, end=" ")

# def intersect_list(arr1, arr2):
#     intersect_arr = []

#     for x in arr1:
#         if x in arr2 and x not in intersect_arr:
#             intersect_arr.append(x)

#     return intersect_arr

# arr1 = read_list()
# arr2 = read_list()

# print("Two list compare: ", end="")
# compare_list(arr1, arr2)

# print("Intersection of two list: ", end="")
# print(*intersect_list(arr1, arr2), sep=", ")

##########? Ex. Matrix
# import numpy as np

# rows = 2 
# cols = 2
# def create_matrix():
#     matrix = np.zeros((rows, cols), dtype=int)

#     for i in range(rows):
#         for j in range(cols):
#             x: int = int(input(f"Insert number at ({i+1, j+1}): "))
#             matrix[i, j] = x 
    
#     return matrix 

# mat_A = create_matrix()
# print(f"First matrix: {mat_A}")

# mat_B = create_matrix()
# print(f"Second matrix: {mat_B}")

# def log_matrix(matrix):
#     # Better way
#     # new_matrix = np.where(matrix > 0, np.log(matrix), np.abs(matrix))
  
#     new_matrix = np.zeros((rows, cols), dtype=float)

#     for i in range(rows):
#         for j in range(cols):
#             cur_element = matrix[i,j]
            
#             new_matrix[i, j] = np.log(cur_element) if cur_element > 0 else np.abs(cur_element)

#     return new_matrix

# def higher_lower_product(mat_A, mat_B):
#     higher = mat_A[1, 0]
#     lower = mat_B[0, 0]

#     for j in range(1, cols):
#         cur_el = mat_A[1, j] 
#         if(cur_el > higher): higher = cur_el

#     for i in range(1, rows):
#         cur_el = mat_B[i, 0]
#         if(cur_el < lower): lower = cur_el

#     return higher * lower        

# print(f"Element product: {mat_A * mat_B}")
# print(f"Dot product: {np.dot(mat_A, mat_B)}")
# print(f"Matrix diference: {mat_A - mat_B}")
# print(f"First matrix log: {log_matrix(mat_A)}")
# print(f"Highest * Lowest of specific row and col: {higher_lower_product(mat_A, mat_B)}")

##########? Ex. Dictionaries
grades = {}

while(True):
    print(""" 
          1 - Insert new pair
          2 - Edit existing pair
          3 - Show dictionary
          4 - Average grade
          0 - Exit
    """)
    opt = int(input("Insert a option: "))
    
    if(opt == 0): break
    if(opt == 1):
        uc = input("Insert UC: ")
        grade = input("Insert grade: ")

        grades.update({uc: grade})
    if(opt == 2):
        uc = input("Which UC you want to edit: ")
        grade = input("What's the new value for that UC: ")

        grades.update({uc:grade})
    if(opt == 3):
        print(grades)
    if(opt == 4):
        sum = 0
        for value in grades.values():
            sum += int(value)

        print(f"The average is {sum / len(grades.values)}")
