import re
import string
import collections # For easy sorting

def ImportAndSort():
	global sortedList # Global so all functions can use this without having to re-read and process

	importFile = open("CS210_Project_Three_Input_File.txt")
	groceryFile = importFile.read()
	importFile.close()

	groceryList = groceryFile.split("\n")
	# Sorts and counts items in groceryList by most to least
	sortedList = collections.Counter(groceryList).most_common()
	

def ItemsAndQuantities():
	for x in sortedList:
		print("(" + str(x[1]) + ") " + x[0])

def JustItems():
	for x in sortedList:
		print(x[0], end = " ") # Prints on one line with a space between items
	print() # Ensures output is displayed
	
def SpecificItemQty(specificItem):
	for x in sortedList:
		if specificItem.upper() == x[0].upper(): # Converted to upper for case insensitivity
			return x[1]
	# If not found, prints message and returns 0, which is an accurate quantity
	print('"' + specificItem + '"' + " was not purchased today.")
	return 0

def HistogramFile():
	# Saves in solution main directory
	outputFile = open("frequency.dat", "w")
	# Writes as "[item name] [item quantity]"
	for x in sortedList:
		outputFile.write(x[0] + " " + str(x[1]) + "\n")
	outputFile.close()