# Cooper Dean
# Problem of the Week - Palindromes
# 10/31/23

# input statement that takes a word input
word = input("Input your word here: ")

# set index & letterCount to 0
index = 0
letterCount = 0

# turn the word into list letterList for indexing
letterList = list(word)
# letterCount = the length of the letter list (tacocat = 7)
letterCount = len(letterList)
    
# sets the starting letter count to 1
palindromeCount = 1  
     
for letters in range(letterCount):
    # if x letter is not equal print not palindrome
    if(letterList[letters] != letterList[letterCount - (letters + 1)]):
        print("Your word is not a palindrome!")
        break
    # if the list is out of range print your word is a palindrome
    elif(letters + 1 == letterCount):
        print("Your word is a palindrome.")
    # if x letter is equal (doesn't fit either loop) increase palindromeCount by 1

    