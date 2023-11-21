##
#@file rrefPython.py
#@brief Structure and user functionality
#@details 
#@return
#
#
#
#
##
testMatrix1 = [[0, 0, 0, 1], 
              [0, 0, 2, 0],
              [0, 0, 0, 0]]

testMatrix2 = [[0, 0, 1, 1], 
               [0, 1, 2, 0],
               [0, 3, 2, 1]]

testMatrix3 = [[0, 0, 0, 0],
               [0, 0, 0, 0],
               [0, 0, 0, 0],
               [0, 0, 0, 0],]

testmatrix4 = [[ 0, 0, 0, 1, -1],
               [ 0, 1, 0, -2, 0],
               [ 1, 0, 0, -3, 2]]

testMatrix5 = [[-5, 1, 3],
               [-2, 2, -2],
               [ 5, -4, -4]]

"""
Iterates through the matrix. For each colum in a row it check if
value is different than 0 and if it's index it's less than the last
non-zero colum index. 

if it is, it means that the first non-zero colum is that one.

Whoever, if it's the first row and we haven't got any non-zero colum 
we don't need to check if it's index it's less than the last non-zero 
colum index but there isn't other non-zero colum.
""" 

def nonzero_col(matrix):
  firstNonZeroColumIndex = -1

  for rowIndex, rowValue in enumerate(matrix):
    for columIndex, columValue in enumerate(rowValue):
      if rowIndex == 0 and firstNonZeroColumIndex == -1:
        if columValue != 0:
          firstNonZeroColumIndex = columIndex
          continue

      if columValue != 0 and columIndex < firstNonZeroColumIndex:
        firstNonZeroColumIndex = columIndex

  return 0 if firstNonZeroColumIndex == -1 else firstNonZeroColumIndex

"""
Iterates through the matrix. We want to find which row has the pivo further left.
What we do is check if the colum index is equal to the first non-zero colum index
and if it's value it's different than 0.

If it is, that means that the row if the pivo further left is that row.
We than just swap that row with the first one.

We also have to check a case where we have two pivo in the same colum.
In that case, we only want to change the pivoted row index when the current
row is lower than the pivoted row index
""" 

def put_pivot(firstNonZeroColumIndex, matrix):
  pivotedRowIndex = -1
  
  for rowIndex, rowValue in enumerate(matrix):
    for columIndex, columValue in enumerate(rowValue):
      if (columIndex == firstNonZeroColumIndex and columValue != 0):
          if(rowIndex < pivotedRowIndex or pivotedRowIndex == -1):
            pivotedRowIndex = rowIndex

  matrix[pivotedRowIndex], matrix[0] = matrix[0], matrix[pivotedRowIndex]

  return matrix 

def elim_col(matrix):
  firstNonZeroColumIndex = nonzero_col(matrix)
  matrixWithPivoInFirstRow = put_pivot(firstNonZeroColumIndex, matrix)

  matrixWithNullColum = matrixWithPivoInFirstRow

  for rowIndex, rowValue in enumerate(matrixWithPivoInFirstRow): 
    if rowIndex == 0: continue

    if(matrixWithNullColum[rowIndex][firstNonZeroColumIndex] != 0):
      for columIndex, columValue in enumerate(rowValue):
          if columValue != 0: 
            if columIndex != firstNonZeroColumIndex:
              continue
            else:
              multiplierToGetNull = columValue / matrixWithNullColum[0][columIndex]

              for columIndex, columValue in enumerate(rowValue):
                matrixWithNullColum[rowIndex][columIndex] = columValue - (multiplierToGetNull * matrixWithNullColum[0][columIndex])
              
              break
  return matrixWithNullColum


testMatrix = testMatrix5
firstNonZeroColumIndex = nonzero_col(testMatrix)
matrixWithPivoInFirstRow  = put_pivot(firstNonZeroColumIndex, testMatrix)

print("Non-zero colum index: ", firstNonZeroColumIndex)
print("Pivo in first row: ", matrixWithPivoInFirstRow)
print("Pivoted colum with 0's: ", elim_col(testMatrix))


print("\n\n******** TEST CASES ********\n")

print("put_pivo Test Matrix 2: ", put_pivot(nonzero_col(testMatrix2), testMatrix2))
print("put_pivo Test Matrix 3: ", put_pivot(nonzero_col(testMatrix3), testMatrix3))
print("elim_colum Test Matrix 2: ", elim_col(testMatrix2))
print("elim_colum Test Matrix 3 (null matrix): ", elim_col(testMatrix3))

