# /user/bin/pyhton3
import _thread
import hashlib
import argparse
from multiprocessing import Pool

tab = ['a','b','c','d','e','f','g','h','i','j','k',
	   'l','m','n','o','p','q','r','s','t','u','v',
	   'w','x','y','z',
	   '0','1','2','3','4','5','6','7','8','9',
	   '!','@','#','$','%','&','*']

nbChar = 8
tabBrute = []
tabRes = []

def getString(input, rang, length):
    str = ""
    inst = input
    for i in range(1, length):
       tmp = int(inst / rang)
       str += tab[int(inst - (tmp * rang)) % rang]
       inst = tmp
    return str;

def checkPWD(passe, tabB):
    m = hashlib.md5()
    m.update(passe.encode('utf-8'))
    passTmp = m.hexdigest()
#    print()
    for i in range(0, len(tabB)):
        print (passTmp + " >>  " + tabB)
        if (passTmp == tabB[i]):
            tmp = tabB[i]
            del tabB[i]
            return tmp
    return None;

def BruteForce(iter, tabB):
#    print (range, tabBrute)
#    for iter in range:
    str = getString(iter, len(tab), nbChar)
#        print(str)
    hasht = checkPWD(str, tabB)
    if hasht is not None:
        tabRes.append(str + " >>  " + hasht)
        if (len(tabPass) == 0):
            for line in tabRes:
                print (line)
        print (str + " >>  " + hasht)
    print ("fin")

def start():
	parser = argparse.ArgumentParser(description='BruteForce ')
	parser.add_argument('--inputFile', default="./input", help='file with the hash')
	parser.add_argument('--dictFile', default="./dico", help='dictionnary file')
	parser.add_argument('--outputFile', default="./output", help='output file')
	args = parser.parse_args()

	print (args.inputFile)
	fileIn = open(args.inputFile, "r")
	fileOut = open(args.outputFile, "w")
	fileDict = open(args.dictFile, "r")

	strTabTmp = fileDict.readlines()

	dictSer = {}
	dictDeser = {}
	for line in strTabTmp:
		m = hashlib.md5()
		m.update(line[:-1].encode("utf-8"))
		tmp = m.hexdigest()
		dictSer[line[:-1]] = tmp
		dictDeser[tmp] = line[:-1]

	strTabTmp = fileIn.readlines()
	tabBrute = []
	for line in strTabTmp:
		line = str(line [:-1])
	#        if line in dictDeser.keys():
	#            print (line + " >>  " + dictDeser[line])
	#            tabRes.append(line + " >>  " + dictDeser[line])
	#        else:
		tabBrute.append(line)

	maxH = len(tab) ** nbChar
	pas = len(tab) ** 4
	q = list()
	for i in range(0, int(maxH/pas)):
		q.append((range(i*pas, (i+1)*pas), tabBrute))
	p = Pool(8).map(BruteForce, q)
	p.join()

start()
